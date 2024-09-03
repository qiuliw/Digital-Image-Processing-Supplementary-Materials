// TArrayEx.h: interface for the CTArrayEx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TARRAYEX_H__35721324_67E3_43FE_9391_F369F8DB07E8__INCLUDED_)
#define AFX_TARRAYEX_H__35721324_67E3_43FE_9391_F369F8DB07E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// [ ******************************************************************* ]
// [ ģ���� CTArray< TYPE > �� CTArrayEx< TYPE > ����������:             ]
// [        �ڹ�����������( ���鸴�� )����( Construction )�н������鸴�� ]
// [        ʱ, CTArray �����������ڴ�Ŀ���, CTArrayEx ���������Ԫ�ص� ]
// [        ����.                                                        ]
// [ ����˵��: CTArray �е� TYPE �ǲ����ڶ�̬�����ڴ����������, ������  ]
// [               ������������( �� int, double �� )�� struct ���� �Լ�  ]
// [               class ����( �� CPoint �� ).                           ]
// [           CTArrayEx �е� TYPE ����Ǵ��ڶ�̬�����ڴ����������, ��  ]
// [               �� struct ���ͺ� class ����( �� CString �� )��        ]
// [           CTArrayEx �������е���������, �������ٶ���; CTArray ֻ��  ]
// [               �ò����ڶ�̬�����ڴ����������, �������ٶȿ�.         ]
// [           ����˵, CTArrayEx �� CTArray ����չ, �� CTArray ��        ]
// [               CTArrayEx ������.                                     ]
// [ ******************************************************************* ]

// [ ******************************************************************* ]
// [ ********************* << һά����ģ����չ >> ********************** ]
// [ ******************************************************************* ]

