// TArray.h: interface for the CTArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TARRAY_H__5C18C5F4_170D_4D56_BFDA_B5173B41596D__INCLUDED_)
#define AFX_TARRAY_H__5C18C5F4_170D_4D56_BFDA_B5173B41596D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// [ ******************************************************************* ]
// [ 模板类 CTArray< TYPE > 和 CTArrayEx< TYPE > 的区别在于:             ]
// [        在构造数组内容( 数组复制 )函数( Construction )中进行数组复制 ]
// [        时, CTArray 是整个数组内存的拷贝, CTArrayEx 是逐个数组元素的 ]
// [        拷贝.                                                        ]
// [ 功能说明: CTArray 中的 TYPE 是不存在动态分配内存的数据类型, 包括简  ]
// [               单的数据类型( 如 int, double 等 )和 struct 类型 以及  ]
// [               class 类型( 如 CPoint 等 ).                           ]
// [           CTArrayEx 中的 TYPE 最好是存在动态分配内存的数据类型, 包  ]
// [               括 struct 类型和 class 类型( 如 CString 等 )。        ]
// [           CTArrayEx 适用所有的数据类型, 但复制速度慢; CTArray 只适  ]
// [               用不存在动态分配内存的数据类型, 但复制速度快.         ]
// [           可以说, CTArrayEx 是 CTArray 的扩展, 而 CTArray 是        ]
// [               CTArrayEx 的特例.                                     ]
// [ ******************************************************************* ]

// [ ******************************************************************* ]
// [ *********************** << 一维数组模板 >> ************************ ]
// [ ******************************************************************* ]

