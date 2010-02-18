//-----------------------------------------------------------------------------
//
//	Defs.h
//
//	Basic types and preprocessor directives
//
//	Copyright (c) 2010 Mal Lansell <openzwave@lansell.org>
//
//	SOFTWARE NOTICE AND LICENSE
//
//	This file is part of OpenZWave.
//
//	OpenZWave is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published
//	by the Free Software Foundation, either version 3 of the License,
//	or (at your option) any later version.
//
//	OpenZWave is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with OpenZWave.  If not, see <http://www.gnu.org/licenses/>.
//
//-----------------------------------------------------------------------------

#ifndef _Defs_H
#define _Defs_H					   

#include <assert.h>

#ifdef NULL
#undef NULL
#endif
#define NULL 0

// Basic types
typedef signed char			int8;
typedef unsigned char		uint8;

typedef signed short		int16;
typedef unsigned short		uint16;

typedef signed int			int32;
typedef unsigned int		uint32;

#ifdef _MSC_VER
typedef signed __int64		int64;
typedef unsigned __int64	uint64;
#endif

#ifdef __GNUC__
typedef signed long long	int64;
typedef unsigned long long  uint64;
#endif

typedef float				float32;
typedef double				float64;


// Declare the OpenZWave namespace
namespace std {}
namespace OpenZWave
{
	// Include the STL namespace
	using namespace std;
}

// Modifications for Microsoft compilers
#ifdef _MSC_VER

// Fix for namespace-related compiler bug
namespace OpenZWave
{
}

// Rename safe versions of sprintf etc
#define snprintf sprintf_s

#endif


#define SOF										0x01
#define ACK										0x06
#define NAK										0x15
#define CAN										0x18

#define NUM_NODE_BITFIELD_BYTES					29		// 29 bytes = 232 bits, one for each possible node in the network.

#define REQUEST									0x00
#define RESPONSE								0x01

#define ZW_GET_VERSION							0x15
#define ZW_MEMORY_GET_ID						0x20	// response: 4byte home id, node id
#define ZW_CLOCK_SET							0x30

#define TRANSMIT_OPTION_ACK		 				0x01
#define TRANSMIT_OPTION_LOW_POWER   			0x02
#define TRANSMIT_OPTION_AUTO_ROUTE  			0x04
#define TRANSMIT_OPTION_FORCE_ROUTE 			0x08

#define TRANSMIT_COMPLETE_OK	  				0x00
#define TRANSMIT_COMPLETE_NO_ACK  				0x01
#define TRANSMIT_COMPLETE_FAIL					0x02
#define TRANSMIT_COMPLETE_NOROUTE 				0x04

#define RECEIVE_STATUS_TYPE_BROAD	 			0x04

#define FUNC_ID_SERIAL_API_GET_INIT_DATA		0x02
#define FUNC_ID_SERIAL_API_GET_CAPABILITIES		0x07
#define FUNC_ID_SERIAL_API_SOFT_RESET			0x08

#define FUNC_ID_APPLICATION_COMMAND_HANDLER		0x04

#define FUNC_ID_ZW_GET_VERSION					0x10
#define FUNC_ID_ZW_SEND_DATA					0x13
#define FUNC_ID_ZW_READ_MEMORY					0x23
#define FUNC_ID_ZW_GET_NODE_PROTOCOL_INFO		0x41
#define FUNC_ID_ZW_SET_DEFAULT					0x42
#define FUNC_ID_ZW_REPLICATION_COMMAND_COMPLETE 0x44
#define FUNC_ID_ZW_ASSIGN_RETURN_ROUTE			0x46
#define FUNC_ID_ZW_REQUEST_NODE_NEIGHBOR_UPDATE 0x48
#define FUNC_ID_ZW_APPLICATION_UPDATE			0x49
#define FUNC_ID_ZW_ADD_NODE_TO_NETWORK			0x4a
#define FUNC_ID_ZW_REMOVE_NODE_FROM_NETWORK		0x4b
#define FUNC_ID_ZW_SET_LEARN_MODE				0x50
#define FUNC_ID_ZW_ENABLE_SUC					0x52
#define FUNC_ID_ZW_SET_SUC_NODE_ID				0x54
#define FUNC_ID_ZW_GET_SUC_NODE_ID				0x56
#define FUNC_ID_ZW_REQUEST_NODE_INFO			0x60
#define FUNC_ID_ZW_REMOVE_FAILED_NODE_ID		0x61