template <class TYPE> class CTArrayEx  
{
	// [ ******** ] ......................................................
	// [ ��Ա���� ] ......................................................
	// [ ******** ] ......................................................
private:
	TYPE* m_memory;      // [ �����ڴ�ָ�� ]
	bool  m_isAllocated; // [ �Ƿ����·������ڴ� ]
	long  m_dimension;   // [ ����ά�� ]
     
	// [ ****************** ] ............................................
	// [ ���캯������������ ] ............................................
	// [ ****************** ] ............................................
public:
	CTArrayEx()                                     // [ ���캯��: ȱʡ���캯�� ]
	{
	    Initialization(); // [ ��ʼ����Ա���� ]
    }

	CTArrayEx( long dimension )                     // [ ���캯��: ���������ڴ� ]
	{
	    Initialization(); // [ ��ʼ����Ա���� ]

	    Construction( dimension ); // [ ������������: ���������ڴ� ]
    }

	CTArrayEx( TYPE* memory, long dimension )       // [ ���캯��: ָ�������ڴ� ]
	{
	    Initialization(); // [ ��ʼ����Ա���� ]

	    Construction( memory, dimension ); // [ ������������: ָ�������ڴ� ]
    }

	CTArrayEx( const CTArrayEx< TYPE >& array )     // [ ���ƹ��캯�� ]
	{
	    Initialization(); // [ ��ʼ����Ա���� ]

	    Construction( array ); // [ ������������: ���鸴�� ]
    }

	~CTArrayEx()                                    // [ �������� ]
	{
	    Destruction();    // [ ������������ ]
    }

	// [ ************ ] ..................................................
	// [ ���ܽӿں��� ] ..................................................
	// [ ************ ] ..................................................
public:
	void Construction( long dimension )                     // [ ������������: ���������ڴ� ]
	{
		if( m_isAllocated == true && m_dimension == dimension && m_memory != NULL ) // [ �����Ҫ����������ڴ��С���䣬����ԭ�������ڴ� ]                            
			return; 

		Destruction(); // [ ������������ ]

		if( dimension > 0 ) // [ ����ά��������� 0 ]
		{
			m_memory = new TYPE[ dimension ]; // [ �����ڴ� ]

			if( m_memory != NULL ) // [ �ж��ڴ�����Ƿ�ɹ� ]
			{
				m_isAllocated = true; // [ ��־�������ڴ� ]
				m_dimension = dimension; // [ ��������ά�� ]
			}
			else
			{
				Verification( "System Error << Can not allocate memory correctly >>" ); // [ ���Ա��� ]
			}
		}
		else
		{
			Verification( "Program Error << Array dimension must be bigger than 0 >>" ); // [ ���Ա��� ]
		}
	}

	void Construction( TYPE* memory, long dimension )       // [ ������������: ָ�������ڴ� ]
	{
		Destruction(); // [ ������������ ]

		if( memory != NULL && dimension > 0 ) // [ ������Ч�Բ��� ]
		{
			m_memory = memory; // [ ���������ڴ�ָ�� ]
			m_dimension = dimension; // [ ��������ά�� ]
		}
		else
		{
			Verification( "Program Error << The assigned array memory pointer can not be null, and array dimension must be bigger than 0 >>" ); // [ ���Ա��� ]
		}
	}

	void Construction( const CTArrayEx< TYPE >& array )     // [ ������������: ���鸴�� ]
	{
		if( array.m_memory != NULL ) // [ �ж������Ƿ�Ϊ�� ]
		{
			Construction( array.m_dimension ); // [ ������ͬά��������: ���������ڴ� ]

			for( int index = 0; index < m_dimension; index++ ) // [ �����������Ԫ�� ]
			{
				m_memory[ index ] = array.m_memory[ index ]; // [ ��������Ԫ�� ]
			}
		}
		else
		{
			Destruction(); // [ ������������ ]
		}
	}

	void Destruction()                                      // [ ������������ ]
	{
		// [ ����������ڴ棬���ͷ��ڴ� ]
		if( m_isAllocated == true )
		{
			delete [] m_memory;
		}
	
		// [ ��ʼ����Ա���� ]
		Initialization( ); 
	}

	CTArrayEx< TYPE >& operator=( const CTArrayEx< TYPE >& array )  // [ ��ֵ������ ]
	{
	    Construction( array ); // [ ������������: ���鸴�� ]

	    return * this; // [ ���ص�ǰ���� ]
    }

	TYPE& operator[]( long index ) const                            // [ �±������ ]
	{
#ifdef _DEBUG

		static TYPE error; // [ �����صľ�̬���� ]

		if( !( index >=0 && index < m_dimension ) ) // [ �����±���Ч�Բ��� ]
		{
			Verification( "Program Error << Array subscript beyond bound >>" ); // [ ���Ա��� ]

			return error; // [ ������ ]
		}

#endif // _DEBUG

		return m_memory[ index ]; // [ ��������Ԫ�� ]
	}

	bool Is_index_valid( long index ) const // [ ���������Ƿ���ȷ ]
	{
	    return index >= 0 && index < m_dimension; // [ �������� ]
    }

	// [ ************ ] ..................................................
    // [ ״̬�������� ] ..................................................
	// [ ************ ] ..................................................
public:
	bool IsNull() const         // [ �Ƿ�Ϊ�� ]
	{
	    return ( m_memory == NULL );
    }

	bool IsNotNull() const      // [ �Ƿ񲻿� ]
	{
	    return ( m_memory != NULL );
    }

	long GetDimension() const   // [ ����ά�� ]
	{
	    return m_dimension;
    }

	long GetUpperBound() const  // [ �����Ͻ� ]
	{
	    return ( m_dimension - 1 );
    }

	long GetSizeInBytes() const // [ ����������ռ�ֽ��� ]
	{
	    return ( m_dimension * sizeof( TYPE ) );
    }

	// [ ************ ] ..................................................
	// [ �ڲ�ʵ�ֺ��� ] ..................................................
	// [ ************ ] ..................................................
private:
	void Initialization() // [ ��ʼ����Ա���� ]
	{
		m_memory = NULL;       // [ ��������ڴ�ָ�� ]
		m_isAllocated = false; // [ ��ʾû�з����ڴ� ]
		m_dimension = 0 ;      // [ ����ά������ ]

		// [ *************************************************************** ]
		// [ ��Ա������ʼ��( Initialization )��, ��Ա�����������¹���:       ]
		// [     1. ����������ڴ�( m_isAllocated == true ), ���ڴ�ָ�벻��  ]
		// [             Ϊ��( m_memory != NULL ) , ������ά��������� 0     ]
		// [             ( m_dimension > 0 ) ��                              ]
		// [     2. ���û�з����ڴ�( m_isAllocated == false ), ���ڴ�ָ�벻 ]
		// [             ��( m_memory != NULL ), ˵��ָ���������ڴ棬������  ]
		// [             ά��������� 0 ( m_dimension > 0 ) ��               ]
		// [     3. ���û�з����ڴ�( m_isAllocated == false ), ���ڴ�ָ��Ϊ ]
		// [             ��( m_memory == NULL ), ������ά������Ϊ 0          ]
		// [             ( m_dimension == 0 ) ��                             ]
		// [ *************************************************************** ]
	}

	void Verification( CString message ) const // [ ���Ա��� ]
	{
#ifdef _DEBUG

	    AfxMessageBox( message ); // [ ���Ա��� ]

#endif // _DEBUG
    }

};

#endif // !defined(AFX_TARRAYEX_H__35721324_67E3_43FE_9391_F369F8DB07E8__INCLUDED_)
