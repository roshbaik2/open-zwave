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

#ifndef _Defs_H
#define _Defs_H					   

#include <assert.h>
#include <list>

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
#define strcasecmp _stricmp

#endif

// Modifications for MiNGW32 compiler
#ifdef MINGW

// Replace "safe" versions of sprintf
#define sprintf_s snprintf

#endif

#define SOF											0x01
#define ACK											0x06
#define NAK											0x15
#define CAN											0x18

#define NUM_NODE_BITFIELD_BYTES						29		// 29 bytes = 232 bits, one for each possible node in the network.

#define REQUEST										0x00
#define RESPONSE									0x01

#define ZW_CLOCK_SET								0x30

#define TRANSMIT_OPTION_ACK		 					0x01
#define TRANSMIT_OPTION_LOW_POWER   				0x02
#define TRANSMIT_OPTION_AUTO_ROUTE  				0x04
#define TRANSMIT_OPTION_FORCE_ROUTE 				0x08

#define TRANSMIT_COMPLETE_OK	  					0x00
#define TRANSMIT_COMPLETE_NO_ACK  					0x01
#define TRANSMIT_COMPLETE_FAIL						0x02
#define TRANSMIT_COMPLETE_NOROUTE 					0x04

#define RECEIVE_STATUS_TYPE_BROAD	 				0x04

#define FUNC_ID_SERIAL_API_GET_INIT_DATA		0x02
#define FUNC_ID_APPLICATION_COMMAND_HANDLER		0x04
#define FUNC_ID_ZW_GET_CONTROLLER_CAPABILITIES		0x05
#define FUNC_ID_SERIAL_API_SET_TIMEOUTS 		0x06
#define FUNC_ID_SERIAL_API_GET_CAPABILITIES		0x07
#define FUNC_ID_SERIAL_API_SOFT_RESET			0x08

#define FUNC_ID_ZW_SEND_DATA				0x13
#define FUNC_ID_ZW_GET_VERSION				0x15
#define FUNC_ID_ZW_R_F_POWER_LEVEL_SET			0x17
#define FUNC_ID_ZW_MEMORY_GET_ID			0x20
#define FUNC_ID_MEMORY_GET_BYTE				0x21
#define FUNC_ID_ZW_READ_MEMORY				0x23

#define FUNC_ID_ZW_SET_LEARN_NODE_STATE			0x40	// Not implemented
#define FUNC_ID_ZW_GET_NODE_PROTOCOL_INFO		0x41	// Get protocol info (baud rate, listening, etc.) for a given node
#define FUNC_ID_ZW_SET_DEFAULT				0x42	// Reset controller and node info to default (original) values
#define FUNC_ID_ZW_NEW_CONTROLLER			0x43	// Not implemented
#define FUNC_ID_ZW_REPLICATION_COMMAND_COMPLETE		0x44	// Replication isn't implemented (yet)
#define FUNC_ID_ZW_REPLICATION_SEND_DATA		0x45	// Replication isn't implemented (yet)
#define FUNC_ID_ZW_ASSIGN_RETURN_ROUTE			0x46	// Assign a return route from the specified node to the controller
#define FUNC_ID_ZW_DELETE_RETURN_ROUTE			0x47	// Delete all return routes from the specified node
#define FUNC_ID_ZW_REQUEST_NODE_NEIGHBOR_UPDATE		0x48	// Ask the specified node to update its neighbors (then read them from the controller)
#define FUNC_ID_ZW_APPLICATION_UPDATE			0x49	// Get a list of supported (and controller) command classes
#define FUNC_ID_ZW_ADD_NODE_TO_NETWORK			0x4a	// Control the addnode (or addcontroller) process...start, stop, etc.
#define FUNC_ID_ZW_REMOVE_NODE_FROM_NETWORK		0x4b	// Control the removenode (or removecontroller) process...start, stop, etc.
#define FUNC_ID_ZW_CREATE_NEW_PRIMARY			0x4c	// Control the createnewprimary process...start, stop, etc.
#define FUNC_ID_ZW_CONTROLLER_CHANGE			0x4d	// Control the transferprimary process...start, stop, etc.
#define FUNC_ID_ZW_SET_LEARN_MODE			0x50	// Put a controller into learn mode for replication/ receipt of configuration info
#define FUNC_ID_ZW_ENABLE_SUC				0x52	// Make a controller a Static Update Controller
#define FUNC_ID_ZW_REQUEST_NETWORK_UPDATE		0x53	// Network update for a SUC(?)
#define FUNC_ID_ZW_SET_SUC_NODE_ID			0x54	// Identify a Static Update Controller node id
#define FUNC_ID_ZW_GET_SUC_NODE_ID			0x56	// Try to retrieve a Static Update Controller node id (zero if no SUC present)
#define FUNC_ID_ZW_REQUEST_NODE_INFO			0x60	// Get info (supported command classes) for the specified node
#define FUNC_ID_ZW_REMOVE_FAILED_NODE_ID		0x61	// Mark a specified node id as failed
#define FUNC_ID_ZW_IS_FAILED_NODE_ID			0x62	// Check to see if a specified node has failed
#define FUNC_ID_ZW_REPLACE_FAILED_NODE			0x63	// Remove a failed node from the controller's list (?)
#define FUNC_ID_ZW_GET_ROUTING_INFO			0x80	// Get a specified node's neighbor information from the controller
#define FUNC_ID_ZW_SET_PROMISCUOUS_MODE			0xD0	// Set controller into promiscuous mode to listen to all frames
#define FUNC_ID_PROMISCUOUS_APPLICATION_COMMAND_HANDLER		0xD1

