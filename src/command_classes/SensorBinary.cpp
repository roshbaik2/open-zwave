//-----------------------------------------------------------------------------
//
//	SensorBinary.cpp
//
//	Implementation of the Z-Wave COMMAND_CLASS_SENSOR_BINARY
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

#include "CommandClasses.h"
#include "SensorBinary.h"
#include "Defs.h"
#include "Msg.h"
#include "Node.h"
#include "Driver.h"
#include "Log.h"

#include "ValueBool.h"

using namespace OpenZWave;

enum SensorBinaryCmd
{
	SensorBinaryCmd_Get		= 0x02,
	SensorBinaryCmd_Report	= 0x03
};


//-----------------------------------------------------------------------------
// <SensorBinary::RequestState>												   
// Request current state from the device									   
//-----------------------------------------------------------------------------
void SensorBinary::RequestState
(
	uint8 const _instance
)
{
	Msg* msg = new Msg( "SensorBinaryCmd_Get", GetNodeId(), REQUEST, FUNC_ID_ZW_SEND_DATA, true );
	msg->Append( GetNodeId() );
	msg->Append( 2 );
	msg->Append( GetCommandClassId() );
	msg->Append( SensorBinaryCmd_Get );
	msg->Append( TRANSMIT_OPTION_ACK | TRANSMIT_OPTION_AUTO_ROUTE );
	GetDriver()->SendMsg( msg );
}

//-----------------------------------------------------------------------------
// <SensorBinary::HandleMsg>
// Handle a message from the Z-Wave network
//-----------------------------------------------------------------------------
bool SensorBinary::HandleMsg
(
	uint8 const* _data,
	uint32 const _length,
	uint32 const _instance	// = 1
)
{
	if( Node* node = GetNode() )
	{
		if (SensorBinaryCmd_Report == (SensorBinaryCmd)_data[0])
		{
			if( ValueBool* value = node->GetValueBool(  ValueID::ValueGenre_User, GetCommandClassId(), _instance, 0 ) )
			{
				value->OnValueChanged( _data[1] != 0 );
			}

			Log::Write( "Received SensorBinary report from node %d: State=%s", GetNodeId(), _data[1] ? "On" : "Off" );
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------
// <SensorBinary::CreateVars>
// Create the values managed by this command class
//-----------------------------------------------------------------------------
void SensorBinary::CreateVars
(
	uint8 const _instance
)
{
	if( Node* node = GetNode() )
	{
		node->CreateValueBool(  ValueID::ValueGenre_User, GetCommandClassId(), _instance, 0, "Sensor", "", true, false );
	}
}






