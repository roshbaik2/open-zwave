//-----------------------------------------------------------------------------
//
//	CommandClass.h
//
//	Base class for all Z-Wave Command Classes
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

#ifndef _CommandClass_H
#define _CommandClass_H

#include <string>
#include <vector>
#include "tinyxml.h"
#include "Defs.h"

namespace OpenZWave
{
	class Driver;
	class Msg;
	class Node;
	class Value;
	class ValueID;

	/** \brief Base class for all Z-Wave command classes.
	 */
	class CommandClass
	{
	public:
		enum
		{
			RequestFlag_Static	= 0x00000001,	/**< Values that never change. */
			RequestFlag_Session = 0x00000002,	/**< Values that change infrequently, and so only need to be requested at start up, or via a manual refresh. */
			RequestFlag_Dynamic	= 0x00000004	/**< Values that change and will be requested if polling is enabled on the node. */
		};

		CommandClass( uint32 const _homeId, uint8 const _nodeId );
		virtual ~CommandClass(){}

		virtual void ReadXML( TiXmlElement const* _ccElement );
		virtual void WriteXML( TiXmlElement* _ccElement );
		virtual bool RequestState( uint32 const _requestFlags ){ return false; }
		
		virtual uint8 const GetCommandClassId()const = 0;		
		virtual string const GetCommandClassName()const = 0;
		virtual bool HandleMsg( uint8 const* _data, uint32 const _length, uint32 const _instance = 1 ) = 0;
		virtual bool SetValue( Value const& _value ){ return false; }
		virtual void SetVersion( uint8 const _version ){ m_version = _version; }

		uint8 GetVersion()const{ return m_version; }
		uint8 GetInstances()const{ return m_instances; }
		uint32 GetHomeId()const{ return m_homeId; }
		uint8 GetNodeId()const{ return m_nodeId; }
		Driver* GetDriver()const;
		Node* GetNodeUnsafe()const;
		void ReleaseNode()const;

		void SetInstances( uint8 const _instances );
		void SetAfterMark(){ m_afterMark = false; }
		bool IsAfterMark()const{ return m_afterMark; }

		// Helper methods
		string ExtractValue( uint8 const* _data, uint8* _scale )const;

		/**
		 *  Append a floating-point value to a message.
		 *  \param _msg The message to which the value should be appended.
		 *  \param _value A string containing a decimal number to be appended.
		 *  \param _scale A byte indicating the scale corresponding to this value (e.g., 1=F and 0=C for temperatures).
		 *  \see Msg
		 */
		void AppendValue( Msg* _msg, string const& _value, uint8 const _scale )const;
		uint8 const GetAppendValueSize( string const& _value )const;
		int32 ValueToInteger( string const& _value, uint8* o_precision, uint8* o_size )const;

	protected:
		/** \brief
		 *   Manages an array of "instances" which hold instance-specific values (???) 
		 */
		template <class T>
		class ValueInstances
		{
		public:
			ValueInstances(): m_instances(NULL), m_numInstances(0){}
			/** 
			 * \brief Destructor.  Iterate through the instance list and release memory allocated to each.
			 * \see m_instances, m_numInstances
			 */
			~ValueInstances()
			{
				for( int i=0; i<m_numInstances; ++i )
				{
					if( m_instances[i] )
					{
						T* instance = static_cast<T*>( m_instances[i] );
						instance->Release();
					}
				}

				delete [] m_instances;
			}

			/**
			 * \brief Add an instance to the instance list.
			 * \param _idx 1-based index of the instance to add.
			 * \param _instance Pointer to the instance object to add.
			 * \see m_instances, m_numInstances
			 */
			void AddInstance( uint8 _idx, T* _instance )
			{
				if( _idx > m_numInstances )
				{
					Grow( _idx );
				}

				if( m_instances[_idx-1] )
				{
					m_instances[_idx-1]->Release();
				}
				m_instances[_idx-1] = _instance;
			}

			bool HasInstances()const{ return( m_numInstances != 0 ); }

			T* GetInstance( uint8 _idx )
			{ 
				return( ( _idx > m_numInstances ) ? NULL : m_instances[_idx-1] ); 
			}

		private:
			void Grow( uint8 _numInstances )
			{
				if( _numInstances > m_numInstances )
				{
					// Realloc the array
					T** newInstances = new T*[_numInstances];
					memcpy( newInstances, m_instances, sizeof(T*) * m_numInstances );
					memset( &newInstances[m_numInstances], 0, sizeof(T*) * (_numInstances-m_numInstances) );
					delete [] m_instances;
					m_instances = newInstances;
					m_numInstances = _numInstances;
				}
			}

			T**	m_instances;
			int m_numInstances;
		};

		virtual void CreateVars( uint8 const _instance ){}

	private:
		uint32	m_homeId;
		uint8	m_nodeId;
		uint8	m_version;
		uint8	m_instances;
		bool	m_afterMark;		// Set to true if the command class is listed after COMMAND_CLASS_MARK, and should not create any values.

	//-----------------------------------------------------------------------------
	// Record which items of static data have been read from the device
	//-----------------------------------------------------------------------------
	public:
		enum StaticRequest
		{
			StaticRequest_Instances		= 0x01,
			StaticRequest_Values		= 0x02,
			StaticRequest_Version		= 0x04
		};

		bool HasStaticRequest( uint8 _request )const{ return( (m_staticRequests & _request) != 0 ); }
		void SetStaticRequest( uint8 _request ){ m_staticRequests |= _request; }
		void ClearStaticRequest( uint8 _request );

	private:
		uint8   m_staticRequests;		
	};

} // namespace OpenZWave

#endif



