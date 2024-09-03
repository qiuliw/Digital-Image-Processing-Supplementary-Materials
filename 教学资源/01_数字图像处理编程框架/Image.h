// Image.h: interface for the CImage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGE_H__377F5446_CBF5_4179_8D56_463F20CD3A86__INCLUDED_)
#define AFX_IMAGE_H__377F5446_CBF5_4179_8D56_463F20CD3A86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Include.h"
#include "TMatrix.h"

// [ ******************************************************************* ]
// [ ************************** << ͼ���� >> *************************** ] 
// [ ******************************************************************* ]

class CImage  
{
	// [ ******** ] ......................................................
	// [ �ڲ����� ] ......................................................
	// [ ******** ] ......................................................
public:
    enum ImageType{ Color, Gray, Unicolor, NoImage }; // [ ͼ������ ]

	// [ ******** ] ......................................................
	// [ ��Ա���� ] ......................................................
	// [ ******** ] ......................................................
private:
	ImageType              m_imageType;     // [ ͼ������ ]
	CTMatrix< RGB_TRIPLE > m_colorImage;    // [ ��ɫͼ������ ]
	CTMatrix< BYTE >       m_grayImage;     // [ �Ҷ�ͼ������ ]
	CTMatrix< BlackWhite>  m_unicolorImage; // [ ��ֵͼ������ ]

	// [ ****************** ] ............................................
	// [ ���캯������������ ] ............................................
	// [ ****************** ] ............................................
public:
	CImage();                      // [ ȱʡ���캯�� ]
	CImage( const CImage& image ); // [ ���ƹ��캯�� ]
	virtual ~CImage();             // [ �������� ]

	// [ ************ ] ..................................................
	// [ ���ܽӿں��� ] ..................................................
	// [ ************ ] ..................................................
public:
	void ImportFrom( const CString& fileName );                      // [ ����ͼ���ļ� ]
	void ImportFrom( const CImage& image );                          // [ ����ͼ������ ]
	void ImportFrom( const CTMatrix< RGB_TRIPLE >& color_image );    // [ �����ɫͼ������ ]
	void ImportFrom( const CTMatrix< BYTE >& gray_image );           // [ ����Ҷ�ͼ������ ]
	void ImportFrom( const CTMatrix< BlackWhite >& unicolor_image ); // [ �����ֵͼ������ ]	
	void ImportFrom( CBitmap& bitmap );                              // [ �����豸���λͼ ]
	void ImportFrom( HANDLE hDIB );                                  // [ �����豸�޹�λͼ ]

	CImage& operator= ( const CImage& image ); // [ ���ظ�ֵ������ ]

	void   ShowImage( CDC* pDC, CPoint leftTop, CSize displaySize = CSize( 0, 0 ) ) const; // [ ��ʾͼ�� ]
	void   SaveImage( const CString& fileName, int jpeg_quality = 100 ) const;             // [ ����ͼ�� ]

	static void ShowImage( const CTMatrix< RGB_TRIPLE >& colorImage, 
		                   CDC* pDC, CPoint leftTop, CSize displaySize = CSize( 0, 0 ) ); // [ ��ʾ��ɫͼ�� ]
	static void ShowImage( const CTMatrix< BYTE >& grayImage, 
		                   CDC* pDC, CPoint leftTop, CSize displaySize = CSize( 0, 0 ) ); // [ ��ʾ�Ҷ�ͼ�� ]
	static void ShowImage( const CTMatrix< BlackWhite >& unicolorImage, 
		                   CDC* pDC, CPoint leftTop, CSize displaySize = CSize( 0, 0 ) ); // [ ��ʾ��ֵͼ�� ]

	static void SaveImage( const CTMatrix< RGB_TRIPLE >& colorImage, const CString& fileName, int jpeg_quality ) ;   // [ �����ɫͼ�� ]
	static void SaveImage( const CTMatrix< BYTE >& grayImage, const CString& fileName, int jpeg_quality ) ;          // [ ����Ҷ�ͼ�� ] 
	static void SaveImage( const CTMatrix< BlackWhite >& unicolorImage, const CString& fileName ); // [ �����ֵͼ�� ]

	// [ ************ ] ..................................................
	// [ ״̬�������� ] ..................................................
	// [ ************ ] ..................................................
public:
	ImageType GetImageType() const; // [ ͼ������ ]

	bool IsColorImage() const;      // [ �Ƿ��ǲ�ɫͼ�� ]
	bool IsGrayImage() const;       // [ �Ƿ��ǻҶ�ͼ�� ]
	bool IsUnicolorImage() const;   // [ �Ƿ��Ƕ�ֵͼ�� ]
	bool IsNull() const;            // [ �Ƿ�Ϊ�� ]