#define ADD_NODE_ANY								0x01
#define ADD_NODE_CONTROLLER							0x02
#define ADD_NODE_SLAVE								0x03
#define ADD_NODE_EXISTING							0x04
#define ADD_NODE_STOP								0x05
#define ADD_NODE_STOP_FAILED						0x06

#define ADD_NODE_STATUS_LEARN_READY		  			0x01
#define ADD_NODE_STATUS_NODE_FOUND		   			0x02
#define ADD_NODE_STATUS_ADDING_SLAVE		 		0x03
#define ADD_NODE_STATUS_ADDING_CONTROLLER			0x04
#define ADD_NODE_STATUS_PROTOCOL_DONE				0x05
#define ADD_NODE_STATUS_DONE				 		0x06
#define ADD_NODE_STATUS_FAILED			   			0x07

#define REMOVE_NODE_ANY								0x01
#define REMOVE_NODE_STOP							0x05

#define REMOVE_NODE_STATUS_LEARN_READY				0x01
#define REMOVE_NODE_STATUS_NODE_FOUND				0x02
#define REMOVE_NODE_STATUS_REMOVING_SLAVE			0x03
#define REMOVE_NODE_STATUS_REMOVING_CONTROLLER		0x04
#define REMOVE_NODE_STATUS_DONE						0x06
#define REMOVE_NODE_STATUS_FAILED					0x07

#define CREATE_PRIMARY_START						0x02
#define CREATE_PRIMARY_STOP							0x05
#define CREATE_PRIMARY_STOP_FAILED					0x06

#define CONTROLLER_CHANGE_START						0x02
#define CONTROLLER_CHANGE_STOP						0x05
#define CONTROLLER_CHANGE_STOP_FAILED				0x06

#define LEARN_MODE_STARTED							0x01
#define LEARN_MODE_DONE								0x06	
#define LEARN_MODE_FAILED							0x07
#define LEARN_MODE_DELETED							0x80

#define REQUEST_NEIGHBOR_UPDATE_STARTED				0x21
#define REQUEST_NEIGHBOR_UPDATE_DONE				0x22
#define REQUEST_NEIGHBOR_UPDATE_FAILED				0x23

#define FAILED_NODE_OK								0x00
#define FAILED_NODE_REMOVED							0x01
#define FAILED_NODE_NOT_REMOVED						0x02
#define FAILED_NODE_REPLACE_WAITING					0x03
#define FAILED_NODE_REPLACE_DONE					0x04
#define FAILED_NODE_REPLACE_FAILED					0x05

#define SUC_UPDATE_DONE								0x00
#define SUC_UPDATE_ABORT							0x01
#define SUC_UPDATE_WAIT								0x02
#define SUC_UPDATE_DISABLED							0x03
#define SUC_UPDATE_OVERFLOW							0x04

#define SUC_FUNC_BASIC_SUC							0x00
#define SUC_FUNC_NODEID_SERVER						0x01

#define UPDATE_STATE_NODE_INFO_RECEIVED				0x84
#define UPDATE_STATE_NODE_INFO_REQ_DONE				0x82
#define UPDATE_STATE_NODE_INFO_REQ_FAILED			0x81
#define UPDATE_STATE_ROUTING_PENDING				0x80
#define UPDATE_STATE_NEW_ID_ASSIGNED				0x40
#define UPDATE_STATE_DELETE_DONE					0x20
#define UPDATE_STATE_SUC_ID							0x10

#define OPTION_HIGH_POWER							0x80

//Device request related
#define BASIC_SET									0x01
#define BASIC_REPORT								0x03

#define COMMAND_CLASS_BASIC							0x20
#define	COMMAND_CLASS_CONTROLLER_REPLICATION		0x21
#define COMMAND_CLASS_APPLICATION_STATUS 			0x22
#define COMMAND_CLASS_HAIL							0x82

#endif // _Defs_H