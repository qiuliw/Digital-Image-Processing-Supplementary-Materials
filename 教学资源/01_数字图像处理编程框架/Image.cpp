// Image.cpp: implementation of the CImage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Image.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// [ ************ ] ......................................................
// [ 缺省构造函数 ] ......................................................
// [ ************ ] ......................................................
CImage::CImage()
{
	m_imageType = NoImage; // [ 初始化图像类型 ]
}

// [ ************ ] ......................................................
// [ 复制构造函数 ] ......................................................
// [ ************ ] ......................................................
CImage::CImage( const CImage& image )
{
	m_imageType = NoImage; // [ 初始化图像类型 ]

	ImportFrom( image ); // [ 导入图像数据 ]
}

// [ ******** ] ..........................................................
// [ 析构函数 ] ..........................................................
// [ ******** ] ..........................................................
CImage::~CImage()
{

}

// [ ************** ] ....................................................
// [ 重载赋值操作符 ] ....................................................
// [ ************** ] ....................................................
CImage& CImage::operator= ( const CImage& image )
{
	ImportFrom( image ); // [ 导入图像数据 ]

	return * this; // [ 返回当前对象 ]
}

// [ ************ ] ......................................................
// [ 导入图像文件 ] ......................................................
// [ ************ ] ......................................................
void CImage::ImportFrom( const CString& fileName )
{
	m_imageType = NoImage; // [ 初始化图像类型 ]

	CString postfix = PostfixToFileName( fileName ); // [ 获取文件名后缀 ]

	if( postfix.CompareNoCase( "BMP" ) == 0 ) // [ BMP 图像 ]
	{
		ImportFromBmpFile( fileName ); // [ 导入 BMP 图像文件 ]
		return; // [ 结束导入 ]
	}

	if( postfix.CompareNoCase( "RAW" ) == 0 ) // [ 如果是 RAW 图像格式，那么 ... ]
	{
		Import_from_raw_file( fileName ); // [ 导入 RAW 图像文件 ]
		return; // [ 结束导入 ]
	}
}

// [ ************ ] ......................................................
// [ 导入图像数据 ] ......................................................
// [ ************ ] ......................................................
void CImage::ImportFrom( const CImage& image )
{
	m_imageType = image.m_imageType; // [ 图像类型 ]

	m_colorImage = image.m_colorImage;       // [ 彩色图像数据 ]
	m_grayImage = image.m_grayImage;         // [ 灰度图像数据 ]
	m_unicolorImage = image.m_unicolorImage; // [ 二值图像数据 ]
}

// [ **************** ] ..................................................
// [ 导入彩色图像数据 ] ..................................................
// [ **************** ] ..................................................
void CImage::ImportFrom( const CTMatrix< RGB_TRIPLE >& color_image )
{
	m_imageType = Color;        // [ 图像类型 ]
	m_colorImage = color_image; // [ 图像数据 ]
}

// [ **************** ] ..................................................
// [ 导入灰度图像数据 ] ..................................................
// [ **************** ] ..................................................
void CImage::ImportFrom( const CTMatrix< BYTE >& gray_image )
{
	m_imageType = Gray;       // [ 图像类型 ]
	m_grayImage = gray_image; // [ 图像数据 ]
}

// [ **************** ] ..................................................
// [ 导入二值图像数据 ] ..................................................
// [ **************** ] ..................................................
void CImage::ImportFrom( const CTMatrix< BlackWhite >& unicolor_image )
{
	m_imageType = Unicolor;           // [ 图像类型 ]
	m_unicolorImage = unicolor_image; // [ 图像数据 ]
}

// [ ******** ] ..........................................................
// [ 显示图像 ] ..........................................................
// [ ******** ] ..........................................................
void CImage::ShowImage( CDC* pDC, CPoint leftTop, CSize displaySize ) const
{
	switch( m_imageType ) // [ 图像类型 ]
	{
	case Color: // [ 彩色图像 ]
		ShowImage( m_colorImage, pDC, leftTop, displaySize ); // [ 显示彩色图像 ]
		break;

	case Gray: // [ 灰度图像 ]
		ShowImage( m_grayImage, pDC, leftTop, displaySize ); // [ 显示灰度图像 ]
		break;

	case Unicolor: // [ 二值图像 ]
		ShowImage( m_unicolorImage, pDC, leftTop, displaySize ); // [ 显示二值图像 ]
		break;
	}
}

// [ ******** ] ..........................................................
// [ 保存图像 ] ..........................................................
// [ ******** ] ..........................................................
void CImage::SaveImage( const CString& fileName, int jpeg_quality ) const
{
	switch( m_imageType ) // [ 图像类型 ]
	{
	case Color: // [ 彩色图像 ]
		SaveImage( m_colorImage, fileName, jpeg_quality ); // [ 保存彩色图像 ]
		break;

	case Gray: // [ 灰度图像 ]
		SaveImage( m_grayImage, fileName, jpeg_quality ); // [ 保存灰度图像 ]
		break;

	case Unicolor: // [ 二值图像 ]
		SaveImage( m_unicolorImage, fileName ); // [ 保存二值图像 ]
		break;
	}
}

// [ ******** ] ..........................................................
// [ 图像类型 ] ..........................................................
// [ ******** ] ..........................................................
CImage::ImageType CImage::GetImageType() const
{
	return m_imageType;
}

// [ ************ ] ......................................................
// [ 彩色图像数据 ] ......................................................
// [ ************ ] ......................................................
const CTMatrix< RGB_TRIPLE >& CImage::Get_color_image() const
{
#ifdef _DEBUG
	if( m_imageType != Color )
	{
		AfxMessageBox( "Program Error << Image Type Error >>" );
	}
#endif // _DEBUG

	return m_colorImage;
}

// [ ************ ] ......................................................
// [ 灰度图像数据 ] ......................................................
// [ ************ ] ......................................................
const CTMatrix< BYTE >& CImage::Get_gray_image() const
{
#ifdef _DEBUG
	if( m_imageType != Gray )
	{
		AfxMessageBox( "Program Error << Image Type Error >>" );
	}
#endif // _DEBUG

	return m_grayImage;
}

// [ ************ ] ......................................................
// [ 二值图像数据 ] ......................................................
// [ ************ ] ......................................................
const CTMatrix< BlackWhite >& CImage::Get_unicolor_image() const
{
#ifdef _DEBUG
	if( m_imageType != Unicolor )
	{
		AfxMessageBox( "Program Error << Image Type Error >>" );
	}
#endif // _DEBUG

	return m_unicolorImage;
}

// [ ******** ] ..........................................................
// [ 图像高度 ] ..........................................................
// [ ******** ] ..........................................................
long CImage::Get_image_height() const
{
	switch( m_imageType ) // [ 图像类型 ]
	{
	case Color: // [ 彩色图像 ]
		return m_colorImage.GetRows();
		break;

	case Gray: // [ 灰度图像 ]
		return m_grayImage.GetRows();
		break;

	case Unicolor: // [ 二值图像 ]
		return m_unicolorImage.GetRows();
		break;

	default: // [ 空图像 ]
		return 0;
		break;
	}
}

// [ ******** ] ..........................................................
// [ 图像宽度 ] ..........................................................
// [ ******** ] ..........................................................
long CImage::Get_image_width() const
{
	switch( m_imageType ) // [ 图像类型 ]
	{
	case Color: // [ 彩色图像 ]
		return m_colorImage.GetColumns();
		break;

	case Gray: // [ 灰度图像 ]
		return m_grayImage.GetColumns();
		break;

	case Unicolor: // [ 二值图像 ]
		return m_unicolorImage.GetColumns();
		break;

	default: // [ 空图像 ]
		return 0;
		break;
	}
}

