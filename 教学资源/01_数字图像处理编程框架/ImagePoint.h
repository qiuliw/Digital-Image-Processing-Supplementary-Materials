// ImagePoint.h: interface for the CImagePoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEPOINT_H__03F4A380_1FEC_473F_9862_D8354A51BF01__INCLUDED_)
#define AFX_IMAGEPOINT_H__03F4A380_1FEC_473F_9862_D8354A51BF01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// [ ******************************************************************* ]
// [ ************************ << ͼ������� >> ************************* ]
// [ ******************************************************************* ]

class CImagePoint  
{
	// [ ******** ] ......................................................
	// [ ��Ա���� ] ......................................................
	// [ ******** ] ......................................................
public:
	long m_row;    // [ ������ ]
	long m_column; // [ ������ ]

	// [ ************** ] ................................................
	// [ ������������� ] ................................................
	// [ ************** ] ................................................
public:
	CImagePoint();                        // [ ���캯�� ]
	CImagePoint( long row, long column ); // [ ��ʼ�����캯�� ]
	virtual ~CImagePoint();               // [ �������� ]

	// [ ************ ] ..................................................
	// [ ���ܽӿں��� ] ..................................................
	// [ ************ ] ..................................................
public:
	bool operator==( CImagePoint point ) const; // [ �Ⱥ����� ]
	bool operator!=( CImagePoint point ) const; // [ ���Ⱥ����� ]

	CImagePoint operator+( CImagePoint point ) const; // [ �Ӻ����� ]
	CImagePoint operator-( CImagePoint point ) const; // [ �������� ]
	
	void operator+=( CImagePoint point ); // [ �ӵ��ں����� ]
	void operator-=( CImagePoint point ); // [ �����ں����� ]

	bool Is_in_rectangle( RECT rect ) const; // [ �жϵ������Ƿ��ھ�����( �����ھ��ε��������� ) ]

};

#endif // !defined(AFX_IMAGEPOINT_H__03F4A380_1FEC_473F_9862_D8354A51BF01__INCLUDED_)
