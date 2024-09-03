// ImagePoint.h: interface for the CImagePoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEPOINT_H__03F4A380_1FEC_473F_9862_D8354A51BF01__INCLUDED_)
#define AFX_IMAGEPOINT_H__03F4A380_1FEC_473F_9862_D8354A51BF01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// [ ******************************************************************* ]
// [ ************************ << 图像点坐标 >> ************************* ]
// [ ******************************************************************* ]

class CImagePoint  
{
	// [ ******** ] ......................................................
	// [ 成员变量 ] ......................................................
	// [ ******** ] ......................................................
public:
	long m_row;    // [ 行坐标 ]
	long m_column; // [ 列坐标 ]

	// [ ************** ] ................................................
	// [ 构造和析构函数 ] ................................................
	// [ ************** ] ................................................
public:
	CImagePoint();                        // [ 构造函数 ]
	CImagePoint( long row, long column ); // [ 初始化构造函数 ]
	virtual ~CImagePoint();               // [ 析构函数 ]

	// [ ************ ] ..................................................
	// [ 功能接口函数 ] ..................................................
	// [ ************ ] ..................................................
public:
	bool operator==( CImagePoint point ) const; // [ 等号重载 ]
	bool operator!=( CImagePoint point ) const; // [ 不等号重载 ]

	CImagePoint operator+( CImagePoint point ) const; // [ 加号重载 ]
	CImagePoint operator-( CImagePoint point ) const; // [ 减号重载 ]
	
	void operator+=( CImagePoint point ); // [ 加等于号重载 ]
	void operator-=( CImagePoint point ); // [ 减等于号重载 ]

	bool Is_in_rectangle( RECT rect ) const; // [ 判断点坐标是否在矩形内( 包括在矩形的四条边上 ) ]

};

#endif // !defined(AFX_IMAGEPOINT_H__03F4A380_1FEC_473F_9862_D8354A51BF01__INCLUDED_)