// [ ******** ] ..........................................................
// [ 图像尺寸 ] ..........................................................
// [ ******** ] ..........................................................
CImagePoint CImage::Get_image_size() const
{
	switch( m_imageType ) // [ 图像类型 ]
	{
	case Color: // [ 彩色图像 ]
		return m_colorImage.Get_size();
		break;

	case Gray: // [ 灰度图像 ]
		return m_grayImage.Get_size();
		break;

	case Unicolor: // [ 二值图像 ]
		return m_unicolorImage.Get_size();
		break;

	default: // [ 空图像 ]
		return CImagePoint( 0, 0 );
		break;
	}
}

// [ ************** ] ....................................................
// [ 是否是彩色图像 ] ....................................................
// [ ************** ] ....................................................
bool CImage::IsColorImage() const
{
	return ( m_imageType == Color );
}

// [ ************** ] ....................................................
// [ 是否是灰度图像 ] ....................................................
// [ ************** ] ....................................................
bool CImage::IsGrayImage() const
{
	return ( m_imageType == Gray );
}

// [ ************** ] ....................................................
// [ 是否是二值图像 ] ....................................................
// [ ************** ] ....................................................
bool CImage::IsUnicolorImage() const
{
	return ( m_imageType == Unicolor );
}

// [ ******** ] ..........................................................
// [ 是否为空 ] ..........................................................
// [ ******** ] ..........................................................
bool CImage::IsNull() const
{
	return ( m_imageType == NoImage );
}

// [ ************** ] ....................................................
// [ 获取文件名后缀 ] ....................................................
// [ ************** ] ....................................................
CString CImage::PostfixToFileName( const CString& fileName ) 
{
	CString postfix; // [ 文件名后缀 ]

	int position = fileName.ReverseFind('.'); // [ 文件名中最个一个点字符的位置 ]

	if( position != -1 ) // [ 文件名是否存在后缀 ]
	{
		postfix = fileName.Right( fileName.GetLength() - position - 1 ); // [ 获取文件名后缀 ]
		 
	    postfix.MakeUpper(); // [ 大写文件名后缀 ]
	}

	return postfix; // [ 返回文件名后缀 ]
}

// [ ****************************** ] ....................................
// [ 设备相关位图转换为设备无关位图 ] ....................................
// [ ****************************** ] ....................................
//
// DDBToDIB		    - Creates a DIB from a DDB
// bitmap		    - Device dependent bitmap
// dwCompression	- Type of compression - see BITMAPINFOHEADER
// pPal			    - Logical palette
//
HANDLE CImage::DDBToDIB( CBitmap& bitmap, DWORD dwCompression, CPalette* pPal )
{
	BITMAP			bm;
	BITMAPINFOHEADER	bi;
	LPBITMAPINFOHEADER 	lpbi;
	DWORD			dwLen;
	HANDLE			hDIB;
	HANDLE			handle;
	HDC 			hDC;
	HPALETTE		hPal;


	ASSERT( bitmap.GetSafeHandle() );

	// The function has no arg for bitfields
	if( dwCompression == BI_BITFIELDS )
		return NULL;

	// If a palette has not been supplied use defaul palette
	hPal = (HPALETTE) pPal->GetSafeHandle();
	if (hPal==NULL)
		hPal = (HPALETTE) GetStockObject(DEFAULT_PALETTE);

	// Get bitmap information
	bitmap.GetObject(sizeof(bm),(LPSTR)&bm);

	// Initialize the bitmapinfoheader
	bi.biSize		= sizeof(BITMAPINFOHEADER);
	bi.biWidth		= bm.bmWidth;
	bi.biHeight 		= bm.bmHeight;
	bi.biPlanes 		= 1;
	bi.biBitCount		= bm.bmPlanes * bm.bmBitsPixel;
	bi.biCompression	= dwCompression;
	bi.biSizeImage		= 0;
	bi.biXPelsPerMeter	= 0;
	bi.biYPelsPerMeter	= 0;
	bi.biClrUsed		= 0;
	bi.biClrImportant	= 0;

	// Compute the size of the  infoheader and the color table
	int nColors = (1 << bi.biBitCount);
	if( nColors > 256 )
		nColors = 0;
	dwLen  = bi.biSize + nColors * sizeof(RGBQUAD);

	// We need a device context to get the DIB from
	hDC = GetDC(NULL);
	hPal = SelectPalette(hDC,hPal,FALSE);
	RealizePalette(hDC);

	// Allocate enough memory to hold bitmapinfoheader and color table
	hDIB = GlobalAlloc(GMEM_FIXED,dwLen);

	if (!hDIB){
		SelectPalette(hDC,hPal,FALSE);
		ReleaseDC(NULL,hDC);
		return NULL;
	}

	lpbi = (LPBITMAPINFOHEADER)hDIB;

	*lpbi = bi;

	// Call GetDIBits with a NULL lpBits param, so the device driver 
	// will calculate the biSizeImage field 
	GetDIBits(hDC, (HBITMAP)bitmap.GetSafeHandle(), 0L, (DWORD)bi.biHeight,
			(LPBYTE)NULL, (LPBITMAPINFO)lpbi, (DWORD)DIB_RGB_COLORS);

	bi = *lpbi;

	// If the driver did not fill in the biSizeImage field, then compute it
	// Each scan line of the image is aligned on a DWORD (32bit) boundary
	if (bi.biSizeImage == 0){
		bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8)
						* bi.biHeight;

		// If a compression scheme is used the result may infact be larger
		// Increase the size to account for this.
		if (dwCompression != BI_RGB)
			bi.biSizeImage = (bi.biSizeImage * 3) / 2;
	}

	// Realloc the buffer so that it can hold all the bits
	dwLen += bi.biSizeImage;
	if (handle = GlobalReAlloc(hDIB, dwLen, GMEM_MOVEABLE))
		hDIB = handle;
	else{
		GlobalFree(hDIB);

		// Reselect the original palette
		SelectPalette(hDC,hPal,FALSE);
		ReleaseDC(NULL,hDC);
		return NULL;
	}

	// Get the bitmap bits
	lpbi = (LPBITMAPINFOHEADER)hDIB;

	// FINALLY get the DIB
	BOOL bGotBits = GetDIBits( hDC, (HBITMAP)bitmap.GetSafeHandle(),
				0L,				// Start scan line
				(DWORD)bi.biHeight,		// # of scan lines
				(LPBYTE)lpbi 			// address for bitmap bits
				+ (bi.biSize + nColors * sizeof(RGBQUAD)),
				(LPBITMAPINFO)lpbi,		// address of bitmapinfo
				(DWORD)DIB_RGB_COLORS);		// Use RGB for color table

	if( !bGotBits )
	{
		GlobalFree(hDIB);

		SelectPalette(hDC,hPal,FALSE);
		ReleaseDC(NULL,hDC);
		return NULL;
	}

	SelectPalette(hDC,hPal,FALSE);
	ReleaseDC(NULL,hDC);
	return hDIB;
}

// [ **************** ] ..................................................
// [ 导入设备相关位图 ] ..................................................
// [ **************** ] ..................................................
void CImage::ImportFrom( CBitmap& bitmap )
{
	m_imageType = NoImage; // [ 初始化图像类型 ]

	// Convert the bitmap to a DIB
	HANDLE hDIB = DDBToDIB( bitmap, BI_RGB, NULL );

	if( hDIB == NULL ) return;

	// [ 导入设备无关位图 ]
	ImportFrom( hDIB );

	// Free the memory allocated by DDBToDIB for the DIB
	GlobalFree( hDIB );
}

