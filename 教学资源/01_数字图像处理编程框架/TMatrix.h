// TMatrix.h: interface for the CTMatrix class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TMATRIX_H__D0F25BB1_AE4C_42ED_BFD4_89FECA42E86A__INCLUDED_)
#define AFX_TMATRIX_H__D0F25BB1_AE4C_42ED_BFD4_89FECA42E86A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TArray.h"
#include "ImagePoint.h"

// [ ******************************************************************* ]
// [ ģ���� CTMatrix< TYPE > �� CTMatrixEx< TYPE > ����������:           ]
// [        �ڹ����������( ������ )����( Construction )�н��о����� ]
// [        ʱ, CTMatrix �����������ڴ�Ŀ���, CTMatrixEx ���������Ԫ�� ]
// [        �Ŀ���.                                                      ]
// [ ����˵��: CTMatrix �е� TYPE �ǲ����ڶ�̬�����ڴ����������, ������ ]
// [               ������������( �� int, double �� )�� struct ���� �Լ�  ]
// [               class ����( �� CPoint �� ).                           ]
// [           CTMatrixEx �е� TYPE ����Ǵ��ڶ�̬�����ڴ����������, �� ]
// [               �� struct ���ͺ� class ����( �� CString �� )��        ]
// [           CTMatrixEx �������е���������, �������ٶ���; CTMatrix ֻ  ]
// [               ���ò����ڶ�̬�����ڴ����������, �������ٶȿ�.       ]
// [           ����˵, CTMatrixEx �� CTMatrix ����չ, �� CTMatrix ��     ]
// [               CTMatrixEx ������.                                    ]
// [ ******************************************************************* ]

// [ ******************************************************************* ]
// [ *********************** << ��ά����ģ�� >> ************************ ]
// [ ******************************************************************* ]