template <class TYPE> class CTArray  
{
	// [ ******** ] ......................................................
	// [ 成员变量 ] ......................................................
	// [ ******** ] ......................................................
private:
	TYPE* m_memory;      // [ 数据内存指针 ]
	bool  m_isAllocated; // [ 是否重新分配了内存 ]
	long  m_dimension;   // [ 数组维数 ]
     
	// [ ****************** ] ............................................
	// [ 构造函数和析构函数 ] ............................................
	// [ ****************** ] ............................................
public:
	CTArray()                                // [ 构造函数: 缺省构造函数 ]
	{
		// [ 初始化成员变量 ] 
	    m_memory      = NULL;  // [ 清空数据内存指针 ]
	    m_isAllocated = false; // [ 表示没有分配内存 ]
	    m_dimension   = 0 ;    // [ 数组维数归零 ]
	}

	CTArray( long dimension )                // [ 构造函数: 分配数组内存 ]
	{
		// [ 初始化成员变量 ]
		m_memory      = NULL;  // [ 清空数据内存指针 ]
		m_isAllocated = false; // [ 表示没有分配内存 ]
		m_dimension   = 0 ;    // [ 数组维数归零 ]

		// [ 构造数组内容: 重新分配数组内存 ]
		if( dimension > 0 ) // [ 数组维数必须大于 0 ]
		{
			m_memory = new TYPE[ dimension ]; // [ 分配内存 ]

			if( m_memory != NULL ) // [ 判断内存分配是否成功 ]
			{
				m_isAllocated = true;      // [ 标志分配了内存 ]
				m_dimension   = dimension; // [ 设置数组维数 ]
			}
			else
			{
				Verification( "System Error << Can not allocate memory correctly >>" ); // [ 测试报告 ]
			}
		}
		else
		{
			Verification( "Program Error << Array dimension must be bigger than 0 >>" ); // [ 测试报告 ]
		}
	}

	CTArray( TYPE* memory, long dimension )  // [ 构造函数: 指派数组内存 ]
	{
		// [ 初始化成员变量 ]
		m_memory      = NULL;  // [ 清空数据内存指针 ]
		m_isAllocated = false; // [ 表示没有分配内存 ]
		m_dimension   = 0 ;    // [ 数组维数归零 ]

		// [ 构造数组内容: 指派数组内存 ]
		if( memory != NULL && dimension > 0 ) // [ 参数有效性测试 ]
		{
			m_isAllocated = false;       // [ 表示没有分配内存 ]
			m_memory      = memory;      // [ 设置数组内存指针 ]
			m_dimension   = dimension;   // [ 设置数组维数 ]
		}
		else
		{
			Verification( "Program Error << The assigned array memory pointer can not be null, and array dimension must be bigger thant 0 >>" ); // [ 测试报告 ]
		}
	}

	CTArray( const CTArray< TYPE >& array )   // [ 复制构造函数 ]
	{
		// [ 初始化成员变量 ]
		m_memory      = NULL;  // [ 清空数据内存指针 ]
		m_isAllocated = false; // [ 表示没有分配内存 ]
		m_dimension   = 0 ;    // [ 数组维数归零 ]

		// [ 构造数组内容: 重新分配数组内存 ]
		if( array.m_memory != NULL ) // [ 判断数组是否为空 ]
		{
			m_memory = new TYPE[ array.m_dimension ]; // [ 分配内存 ]

			if( m_memory != NULL ) // [ 判断内存分配是否成功 ]
			{
		 	   m_isAllocated = true;                // [ 标志分配了内存 ]
		   	   m_dimension   = array.m_dimension;   // [ 设置数组维数 ]

			   long sizeInBytes = m_dimension * sizeof( TYPE ); // [ 数组内容所占字节数 ]
		 	   memcpy( m_memory, array.m_memory, sizeInBytes ); // [ 导入数组内容 ]		    
			}
			else
			{
			    Verification( "System Error << Can not allocate memory correctly >>" ); // [ 测试报告 ]
			}	
		}
	}

	~CTArray()                               // [ 析构函数 ]
	{
		// [ 如果分配了内存，则释放内存 ]
		if( m_isAllocated == true )
		{
			delete [] m_memory;
		}
	}

	// [ ************ ] ..................................................
	// [ 功能接口函数 ] ..................................................
	// [ ************ ] ..................................................
public:
	void Construction( long dimension )               // [ 构造数组内容: 分配数组内存 ]
	{	  
		// [ 如果所要分配的数组内存大小不变，则保留原有数组内存 ]
		if( m_isAllocated == true && m_dimension == dimension && m_memory != NULL ) 
		{
			return;            // [ 函数返回 ]  
		}

		// [ 如果分配了内存，则释放内存 ]
		if( m_isAllocated == true )
		{
			delete [] m_memory;
		}
	
		// [ 初始化成员变量 ]
		m_memory      = NULL;  // [ 清空数据内存指针 ]
		m_isAllocated = false; // [ 表示没有分配内存 ]
		m_dimension   = 0 ;    // [ 数组维数归零 ]

		// [ 构造数组内容: 重新分配数组内存 ]
		if( dimension > 0 ) // [ 数组维数必须大于 0 ]
		{
			m_memory = new TYPE[ dimension ]; // [ 分配内存 ]

			if( m_memory != NULL ) // [ 判断内存分配是否成功 ]
			{
				m_isAllocated = true;      // [ 标志分配了内存 ]
				m_dimension   = dimension; // [ 设置数组维数 ]
			}
			else
			{
				Verification( "System Error << Can not allocate memory correctly >>" ); // [ 测试报告 ]
			}
		}
		else
		{
			Verification( "Program Error << Array dimension must be bigger than 0 >>" ); // [ 测试报告 ]
		}
	}

	void Construction( TYPE* memory, long dimension ) // [ 构造数组内容: 指派数组内存 ]
	{
		// [ 如果分配了内存，则释放内存 ]
		if( m_isAllocated == true )
		{
			delete [] m_memory;
		}
	
		// [ 初始化成员变量 ]
		m_memory      = NULL;  // [ 清空数据内存指针 ]
		m_isAllocated = false; // [ 表示没有分配内存 ]
		m_dimension   = 0 ;    // [ 数组维数归零 ]

		// [ 构造数组内容: 指派数组内存 ]
		if( memory != NULL && dimension > 0 ) // [ 参数有效性测试 ]
		{
			m_isAllocated = false;       // [ 表示没有分配内存 ]
			m_memory      = memory;      // [ 设置数组内存指针 ]
			m_dimension   = dimension;   // [ 设置数组维数 ]
		}
		else
		{
			Verification( "Program Error << The assigned array memory pointer can not be null, and array dimension must be bigger than 0 >>" ); // [ 测试报告 ]
		}
	}

	void Construction( const CTArray< TYPE >& array ) // [ 构造数组内容: 数组复制 ]
	{
		if( array.m_memory != NULL ) // [ 判断数组是否为空 ]
		{
			// [ 如果所要分配的数组内存大小不变，则保留原有数组内存 ]
		    if( m_isAllocated == true && m_dimension == array.m_dimension && m_memory != NULL ) 
			{
				long sizeInBytes = m_dimension * sizeof( TYPE ); // [ 数组内容所占字节数 ]
			    memcpy( m_memory, array.m_memory, sizeInBytes ); // [ 导入数组内容 ]

			    return; // [ 函数返回 ]  
			}

		    // [ 如果分配了内存，则释放内存 ]
		    if( m_isAllocated == true )
			{
			    delete [] m_memory;
			}
	
	  	    // [ 初始化成员变量 ]
	  	    m_memory      = NULL;  // [ 清空数据内存指针 ]
	 	    m_isAllocated = false; // [ 表示没有分配内存 ]
	 	    m_dimension   = 0 ;    // [ 数组维数归零 ]

	 	    // [ 构造数组内容: 重新分配数组内存 ]
			m_memory = new TYPE[ array.m_dimension ]; // [ 分配内存 ]

			if( m_memory != NULL ) // [ 判断内存分配是否成功 ]
			{
			    m_isAllocated = true;                // [ 标志分配了内存 ]
			    m_dimension   = array.m_dimension;   // [ 设置数组维数 ]

				long sizeInBytes = m_dimension * sizeof( TYPE ); // [ 数组内容所占字节数 ]
			    memcpy( m_memory, array.m_memory, sizeInBytes ); // [ 导入数组内容 ]		    
			}
			else
			{
			    Verification( "System Error << Can not allocate memory correctly >>" ); // [ 测试报告 ]
			}	
		}
		else
		{
	 	    // [ 如果分配了内存，则释放内存 ]
		    if( m_isAllocated == true )
			{
			    delete [] m_memory;
			}
	
	 	    // [ 初始化成员变量 ]
	        m_memory      = NULL;  // [ 清空数据内存指针 ]
	        m_isAllocated = false; // [ 表示没有分配内存 ]
	        m_dimension   = 0 ;    // [ 数组维数归零 ]
	    }
	}

	void Destruction()                                // [ 析构数组内容 ]
	{
		// [ 如果分配了内存，则释放内存 ]
		if( m_isAllocated == true )
		{
			delete [] m_memory;
		}
	
		// [ 初始化成员变量 ]
		m_memory      = NULL;  // [ 清空数据内存指针 ]
		m_isAllocated = false; // [ 表示没有分配内存 ]
		m_dimension   = 0 ;    // [ 数组维数归零 ]
	}

	void ImportFrom( const void* source )    // [ 导入数组内容 ]
	{
		if( m_memory != NULL && source != NULL ) // [ 校验数组非空 且 导入源数据非空 ]
		{
			long sizeInBytes = m_dimension * sizeof( TYPE ); // [ 数组内容所占字节数 ]
			memcpy( m_memory, source, sizeInBytes );         // [ 导入数组内容 ]
		}
	}

	void ExportTo( void* destination ) const // [ 导出数组内容 ]
	{
		if( m_memory != NULL && destination != NULL ) // [ 校验数组非空 且 导出目标数据非空 ]
		{
			long sizeInBytes = m_dimension * sizeof( TYPE ); // [ 数组内容所占字节数 ]
			memcpy( destination, m_memory, sizeInBytes );    // [ 导出数组内容 ]
		}
	}
	
	CTArray< TYPE >& operator= ( const CTArray< TYPE >& array )  // [ 复制赋值操作符 ]
	{
		if( array.m_memory != NULL ) // [ 判断数组是否为空 ]
		{
			// [ 如果所要分配的数组内存大小不变，则保留原有数组内存 ]
	  	    if( m_isAllocated == true && m_dimension == array.m_dimension && m_memory != NULL ) 
			{
				long sizeInBytes = m_dimension * sizeof( TYPE ); // [ 数组内容所占字节数 ]
			    memcpy( m_memory, array.m_memory, sizeInBytes ); // [ 导入数组内容 ]

		 	   return * this; // [ 返回当前对象 ]  
			}

	  	    // [ 如果分配了内存，则释放内存 ]
	   	    if( m_isAllocated == true )
			{
			    delete [] m_memory;
			}
	
	 	    // [ 初始化成员变量 ]
	  	    m_memory      = NULL;  // [ 清空数据内存指针 ]
	  	    m_isAllocated = false; // [ 表示没有分配内存 ]
	    	m_dimension   = 0 ;    // [ 数组维数归零 ]

	    	// [ 构造数组内容: 重新分配数组内存 ]
			m_memory = new TYPE[ array.m_dimension ]; // [ 分配内存 ]

			if( m_memory != NULL ) // [ 判断内存分配是否成功 ]
			{
			    m_isAllocated = true;                // [ 标志分配了内存 ]
			    m_dimension   = array.m_dimension;   // [ 设置数组维数 ]

				long sizeInBytes = m_dimension * sizeof( TYPE ); // [ 数组内容所占字节数 ]
			    memcpy( m_memory, array.m_memory, sizeInBytes ); // [ 导入数组内容 ]		    
			}
			else
			{
		 	    Verification( "System Error << Can not allocate memory correctly >>" ); // [ 测试报告 ]
			}		
		}
		else
		{
	    	// [ 如果分配了内存，则释放内存 ]
	   	    if( m_isAllocated == true )
			{
		    	delete [] m_memory;
			}
	
	    	// [ 初始化成员变量 ]
	   	    m_memory      = NULL;  // [ 清空数据内存指针 ]
	    	m_isAllocated = false; // [ 表示没有分配内存 ]
	    	m_dimension   = 0 ;    // [ 数组维数归零 ]
		}

		return * this; // [ 返回当前对象 ]
	}

	TYPE& operator[]( long index ) const                         // [ 下标操作符 ]
	{
#ifdef _DEBUG

		static TYPE error; // [ 出错返回的静态变量 ]

		if( !( index >= 0 && index <= ( m_dimension - 1 ) ) ) // [ 数组下标有效性测试 ]
		{
			Verification( "Program Error << Array subscript beyond bound >>" ); // [ 测试报告 ]

			return error; // [ 出错返回 ]
		}

#endif // _DEBUG

		return m_memory[ index ]; // [ 返回数组元素 ]
	}

	TYPE& operator()( long index ) const                         // [ 进行强制安全检查的下标操作符 ]
	{
		static TYPE error; // [ 出错返回的静态变量 ]

		if( !( index >= 0 && index <= ( m_dimension - 1 ) ) ) // [ 数组下标有效性测试 ]
		{
			return error; // [ 出错返回 ]
		}
		else
		{
			return m_memory[ index ]; // [ 返回数组元素 ]
		}
	}

	bool Is_index_valid( long index ) const                      // [ 数组索引是否正确 ]
	{
	    return index >= 0 && index < m_dimension; // [ 数组索引 ]
    }

	// [ ************ ] ..................................................
    // [ 状态参数函数 ] ..................................................
	// [ ************ ] ..................................................
public:
	bool IsNull() const         // [ 是否为空 ]
	{
	    return ( m_memory == NULL ); // [ 是否为空 ]
    }

	bool IsNotNull() const      // [ 是否不空 ]
	{
	    return ( m_memory != NULL ); // [ 是否不空 ]
    }

	long GetDimension() const   // [ 数组维数 ]
	{
	    return m_dimension; // [ 数组维数 ]
    }

	long GetUpperBound() const  // [ 数组上界 ]
	{
	    return ( m_dimension - 1 ); // [ 数组上界 ]
    }

	long GetSizeInBytes() const // [ 数组内容所占字节数 ]
	{
	    return ( m_dimension * sizeof( TYPE ) ); // [ 数组内容所占字节数 ]
    }

	// [ ************ ] ..................................................
	// [ 内部实现函数 ] ..................................................
	// [ ************ ] ..................................................
private:
	void Verification( CString message ) const // [ 测试报告 ]
	{
#ifdef _DEBUG

	    AfxMessageBox( message ); // [ 测试报告 ]

#endif // _DEBUG
    }

};