//enum ZWFunctions
//{
//	CmdNone=0x00,
//    CmdSerialApiGetInitData=0x02,
//    CmdSerialApiApplNodeInformation=0x03,
//    CmdApplicationCommandHandler=0x04,
//    CmdZWaveGetControllerCapabilities=0x05,
//    CmdSerialApiSetTimeouts=0x06,
//    CmdSerialApiGetCapabilities=0x07,
//    CmdSerialApiSoftReset=0x08,
//    CmdZWaveSetRFReceiveMode=0x10,
//    CmdZWaveSetSleepMode=0x11,
//    CmdZWaveSendNodeInformation=0x12,
//    CmdZWaveSendData=0x13,
//    CmdZWaveSendDataMulti=0x14,
//    CmdZWaveGetVersion=0x15,
//    CmdZWaveSendDataAbort=0x16,
//    CmdZWaveRFPowerLevelSet=0x17,
//    CmdZWaveSendDataMeta=0x18,
//    CmdMemoryGetId=0x20,
//    CmdMemoryGetByte=0x21,
//    CmdMemoryPutByte=0x22,
//    CmdMemoryGetBuffer=0x23,
//    CmdMemoryPutBuffer=0x24,
//    CmdClockSet=0x30,
//    CmdClockGet=0x31,
//    CmdClockCompare=0x32,
//    CmdRtcTimerCreate=0x33,
//    CmdRtcTimerRead=0x34,
//    CmdRtcTimerDelete=0x35,
//    CmdRtcTimerCall=0x36,
//    CmdZWaveGetNodeProtocolInfo=0x41,
//    CmdZWaveSetDefault=0x42,
//    CmdZWaveReplicationCommandComplete=0x44,
//    CmdZWaveReplicationSendData=0x45,
//    CmdZWaveAssignReturnRoute=0x46,
//    CmdZWaveDeleteReturnRoute=0x47,
//    CmdZWaveRequestNodeNeighborUpdate=0x48,
//    CmdApplicationControllerUpdate=0x49,
//    CmdZWaveAddNodeToNetwork=0x4a,
//    CmdZWaveRemoveNodeFromNetwork=0x4b,
//    CmdZWaveCreateNewPrimary=0x4c,
//    CmdZWaveControllerChange=0x4d,
//    CmdZWaveSetLearnMode=0x50,
//    CmdZWaveAssignSucReturnRoute=0x51,
//    CmdZWaveEnableSuc=0x52,
//    CmdZWaveRequestNetworkUpdate=0x53,
//    CmdZWaveSetSucNodeId=0x54,
//    CmdZWaveDeleteSucReturnRoute=0x55,
//    CmdZWaveGetSucNodeId=0x56,
//    CmdZWaveSendSucId=0x57,
//    CmdZWaveRediscoveryNeeded=0x59,
//    CmdZWaveRequestNodeInfo=0x60,
//    CmdZWaveRemoveFailedNodeId=0x61,
//    CmdZWaveIsFailedNode=0x62,
//    CmdZWaveReplaceFailedNode=0x63,
//    CmdTimerStart=0x70,
//    CmdTimerRestart=0x71,
//    CmdTimerCancel=0x72,
//    CmdTimerCall=0x73,
//    CmdGetRoutingTableLine=0x80,
//    CmdGetTXCounter=0x81,
//    CmdResetTXCounter=0x82,
//    CmdStoreNodeInfo=0x83,
//    CmdStoreHomeId=0x84,
//    CmdLockRouteResponse=0x90,
//    CmdZWaveSendDataRouteDemo=0x91,
//    CmdSerialApiTest=0x95,
//    CmdSerialApiSlaveNodeInfo=0xa0,
//    CmdApplicationSlaveCommandHandler=0xa1,
//    CmdZWaveSendSlaveNodeInfo=0xa2,
//    CmdZWaveSendSlaveData=0xa3,
//    CmdZWaveSetSlaveLearnMode=0xa4,
//    CmdZWaveGetVirtualNodes=0xa5,
//    CmdZWaveIsVirtualNode=0xa6,
//    CmdZWaveSetPromiscuousMode=0xd0


#define ADD_NODE_ANY							0x01
#define ADD_NODE_ANY							0x01
#define ADD_NODE_CONTROLLER						0x02
#define ADD_NODE_SLAVE							0x03
#define ADD_NODE_EXISTING						0x04
#define ADD_NODE_STOP							0x05
#define ADD_NODE_STOP_FAILED					0x06

#define ADD_NODE_STATUS_LEARN_READY		  		0x01
#define ADD_NODE_STATUS_NODE_FOUND		   		0x02
#define ADD_NODE_STATUS_ADDING_SLAVE		 	0x03
#define ADD_NODE_STATUS_ADDING_CONTROLLER		0x04
#define ADD_NODE_STATUS_PROTOCOL_DONE			0x05
#define ADD_NODE_STATUS_DONE				 	0x06
#define ADD_NODE_STATUS_FAILED			   		0x07
#define ADD_NODE_OPTION_HIGH_POWER				0x80

#define REMOVE_NODE_ANY							0x01
#define REMOVE_NODE_STOP						0x05
#define REMOVE_NODE_STATUS_LEARN_READY			0x01
#define REMOVE_NODE_STATUS_NODE_FOUND			0x02
#define REMOVE_NODE_STATUS_ADDING_SLAVE			0x03
#define REMOVE_NODE_STATUS_ADDING_CONTROLLER	0x04
#define REMOVE_NODE_STATUS_PROTOCOL_DONE		0x05
#define REMOVE_NODE_STATUS_DONE					0x06
#define REMOVE_NODE_STATUS_FAILED				0x07

#define ZW_SUC_FUNC_BASIC_SUC					0x00
#define ZW_SUC_FUNC_NODEID_SERVER				0x01

#define UPDATE_STATE_DELETE_DONE				0x20
#define UPDATE_STATE_NEW_ID_ASSIGNED			0x40
#define UPDATE_STATE_NODE_INFO_REQ_FAILED		0x81
#define UPDATE_STATE_NODE_INFO_RECEIVED			0x84

#endif // _Defs_H