// [ **************** ] ..................................................
// [ 导入设备无关位图 ] ..................................................
// [ **************** ] ..................................................
void CImage::ImportFrom( HANDLE hDIB )
{
	BITMAPFILEHEADER	hdr;
	LPBITMAPINFOHEADER	lpbi;

	if (!hDIB) return;

	lpbi = (LPBITMAPINFOHEADER)hDIB;

	int nColors = 1 << lpbi->biBitCount;
	if( nColors > 256 )
		nColors = 0;

	// Fill in the fields of the file header 
	hdr.bfType		= ((WORD) ('M' << 8) | 'B');	// is always "BM"
	hdr.bfSize		= DWORD( GlobalSize (hDIB) + sizeof( hdr ) );
	hdr.bfReserved1 	= 0;
	hdr.bfReserved2 	= 0;
	hdr.bfOffBits		= (DWORD) (sizeof( hdr ) + lpbi->biSize +
						nColors * sizeof(RGBQUAD));

	//////////////////////////////////////////////////////////////////////

	BITMAPFILEHEADER* bitmapFileHeader; // [ 文件头指针 ]
	BITMAPINFOHEADER* bitmapInfoHeader; // [ 信息头指针 ]
	BITMAPINFO* bitmapInfo; // [ 信息指针 ]
	RGBQUAD* colorTemplate; // [ 调色板指针 ]
	BYTE* bitmapData; // [ 数据指针 ]

	bitmapFileHeader = &hdr; // [ 设置文件头指针 ]
	bitmapInfoHeader = lpbi; // [ 设置信息头指针 ]
	bitmapInfo = ( BITMAPINFO* )bitmapInfoHeader; // [ 设置信息指针 ]
	colorTemplate = ( RGBQUAD* )bitmapInfo->bmiColors; // [ 设置调色板指针 ] 
	bitmapData = (BYTE*)hDIB + bitmapFileHeader->bfOffBits - sizeof( hdr ); // [ 设置数据指针 ]

    if( bitmapFileHeader->bfType != ((WORD) ('M' << 8) | 'B') ) // [ 检查 BMP 文件的合法性 ]
	{
		return; // [ 函数返回 ]
	}

    long imageWidth = bitmapInfoHeader->biWidth; // [ 图像宽度( 像素 ) ]
	long imageHeight = bitmapInfoHeader->biHeight; // [ 图像高度( 像素 ) ]	
	imageHeight = ( imageHeight > 0 ) ? imageHeight : - imageHeight ; // [ 修正图像高度 ]
	bool isBottomUp = bitmapInfoHeader->biHeight > 0; // [ 图像存储顺序 ]
	long bitCount = bitmapInfoHeader->biBitCount; // [ 像素存储位数 ]
	long bytesPerMemoryRow = ( imageWidth * bitCount + 7 ) / 8 ; // [ 内存中图像行存储字节数 ]
	long bytesPerFileRow = ( ( bytesPerMemoryRow + 3 ) / 4 ) * 4 ; // [ 文件中图像行存储字节数 ]

	switch( bitCount ) // [ 像素存储位数 ]
	{
	case 1: // [ 二值图像 ]
		ImportFrom_1_BmpFile( bitmapData, colorTemplate, isBottomUp,
			                  imageHeight, imageWidth,
							  bytesPerMemoryRow, bytesPerFileRow ); // [ 导入 1 位 BMP 图像数据 ]
		break;

	case 8: // [ 灰度图像 ]
		ImportFrom_8_BmpFile( bitmapData, colorTemplate, isBottomUp,
			                  imageHeight, imageWidth,
							  bytesPerMemoryRow, bytesPerFileRow ); // [ 导入 8 位 BMP 图像数据 ]
		break;

	case 24: // [ 彩色图像 ]
		ImportFrom_24_BmpFile( bitmapData, isBottomUp, 
			                   imageHeight, imageWidth, 
							   bytesPerMemoryRow, bytesPerFileRow ); // [ 导入 24 位 BMP 图像数据 ]
		break;

	case 32: // [ 彩色图像 ]
		ImportFrom_32_BmpFile( bitmapData, isBottomUp, 
			                   imageHeight, imageWidth, 
							   bytesPerMemoryRow, bytesPerFileRow ); // [ 导入 32 位 BMP 图像数据 ]
		break;
	}
}

// [ ***************** ] .................................................
// [ 导入 BMP 图像文件 ] .................................................
// [ ***************** ] .................................................
void CImage::ImportFromBmpFile( const CString& fileName )
{
	CFile bitmapFile; // [ 图像文件 ]

	if( !bitmapFile.Open( fileName, CFile::modeRead ) ) // [ 打开图像文件 ]
		return;

	long fileLength = long( bitmapFile.GetLength() ); // [ 图像文件长度( 字节数 ) ]
	BYTE* fileBuffer = new BYTE[ fileLength ]; // [ 申请图像文件缓存 ]
	bitmapFile.Read( fileBuffer, fileLength ); // [ 读取整个图像文件 ]

	BITMAPFILEHEADER* bitmapFileHeader; // [ 文件头指针 ]
	BITMAPINFOHEADER* bitmapInfoHeader; // [ 信息头指针 ]
	BITMAPINFO* bitmapInfo; // [ 信息指针 ]
	RGBQUAD* colorTemplate; // [ 调色板指针 ]
	BYTE* bitmapData; // [ 数据指针 ]

	bitmapFileHeader = ( BITMAPFILEHEADER* )fileBuffer; // [ 设置文件头指针 ]
	bitmapInfoHeader = ( BITMAPINFOHEADER* )( fileBuffer + sizeof( BITMAPFILEHEADER ) ); // [ 设置信息头指针 ]
	bitmapInfo = ( BITMAPINFO* )bitmapInfoHeader; // [ 设置信息指针 ]
	colorTemplate = ( RGBQUAD* )bitmapInfo->bmiColors; // [ 设置调色板指针 ] 
	bitmapData = fileBuffer + bitmapFileHeader->bfOffBits; // [ 设置数据指针 ]

    if( bitmapFileHeader->bfType != ((WORD) ('M' << 8) | 'B') ) // [ 检查 BMP 文件的合法性 ]
	{
		delete [] fileBuffer; // [ 释放图像文件缓存 ]
	    bitmapFile.Close(); // [ 关闭图像文件 ]
		return; // [ 函数返回 ]
	}

    long imageWidth = bitmapInfoHeader->biWidth; // [ 图像宽度( 像素 ) ]
	long imageHeight = bitmapInfoHeader->biHeight; // [ 图像高度( 像素 ) ]	
	imageHeight = ( imageHeight > 0 ) ? imageHeight : - imageHeight ; // [ 修正图像高度 ]
	bool isBottomUp = bitmapInfoHeader->biHeight > 0; // [ 图像存储顺序 ]
	long bitCount = bitmapInfoHeader->biBitCount; // [ 像素存储位数 ]
	long bytesPerMemoryRow = ( imageWidth * bitCount + 7 ) / 8 ; // [ 内存中图像行存储字节数 ]
	long bytesPerFileRow = ( ( bytesPerMemoryRow + 3 ) / 4 ) * 4 ; // [ 文件中图像行存储字节数 ]

	switch( bitCount ) // [ 像素存储位数 ]
	{
	case 1: // [ 二值图像 ]
		ImportFrom_1_BmpFile( bitmapData, colorTemplate, isBottomUp,
			                  imageHeight, imageWidth,
							  bytesPerMemoryRow, bytesPerFileRow ); // [ 导入 1 位 BMP 图像数据 ]
		break;

	case 8: // [ 灰度图像 ]
		ImportFrom_8_BmpFile( bitmapData, colorTemplate, isBottomUp,
			                  imageHeight, imageWidth,
							  bytesPerMemoryRow, bytesPerFileRow ); // [ 导入 8 位 BMP 图像数据 ]
		break;

	case 24: // [ 彩色图像 ]
		ImportFrom_24_BmpFile( bitmapData, isBottomUp, 
			                   imageHeight, imageWidth, 
							   bytesPerMemoryRow, bytesPerFileRow ); // [ 导入 24 位 BMP 图像数据 ]
		break;

	case 32: // [ 彩色图像 ]
		ImportFrom_32_BmpFile( bitmapData, isBottomUp, 
			                   imageHeight, imageWidth, 
							   bytesPerMemoryRow, bytesPerFileRow ); // [ 导入 32 位 BMP 图像数据 ]
		break;
	}

	delete [] fileBuffer; // [ 释放图像文件缓存 ]

	bitmapFile.Close(); // [ 关闭图像文件 ]
}