template <class TYPE> class CTMatrix  
{
	// [ ******** ] ......................................................
    // [ ��Ա���� ] ......................................................
	// [ ******** ] ......................................................
private:
	TYPE* m_memory;  // [ ���������ڴ�ָ�� ]
	long  m_rows;    // [ ��������� ]
	long  m_columns; // [ ��������� ]

	// [ ****************** ] ............................................
	// [ ���캯������������ ] ............................................
	// [ ****************** ] ............................................
public:
	CTMatrix()                                  // [ ���캯��: ȱʡ���캯�� ]
	{
	    Initialization(); // [ ��ʼ����Ա���� ]
    }

	CTMatrix( long rows, long columns )         // [ ���캯��: ��������ڴ� ]
	{
	    Initialization(); // [ ��ʼ����Ա���� ]

	    Construction( rows, columns ); // [ �����������: ��������ڴ� ]
    }

	CTMatrix( const CTMatrix< TYPE >& matrix )  // [ ���ƹ��캯�� ]
	{
	    Initialization(); // [ ��ʼ����Ա���� ]

	    Construction( matrix ); // [ �����������: ������ ]
    }

	~CTMatrix()                                 // [ �������� ]
	{
	    Destruction( ); // [ ������������ ]
    }

	// [ ************ ] ..................................................
	// [ ���ܽӿں��� ] ..................................................
	// [ ************ ] ..................................................
public:
	void Construction( long rows, long columns )        // [ �����������: ��������ڴ� ]
	{
		if( m_rows == rows && m_columns == columns && m_memory != NULL ) // [ �����Ҫ����ľ����ڴ��С���䣬����ԭ�о����ڴ� ]
			return ;

		Destruction( ); // [ ������������ ]

		if( rows > 0 && columns > 0 ) // [ ����������������������� 0 ]
		{
			long elements = rows * columns ; // [ ����Ԫ�ظ��� ]

			m_memory = new TYPE[ elements ]; // [ �����ڴ� ]

			if( m_memory != NULL ) // [ �жϷ����ڴ��Ƿ�ɹ� ]
			{
				m_rows = rows; // [ ���þ������� ]
				m_columns = columns; // [ ���þ������� ]
			}
			else
			{
				Verification( "System Error << Can not allocate memory correctly >>" ); // [ ���Ա��� ]
			}
		}
		else
		{
			Verification( "Program Error << Matrix rows and columns must be bigger than 0 >>" ); // [ ���Ա��� ]
		}
	}

	void Construction( const CTMatrix< TYPE >& matrix ) // [ �����������: ������ ]
	{
		if( matrix.m_memory != NULL ) // [ �жϾ��������Ƿ�Ϊ�� ]
		{
			Construction( matrix.m_rows, matrix.m_columns ); // [ ������ͬ�ߴ�ľ���: ��������ڴ� ]

			long sizeInBytes = m_rows * m_columns * sizeof( TYPE ); // [ ����������ռ�ֽ��� ]
			memcpy( m_memory, matrix.m_memory, sizeInBytes ); // [ ���ƾ������� ]
		}
		else
		{
			Destruction( ); // [ ������������ ]
		}
	}

	void Destruction()                                  // [ ������������ ]
	{
		if( m_memory != NULL ) // [ �ж��Ƿ�������ڴ� ]
		{
			delete [] m_memory; // [ �ͷ��ڴ� ]

			Initialization( ); // [ ��ʼ����Ա���� ]
		}
	}     

	void ImportFrom( const void* source )    // [ ����������� ]
	{
	    if( m_memory != NULL ) // [ �жϾ����Ƿ�Ϊ�� ]
	    {
		    long sizeInBytes = m_rows * m_columns * sizeof( TYPE ); // [ ����������ռ�ֽ��� ]
		    memcpy( m_memory, source, sizeInBytes ); // [ ����������� ]
    	}
    }

	void ExportTo( void* destination ) const // [ ������������ ]
	{
		if( m_memory != NULL ) // [ �жϾ����Ƿ�Ϊ�� ]
		{
			long sizeInBytes = m_rows * m_columns * sizeof( TYPE ); // [ ����������ռ�ֽ��� ]
			memcpy( destination, m_memory, sizeInBytes ); // [ ������������ ] 
		}
	}

	CTMatrix< TYPE >& operator=( const CTMatrix< TYPE >& matrix )  // [ ��ֵ������ ]
	{
	    Construction( matrix ); // [ �����������: ������ ]

	    return * this; // [ ���ص�ǰ���� ]
    }

#ifdef _DEBUG
	CTArray< TYPE >& operator[]( long index ) const                // [ �±������ ]
	{
    	static CTArray< TYPE > error; // [ �����صľ�̬���� ]

		if( !( index >= 0 && index < m_rows ) ) // [ �����ж�λ��Ч�Բ��� ]
		{
			Verification( "Program Error << Matrix row index beyond bound >>" ); // [ ���Ա��� ]

			return error; // [ ������ ]
		}

		static CTArray< TYPE > rowArray; // [ ���������� ]

		rowArray.Construction( m_memory + index * m_columns, m_columns ); // [ ������������: ָ�������ڴ� ]

		return rowArray; // [ ���ؾ��������� ]
	}

#else // _DEBUG
	TYPE*            operator[]( long index ) const                // [ �±������ ]
	{
	    return m_memory + index * m_columns; // [ ���ؾ����������ַ ]
    }

#endif // _DEBUG

	TYPE&            operator[]( const CImagePoint& point ) const  // [ �±������ ]
	{
#ifdef _DEBUG

	    return ( *this )[ point.m_row ][ point.m_column ] ;

#else // _DEBUG

	    return *( m_memory + point.m_row * m_columns + point.m_column );

#endif // _DEBUG
    }

	bool Is_point_valid( const CImagePoint& point ) const // [ �������Ƿ���ȷ ]
	{
	    return point.m_row    >= 0 && point.m_row    < m_rows     // [ ������ ]
		    && point.m_column >= 0 && point.m_column < m_columns; // [ ������ ]
    }

	bool Is_row_valid( long row ) const                   // [ �������Ƿ���ȷ ]
	{
	    return row >= 0 && row < m_rows; // [ ������ ]
    }

	bool Is_column_valid( long column ) const             // [ �������Ƿ���ȷ ]
	{
	    return column >= 0 && column < m_columns; // [ ������ ]
    }

	// [ ************ ] ..................................................
    // [ ״̬�������� ] ..................................................
	// [ ************ ] ..................................................
public:
	bool IsNull() const              // [ �Ƿ�Ϊ�� ]
	{
	    return ( m_memory == NULL );
    } 

	bool IsNotNull() const           // [ �Ƿ񲻿� ]
	{
	    return ( m_memory != NULL );
    }

	long GetRows() const             // [ �������� ]
	{
	    return m_rows;
    }

	long GetColumns() const          // [ �������� ]
	{
	    return m_columns;
    }

	long Get_height() const          // [ ����߶�( �������� ) ]
	{
	    return m_rows;
    }

	long Get_width() const           // [ ������( �������� ) ]
	{
	    return m_columns;
    }

	long GetRowUpperBound() const    // [ �������Ͻ� ]
	{
	    return ( m_rows - 1 );
    }

	long GetColumnUpperBound() const // [ �������Ͻ� ]
	{
	    return ( m_columns - 1 );
    }

	long GetElements() const         // [ ����Ԫ�ظ��� ]
	{
	    return ( m_rows * m_columns );
    }

	long GetSizeInBytes() const      // [ ����������ռ�ֽ��� ]
	{
	    return ( m_rows * m_columns * sizeof( TYPE ) );
    }

	CImagePoint Get_size() const     // [ ����ߴ�( �������������� ) ]
	{
	    return CImagePoint( m_rows, m_columns );
    }

	// [ ************ ] ..................................................
	// [ �ڲ�ʵ�ֺ��� ] ..................................................
	// [ ************ ] ..................................................
private:
	void Initialization() // [ ��ʼ����Ա���� ]
	{
		m_memory = NULL; // [ �����ڴ�ָ����� ]
		m_rows = 0;      // [ ������������ ]
		m_columns = 0;   // [ ������������ ]

		// [ *************************************************************** ]
		// [ ��ʼ����Ա����( Initialization )��, ��Ա�����������¹���:       ]
		// [     1. ��������ڴ�ָ�벻��( m_memory != NULL ), ������������� ]
		// [        ������Ϊ��( m_rows > 0 && m_columns > 0 ).               ]
		// [     2. ��������ڴ�ָ��Ϊ��( m_memory == NULL ), ������������� ]
		// [        ����Ϊ��( m_rows == 0 && m_columns == 0 ).               ]
		// [     3. ��������������Ҫô��Ϊ�㣬Ҫô����Ϊ��.                  ]
		// [ *************************************************************** ]
	} 

	void Verification( CString message ) const // [ ���Ա��� ]
	{
#ifdef _DEBUG

	    AfxMessageBox( message ); // [ ���Ա��� ]

#endif // _DEBUG
    }

};

#endif // !defined(AFX_TMATRIX_H__D0F25BB1_AE4C_42ED_BFD4_89FECA42E86A__INCLUDED_)
