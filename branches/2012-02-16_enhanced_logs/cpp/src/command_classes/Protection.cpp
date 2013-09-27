//-----------------------------------------------------------------------------
//
//	Protection.cpp
//
//	Implementation of the Z-Wave COMMAND_CLASS_PROTECTION
//
//	Copyright (c) 2010 Mal Lansell <openzwave@lansell.org>
//
//	SOFTWARE NOTICE AND LICENSE
//
//	This file is part of OpenZWave.
//
//	OpenZWave is free software: you can redistribute it and/or modify
//	it under the terms of the GNU Lesser General Public License as published
//	by the Free Software Foundation, either version 3 of the License,
//	or (at your option) any later version.
//
//	OpenZWave is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU Lesser General Public License for more details.
//
//	You should have received a copy of the GNU Lesser General Public License
//	along with OpenZWave.  If not, see <http://www.gnu.org/licenses/>.
//
//-----------------------------------------------------------------------------

#include <vector>

#include "CommandClasses.h"
#include "Protection.h"
#include "Defs.h"
#include "Msg.h"
#include "Node.h"
#include "Driver.h"
#include "Log.h"

#include "ValueList.h"

using namespace OpenZWave;

enum ProtectionCmd
{
	ProtectionCmd_Set		= 0x01,
	ProtectionCmd_Get		= 0x02,
	ProtectionCmd_Report	= 0x03
};

static char const* c_protectionStateNames[] = 
{
	"Unprotected",
	"Protection by Sequence",
	"No Operation Possible"
};

//-----------------------------------------------------------------------------
// <Protection::RequestState>												   
// Request current state from the device									   
//-----------------------------------------------------------------------------
bool Protection::RequestState
(
	uint32 const _requestFlags,
	uint8 const _instance,
	Driver::MsgQueue const _queue
)
{
	if( _requestFlags & RequestFlag_Session )
	{
		return RequestValue( _requestFlags, 0, _instance, _queue );
	}

	return false;
}

//-----------------------------------------------------------------------------
// <Protection::RequestValue>												   
// Request current value from the device									   
//-----------------------------------------------------------------------------
bool Protection::RequestValue
(
	uint32 const _requestFlags,
	uint8 const _dummy1,	// = 0 (not used)
	uint8 const _instance,
	Driver::MsgQueue const _queue
)
{
	Msg* msg = new Msg( "ProtectionCmd_Get", GetNodeId(), REQUEST, FUNC_ID_ZW_SEND_DATA, true, true, FUNC_ID_APPLICATION_COMMAND_HANDLER, GetCommandClassId() );
	msg->SetInstance( this, _instance );
	msg->Append( GetNodeId() );
	msg->Append( 2 );
	msg->Append( GetCommandClassId() );
	msg->Append( ProtectionCmd_Get );
	msg->Append( TRANSMIT_OPTION_ACK | TRANSMIT_OPTION_AUTO_ROUTE );
	GetDriver()->SendMsg( msg, _queue );
	return true;
}

//-----------------------------------------------------------------------------
// <Protection::HandleMsg>
// Handle a message from the Z-Wave network
//-----------------------------------------------------------------------------
bool Protection::HandleMsg
(
	uint8 const* _data,
	uint32 const _length,
	uint32 const _instance	// = 1
)
{
	if (ProtectionCmd_Report == (ProtectionCmd)_data[0])
	{
		Log::Write( LogLevel_Info, "Received a Protection report from node %d: %s", GetNodeId(), c_protectionStateNames[_data[1]] );
		if( ValueList* value = static_cast<ValueList*>( GetValue( _instance, 0 ) ) )
		{
			value->OnValueChanged( (int)_data[1] );
			value->Release();
		}

		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
// <Protection::SetValue>
// Set the device's protection state
//-----------------------------------------------------------------------------
bool Protection::SetValue
(
	Value const& _value
)
{
	if( ValueID::ValueType_List == _value.GetID().GetType() )
	{
		ValueList const* value = static_cast<ValueList const*>(&_value);
		ValueList::Item const& item = value->GetItem();

		Log::Write( LogLevel_Info, "Protection::Set - Setting protection state on node %d to '%s'", GetNodeId(), item.m_label.c_str() );
		Msg* msg = new Msg( "Protection Set", GetNodeId(), REQUEST, FUNC_ID_ZW_SEND_DATA, true );		
		msg->SetInstance( this, _value.GetID().GetInstance() );
		msg->Append( GetNodeId() );
		msg->Append( 3 );
		msg->Append( GetCommandClassId() );
		msg->Append( ProtectionCmd_Set );
		msg->Append( (uint8)item.m_value );
		msg->Append( TRANSMIT_OPTION_ACK | TRANSMIT_OPTION_AUTO_ROUTE );
		GetDriver()->SendMsg( msg, Driver::MsgQueue_Send );
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
// <Protection::CreateVars>
// Create the values managed by this command class
//-----------------------------------------------------------------------------
void Protection::CreateVars
(
	uint8 const _instance
)
{
	if( Node* node = GetNodeUnsafe() )
	{
		vector<ValueList::Item> items;

		ValueList::Item item;
		for( uint8 i=0; i<3; ++i )
		{
			item.m_label = c_protectionStateNames[i];
			item.m_value = i;
			items.push_back( item ); 
		}

		node->CreateValueList(  ValueID::ValueGenre_System, GetCommandClassId(), _instance, 0, "Protection", "", false, false, items, 0 );
	}
}