// [ *********************** ] ...........................................
// [ 导入 32 位 BMP 图像数据 ] ...........................................
// [ *********************** ] ...........................................
void CImage::ImportFrom_32_BmpFile( BYTE* bitmapData, bool isBottomUp,
		                            long imageHeight, long imageWidth, 
								    long bytesPerMemoryRow, long bytesPerFileRow )
{
	m_imageType = Color; // [ 设为彩色图像 ]
	m_colorImage.Construction( imageHeight, imageWidth ); // [ 构造图像 ]

	BYTE* swapBuffer = new BYTE[ imageWidth * 3 * imageHeight ]; // [ 申请缓冲区 ]

	for( int row = 0; row < imageHeight; row++ )
		for( int column = 0; column < imageWidth; column ++ )
		{
			if( isBottomUp ) // [ 自下而上, 自左而右的图像数据存储顺序 ]
			{
				swapBuffer[ row * imageWidth * 3 + column * 3     ] = bitmapData[ ( imageHeight - row - 1 ) * bytesPerFileRow + column * 4 ];
				swapBuffer[ row * imageWidth * 3 + column * 3 + 1 ] = bitmapData[ ( imageHeight - row - 1 ) * bytesPerFileRow + column * 4 + 1 ];
				swapBuffer[ row * imageWidth * 3 + column * 3 + 2 ] = bitmapData[ ( imageHeight - row - 1 ) * bytesPerFileRow + column * 4 + 2 ];
			}
			else // [ 自上而下, 自左而右的图像数据存储顺序 ]
			{
				swapBuffer[ row * imageWidth * 3 + column * 3     ] = bitmapData[ row * bytesPerFileRow + column * 4 ];
				swapBuffer[ row * imageWidth * 3 + column * 3 + 1 ] = bitmapData[ row * bytesPerFileRow + column * 4 + 1 ];
				swapBuffer[ row * imageWidth * 3 + column * 3 + 2 ] = bitmapData[ row * bytesPerFileRow + column * 4 + 2 ];
			}
		}
		
	m_colorImage.ImportFrom( swapBuffer ); // [ 导入图像内容 ]

	delete [] swapBuffer; // [ 释放缓冲区 ]
}

// [ ***************** ] .................................................
// [ 导入 RAW 图像文件 ] .................................................
// [ ***************** ] .................................................
void CImage::Import_from_raw_file( const CString& file_name )
{
	// [ 此 RAW 格式图像导入函数，只处理一种 RAW 格式，即图像像素高度和 ]
	// [ 宽度都为 512，并且图像数据是按照“BGR，BGR，...”的顺序进行存  ]
	// [ 储。对于其它格式的 RAW 图像文件，则一律放弃数据读取。          ]

	const long image_height = 512; // [ 图像像素高度 ]
	const long image_width = 512;  // [ 图像像素宽度 ]

	CFile raw_file( file_name, CFile::modeRead ); // [ 读打开 RAW 图像文件 ]

	if( raw_file.GetLength() != image_height * image_width * 3 ) // [ 如果图像尺寸不匹配，那么 ... ]
	{
		raw_file.Close(); // [ 关闭 RAW 图像文件 ]
		return;           // [ 结束返回 ]
	}

	m_imageType = Color;                                    // [ 设为彩色图像 ]
	m_colorImage.Construction( image_height, image_width ); // [ 构造图像 ]

	raw_file.Read( &( m_colorImage[0][0] ), m_colorImage.GetSizeInBytes() ); // [ 读取 RAW 图像文件数据 ]

	raw_file.Close(); // [ 关闭 RAW 图像文件 ]
}

// [ *********************** ] ...........................................
// [ 导入 24 位 BMP 图像数据 ] ...........................................
// [ *********************** ] ...........................................
void CImage::ImportFrom_24_BmpFile( BYTE* bitmapData, bool isBottomUp, 
								    long imageHeight, long imageWidth, 
									long bytesPerMemoryRow, long bytesPerFileRow )
{
	m_imageType = Color; // [ 设为彩色图像 ]
	m_colorImage.Construction( imageHeight, imageWidth ); // [ 构造图像 ]

	BYTE* swapBuffer = new BYTE[ bytesPerMemoryRow * imageHeight ]; // [ 申请缓冲区 ]

	if( isBottomUp ) // [ 自下而上, 自左而右的图像数据存储顺序 ]
		for( int row = 0; row < imageHeight; row++ )
			memcpy( swapBuffer + row * bytesPerMemoryRow, 
			        bitmapData + ( imageHeight - row - 1 ) * bytesPerFileRow,
				    bytesPerMemoryRow); // [ 图像上下翻转 ]
	else // [ 自上而下, 自左而右的图像数据存储顺序 ]
		for( int row = 0; row < imageHeight; row++ )
			memcpy( swapBuffer + row * bytesPerMemoryRow,
			        bitmapData + row * bytesPerFileRow,
					bytesPerMemoryRow);
	
	m_colorImage.ImportFrom( swapBuffer ); // [ 导入图像内容 ]

	delete [] swapBuffer; // [ 释放缓冲区 ]
}

// [ ********************** ] ............................................
// [ 导入 8 位 BMP 图像数据 ] ............................................
// [ ********************** ] ............................................
void CImage::ImportFrom_8_BmpFile( BYTE* bitmapData, RGBQUAD* colorTemplate, bool isBottomUp,
		                           long imageHeight, long imageWidth,
							       long bytesPerMemoryRow, long bytesPerFileRow )
{
	m_imageType = Gray; // [ 设为灰度图像 ]
	m_grayImage.Construction( imageHeight, imageWidth ); // [ 构造图像 ]

    BYTE* swapBuffer = new BYTE[ imageHeight * imageWidth ]; // [ 申请缓冲区 ]
	
	for( int row = 0; row < imageHeight; row++ )
		for( int column = 0; column < imageWidth; column++ )
		{
			BYTE colorIndex; // [ 调色板索引 ]
			if( isBottomUp ) // [ 自下而上, 自左而右的图像数据存储顺序 ]
				colorIndex = bitmapData[ ( imageHeight - row - 1 ) * bytesPerFileRow + column ];  
			else // [ 自上而下, 自左而右的图像数据存储顺序 ]
				colorIndex = bitmapData[ row * bytesPerFileRow + column ];

			RGBQUAD quad = colorTemplate[ colorIndex ]; // [ 查找调色板 ]
			BYTE maxComponent = max( max( quad.rgbBlue, quad.rgbGreen ), quad.rgbRed ) ; // [ 最大颜色分量 ]
			swapBuffer[ row * imageWidth + column ] = maxComponent ; // [ 灰度设置 ]
		}

	m_grayImage.ImportFrom( swapBuffer ); // [ 导入图像内容 ]

	delete [] swapBuffer; // [ 释放缓冲区 ]
}

