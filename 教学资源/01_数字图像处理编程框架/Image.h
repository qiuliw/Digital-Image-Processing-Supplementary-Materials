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
// [ ************************** << 图像类 >> *************************** ] 
// [ ******************************************************************* ]

class CImage  
{
	// [ ******** ] ......................................................
	// [ 内部类型 ] ......................................................
	// [ ******** ] ......................................................
public:
    enum ImageType{ Color, Gray, Unicolor, NoImage }; // [ 图像类型 ]

	// [ ******** ] ......................................................
	// [ 成员变量 ] ......................................................
	// [ ******** ] ......................................................
private:
	ImageType              m_imageType;     // [ 图像类型 ]
	CTMatrix< RGB_TRIPLE > m_colorImage;    // [ 彩色图像数据 ]
	CTMatrix< BYTE >       m_grayImage;     // [ 灰度图像数据 ]
	CTMatrix< BlackWhite>  m_unicolorImage; // [ 二值图像数据 ]

	// [ ****************** ] ............................................
	// [ 构造函数和析构函数 ] ............................................
	// [ ****************** ] ............................................
public:
	CImage();                      // [ 缺省构造函数 ]
	CImage( const CImage& image ); // [ 复制构造函数 ]
	virtual ~CImage();             // [ 析构函数 ]

	// [ ************ ] ..................................................
	// [ 功能接口函数 ] ..................................................
	// [ ************ ] ..................................................
public:
	void ImportFrom( const CString& fileName );                      // [ 导入图像文件 ]
	void ImportFrom( const CImage& image );                          // [ 导入图像数据 ]
	void ImportFrom( const CTMatrix< RGB_TRIPLE >& color_image );    // [ 导入彩色图像数据 ]
	void ImportFrom( const CTMatrix< BYTE >& gray_image );           // [ 导入灰度图像数据 ]
	void ImportFrom( const CTMatrix< BlackWhite >& unicolor_image ); // [ 导入二值图像数据 ]	
	void ImportFrom( CBitmap& bitmap );                              // [ 导入设备相关位图 ]
	void ImportFrom( HANDLE hDIB );                                  // [ 导入设备无关位图 ]

	CImage& operator= ( const CImage& image ); // [ 重载赋值操作符 ]

	void   ShowImage( CDC* pDC, CPoint leftTop, CSize displaySize = CSize( 0, 0 ) ) const; // [ 显示图像 ]
	void   SaveImage( const CString& fileName, int jpeg_quality = 100 ) const;             // [ 保存图像 ]

	static void ShowImage( const CTMatrix< RGB_TRIPLE >& colorImage, 
		                   CDC* pDC, CPoint leftTop, CSize displaySize = CSize( 0, 0 ) ); // [ 显示彩色图像 ]
	static void ShowImage( const CTMatrix< BYTE >& grayImage, 
		                   CDC* pDC, CPoint leftTop, CSize displaySize = CSize( 0, 0 ) ); // [ 显示灰度图像 ]
	static void ShowImage( const CTMatrix< BlackWhite >& unicolorImage, 
		                   CDC* pDC, CPoint leftTop, CSize displaySize = CSize( 0, 0 ) ); // [ 显示二值图像 ]

	static void SaveImage( const CTMatrix< RGB_TRIPLE >& colorImage, const CString& fileName, int jpeg_quality ) ;   // [ 保存彩色图像 ]
	static void SaveImage( const CTMatrix< BYTE >& grayImage, const CString& fileName, int jpeg_quality ) ;          // [ 保存灰度图像 ] 
	static void SaveImage( const CTMatrix< BlackWhite >& unicolorImage, const CString& fileName ); // [ 保存二值图像 ]

	// [ ************ ] ..................................................
	// [ 状态参数函数 ] ..................................................
	// [ ************ ] ..................................................
public:
	ImageType GetImageType() const; // [ 图像类型 ]

	bool IsColorImage() const;      // [ 是否是彩色图像 ]
	bool IsGrayImage() const;       // [ 是否是灰度图像 ]
	bool IsUnicolorImage() const;   // [ 是否是二值图像 ]
	bool IsNull() const;            // [ 是否为空 ]