// [ ******************************************************************* ]
// [ ************* << 模板类 CTStack 用于栈的管理和操作 >> ************* ]
// [ ******************************************************************* ]

template <class TYPE> class CTStack
{
	// [ ******** ] ......................................................
	// [ 成员变量 ] ......................................................
	// [ ******** ] ......................................................
private:
	CTArray< TYPE > m_array_of_elements; // [ 用于存放栈元素的数组 ]
	long m_index_of_top;                 // [ 指示栈顶元素在数组中的当前位置 ]
	                                     // [ 如果 m_index_of_top 等于 -1 ，则表示栈为空。如果 m_index_of_top ]
	                                     // [ 大于等于 0 且 小于 m_array_of_elements 的维数，则表示栈中有元素 ]                                   ]

	// [ ************** ] ................................................
	// [ 构造和析构函数 ] ................................................
	// [ ************** ] ................................................
public:
	CTStack(void) // [ 构造函数 ]
	{
	    m_index_of_top = -1 ;  // [ 设置栈为空 ]
	    Reset_stack( 100 ); // [ 栈元素数组缺省大小为 100 ]
    }

	CTStack( long maximum_of_elements ) // [ 指定栈元素数组大小的构造函数 ]
	{
	    m_index_of_top = -1 ;        // [ 设置栈为空 ]
	    Reset_stack( maximum_of_elements ); // [ 根据指定的大小对栈元素数组进行分配空间 ]
    }

	~CTStack(void) // [ 析构函数 ]
	{
	    m_array_of_elements.Destruction(); // [ 释放栈元素数组的空间。(可以不显式释放空间，因为程序会自动释放空间) ]
    }

	// [ ************ ] ..................................................
	// [ 功能接口函数 ] ..................................................
	// [ ************ ] ..................................................
public:
	const TYPE& Push( const TYPE& element ) // [ 将元素压栈，并返回入栈元素。当栈满时，取消操作，并提示 "栈溢出" 出错信息 ]
    {
		if( !Is_full() ) // [ 如果栈非满时，将栈顶指针上移一个元素，并赋值以压栈元素 ]
		{
			m_array_of_elements[ ++m_index_of_top ] = element;
		}
		else // [ 如果栈满时，提示 "栈溢出" 出错信息 ]
		{
			Verification( "Fatal Error: Overfall of Stack!" );
		}
	
		return element;// [ 返回入栈元素 ]
	}

	const TYPE& Pop( )                      // [ 将元素弹栈，并返回出栈元素。当栈空时，取消操作 ]
	{
		static TYPE error; // [ 出错时返回值 ]

		if( !Is_empty() ) // [ 如果栈非空时，返回栈顶元素，并将栈顶指针下移一个元素 ]
		{
			return m_array_of_elements[ m_index_of_top-- ];
		}
		else // [ 如果栈为空时，则取消操作 ]	
		{
			return error;// [ 出错返回 ]
		}
	}

	BOOL Is_empty( ) const // [ 判断栈是否为空。如果为空，则返回 TRUE ，否则返回 FALSE ]
	{
	    return ( m_index_of_top == -1 );// [ 如果 m_index_of_top 为 -1 ，则表示栈为空，否则非空 ]
    }

	BOOL Is_full( ) const  // [ 判断栈是否已满。如果已满，则返回 TRUE ，否则返回 FALSE ]
	{
	    return ( m_index_of_top == m_array_of_elements.GetUpperBound() ); // [ 如果 m_index_of_top 等于栈元素数组的上界，则返回 TRUE ，否则返回 FALSE ]
    }

	const TYPE& Get_element_of_top( ) const               // [ 获取栈顶元素 ]
	{
		static TYPE error; // [ 出错时返回值 ]

		if( !Is_empty() ) // [ 如果栈非空时，返回栈顶元素 ]
		{
			return m_array_of_elements[ m_index_of_top ];
		}
		else // [ 如果栈为空时，则取消操作 ]	
		{	
			return error;// [ 出错返回 ]
		}
	}

	const TYPE& Set_element_of_top( const TYPE& element ) // [ 设置栈顶元素 ]
	{
		if ( !Is_empty() ) // [ 只有当栈非空时，才进行设置栈顶元素 ]
		{
			m_array_of_elements[ m_index_of_top ] = element ;// [ 设置栈顶元素 ]
		}

		return element;// [ 正常返回 ]
	}

	long Get_number_of_elements( ) const  // [ 获取当前栈中元素的个数 ]
	{
	    return ( m_index_of_top + 1 );// [ 当前栈中元素的个数等于栈顶指针 m_index_of_top 加 1  ]
    }

    long Get_maximum_of_elements( ) const // [ 获取栈元素数组的大小 ]
	{
	    return m_array_of_elements.GetDimension() ;// [ 返回栈元素数组的大小 ]
    }

	BOOL Reset_stack( long maximum_of_elements ) // [ 重新设置栈元素数组的大小。注意：此操作将摧毁所有原来的数据!!! ]
	                                              // [ 只有在栈为空的时候，此操作才生效，否则，系统会提示出错信息    ]
    {	
		if( Is_empty() && maximum_of_elements > 0 ) // [ 如果栈为空，则对栈元素数组进行重新分配 ]
		{
			m_array_of_elements.Construction( maximum_of_elements );// [ 对栈元素数组重新分配空间 ]

			return TRUE;// [ 正常返回 ]
		}
		else// [ 如果栈非空，则进行出错控制 ]
		{
			Verification( "ERROR: Can not reallocate the stack!" );

			return FALSE;//[ 出错返回 ]
		}
	}

	// [ ************ ] ..................................................
	// [ 内部实现函数 ] ..................................................
	// [ ************ ] ..................................................
private:
	void Verification( CString message ) const // [ 测试报告 ]
	{
#ifdef _DEBUG

	    AfxMessageBox( message ); // [ 测试报告 ]

#endif // _DEBUG
    }

};

#endif // !defined(AFX_TARRAY_H__5C18C5F4_170D_4D56_BFDA_B5173B41596D__INCLUDED_)