// [ ********************** ] ............................................
// [ 导入 1 位 BMP 图像数据 ] ............................................
// [ ********************** ] ............................................
void CImage::ImportFrom_1_BmpFile( BYTE* bitmapData, RGBQUAD* colorTemplate, bool isBottomUp,
		                           long imageHeight, long imageWidth,
							       long bytesPerMemoryRow, long bytesPerFileRow )
{
	m_imageType = Unicolor; // [ 设为二值图像 ]
	m_unicolorImage.Construction( imageHeight, imageWidth ); // [ 构造图像 ]

	BlackWhite* swapBuffer = new BlackWhite[ imageWidth * imageHeight ] ; // [ 申请缓冲区 ]
	
	for( int row = 0; row < imageHeight; row++ )
		for( int column = 0; column < imageWidth; column++ )
		{
			long indexByte = column / 8 ; // [ 像素所在字节索引 ]
			long indexBit = 7 - column % 8 ; // [ 像素所在位索引( 相对最后一位 ) ]

			BYTE entireByte; // [ 像素所在字节 ]
			if( isBottomUp ) // [ 自下而上, 自左而右的图像数据存储顺序 ]
				entireByte = bitmapData[ ( imageHeight - row - 1 ) * bytesPerFileRow + indexByte ]; 
			else // [ 自上而下, 自左而右的图像数据存储顺序 ]
				entireByte = bitmapData[ row * bytesPerFileRow + indexByte ];

			BYTE colorIndex = ( entireByte >> indexBit ) & 1 ; // [ 调色板索引 ]
			RGBQUAD quad = colorTemplate[ colorIndex ]; // [ 查找调色板 ]
			BYTE maxComponent = max( max( quad.rgbBlue, quad.rgbGreen ), quad.rgbRed ) ; // [ 最大颜色分量 ]
			swapBuffer[ row * imageWidth + column ] = ( maxComponent > 128 ) ? White : Black ; // [ 二值转换 ]
		}

	m_unicolorImage.ImportFrom( swapBuffer ); // [ 导入图像内容 ]

	delete [] swapBuffer; // [ 释放缓冲区 ]
}

// [ ************ ] ......................................................
// [ 显示彩色图像 ] ......................................................
// [ ************ ] ......................................................
void CImage::ShowImage( const CTMatrix< RGB_TRIPLE >& colorImage, CDC* pDC, CPoint leftTop, CSize displaySize )
{
	if( colorImage.IsNull() ) // [ 判断图像是否为空 ]
		return;

	long imageHeight = colorImage.GetRows( ); // [ 图像高度( 像素 ) ]
	long imageWidth = colorImage.GetColumns( ); // [ 图像宽度( 像素 ) ]
	long bytesPerMemoryRow = imageWidth * sizeof( RGB_TRIPLE ); // [ 内存中图像行存储字节数 ]
	long bytesPerFileRow = ( ( bytesPerMemoryRow + 3 ) / 4 ) * 4 ; // [ 文件中图像行存储字节数 ]

	BITMAPINFO* bitmapInfo = new BITMAPINFO ; // [ 申请位图信息内存 ]
	BYTE* bitmapData = new BYTE[ colorImage.GetSizeInBytes() ]; // [ 申请位图数据内存 ]
    BYTE* swapBuffer = ( bytesPerMemoryRow == bytesPerFileRow ) ? 
                       bitmapData : ( new BYTE[ imageHeight * bytesPerFileRow ] ); // [ 申请图像显示缓冲区 ]
	
	Construct_24_Info( bitmapInfo, imageHeight, imageWidth ); // [ 构造 24 位信息 ]
	colorImage.ExportTo( bitmapData ); // [ 导出图像内容 ]
	if( bytesPerMemoryRow != bytesPerFileRow ) 
		for( int row = 0; row < imageHeight; row++ )
			memcpy( swapBuffer + row * bytesPerFileRow, 
			        bitmapData + row * bytesPerMemoryRow, 
					bytesPerMemoryRow ); // [ 设置图像显示缓冲区内容 ]

    if( displaySize == CSize(0, 0) ) // [ 正常显示 ]
	{
		::SetDIBitsToDevice( pDC->GetSafeHdc(), leftTop.x, leftTop.y,
		                     (DWORD)imageWidth, (DWORD)imageHeight,
		                     0, 0, 0, (UINT)imageHeight,
							 swapBuffer, bitmapInfo,
		                     DIB_RGB_COLORS);
	}
	else // [ 伸缩显示 ]
	{
		int oldMode = pDC->GetStretchBltMode( ); // [ 保存旧的位图伸缩模式 ]
		pDC->SetStretchBltMode( COLORONCOLOR ); // [ 设置新的位图伸缩模式 ]

        ::StretchDIBits( pDC->GetSafeHdc(), leftTop.x, leftTop.y,
		                 displaySize.cx, displaySize.cy,
		                 0, 0, imageWidth, imageHeight,
						 swapBuffer, bitmapInfo,
		                 DIB_RGB_COLORS, SRCCOPY);

		pDC->SetStretchBltMode( oldMode ); // [ 恢复旧的位图伸缩模式 ]
	}

	if( bytesPerMemoryRow != bytesPerFileRow ) delete [] swapBuffer; // [ 释放图像显示缓冲区 ]
	delete [] bitmapData; // [ 释放位图数据内存 ]
	delete bitmapInfo; // [ 释放位图信息内存 ]

}

// [ ************ ] ......................................................
// [ 显示灰度图像 ] ......................................................
// [ ************ ] ......................................................
void CImage::ShowImage( const CTMatrix< BYTE >& grayImage, CDC* pDC, CPoint leftTop, CSize displaySize )
{
	if( grayImage.IsNull() ) // [ 判断图像是否为空 ]
		return;

	long imageHeight = grayImage.GetRows(); // [ 图像高度( 像素 ) ]
	long imageWidth = grayImage.GetColumns(); // [ 图像宽度( 像素 ) ]
	long bytesPerFileRow = ( ( imageWidth + 3 ) / 4 ) * 4 ; // [ 文件中图像行存储字节数 ]

	BITMAPINFO* bitmapInfo = ( BITMAPINFO* )( new BYTE[ sizeof( BITMAPINFOHEADER ) + 256 * sizeof( RGBQUAD ) ] ); // [ 申请位图信息内存 ]
	BYTE* bitmapData = new BYTE[ grayImage.GetSizeInBytes() ]; // [ 申请位图数据内存 ]
	BYTE* swapBuffer = ( imageWidth == bytesPerFileRow ) ? 
                       bitmapData : ( new BYTE[ imageHeight * bytesPerFileRow ] ); // [ 申请图像显示缓冲区 ]

	Construct_8_Info( bitmapInfo, imageHeight, imageWidth ); // [ 构造 8 位信息 ]
	grayImage.ExportTo( bitmapData ); // [ 导出图像内容 ]
	if( imageWidth != bytesPerFileRow ) 
		for( int row = 0; row < imageHeight; row++ )
			memcpy( swapBuffer + row * bytesPerFileRow, 
			        bitmapData + row * imageWidth, 
					imageWidth ); // [ 设置图像显示缓冲区内容 ]

	if( displaySize == CSize(0, 0) ) // [ 正常显示 ]
	{
		::SetDIBitsToDevice( pDC->GetSafeHdc(), leftTop.x, leftTop.y,
		                     (DWORD)imageWidth, (DWORD)imageHeight,
		                     0, 0, 0, (UINT)imageHeight,
							 swapBuffer, bitmapInfo,
		                     DIB_RGB_COLORS);
	}
	else // [ 伸缩显示 ]
	{
		int oldMode = pDC->GetStretchBltMode( ); // [ 保存旧的位图伸缩模式 ]
		pDC->SetStretchBltMode( COLORONCOLOR ); // [ 设置新的位图伸缩模式 ]

        ::StretchDIBits( pDC->GetSafeHdc(), leftTop.x, leftTop.y,
		                 displaySize.cx, displaySize.cy,
		                 0, 0, imageWidth, imageHeight,
						 swapBuffer, bitmapInfo,
		                 DIB_RGB_COLORS, SRCCOPY);

		pDC->SetStretchBltMode( oldMode ); // [ 恢复旧的位图伸缩模式 ]
	}

	if( imageWidth != bytesPerFileRow ) delete [] swapBuffer; // [ 释放图像显示缓冲区 ]
	delete [] bitmapData; // [ 释放位图数据内存 ]
	delete [] bitmapInfo; // [ 释放位图信息内存 ]
}