	const CTMatrix< RGB_TRIPLE >& Get_color_image() const;    // [ 彩色图像数据 ]
	const CTMatrix< BYTE >& Get_gray_image() const;           // [ 灰度图像数据 ]
	const CTMatrix< BlackWhite >& Get_unicolor_image() const; // [ 二值图像数据 ]

	long        Get_image_height() const; // [ 图像高度 ]
	long        Get_image_width() const;  // [ 图像宽度 ] 
	CImagePoint Get_image_size() const;   // [ 图像尺寸 ]

	// [ ************ ] ..................................................
	// [ 内部实现函数 ] ..................................................
	// [ ************ ] ..................................................
private:
	static CString PostfixToFileName( const CString& fileName );                          // [ 获取文件名后缀 ]

	void ImportFromBmpFile( const CString& fileName );                                    // [ 导入 BMP 图像文件 ]
	void ImportFrom_32_BmpFile( BYTE* bitmapData, bool isBottomUp,
		                        long imageHeight, long imageWidth, 
								long bytesPerMemoryRow, long bytesPerFileRow );           // [ 导入 32 位 BMP 图像数据 ]
    void ImportFrom_24_BmpFile( BYTE* bitmapData, bool isBottomUp,
		                        long imageHeight, long imageWidth, 
								long bytesPerMemoryRow, long bytesPerFileRow );           // [ 导入 24 位 BMP 图像数据 ]
	void ImportFrom_8_BmpFile( BYTE* bitmapData, RGBQUAD* colorTemplate, bool isBottomUp,
		                       long imageHeight, long imageWidth,
							   long bytesPerMemoryRow, long bytesPerFileRow );            // [ 导入 8 位 BMP 图像数据 ]
	void ImportFrom_1_BmpFile( BYTE* bitmapData, RGBQUAD* colorTemplate, bool isBottomUp,
		                       long imageHeight, long imageWidth,
							   long bytesPerMemoryRow, long bytesPerFileRow );            // [ 导入 1 位 BMP 图像数据 ]

	void Import_from_raw_file( const CString& file_name );                                // [ 导入 RAW 图像文件 ]

	HANDLE DDBToDIB( CBitmap& bitmap, DWORD dwCompression, CPalette* pPal );              // [ 设备相关位图转换为设备无关位图 ]

	static void SaveImageToBmpFile( const CTMatrix< RGB_TRIPLE >& colorImage, const CString& fileName );    // [ 保存彩色图像为 BMP 文件 ]
	static void SaveImageToBmpFile( const CTMatrix< BYTE >& grayImage, const CString& fileName );           // [ 保存灰度图像为 BMP 文件 ]
	static void SaveImageToBmpFile( const CTMatrix< BlackWhite >& unicolorImage, const CString& fileName ); // [ 保存二值图像为 BMP 文件 ]

	static void SaveImageToJpegFile( const CTMatrix< RGB_TRIPLE >& colorImage, const CString& fileName, int jpeg_quality ); // [ 保存彩色图像为 JPEG 文件 ]
	static void SaveImageToJpegFile( const CTMatrix< BYTE >& grayImage, const CString& fileName, int jpeg_quality );        // [ 保存灰度图像为 JPEG 文件 ]

	static void Construct_1_Info( BITMAPINFO* bitmapInfo, long imageHeight, long imageWidth );              // [ 构造 1 位信息 ]
	static void Construct_1_FileHeader( BITMAPFILEHEADER* fileHeader, long imageHeight, long imageWidth );  // [ 构造 1 位文件头 ]

	static void Construct_8_Info( BITMAPINFO* bitmapInfo, long imageHeight, long imageWidth );              // [ 构造 8 位信息 ]
	static void Construct_8_FileHeader( BITMAPFILEHEADER* fileHeader, long imageHeight, long imageWidth );  // [ 构造 8 位文件头 ]

	static void Construct_24_Info( BITMAPINFO* bitmapInfo, long imageHeight, long imageWidth );             // [ 构造 24 位信息 ]
	static void Construct_24_FileHeader( BITMAPFILEHEADER* fileHeader, long imageHeight, long imageWidth ); // [ 构造 24 位文件头 ]

	static void Construct_32_Info( BITMAPINFO* bitmapInfo, long imageHeight, long imageWidth );             // [ 构造 32 位信息 ]

};

#endif // !defined(AFX_IMAGE_H__377F5446_CBF5_4179_8D56_463F20CD3A86__INCLUDED_)
