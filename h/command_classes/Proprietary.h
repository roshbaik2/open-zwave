//-----------------------------------------------------------------------------
//
//	Proprietary.h
//
//	Implementation of the Z-Wave COMMAND_CLASS_PROPRIETARY
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

#ifndef _Proprietary_H
#define _Proprietary_H

#include "CommandClass.h"

namespace OpenZWave
{
	class Proprietary: public CommandClass
	{
	public:
		static CommandClass* Create( uint8 const _nodeId ){ return new Proprietary( _nodeId ); }
		virtual ~Proprietary(){}

		static uint8 const StaticGetCommandClassId(){ return 0x88; }
		static string const StaticGetCommandClassName(){ return "COMMAND_CLASS_PROPRIETARY"; }

		// From CommandClass
		virtual uint8 const GetCommandClassId()const{ return StaticGetCommandClassId(); }
		virtual string const GetCommandClassName()const{ return StaticGetCommandClassName(); }
		virtual bool HandleMsg( uint8 const* _data, uint32 const _length, uint32 const _instance = 0 );

	private:
		Proprietary( uint8 const _nodeId ): CommandClass( _nodeId ){}
	};

} // namespace OpenZWave

#endif