// [ ************ ] ......................................................
// [ 显示二值图像 ] ......................................................
// [ ************ ] ......................................................
void CImage::ShowImage( const CTMatrix< BlackWhite >& unicolorImage, CDC* pDC, CPoint leftTop, CSize displaySize )
{
	if( unicolorImage.IsNull() ) // [ 判断图像是否为空 ]
		return;

	long imageHeight = unicolorImage.GetRows(); // [ 图像高度( 像素 ) ]
	long imageWidth = unicolorImage.GetColumns(); // [ 图像宽度( 像素 ) ]

	BITMAPINFO* bitmapInfo = new BITMAPINFO ; // [ 申请位图信息内存 ]
	BYTE* bitmapData = new BYTE[ unicolorImage.GetSizeInBytes() ]; // [ 申请位图数据内存 ]

	Construct_32_Info( bitmapInfo, imageHeight, imageWidth ); // [ 构造 32 信息 ]
	unicolorImage.ExportTo( bitmapData ); // [ 导出图像内容 ]

	if( displaySize == CSize(0, 0) ) // [ 正常显示 ]
	{
		::SetDIBitsToDevice( pDC->GetSafeHdc(), leftTop.x, leftTop.y,
		                     (DWORD)imageWidth, (DWORD)imageHeight,
		                     0, 0, 0, (UINT)imageHeight,
							 bitmapData, bitmapInfo,
		                     DIB_RGB_COLORS);
	}
	else // [ 伸缩显示 ]
	{
		int oldMode = pDC->GetStretchBltMode( ); // [ 保存旧的位图伸缩模式 ]
		pDC->SetStretchBltMode( COLORONCOLOR ); // [ 设置新的位图伸缩模式 ]

        ::StretchDIBits( pDC->GetSafeHdc(), leftTop.x, leftTop.y,
		                 displaySize.cx, displaySize.cy,
		                 0, 0, imageWidth, imageHeight,
						 bitmapData, bitmapInfo,
		                 DIB_RGB_COLORS, SRCCOPY);

		pDC->SetStretchBltMode( oldMode ); // [ 恢复旧的位图伸缩模式 ]
	}

	delete [] bitmapData; // [ 释放位图数据内存 ]
	delete bitmapInfo; // [ 释放位图信息内存 ]
}

// [ ************* ] .....................................................
// [ 构造 1 位信息 ] .....................................................
// [ ************* ] .....................................................
void CImage::Construct_1_Info( BITMAPINFO* bitmapInfo, long imageHeight, long imageWidth )
{
	long bytesPerMemoryRow = ( imageWidth + 7 ) / 8 ; // [ 内存中图像行存储字节数 ]
	long bytesPerFileRow = ( ( bytesPerMemoryRow + 3 ) / 4 ) * 4 ; // [ 文件中图像行存储字节数 ]

	bitmapInfo->bmiHeader.biBitCount = 1 ;
	bitmapInfo->bmiHeader.biClrImportant = 0;
	bitmapInfo->bmiHeader.biClrUsed = 0;
	bitmapInfo->bmiHeader.biCompression = BI_RGB;
	bitmapInfo->bmiHeader.biHeight = - imageHeight;
	bitmapInfo->bmiHeader.biPlanes = 1;
	bitmapInfo->bmiHeader.biSizeImage = imageHeight * bytesPerFileRow ;
	bitmapInfo->bmiHeader.biSize = 40;
	bitmapInfo->bmiHeader.biWidth = imageWidth;
	bitmapInfo->bmiHeader.biXPelsPerMeter = 3780;
	bitmapInfo->bmiHeader.biYPelsPerMeter = 3780;

	RGBQUAD* colorTemplate = bitmapInfo->bmiColors;

	colorTemplate[0].rgbBlue = BYTE( 0 );
	colorTemplate[0].rgbGreen = BYTE( 0 );
	colorTemplate[0].rgbRed = BYTE( 0 );
	colorTemplate[0].rgbReserved = BYTE( 0 );

	colorTemplate[1].rgbBlue = BYTE( 255 );
	colorTemplate[1].rgbGreen = BYTE( 255 );
	colorTemplate[1].rgbRed = BYTE( 255 );
	colorTemplate[1].rgbReserved = BYTE( 0 );
}

// [ *************** ] ...................................................
// [ 构造 1 位文件头 ] ...................................................
// [ *************** ] ...................................................
void CImage::Construct_1_FileHeader( BITMAPFILEHEADER* fileHeader, long imageHeight, long imageWidth )
{
	long bytesPerMemoryRow = ( imageWidth + 7 ) / 8 ; // [ 内存中图像行存储字节数 ]
	long bytesPerFileRow = ( ( bytesPerMemoryRow + 3 ) / 4 ) * 4 ; // [ 文件中图像行存储字节数 ]

	fileHeader->bfType = ((WORD) ('M' << 8) | 'B') ;  
	fileHeader->bfReserved1 = 0 ;  
	fileHeader->bfReserved2 = 0 ;  
	fileHeader->bfOffBits = sizeof( BITMAPFILEHEADER ) + sizeof( BITMAPINFOHEADER ) + 2 * sizeof( RGBQUAD ) ;
	fileHeader->bfSize = fileHeader->bfOffBits + imageHeight * bytesPerFileRow ;
}

// [ ************* ] .....................................................
// [ 构造 8 位信息 ] .....................................................
// [ ************* ] .....................................................
void CImage::Construct_8_Info( BITMAPINFO* bitmapInfo, long imageHeight, long imageWidth )
{
	bitmapInfo->bmiHeader.biBitCount = 8 ;
	bitmapInfo->bmiHeader.biClrImportant = 0;
	bitmapInfo->bmiHeader.biClrUsed = 0;
	bitmapInfo->bmiHeader.biCompression = BI_RGB;
	bitmapInfo->bmiHeader.biHeight = - imageHeight;
	bitmapInfo->bmiHeader.biPlanes = 1;
	bitmapInfo->bmiHeader.biSizeImage = imageHeight * ( ( ( imageWidth + 3 ) / 4 ) * 4 ) ;
	bitmapInfo->bmiHeader.biSize = 40;
	bitmapInfo->bmiHeader.biWidth = imageWidth;
	bitmapInfo->bmiHeader.biXPelsPerMeter = 3780;
	bitmapInfo->bmiHeader.biYPelsPerMeter = 3780;

	RGBQUAD* colorTemplate = bitmapInfo->bmiColors;
	for( int index = 0; index < 256; index++ )
	{
		colorTemplate[index].rgbBlue = BYTE( index );
		colorTemplate[index].rgbGreen = BYTE( index );
		colorTemplate[index].rgbRed = BYTE( index );
		colorTemplate[index].rgbReserved = BYTE( 0 );
	}
}

