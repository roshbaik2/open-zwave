//-----------------------------------------------------------------------------
//
//	SensorAlarm.cpp
//
//	Implementation of the Z-Wave COMMAND_CLASS_SENSOR_ALARM
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
#include "SensorAlarm.h"
#include "Defs.h"
#include "Msg.h"
#include "Node.h"
#include "Driver.h"
#include "Log.h"

#include "ValueByte.h"

using namespace OpenZWave;

enum SensorAlarmCmd
{
	SensorAlarmCmd_Get				= 0x01,
	SensorAlarmCmd_Report			= 0x02,
	SensorAlarmCmd_SupportedGet		= 0x03,
	SensorAlarmCmd_SupportedReport	= 0x04
};

static char const* c_alarmTypeName[] = 
{
	"General",
	"Smoke",
	"Carbon Monoxide",
	"Carbon Dioxide",
	"Heat",
	"Flood"
};


//-----------------------------------------------------------------------------
// <SensorAlarm::SensorAlarm>
// Constructor
//-----------------------------------------------------------------------------
SensorAlarm::SensorAlarm
(
	uint32 const _homeId,
	uint8 const _nodeId
):
	CommandClass( _homeId, _nodeId )
{
	SetStaticRequest( StaticRequest_Values ); 
}

//-----------------------------------------------------------------------------
// <SensorAlarm::RequestState>
// Get the static thermostat setpoint details from the device
//-----------------------------------------------------------------------------
bool SensorAlarm::RequestState
(
	uint32 const _requestFlags
)
{
	bool requests = false;
	if( ( _requestFlags & RequestFlag_Static ) && HasStaticRequest( StaticRequest_Values ) )
	{
		RequestValue( 0xff );
		requests = true;
	}

	if( _requestFlags & RequestFlag_Dynamic )
	{
		for( uint8 i=0; i<SensorAlarm_Count; ++i )
		{
			if( NULL != GetValue( 1, i ) )
			{
				// There is a value for this alarm type, so request it
				RequestValue( i );
			}
		}
		requests = true;
	}

	return requests;
}

//-----------------------------------------------------------------------------
// <SensorAlarm::RequestValue>
// Get the sensor alarm details from the device
//-----------------------------------------------------------------------------
void SensorAlarm::RequestValue
(
	uint8 const _index		// = 0
)
{
	if( _index == 0xff )
	{
		// Request the supported setpoints
		Msg* msg = new Msg( "Request Supported Alarm Types", GetNodeId(), REQUEST, FUNC_ID_ZW_SEND_DATA, true, true, FUNC_ID_APPLICATION_COMMAND_HANDLER, GetCommandClassId() );
		msg->Append( GetNodeId() );
		msg->Append( 2 );
		msg->Append( GetCommandClassId() );
		msg->Append( SensorAlarmCmd_SupportedGet );
		msg->Append( TRANSMIT_OPTION_ACK | TRANSMIT_OPTION_AUTO_ROUTE );
		GetDriver()->SendMsg( msg );
		return;
	}
	else
	{
		// Request the setpoint value
		Msg* msg = new Msg( "Request alarm state", GetNodeId(), REQUEST, FUNC_ID_ZW_SEND_DATA, true, true, FUNC_ID_APPLICATION_COMMAND_HANDLER, GetCommandClassId() );
		msg->Append( GetNodeId() );
		msg->Append( 3 );
		msg->Append( GetCommandClassId() );
		msg->Append( SensorAlarmCmd_Get );
		msg->Append( _index );
		msg->Append( TRANSMIT_OPTION_ACK | TRANSMIT_OPTION_AUTO_ROUTE );
		GetDriver()->SendMsg( msg );
	}
}

//-----------------------------------------------------------------------------
// <SensorAlarm::HandleMsg>
// Handle a message from the Z-Wave network
//-----------------------------------------------------------------------------
bool SensorAlarm::HandleMsg
(
	uint8 const* _data,
	uint32 const _length,
	uint32 const _instance	// = 1
)
{
	if( SensorAlarmCmd_Report == (SensorAlarmCmd)_data[0] )
	{
		// We have received an alarm state report from the Z-Wave device
		if( ValueByte* value = static_cast<ValueByte*>( GetValue( _instance, _data[2] ) ) )
		{
			uint8 sourceNodeId = _data[1];
			uint8 state = _data[3];
			// uint16 time = (((uint16)_data[4])<<8) | (uint16)_data[5];  Don't know what to do with this yet.

			value->OnValueChanged( state );
			Log::Write( "Received alarm state report from node %d: %s = %d", sourceNodeId, value->GetLabel().c_str(), state );		
		}

		return true;
	}
			
	if( SensorAlarmCmd_SupportedReport == (SensorAlarmCmd)_data[0] )
	{
		if( Node* node = GetNodeUnsafe() )
		{
			// We have received the supported alarm types from the Z-Wave device
			Log::Write( "Received supported alarm types from node %d", GetNodeId() );		

			// Parse the data for the supported alarm types
			uint8 numBytes = _data[1];
			for( uint32 i=0; i<numBytes; ++i )
			{
				for( int32 bit=0; bit<8; ++bit )
				{
					if( ( _data[i+2] & (1<<bit) ) != 0 )
					{
						// Add supported setpoint
						int32 index = (int32)(i<<3) + bit;
						if( index < SensorAlarm_Count )
						{
							node->CreateValueByte( ValueID::ValueGenre_User, GetCommandClassId(), _instance, index, c_alarmTypeName[index], "", true, 0 );
							Log::Write( "    Added alarm type: %s", c_alarmTypeName[index] );
						}
					}
				}
			}
		}

		ClearStaticRequest( StaticRequest_Values );
		return true;
	}

	return false;
}

