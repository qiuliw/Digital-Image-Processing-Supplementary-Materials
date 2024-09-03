// TArray.h: interface for the CTArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TARRAY_H__5C18C5F4_170D_4D56_BFDA_B5173B41596D__INCLUDED_)
#define AFX_TARRAY_H__5C18C5F4_170D_4D56_BFDA_B5173B41596D__INCLUDED_

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
// [ *********************** << һά����ģ�� >> ************************ ]
// [ ******************************************************************* ]

template <class TYPE> class CTArray  
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
	CTArray()                                // [ ���캯��: ȱʡ���캯�� ]
	{
		// [ ��ʼ����Ա���� ] 
	    m_memory      = NULL;  // [ ��������ڴ�ָ�� ]
	    m_isAllocated = false; // [ ��ʾû�з����ڴ� ]
	    m_dimension   = 0 ;    // [ ����ά������ ]
	}

	CTArray( long dimension )                // [ ���캯��: ���������ڴ� ]
	{
		// [ ��ʼ����Ա���� ]
		m_memory      = NULL;  // [ ��������ڴ�ָ�� ]
		m_isAllocated = false; // [ ��ʾû�з����ڴ� ]
		m_dimension   = 0 ;    // [ ����ά������ ]

		// [ ������������: ���·��������ڴ� ]
		if( dimension > 0 ) // [ ����ά��������� 0 ]
		{
			m_memory = new TYPE[ dimension ]; // [ �����ڴ� ]

			if( m_memory != NULL ) // [ �ж��ڴ�����Ƿ�ɹ� ]
			{
				m_isAllocated = true;      // [ ��־�������ڴ� ]
				m_dimension   = dimension; // [ ��������ά�� ]
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

	CTArray( TYPE* memory, long dimension )  // [ ���캯��: ָ�������ڴ� ]
	{
		// [ ��ʼ����Ա���� ]
		m_memory      = NULL;  // [ ��������ڴ�ָ�� ]
		m_isAllocated = false; // [ ��ʾû�з����ڴ� ]
		m_dimension   = 0 ;    // [ ����ά������ ]

		// [ ������������: ָ�������ڴ� ]
		if( memory != NULL && dimension > 0 ) // [ ������Ч�Բ��� ]
		{
			m_isAllocated = false;       // [ ��ʾû�з����ڴ� ]
			m_memory      = memory;      // [ ���������ڴ�ָ�� ]
			m_dimension   = dimension;   // [ ��������ά�� ]
		}
		else
		{
			Verification( "Program Error << The assigned array memory pointer can not be null, and array dimension must be bigger thant 0 >>" ); // [ ���Ա��� ]
		}
	}

	CTArray( const CTArray< TYPE >& array )   // [ ���ƹ��캯�� ]
	{
		// [ ��ʼ����Ա���� ]
		m_memory      = NULL;  // [ ��������ڴ�ָ�� ]
		m_isAllocated = false; // [ ��ʾû�з����ڴ� ]
		m_dimension   = 0 ;    // [ ����ά������ ]

		// [ ������������: ���·��������ڴ� ]
		if( array.m_memory != NULL ) // [ �ж������Ƿ�Ϊ�� ]
		{
			m_memory = new TYPE[ array.m_dimension ]; // [ �����ڴ� ]

			if( m_memory != NULL ) // [ �ж��ڴ�����Ƿ�ɹ� ]
			{
		 	   m_isAllocated = true;                // [ ��־�������ڴ� ]
		   	   m_dimension   = array.m_dimension;   // [ ��������ά�� ]

			   long sizeInBytes = m_dimension * sizeof( TYPE ); // [ ����������ռ�ֽ��� ]
		 	   memcpy( m_memory, array.m_memory, sizeInBytes ); // [ ������������ ]		    
			}
			else
			{
			    Verification( "System Error << Can not allocate memory correctly >>" ); // [ ���Ա��� ]
			}	
		}
	}

	~CTArray()                               // [ �������� ]
	{
		// [ ����������ڴ棬���ͷ��ڴ� ]
		if( m_isAllocated == true )
		{
			delete [] m_memory;
		}
	}

	// [ ************ ] ..................................................
	// [ ���ܽӿں��� ] ..................................................
	// [ ************ ] ..................................................
public:
	void Construction( long dimension )               // [ ������������: ���������ڴ� ]
	{	  
		// [ �����Ҫ����������ڴ��С���䣬����ԭ�������ڴ� ]
		if( m_isAllocated == true && m_dimension == dimension && m_memory != NULL ) 
		{
			return;            // [ �������� ]  
		}

		// [ ����������ڴ棬���ͷ��ڴ� ]
		if( m_isAllocated == true )
		{
			delete [] m_memory;
		}
	
		// [ ��ʼ����Ա���� ]
		m_memory      = NULL;  // [ ��������ڴ�ָ�� ]
		m_isAllocated = false; // [ ��ʾû�з����ڴ� ]
		m_dimension   = 0 ;    // [ ����ά������ ]

		// [ ������������: ���·��������ڴ� ]
		if( dimension > 0 ) // [ ����ά��������� 0 ]
		{
			m_memory = new TYPE[ dimension ]; // [ �����ڴ� ]

			if( m_memory != NULL ) // [ �ж��ڴ�����Ƿ�ɹ� ]
			{
				m_isAllocated = true;      // [ ��־�������ڴ� ]
				m_dimension   = dimension; // [ ��������ά�� ]
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

	void Construction( TYPE* memory, long dimension ) // [ ������������: ָ�������ڴ� ]
	{
		// [ ����������ڴ棬���ͷ��ڴ� ]
		if( m_isAllocated == true )
		{
			delete [] m_memory;
		}
	
		// [ ��ʼ����Ա���� ]
		m_memory      = NULL;  // [ ��������ڴ�ָ�� ]
		m_isAllocated = false; // [ ��ʾû�з����ڴ� ]
		m_dimension   = 0 ;    // [ ����ά������ ]

		// [ ������������: ָ�������ڴ� ]
		if( memory != NULL && dimension > 0 ) // [ ������Ч�Բ��� ]
		{
			m_isAllocated = false;       // [ ��ʾû�з����ڴ� ]
			m_memory      = memory;      // [ ���������ڴ�ָ�� ]
			m_dimension   = dimension;   // [ ��������ά�� ]
		}
		else
		{
			Verification( "Program Error << The assigned array memory pointer can not be null, and array dimension must be bigger than 0 >>" ); // [ ���Ա��� ]
		}
	}

	void Construction( const CTArray< TYPE >& array ) // [ ������������: ���鸴�� ]
	{
		if( array.m_memory != NULL ) // [ �ж������Ƿ�Ϊ�� ]
		{
			// [ �����Ҫ����������ڴ��С���䣬����ԭ�������ڴ� ]
		    if( m_isAllocated == true && m_dimension == array.m_dimension && m_memory != NULL ) 
			{
				long sizeInBytes = m_dimension * sizeof( TYPE ); // [ ����������ռ�ֽ��� ]
			    memcpy( m_memory, array.m_memory, sizeInBytes ); // [ ������������ ]

			    return; // [ �������� ]  
			}

		    // [ ����������ڴ棬���ͷ��ڴ� ]
		    if( m_isAllocated == true )
			{
			    delete [] m_memory;
			}
	
	  	    // [ ��ʼ����Ա���� ]
	  	    m_memory      = NULL;  // [ ��������ڴ�ָ�� ]
	 	    m_isAllocated = false; // [ ��ʾû�з����ڴ� ]
	 	    m_dimension   = 0 ;    // [ ����ά������ ]

	 	    // [ ������������: ���·��������ڴ� ]
			m_memory = new TYPE[ array.m_dimension ]; // [ �����ڴ� ]

			if( m_memory != NULL ) // [ �ж��ڴ�����Ƿ�ɹ� ]
			{
			    m_isAllocated = true;                // [ ��־�������ڴ� ]
			    m_dimension   = array.m_dimension;   // [ ��������ά�� ]

				long sizeInBytes = m_dimension * sizeof( TYPE ); // [ ����������ռ�ֽ��� ]
			    memcpy( m_memory, array.m_memory, sizeInBytes ); // [ ������������ ]		    
			}
			else
			{
			    Verification( "System Error << Can not allocate memory correctly >>" ); // [ ���Ա��� ]
			}	
		}
		else
		{
	 	    // [ ����������ڴ棬���ͷ��ڴ� ]
		    if( m_isAllocated == true )
			{
			    delete [] m_memory;
			}
	
	 	    // [ ��ʼ����Ա���� ]
	        m_memory      = NULL;  // [ ��������ڴ�ָ�� ]
	        m_isAllocated = false; // [ ��ʾû�з����ڴ� ]
	        m_dimension   = 0 ;    // [ ����ά������ ]
	    }
	}

	void Destruction()                                // [ ������������ ]
	{
		// [ ����������ڴ棬���ͷ��ڴ� ]
		if( m_isAllocated == true )
		{
			delete [] m_memory;
		}
	
		// [ ��ʼ����Ա���� ]
		m_memory      = NULL;  // [ ��������ڴ�ָ�� ]
		m_isAllocated = false; // [ ��ʾû�з����ڴ� ]
		m_dimension   = 0 ;    // [ ����ά������ ]
	}

	void ImportFrom( const void* source )    // [ ������������ ]
	{
		if( m_memory != NULL && source != NULL ) // [ У������ǿ� �� ����Դ���ݷǿ� ]
		{
			long sizeInBytes = m_dimension * sizeof( TYPE ); // [ ����������ռ�ֽ��� ]
			memcpy( m_memory, source, sizeInBytes );         // [ ������������ ]
		}
	}

	void ExportTo( void* destination ) const // [ ������������ ]
	{
		if( m_memory != NULL && destination != NULL ) // [ У������ǿ� �� ����Ŀ�����ݷǿ� ]
		{
			long sizeInBytes = m_dimension * sizeof( TYPE ); // [ ����������ռ�ֽ��� ]
			memcpy( destination, m_memory, sizeInBytes );    // [ ������������ ]
		}
	}
	
	CTArray< TYPE >& operator= ( const CTArray< TYPE >& array )  // [ ���Ƹ�ֵ������ ]
	{
		if( array.m_memory != NULL ) // [ �ж������Ƿ�Ϊ�� ]
		{
			// [ �����Ҫ����������ڴ��С���䣬����ԭ�������ڴ� ]
	  	    if( m_isAllocated == true && m_dimension == array.m_dimension && m_memory != NULL ) 
			{
				long sizeInBytes = m_dimension * sizeof( TYPE ); // [ ����������ռ�ֽ��� ]
			    memcpy( m_memory, array.m_memory, sizeInBytes ); // [ ������������ ]

		 	   return * this; // [ ���ص�ǰ���� ]  
			}

	  	    // [ ����������ڴ棬���ͷ��ڴ� ]
	   	    if( m_isAllocated == true )
			{
			    delete [] m_memory;
			}
	
	 	    // [ ��ʼ����Ա���� ]
	  	    m_memory      = NULL;  // [ ��������ڴ�ָ�� ]
	  	    m_isAllocated = false; // [ ��ʾû�з����ڴ� ]
	    	m_dimension   = 0 ;    // [ ����ά������ ]

	    	// [ ������������: ���·��������ڴ� ]
			m_memory = new TYPE[ array.m_dimension ]; // [ �����ڴ� ]

			if( m_memory != NULL ) // [ �ж��ڴ�����Ƿ�ɹ� ]
			{
			    m_isAllocated = true;                // [ ��־�������ڴ� ]
			    m_dimension   = array.m_dimension;   // [ ��������ά�� ]

				long sizeInBytes = m_dimension * sizeof( TYPE ); // [ ����������ռ�ֽ��� ]
			    memcpy( m_memory, array.m_memory, sizeInBytes ); // [ ������������ ]		    
			}
			else
			{
		 	    Verification( "System Error << Can not allocate memory correctly >>" ); // [ ���Ա��� ]
			}		
		}
		else
		{
	    	// [ ����������ڴ棬���ͷ��ڴ� ]
	   	    if( m_isAllocated == true )
			{
		    	delete [] m_memory;
			}
	
	    	// [ ��ʼ����Ա���� ]
	   	    m_memory      = NULL;  // [ ��������ڴ�ָ�� ]
	    	m_isAllocated = false; // [ ��ʾû�з����ڴ� ]
	    	m_dimension   = 0 ;    // [ ����ά������ ]
		}

		return * this; // [ ���ص�ǰ���� ]
	}

	TYPE& operator[]( long index ) const                         // [ �±������ ]
	{
#ifdef _DEBUG

		static TYPE error; // [ �����صľ�̬���� ]

		if( !( index >= 0 && index <= ( m_dimension - 1 ) ) ) // [ �����±���Ч�Բ��� ]
		{
			Verification( "Program Error << Array subscript beyond bound >>" ); // [ ���Ա��� ]

			return error; // [ ������ ]
		}

#endif // _DEBUG

		return m_memory[ index ]; // [ ��������Ԫ�� ]
	}

	TYPE& operator()( long index ) const                         // [ ����ǿ�ư�ȫ�����±������ ]
	{
		static TYPE error; // [ �����صľ�̬���� ]

		if( !( index >= 0 && index <= ( m_dimension - 1 ) ) ) // [ �����±���Ч�Բ��� ]
		{
			return error; // [ ������ ]
		}
		else
		{
			return m_memory[ index ]; // [ ��������Ԫ�� ]
		}
	}

	bool Is_index_valid( long index ) const                      // [ ���������Ƿ���ȷ ]
	{
	    return index >= 0 && index < m_dimension; // [ �������� ]
    }

	// [ ************ ] ..................................................
    // [ ״̬�������� ] ..................................................
	// [ ************ ] ..................................................
public:
	bool IsNull() const         // [ �Ƿ�Ϊ�� ]
	{
	    return ( m_memory == NULL ); // [ �Ƿ�Ϊ�� ]
    }

	bool IsNotNull() const      // [ �Ƿ񲻿� ]
	{
	    return ( m_memory != NULL ); // [ �Ƿ񲻿� ]
    }

	long GetDimension() const   // [ ����ά�� ]
	{
	    return m_dimension; // [ ����ά�� ]
    }

	long GetUpperBound() const  // [ �����Ͻ� ]
	{
	    return ( m_dimension - 1 ); // [ �����Ͻ� ]
    }

	long GetSizeInBytes() const // [ ����������ռ�ֽ��� ]
	{
	    return ( m_dimension * sizeof( TYPE ) ); // [ ����������ռ�ֽ��� ]
    }

	// [ ************ ] ..................................................
	// [ �ڲ�ʵ�ֺ��� ] ..................................................
	// [ ************ ] ..................................................
private:
	void Verification( CString message ) const // [ ���Ա��� ]
	{
#ifdef _DEBUG

	    AfxMessageBox( message ); // [ ���Ա��� ]

#endif // _DEBUG
    }

};

// [ ******************************************************************* ]
// [ ************* << ģ���� CTStack ����ջ�Ĺ���Ͳ��� >> ************* ]
// [ ******************************************************************* ]

template <class TYPE> class CTStack
{
	// [ ******** ] ......................................................
	// [ ��Ա���� ] ......................................................
	// [ ******** ] ......................................................
private:
	CTArray< TYPE > m_array_of_elements; // [ ���ڴ��ջԪ�ص����� ]
	long m_index_of_top;                 // [ ָʾջ��Ԫ���������еĵ�ǰλ�� ]
	                                     // [ ��� m_index_of_top ���� -1 �����ʾջΪ�ա���� m_index_of_top ]
	                                     // [ ���ڵ��� 0 �� С�� m_array_of_elements ��ά�������ʾջ����Ԫ�� ]                                   ]

	// [ ************** ] ................................................
	// [ ������������� ] ................................................
	// [ ************** ] ................................................
public:
	CTStack(void) // [ ���캯�� ]
	{
	    m_index_of_top = -1 ;  // [ ����ջΪ�� ]
	    Reset_stack( 100 ); // [ ջԪ������ȱʡ��СΪ 100 ]
    }

	CTStack( long maximum_of_elements ) // [ ָ��ջԪ�������С�Ĺ��캯�� ]
	{
	    m_index_of_top = -1 ;        // [ ����ջΪ�� ]
	    Reset_stack( maximum_of_elements ); // [ ����ָ���Ĵ�С��ջԪ��������з���ռ� ]
    }

	~CTStack(void) // [ �������� ]
	{
	    m_array_of_elements.Destruction(); // [ �ͷ�ջԪ������Ŀռ䡣(���Բ���ʽ�ͷſռ䣬��Ϊ������Զ��ͷſռ�) ]
    }

	// [ ************ ] ..................................................
	// [ ���ܽӿں��� ] ..................................................
	// [ ************ ] ..................................................
public:
	const TYPE& Push( const TYPE& element ) // [ ��Ԫ��ѹջ����������ջԪ�ء���ջ��ʱ��ȡ������������ʾ "ջ���" ������Ϣ ]
    {
		if( !Is_full() ) // [ ���ջ����ʱ����ջ��ָ������һ��Ԫ�أ�����ֵ��ѹջԪ�� ]
		{
			m_array_of_elements[ ++m_index_of_top ] = element;
		}
		else // [ ���ջ��ʱ����ʾ "ջ���" ������Ϣ ]
		{
			Verification( "Fatal Error: Overfall of Stack!" );
		}
	
		return element;// [ ������ջԪ�� ]
	}

	const TYPE& Pop( )                      // [ ��Ԫ�ص�ջ�������س�ջԪ�ء���ջ��ʱ��ȡ������ ]
	{
		static TYPE error; // [ ����ʱ����ֵ ]

		if( !Is_empty() ) // [ ���ջ�ǿ�ʱ������ջ��Ԫ�أ�����ջ��ָ������һ��Ԫ�� ]
		{
			return m_array_of_elements[ m_index_of_top-- ];
		}
		else // [ ���ջΪ��ʱ����ȡ������ ]	
		{
			return error;// [ ������ ]
		}
	}

	BOOL Is_empty( ) const // [ �ж�ջ�Ƿ�Ϊ�ա����Ϊ�գ��򷵻� TRUE �����򷵻� FALSE ]
	{
	    return ( m_index_of_top == -1 );// [ ��� m_index_of_top Ϊ -1 �����ʾջΪ�գ�����ǿ� ]
    }

	BOOL Is_full( ) const  // [ �ж�ջ�Ƿ�����������������򷵻� TRUE �����򷵻� FALSE ]
	{
	    return ( m_index_of_top == m_array_of_elements.GetUpperBound() ); // [ ��� m_index_of_top ����ջԪ��������Ͻ磬�򷵻� TRUE �����򷵻� FALSE ]
    }

	const TYPE& Get_element_of_top( ) const               // [ ��ȡջ��Ԫ�� ]
	{
		static TYPE error; // [ ����ʱ����ֵ ]

		if( !Is_empty() ) // [ ���ջ�ǿ�ʱ������ջ��Ԫ�� ]
		{
			return m_array_of_elements[ m_index_of_top ];
		}
		else // [ ���ջΪ��ʱ����ȡ������ ]	
		{	
			return error;// [ ������ ]
		}
	}

	const TYPE& Set_element_of_top( const TYPE& element ) // [ ����ջ��Ԫ�� ]
	{
		if ( !Is_empty() ) // [ ֻ�е�ջ�ǿ�ʱ���Ž�������ջ��Ԫ�� ]
		{
			m_array_of_elements[ m_index_of_top ] = element ;// [ ����ջ��Ԫ�� ]
		}

		return element;// [ �������� ]
	}

	long Get_number_of_elements( ) const  // [ ��ȡ��ǰջ��Ԫ�صĸ��� ]
	{
	    return ( m_index_of_top + 1 );// [ ��ǰջ��Ԫ�صĸ�������ջ��ָ�� m_index_of_top �� 1  ]
    }

    long Get_maximum_of_elements( ) const // [ ��ȡջԪ������Ĵ�С ]
	{
	    return m_array_of_elements.GetDimension() ;// [ ����ջԪ������Ĵ�С ]
    }

	BOOL Reset_stack( long maximum_of_elements ) // [ ��������ջԪ������Ĵ�С��ע�⣺�˲������ݻ�����ԭ��������!!! ]
	                                              // [ ֻ����ջΪ�յ�ʱ�򣬴˲�������Ч������ϵͳ����ʾ������Ϣ    ]
    {	
		if( Is_empty() && maximum_of_elements > 0 ) // [ ���ջΪ�գ����ջԪ������������·��� ]
		{
			m_array_of_elements.Construction( maximum_of_elements );// [ ��ջԪ���������·���ռ� ]

			return TRUE;// [ �������� ]
		}
		else// [ ���ջ�ǿգ�����г������ ]
		{
			Verification( "ERROR: Can not reallocate the stack!" );

			return FALSE;//[ ������ ]
		}
	}

	// [ ************ ] ..................................................
	// [ �ڲ�ʵ�ֺ��� ] ..................................................
	// [ ************ ] ..................................................
private:
	void Verification( CString message ) const // [ ���Ա��� ]
	{
#ifdef _DEBUG

	    AfxMessageBox( message ); // [ ���Ա��� ]

#endif // _DEBUG
    }

};

#endif // !defined(AFX_TARRAY_H__5C18C5F4_170D_4D56_BFDA_B5173B41596D__INCLUDED_)