// [ *************** ] ...................................................
// [ 构造 8 位文件头 ] ...................................................
// [ *************** ] ...................................................
void CImage::Construct_8_FileHeader( BITMAPFILEHEADER* fileHeader, long imageHeight, long imageWidth )
{
	fileHeader->bfType = ((WORD) ('M' << 8) | 'B') ;  
	fileHeader->bfReserved1 = 0 ;  
	fileHeader->bfReserved2 = 0 ;  
	fileHeader->bfOffBits = sizeof( BITMAPFILEHEADER ) + sizeof( BITMAPINFOHEADER ) + 256 * sizeof( RGBQUAD ) ;
	fileHeader->bfSize = fileHeader->bfOffBits + imageHeight * ( ( ( imageWidth + 3 ) / 4 ) * 4 ) ;
}

// [ ************** ] ....................................................
// [ 构造 24 位信息 ] ....................................................
// [ ************** ] ....................................................
void CImage::Construct_24_Info( BITMAPINFO* bitmapInfo, long imageHeight, long imageWidth )
{	 
	bitmapInfo->bmiHeader.biBitCount = 24;
	bitmapInfo->bmiHeader.biClrImportant = 0;
	bitmapInfo->bmiHeader.biClrUsed = 0;
	bitmapInfo->bmiHeader.biCompression = BI_RGB;
	bitmapInfo->bmiHeader.biHeight = - imageHeight;
	bitmapInfo->bmiHeader.biPlanes = 1;
	bitmapInfo->bmiHeader.biSizeImage = imageHeight * ( ( ( ( imageWidth * 3 ) + 3 ) / 4 ) * 4 );
	bitmapInfo->bmiHeader.biSize = 40;
	bitmapInfo->bmiHeader.biWidth = imageWidth;
	bitmapInfo->bmiHeader.biXPelsPerMeter = 3780;
	bitmapInfo->bmiHeader.biYPelsPerMeter = 3780;

	bitmapInfo->bmiColors[0].rgbBlue = (BYTE)0;
    bitmapInfo->bmiColors[0].rgbGreen = (BYTE)0;
	bitmapInfo->bmiColors[0].rgbRed = (BYTE)0;
	bitmapInfo->bmiColors[0].rgbReserved = (BYTE)0;
}

// [ **************** ] ..................................................
// [ 构造 24 位文件头 ] ..................................................
// [ **************** ] ..................................................
void CImage::Construct_24_FileHeader( BITMAPFILEHEADER* fileHeader, long imageHeight, long imageWidth )
{
	fileHeader->bfType = ((WORD) ('M' << 8) | 'B') ; 
	fileHeader->bfReserved1 = 0 ; 
	fileHeader->bfReserved2 = 0 ; 
	fileHeader->bfOffBits = 54 ;
	fileHeader->bfSize = fileHeader->bfOffBits + imageHeight * ( ( ( ( imageWidth * 3 ) + 3 ) / 4 ) * 4 ) ;
}

// [ ************** ] ....................................................
// [ 构造 32 位信息 ] ....................................................
// [ ************** ] ....................................................
void CImage::Construct_32_Info( BITMAPINFO* bitmapInfo, long imageHeight, long imageWidth )
{
	bitmapInfo->bmiHeader.biBitCount = 32;
	bitmapInfo->bmiHeader.biClrImportant = 0;
	bitmapInfo->bmiHeader.biClrUsed = 0;
	bitmapInfo->bmiHeader.biCompression = BI_RGB;
	bitmapInfo->bmiHeader.biHeight = - imageHeight;
	bitmapInfo->bmiHeader.biPlanes = 1;
	bitmapInfo->bmiHeader.biSizeImage = imageHeight * imageWidth * 4 ;
	bitmapInfo->bmiHeader.biSize = 40;
	bitmapInfo->bmiHeader.biWidth = imageWidth;
	bitmapInfo->bmiHeader.biXPelsPerMeter = 3780;
	bitmapInfo->bmiHeader.biYPelsPerMeter = 3780;

	bitmapInfo->bmiColors[0].rgbBlue = (BYTE)0;
    bitmapInfo->bmiColors[0].rgbGreen = (BYTE)0;
	bitmapInfo->bmiColors[0].rgbRed = (BYTE)0;
	bitmapInfo->bmiColors[0].rgbReserved = (BYTE)0;
}

// [ ************ ] ......................................................
// [ 保存彩色图像 ] ......................................................
// [ ************ ] ......................................................
void CImage::SaveImage( const CTMatrix< RGB_TRIPLE >& colorImage, const CString& fileName, int jpeg_quality ) 
{
	CString postfix = PostfixToFileName( fileName ); // [ 获取文件名后缀 ]

	if( postfix.CompareNoCase( "BMP" ) == 0 ) // [ BMP 图像 ]
	{
		SaveImageToBmpFile( colorImage, fileName ); // [ 保存彩色图像为 BMP 文件 ]
		return; // [ 结束返回 ]
	}
}   

// [ ************ ] ......................................................
// [ 保存灰度图像 ] ......................................................
// [ ************ ] ......................................................
void CImage::SaveImage( const CTMatrix< BYTE >& grayImage, const CString& fileName, int jpeg_quality ) 
{
	CString postfix = PostfixToFileName( fileName ); // [ 获取文件名后缀 ]

	if( postfix.CompareNoCase( "BMP" ) == 0 ) // [ BMP 图像 ]
	{
		SaveImageToBmpFile( grayImage, fileName ); // [ 保存灰度图像为 BMP 文件 ]
		return; // [ 结束返回 ]
	}
}

// [ ************ ] ......................................................
// [ 保存二值图像 ] ......................................................
// [ ************ ] ......................................................
void CImage::SaveImage( const CTMatrix< BlackWhite >& unicolorImage, const CString& fileName )
{
	CString postfix = PostfixToFileName( fileName ); // [ 获取文件名后缀 ]

	if( postfix.CompareNoCase( "BMP" ) == 0 ) // [ BMP 图像 ]
	{
		SaveImageToBmpFile( unicolorImage, fileName ); // [ 保存二值图像为 BMP 文件 ]
		return; // [ 结束返回 ]
	}
}

// [ *********************** ] ...........................................
// [ 保存彩色图像为 BMP 文件 ] ...........................................
// [ *********************** ] ...........................................
void CImage::SaveImageToBmpFile( const CTMatrix< RGB_TRIPLE >& colorImage, const CString& fileName )
{
	if( colorImage.IsNull() ) // [ 判断图像是否为空 ]
		return;

	CFile bitmapFile; // [ Bmp 文件 ]
	if( !bitmapFile.Open( fileName, CFile::modeCreate | CFile::modeWrite ) ) // [ 打开文件 ]
		return;

	long imageHeight = colorImage.GetRows( ); // [ 图像高度( 像素 ) ]
	long imageWidth = colorImage.GetColumns( ); // [ 图像宽度( 像素 ) ]
	long bytesPerMemoryRow = imageWidth * sizeof( RGB_TRIPLE ); // [ 内存中图像行存储字节数 ]
	long bytesPerFileRow = ( ( bytesPerMemoryRow + 3 ) / 4 ) * 4 ; // [ 文件中图像行存储字节数 ]

	BITMAPFILEHEADER* fileHeader = new BITMAPFILEHEADER ; // [ 申请文件头内存 ]
	BITMAPINFO* bitmapInfo = new BITMAPINFO ; // [ 申请位图信息内存 ]
	BYTE* bitmapData = new BYTE[ colorImage.GetSizeInBytes() ]; // [ 申请位图数据内存 ]
    BYTE* swapBuffer = ( bytesPerMemoryRow == bytesPerFileRow ) ? 
                       bitmapData : ( new BYTE[ imageHeight * bytesPerFileRow ] ); // [ 申请图像保存缓冲区 ]
	
	Construct_24_FileHeader( fileHeader, imageHeight, imageWidth ); // [ 构造 24 位文件头 ]
	Construct_24_Info( bitmapInfo, imageHeight, imageWidth ); // [ 构造 24 位信息 ]
	colorImage.ExportTo( bitmapData ); // [ 导出图像内容 ]
	if( bytesPerMemoryRow != bytesPerFileRow ) 
		for( int row = 0; row < imageHeight; row++ )
			memcpy( swapBuffer + row * bytesPerFileRow, 
			        bitmapData + row * bytesPerMemoryRow, 
					bytesPerMemoryRow ); // [ 设置图像保存缓冲区内容 ]

    bitmapFile.Write( fileHeader, sizeof( BITMAPFILEHEADER ) ); // [ 保存文件头 ]
	bitmapFile.Write( bitmapInfo, sizeof( BITMAPINFOHEADER ) ); // [ 保存信息头 ]
	bitmapFile.Write( swapBuffer, bytesPerFileRow * imageHeight ); // [ 保存图像内容 ]

	if( bytesPerMemoryRow != bytesPerFileRow ) delete [] swapBuffer; // [ 释放图像保存缓冲区 ]
	delete [] bitmapData; // [ 释放位图数据内存 ]
	delete bitmapInfo; // [ 释放位图信息内存 ]
	delete fileHeader; // [ 释放文件头内存 ]

	bitmapFile.Close(); // [ 关闭文件 ]
}

