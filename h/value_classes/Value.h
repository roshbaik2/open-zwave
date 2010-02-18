//-----------------------------------------------------------------------------
//
//	Value.h
//
//	Base class for all OpenZWave Value Classes
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

#ifndef _Value_H
#define _Value_H

#include <string>
#include "Defs.h"
#include "ValueID.h"

class TiXmlElement;

namespace OpenZWave
{
	class Value
	{
		friend class ValueStore;

	public:
		enum
		{
			Genre_All = 0,
			Genre_User,			// Basic values an ordinary user would be interested in
			Genre_Config,		// Device-Specific configuration parameters
			Genre_System		// Values of significance only to users who understand the Z-Wave protocol 
		};

		Value( uint8 const _nodeId, uint8 const _commandClassId, uint8 const _instance, uint8 const _index, uint32 const _genre, string const& _label, bool const _bReadOnly );
		Value( uint8 const _nodeId, TiXmlElement* _valueElement );

		virtual void WriteXML( TiXmlElement* _valueElement );

		virtual uint8 const GetValueTypeId()const = 0;		
		virtual string const GetValueTypeName()const = 0;

		virtual string GetAsString()const = 0;

		ValueID const& GetID()const{ return m_id; }
		bool IsReadOnly()const{ return m_bReadOnly; }

		string const& GetLabel()const{ return m_label; }
		void SetLabel( string const& _label ){ m_label = _label; }

		string const& GetUnits()const{ return m_units; }
		void SetUnits( string const& _units ){ m_units = _units; }

		uint32 Release(){ if( !(--m_refs) ){ delete this; return 0; } return m_refs; }

	protected:
		virtual ~Value(){}

		bool Set();				// Fot the user to change a value in a device
		void OnValueChanged();	// A value in a device has been changed.

	private:
		uint32 AddRef(){ ++m_refs; return m_refs; }

		uint32		m_refs;
		uint32		m_genre;
		ValueID		m_id;
		string		m_label;
		string		m_units;
		bool		m_bReadOnly;
	};

} // namespace OpenZWave

#endif