	const CTMatrix< RGB_TRIPLE >& Get_color_image() const;    // [ ��ɫͼ������ ]
	const CTMatrix< BYTE >& Get_gray_image() const;           // [ �Ҷ�ͼ������ ]
	const CTMatrix< BlackWhite >& Get_unicolor_image() const; // [ ��ֵͼ������ ]

	long        Get_image_height() const; // [ ͼ��߶� ]
	long        Get_image_width() const;  // [ ͼ���� ] 
	CImagePoint Get_image_size() const;   // [ ͼ��ߴ� ]

	// [ ************ ] ..................................................
	// [ �ڲ�ʵ�ֺ��� ] ..................................................
	// [ ************ ] ..................................................
private:
	static CString PostfixToFileName( const CString& fileName );                          // [ ��ȡ�ļ�����׺ ]

	void ImportFromBmpFile( const CString& fileName );                                    // [ ���� BMP ͼ���ļ� ]
	void ImportFrom_32_BmpFile( BYTE* bitmapData, bool isBottomUp,
		                        long imageHeight, long imageWidth, 
								long bytesPerMemoryRow, long bytesPerFileRow );           // [ ���� 32 λ BMP ͼ������ ]
    void ImportFrom_24_BmpFile( BYTE* bitmapData, bool isBottomUp,
		                        long imageHeight, long imageWidth, 
								long bytesPerMemoryRow, long bytesPerFileRow );           // [ ���� 24 λ BMP ͼ������ ]
	void ImportFrom_8_BmpFile( BYTE* bitmapData, RGBQUAD* colorTemplate, bool isBottomUp,
		                       long imageHeight, long imageWidth,
							   long bytesPerMemoryRow, long bytesPerFileRow );            // [ ���� 8 λ BMP ͼ������ ]
	void ImportFrom_1_BmpFile( BYTE* bitmapData, RGBQUAD* colorTemplate, bool isBottomUp,
		                       long imageHeight, long imageWidth,
							   long bytesPerMemoryRow, long bytesPerFileRow );            // [ ���� 1 λ BMP ͼ������ ]

	void Import_from_raw_file( const CString& file_name );                                // [ ���� RAW ͼ���ļ� ]

	HANDLE DDBToDIB( CBitmap& bitmap, DWORD dwCompression, CPalette* pPal );              // [ �豸���λͼת��Ϊ�豸�޹�λͼ ]

	static void SaveImageToBmpFile( const CTMatrix< RGB_TRIPLE >& colorImage, const CString& fileName );    // [ �����ɫͼ��Ϊ BMP �ļ� ]
	static void SaveImageToBmpFile( const CTMatrix< BYTE >& grayImage, const CString& fileName );           // [ ����Ҷ�ͼ��Ϊ BMP �ļ� ]
	static void SaveImageToBmpFile( const CTMatrix< BlackWhite >& unicolorImage, const CString& fileName ); // [ �����ֵͼ��Ϊ BMP �ļ� ]

	static void SaveImageToJpegFile( const CTMatrix< RGB_TRIPLE >& colorImage, const CString& fileName, int jpeg_quality ); // [ �����ɫͼ��Ϊ JPEG �ļ� ]
	static void SaveImageToJpegFile( const CTMatrix< BYTE >& grayImage, const CString& fileName, int jpeg_quality );        // [ ����Ҷ�ͼ��Ϊ JPEG �ļ� ]

	static void Construct_1_Info( BITMAPINFO* bitmapInfo, long imageHeight, long imageWidth );              // [ ���� 1 λ��Ϣ ]
	static void Construct_1_FileHeader( BITMAPFILEHEADER* fileHeader, long imageHeight, long imageWidth );  // [ ���� 1 λ�ļ�ͷ ]

	static void Construct_8_Info( BITMAPINFO* bitmapInfo, long imageHeight, long imageWidth );              // [ ���� 8 λ��Ϣ ]
	static void Construct_8_FileHeader( BITMAPFILEHEADER* fileHeader, long imageHeight, long imageWidth );  // [ ���� 8 λ�ļ�ͷ ]

	static void Construct_24_Info( BITMAPINFO* bitmapInfo, long imageHeight, long imageWidth );             // [ ���� 24 λ��Ϣ ]
	static void Construct_24_FileHeader( BITMAPFILEHEADER* fileHeader, long imageHeight, long imageWidth ); // [ ���� 24 λ�ļ�ͷ ]

	static void Construct_32_Info( BITMAPINFO* bitmapInfo, long imageHeight, long imageWidth );             // [ ���� 32 λ��Ϣ ]

};

#endif // !defined(AFX_IMAGE_H__377F5446_CBF5_4179_8D56_463F20CD3A86__INCLUDED_)