// [ *********************** ] ...........................................
// [ 保存灰度图像为 BMP 文件 ] ...........................................
// [ *********************** ] ...........................................
void CImage::SaveImageToBmpFile( const CTMatrix< BYTE >& grayImage, const CString& fileName )
{
	if( grayImage.IsNull() ) // [ 判断图像是否为空 ]
		return;

	CFile bitmapFile; // [ Bmp 文件 ]
	if( !bitmapFile.Open( fileName, CFile::modeCreate | CFile::modeWrite ) ) // [ 打开文件 ]
		return;

	long imageHeight = grayImage.GetRows(); // [ 图像高度( 像素 ) ]
	long imageWidth = grayImage.GetColumns(); // [ 图像宽度( 像素 ) ]
	long bytesPerFileRow = ( ( imageWidth + 3 ) / 4 ) * 4 ; // [ 文件中图像行存储字节数 ]

	BITMAPFILEHEADER* fileHeader = new BITMAPFILEHEADER ; // [ 申请文件头内存 ]
	BITMAPINFO* bitmapInfo = ( BITMAPINFO* )( new BYTE[ sizeof( BITMAPINFOHEADER ) + 256 * sizeof( RGBQUAD ) ] ); // [ 申请位图信息内存 ]
	BYTE* bitmapData = new BYTE[ grayImage.GetSizeInBytes() ]; // [ 申请位图数据内存 ]
	BYTE* swapBuffer = ( imageWidth == bytesPerFileRow ) ? 
                       bitmapData : ( new BYTE[ imageHeight * bytesPerFileRow ] ); // [ 申请图像保存缓冲区 ]

	Construct_8_FileHeader( fileHeader, imageHeight, imageWidth ); // [ 构造 8 位文件头 ]
	Construct_8_Info( bitmapInfo, imageHeight, imageWidth ); // [ 构造 8 位信息 ]
	grayImage.ExportTo( bitmapData ); // [ 导出图像内容 ]
	if( imageWidth != bytesPerFileRow ) 
		for( int row = 0; row < imageHeight; row++ )
			memcpy( swapBuffer + row * bytesPerFileRow, 
			        bitmapData + row * imageWidth, 
					imageWidth ); // [ 设置图像保存缓冲区内容 ]

	bitmapFile.Write( fileHeader, sizeof( BITMAPFILEHEADER ) ); // [ 保存文件头 ]
	bitmapFile.Write( bitmapInfo, sizeof( BITMAPINFOHEADER ) + 256 * sizeof( RGBQUAD ) ); // [ 保存信息头 ]
	bitmapFile.Write( swapBuffer, bytesPerFileRow * imageHeight ); // [ 保存图像内容 ]

	if( imageWidth != bytesPerFileRow ) delete [] swapBuffer; // [ 释放图像保存缓冲区 ]
	delete [] bitmapData; // [ 释放位图数据内存 ]
	delete [] bitmapInfo; // [ 释放位图信息内存 ]
	delete fileHeader; // [ 释放文件头内存 ]

	bitmapFile.Close(); // [ 关闭文件 ]
}

// [ *********************** ] ...........................................
// [ 保存二值图像为 BMP 文件 ] ...........................................
// [ *********************** ] ...........................................
void CImage::SaveImageToBmpFile( const CTMatrix< BlackWhite >& unicolorImage, const CString& fileName )
{
	if( unicolorImage.IsNull() ) // [ 判断图像是否为空 ]
		return; 

	CFile bitmapFile; // [ Bmp 文件 ]
	if( !bitmapFile.Open( fileName, CFile::modeCreate | CFile::modeWrite ) ) // [ 打开文件 ]
		return;

	long imageHeight = unicolorImage.GetRows(); // [ 图像高度( 像素 ) ]
	long imageWidth = unicolorImage.GetColumns(); // [ 图像宽度( 像素 ) ]
    long bytesPerMemoryRow = ( imageWidth + 7 ) / 8 ; // [ 内存中图像行存储字节数 ]
	long bytesPerFileRow = ( ( bytesPerMemoryRow + 3 ) / 4 ) * 4 ; // [ 文件中图像行存储字节数 ]

	BITMAPFILEHEADER* fileHeader = new BITMAPFILEHEADER ; // [ 申请文件头内存 ]
	BITMAPINFO* bitmapInfo = ( BITMAPINFO* )( new BYTE[ sizeof( BITMAPINFOHEADER ) + 2 * sizeof( RGBQUAD ) ] ); // [ 申请位图信息内存 ]
	BYTE* swapBuffer = new BYTE[ imageHeight * bytesPerFileRow ]; // [ 申请图像保存缓冲区 ]

	Construct_1_FileHeader( fileHeader, imageHeight, imageWidth ); // [ 构造 1 位文件头 ]
	Construct_1_Info( bitmapInfo, imageHeight, imageWidth ); // [ 构造 1 位信息 ]
	for( int row = 0; row < imageHeight; row++ )
		for( int column = 0; column < imageWidth; column++ )
		{
			long indexByte = column / 8 ; // [ 像素所在字节索引 ]
			long indexBit = 7 - column % 8 ; // [ 像素所在位索引( 相对最后一位 ) ]

			if( unicolorImage[row][column] == White )
				swapBuffer[ row * bytesPerFileRow + indexByte ] |= ( 1 << indexBit ); // [ 设置 1 ]
			else
				swapBuffer[ row * bytesPerFileRow + indexByte ] &= ( 1 << indexBit ) ^ 0xFF; // [ 设置 0 ]
		}

	bitmapFile.Write( fileHeader, sizeof( BITMAPFILEHEADER ) ); // [ 保存文件头 ]
	bitmapFile.Write( bitmapInfo, sizeof( BITMAPINFOHEADER ) + 2 * sizeof( RGBQUAD ) ); // [ 保存信息头 ]
	bitmapFile.Write( swapBuffer, bytesPerFileRow * imageHeight ); // [ 保存图像内容 ]

	delete [] swapBuffer; // [ 释放图像保存缓冲区 ]
	delete [] bitmapInfo; // [ 释放位图信息内存 ]
	delete fileHeader; // [ 释放文件头内存 ]

	bitmapFile.Close(); // [ 关闭文件 ]
}
