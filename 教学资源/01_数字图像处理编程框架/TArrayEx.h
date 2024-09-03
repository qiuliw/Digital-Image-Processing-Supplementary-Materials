// TArrayEx.h: interface for the CTArrayEx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TARRAYEX_H__35721324_67E3_43FE_9391_F369F8DB07E8__INCLUDED_)
#define AFX_TARRAYEX_H__35721324_67E3_43FE_9391_F369F8DB07E8__INCLUDED_

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
// [ ********************* << 一维数组模板扩展 >> ********************** ]
// [ ******************************************************************* ]

template <class TYPE> class CTArrayEx  
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
	CTArrayEx()                                     // [ 构造函数: 缺省构造函数 ]
	{
	    Initialization(); // [ 初始化成员变量 ]
    }

	CTArrayEx( long dimension )                     // [ 构造函数: 分配数组内存 ]
	{
	    Initialization(); // [ 初始化成员变量 ]

	    Construction( dimension ); // [ 构造数组内容: 分配数组内存 ]
    }

	CTArrayEx( TYPE* memory, long dimension )       // [ 构造函数: 指派数组内存 ]
	{
	    Initialization(); // [ 初始化成员变量 ]

	    Construction( memory, dimension ); // [ 构造数组内容: 指派数组内存 ]
    }

	CTArrayEx( const CTArrayEx< TYPE >& array )     // [ 复制构造函数 ]
	{
	    Initialization(); // [ 初始化成员变量 ]

	    Construction( array ); // [ 构造数组内容: 数组复制 ]
    }

	~CTArrayEx()                                    // [ 析构函数 ]
	{
	    Destruction();    // [ 析构数组内容 ]
    }

	// [ ************ ] ..................................................
	// [ 功能接口函数 ] ..................................................
	// [ ************ ] ..................................................
public:
	void Construction( long dimension )                     // [ 构造数组内容: 分配数组内存 ]
	{
		if( m_isAllocated == true && m_dimension == dimension && m_memory != NULL ) // [ 如果所要分配的数组内存大小不变，则保留原有数组内存 ]                            
			return; 

		Destruction(); // [ 析构数组内容 ]

		if( dimension > 0 ) // [ 数组维数必须大于 0 ]
		{
			m_memory = new TYPE[ dimension ]; // [ 分配内存 ]

			if( m_memory != NULL ) // [ 判断内存分配是否成功 ]
			{
				m_isAllocated = true; // [ 标志分配了内存 ]
				m_dimension = dimension; // [ 设置数组维数 ]
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

	void Construction( TYPE* memory, long dimension )       // [ 构造数组内容: 指派数组内存 ]
	{
		Destruction(); // [ 析构数组内容 ]

		if( memory != NULL && dimension > 0 ) // [ 参数有效性测试 ]
		{
			m_memory = memory; // [ 设置数组内存指针 ]
			m_dimension = dimension; // [ 设置数组维数 ]
		}
		else
		{
			Verification( "Program Error << The assigned array memory pointer can not be null, and array dimension must be bigger than 0 >>" ); // [ 测试报告 ]
		}
	}

	void Construction( const CTArrayEx< TYPE >& array )     // [ 构造数组内容: 数组复制 ]
	{
		if( array.m_memory != NULL ) // [ 判断数组是否为空 ]
		{
			Construction( array.m_dimension ); // [ 构造相同维数的数组: 分配数组内存 ]

			for( int index = 0; index < m_dimension; index++ ) // [ 逐个复制数组元素 ]
			{
				m_memory[ index ] = array.m_memory[ index ]; // [ 复制数组元素 ]
			}
		}
		else
		{
			Destruction(); // [ 析构数组内容 ]
		}
	}

	void Destruction()                                      // [ 析构数组内容 ]
	{
		// [ 如果分配了内存，则释放内存 ]
		if( m_isAllocated == true )
		{
			delete [] m_memory;
		}
	
		// [ 初始化成员变量 ]
		Initialization( ); 
	}

	CTArrayEx< TYPE >& operator=( const CTArrayEx< TYPE >& array )  // [ 赋值操作符 ]
	{
	    Construction( array ); // [ 构造数组内容: 数组复制 ]

	    return * this; // [ 返回当前对象 ]
    }

	TYPE& operator[]( long index ) const                            // [ 下标操作符 ]
	{
#ifdef _DEBUG

		static TYPE error; // [ 出错返回的静态变量 ]

		if( !( index >=0 && index < m_dimension ) ) // [ 数组下标有效性测试 ]
		{
			Verification( "Program Error << Array subscript beyond bound >>" ); // [ 测试报告 ]

			return error; // [ 出错返回 ]
		}

#endif // _DEBUG

		return m_memory[ index ]; // [ 返回数组元素 ]
	}

	bool Is_index_valid( long index ) const // [ 数组索引是否正确 ]
	{
	    return index >= 0 && index < m_dimension; // [ 数组索引 ]
    }

	// [ ************ ] ..................................................
    // [ 状态参数函数 ] ..................................................
	// [ ************ ] ..................................................
public:
	bool IsNull() const         // [ 是否为空 ]
	{
	    return ( m_memory == NULL );
    }

	bool IsNotNull() const      // [ 是否不空 ]
	{
	    return ( m_memory != NULL );
    }

	long GetDimension() const   // [ 数组维数 ]
	{
	    return m_dimension;
    }

	long GetUpperBound() const  // [ 数组上界 ]
	{
	    return ( m_dimension - 1 );
    }

	long GetSizeInBytes() const // [ 数组内容所占字节数 ]
	{
	    return ( m_dimension * sizeof( TYPE ) );
    }

	// [ ************ ] ..................................................
	// [ 内部实现函数 ] ..................................................
	// [ ************ ] ..................................................
private:
	void Initialization() // [ 初始化成员变量 ]
	{
		m_memory = NULL;       // [ 清空数据内存指针 ]
		m_isAllocated = false; // [ 表示没有分配内存 ]
		m_dimension = 0 ;      // [ 数组维数归零 ]

		// [ *************************************************************** ]
		// [ 成员变量初始化( Initialization )后, 成员变量遵守如下规则:       ]
		// [     1. 如果分配了内存( m_isAllocated == true ), 则内存指针不能  ]
		// [             为空( m_memory != NULL ) , 且数组维数必须大于 0     ]
		// [             ( m_dimension > 0 ) 。                              ]
		// [     2. 如果没有分配内存( m_isAllocated == false ), 且内存指针不 ]
		// [             空( m_memory != NULL ), 说明指派了数组内存，则数组  ]
		// [             维数必须大于 0 ( m_dimension > 0 ) 。               ]
		// [     3. 如果没有分配内存( m_isAllocated == false ), 且内存指针为 ]
		// [             空( m_memory == NULL ), 则数组维数必须为 0          ]
		// [             ( m_dimension == 0 ) 。                             ]
		// [ *************************************************************** ]
	}

	void Verification( CString message ) const // [ 测试报告 ]
	{
#ifdef _DEBUG

	    AfxMessageBox( message ); // [ 测试报告 ]

#endif // _DEBUG
    }

};

#endif // !defined(AFX_TARRAYEX_H__35721324_67E3_43FE_9391_F369F8DB07E8__INCLUDED_)
