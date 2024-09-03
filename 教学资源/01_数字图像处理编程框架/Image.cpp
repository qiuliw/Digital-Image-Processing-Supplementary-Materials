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
// [ ȱʡ���캯�� ] ......................................................
// [ ************ ] ......................................................
CImage::CImage()
{
	m_imageType = NoImage; // [ ��ʼ��ͼ������ ]
}

// [ ************ ] ......................................................
// [ ���ƹ��캯�� ] ......................................................
// [ ************ ] ......................................................
CImage::CImage( const CImage& image )
{
	m_imageType = NoImage; // [ ��ʼ��ͼ������ ]

	ImportFrom( image ); // [ ����ͼ������ ]
}

// [ ******** ] ..........................................................
// [ �������� ] ..........................................................
// [ ******** ] ..........................................................
CImage::~CImage()
{

}

// [ ************** ] ....................................................
// [ ���ظ�ֵ������ ] ....................................................
// [ ************** ] ....................................................
CImage& CImage::operator= ( const CImage& image )
{
	ImportFrom( image ); // [ ����ͼ������ ]

	return * this; // [ ���ص�ǰ���� ]
}

// [ ************ ] ......................................................
// [ ����ͼ���ļ� ] ......................................................
// [ ************ ] ......................................................
void CImage::ImportFrom( const CString& fileName )
{
	m_imageType = NoImage; // [ ��ʼ��ͼ������ ]

	CString postfix = PostfixToFileName( fileName ); // [ ��ȡ�ļ�����׺ ]

	if( postfix.CompareNoCase( "BMP" ) == 0 ) // [ BMP ͼ�� ]
	{
		ImportFromBmpFile( fileName ); // [ ���� BMP ͼ���ļ� ]
		return; // [ �������� ]
	}

	if( postfix.CompareNoCase( "RAW" ) == 0 ) // [ ����� RAW ͼ���ʽ����ô ... ]
	{
		Import_from_raw_file( fileName ); // [ ���� RAW ͼ���ļ� ]
		return; // [ �������� ]
	}
}

// [ ************ ] ......................................................
// [ ����ͼ������ ] ......................................................
// [ ************ ] ......................................................
void CImage::ImportFrom( const CImage& image )
{
	m_imageType = image.m_imageType; // [ ͼ������ ]

	m_colorImage = image.m_colorImage;       // [ ��ɫͼ������ ]
	m_grayImage = image.m_grayImage;         // [ �Ҷ�ͼ������ ]
	m_unicolorImage = image.m_unicolorImage; // [ ��ֵͼ������ ]
}

// [ **************** ] ..................................................
// [ �����ɫͼ������ ] ..................................................
// [ **************** ] ..................................................
void CImage::ImportFrom( const CTMatrix< RGB_TRIPLE >& color_image )
{
	m_imageType = Color;        // [ ͼ������ ]
	m_colorImage = color_image; // [ ͼ������ ]
}

// [ **************** ] ..................................................
// [ ����Ҷ�ͼ������ ] ..................................................
// [ **************** ] ..................................................
void CImage::ImportFrom( const CTMatrix< BYTE >& gray_image )
{
	m_imageType = Gray;       // [ ͼ������ ]
	m_grayImage = gray_image; // [ ͼ������ ]
}

// [ **************** ] ..................................................
// [ �����ֵͼ������ ] ..................................................
// [ **************** ] ..................................................
void CImage::ImportFrom( const CTMatrix< BlackWhite >& unicolor_image )
{
	m_imageType = Unicolor;           // [ ͼ������ ]
	m_unicolorImage = unicolor_image; // [ ͼ������ ]
}

// [ ******** ] ..........................................................
// [ ��ʾͼ�� ] ..........................................................
// [ ******** ] ..........................................................
void CImage::ShowImage( CDC* pDC, CPoint leftTop, CSize displaySize ) const
{
	switch( m_imageType ) // [ ͼ������ ]
	{
	case Color: // [ ��ɫͼ�� ]
		ShowImage( m_colorImage, pDC, leftTop, displaySize ); // [ ��ʾ��ɫͼ�� ]
		break;

	case Gray: // [ �Ҷ�ͼ�� ]
		ShowImage( m_grayImage, pDC, leftTop, displaySize ); // [ ��ʾ�Ҷ�ͼ�� ]
		break;

	case Unicolor: // [ ��ֵͼ�� ]
		ShowImage( m_unicolorImage, pDC, leftTop, displaySize ); // [ ��ʾ��ֵͼ�� ]
		break;
	}
}

// [ ******** ] ..........................................................
// [ ����ͼ�� ] ..........................................................
// [ ******** ] ..........................................................
void CImage::SaveImage( const CString& fileName, int jpeg_quality ) const
{
	switch( m_imageType ) // [ ͼ������ ]
	{
	case Color: // [ ��ɫͼ�� ]
		SaveImage( m_colorImage, fileName, jpeg_quality ); // [ �����ɫͼ�� ]
		break;

	case Gray: // [ �Ҷ�ͼ�� ]
		SaveImage( m_grayImage, fileName, jpeg_quality ); // [ ����Ҷ�ͼ�� ]
		break;

	case Unicolor: // [ ��ֵͼ�� ]
		SaveImage( m_unicolorImage, fileName ); // [ �����ֵͼ�� ]
		break;
	}
}

// [ ******** ] ..........................................................
// [ ͼ������ ] ..........................................................
// [ ******** ] ..........................................................
CImage::ImageType CImage::GetImageType() const
{
	return m_imageType;
}

// [ ************ ] ......................................................
// [ ��ɫͼ������ ] ......................................................
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
// [ �Ҷ�ͼ������ ] ......................................................
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
// [ ��ֵͼ������ ] ......................................................
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
// [ ͼ��߶� ] ..........................................................
// [ ******** ] ..........................................................
long CImage::Get_image_height() const
{
	switch( m_imageType ) // [ ͼ������ ]
	{
	case Color: // [ ��ɫͼ�� ]
		return m_colorImage.GetRows();
		break;

	case Gray: // [ �Ҷ�ͼ�� ]
		return m_grayImage.GetRows();
		break;

	case Unicolor: // [ ��ֵͼ�� ]
		return m_unicolorImage.GetRows();
		break;

	default: // [ ��ͼ�� ]
		return 0;
		break;
	}
}

// [ ******** ] ..........................................................
// [ ͼ���� ] ..........................................................
// [ ******** ] ..........................................................
long CImage::Get_image_width() const
{
	switch( m_imageType ) // [ ͼ������ ]
	{
	case Color: // [ ��ɫͼ�� ]
		return m_colorImage.GetColumns();
		break;

	case Gray: // [ �Ҷ�ͼ�� ]
		return m_grayImage.GetColumns();
		break;

	case Unicolor: // [ ��ֵͼ�� ]
		return m_unicolorImage.GetColumns();
		break;

	default: // [ ��ͼ�� ]
		return 0;
		break;
	}
}

// [ ******** ] ..........................................................
// [ ͼ��ߴ� ] ..........................................................
// [ ******** ] ..........................................................
CImagePoint CImage::Get_image_size() const
{
	switch( m_imageType ) // [ ͼ������ ]
	{
	case Color: // [ ��ɫͼ�� ]
		return m_colorImage.Get_size();
		break;

	case Gray: // [ �Ҷ�ͼ�� ]
		return m_grayImage.Get_size();
		break;

	case Unicolor: // [ ��ֵͼ�� ]
		return m_unicolorImage.Get_size();
		break;

	default: // [ ��ͼ�� ]
		return CImagePoint( 0, 0 );
		break;
	}
}

// [ ************** ] ....................................................
// [ �Ƿ��ǲ�ɫͼ�� ] ....................................................
// [ ************** ] ....................................................
bool CImage::IsColorImage() const
{
	return ( m_imageType == Color );
}

// [ ************** ] ....................................................
// [ �Ƿ��ǻҶ�ͼ�� ] ....................................................
// [ ************** ] ....................................................
bool CImage::IsGrayImage() const
{
	return ( m_imageType == Gray );
}

// [ ************** ] ....................................................
// [ �Ƿ��Ƕ�ֵͼ�� ] ....................................................
// [ ************** ] ....................................................
bool CImage::IsUnicolorImage() const
{
	return ( m_imageType == Unicolor );
}

// [ ******** ] ..........................................................
// [ �Ƿ�Ϊ�� ] ..........................................................
// [ ******** ] ..........................................................
bool CImage::IsNull() const
{
	return ( m_imageType == NoImage );
}

// [ ************** ] ....................................................
// [ ��ȡ�ļ�����׺ ] ....................................................
// [ ************** ] ....................................................
CString CImage::PostfixToFileName( const CString& fileName ) 
{
	CString postfix; // [ �ļ�����׺ ]

	int position = fileName.ReverseFind('.'); // [ �ļ��������һ�����ַ���λ�� ]

	if( position != -1 ) // [ �ļ����Ƿ���ں�׺ ]
	{
		postfix = fileName.Right( fileName.GetLength() - position - 1 ); // [ ��ȡ�ļ�����׺ ]
		 
	    postfix.MakeUpper(); // [ ��д�ļ�����׺ ]
	}

	return postfix; // [ �����ļ�����׺ ]
}

// [ ****************************** ] ....................................
// [ �豸���λͼת��Ϊ�豸�޹�λͼ ] ....................................
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
// [ �����豸���λͼ ] ..................................................
// [ **************** ] ..................................................
void CImage::ImportFrom( CBitmap& bitmap )
{
	m_imageType = NoImage; // [ ��ʼ��ͼ������ ]

	// Convert the bitmap to a DIB
	HANDLE hDIB = DDBToDIB( bitmap, BI_RGB, NULL );

	if( hDIB == NULL ) return;

	// [ �����豸�޹�λͼ ]
	ImportFrom( hDIB );

	// Free the memory allocated by DDBToDIB for the DIB
	GlobalFree( hDIB );
}

// [ **************** ] ..................................................
// [ �����豸�޹�λͼ ] ..................................................
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

	BITMAPFILEHEADER* bitmapFileHeader; // [ �ļ�ͷָ�� ]
	BITMAPINFOHEADER* bitmapInfoHeader; // [ ��Ϣͷָ�� ]
	BITMAPINFO* bitmapInfo; // [ ��Ϣָ�� ]
	RGBQUAD* colorTemplate; // [ ��ɫ��ָ�� ]
	BYTE* bitmapData; // [ ����ָ�� ]

	bitmapFileHeader = &hdr; // [ �����ļ�ͷָ�� ]
	bitmapInfoHeader = lpbi; // [ ������Ϣͷָ�� ]
	bitmapInfo = ( BITMAPINFO* )bitmapInfoHeader; // [ ������Ϣָ�� ]
	colorTemplate = ( RGBQUAD* )bitmapInfo->bmiColors; // [ ���õ�ɫ��ָ�� ] 
	bitmapData = (BYTE*)hDIB + bitmapFileHeader->bfOffBits - sizeof( hdr ); // [ ��������ָ�� ]

    if( bitmapFileHeader->bfType != ((WORD) ('M' << 8) | 'B') ) // [ ��� BMP �ļ��ĺϷ��� ]
	{
		return; // [ �������� ]
	}

    long imageWidth = bitmapInfoHeader->biWidth; // [ ͼ����( ���� ) ]
	long imageHeight = bitmapInfoHeader->biHeight; // [ ͼ��߶�( ���� ) ]	
	imageHeight = ( imageHeight > 0 ) ? imageHeight : - imageHeight ; // [ ����ͼ��߶� ]
	bool isBottomUp = bitmapInfoHeader->biHeight > 0; // [ ͼ��洢˳�� ]
	long bitCount = bitmapInfoHeader->biBitCount; // [ ���ش洢λ�� ]
	long bytesPerMemoryRow = ( imageWidth * bitCount + 7 ) / 8 ; // [ �ڴ���ͼ���д洢�ֽ��� ]
	long bytesPerFileRow = ( ( bytesPerMemoryRow + 3 ) / 4 ) * 4 ; // [ �ļ���ͼ���д洢�ֽ��� ]

	switch( bitCount ) // [ ���ش洢λ�� ]
	{
	case 1: // [ ��ֵͼ�� ]
		ImportFrom_1_BmpFile( bitmapData, colorTemplate, isBottomUp,
			                  imageHeight, imageWidth,
							  bytesPerMemoryRow, bytesPerFileRow ); // [ ���� 1 λ BMP ͼ������ ]
		break;

	case 8: // [ �Ҷ�ͼ�� ]
		ImportFrom_8_BmpFile( bitmapData, colorTemplate, isBottomUp,
			                  imageHeight, imageWidth,
							  bytesPerMemoryRow, bytesPerFileRow ); // [ ���� 8 λ BMP ͼ������ ]
		break;

	case 24: // [ ��ɫͼ�� ]
		ImportFrom_24_BmpFile( bitmapData, isBottomUp, 
			                   imageHeight, imageWidth, 
							   bytesPerMemoryRow, bytesPerFileRow ); // [ ���� 24 λ BMP ͼ������ ]
		break;

	case 32: // [ ��ɫͼ�� ]
		ImportFrom_32_BmpFile( bitmapData, isBottomUp, 
			                   imageHeight, imageWidth, 
							   bytesPerMemoryRow, bytesPerFileRow ); // [ ���� 32 λ BMP ͼ������ ]
		break;
	}
}

// [ ***************** ] .................................................
// [ ���� BMP ͼ���ļ� ] .................................................
// [ ***************** ] .................................................
void CImage::ImportFromBmpFile( const CString& fileName )
{
	CFile bitmapFile; // [ ͼ���ļ� ]

	if( !bitmapFile.Open( fileName, CFile::modeRead ) ) // [ ��ͼ���ļ� ]
		return;

	long fileLength = long( bitmapFile.GetLength() ); // [ ͼ���ļ�����( �ֽ��� ) ]
	BYTE* fileBuffer = new BYTE[ fileLength ]; // [ ����ͼ���ļ����� ]
	bitmapFile.Read( fileBuffer, fileLength ); // [ ��ȡ����ͼ���ļ� ]

	BITMAPFILEHEADER* bitmapFileHeader; // [ �ļ�ͷָ�� ]
	BITMAPINFOHEADER* bitmapInfoHeader; // [ ��Ϣͷָ�� ]
	BITMAPINFO* bitmapInfo; // [ ��Ϣָ�� ]
	RGBQUAD* colorTemplate; // [ ��ɫ��ָ�� ]
	BYTE* bitmapData; // [ ����ָ�� ]

	bitmapFileHeader = ( BITMAPFILEHEADER* )fileBuffer; // [ �����ļ�ͷָ�� ]
	bitmapInfoHeader = ( BITMAPINFOHEADER* )( fileBuffer + sizeof( BITMAPFILEHEADER ) ); // [ ������Ϣͷָ�� ]
	bitmapInfo = ( BITMAPINFO* )bitmapInfoHeader; // [ ������Ϣָ�� ]
	colorTemplate = ( RGBQUAD* )bitmapInfo->bmiColors; // [ ���õ�ɫ��ָ�� ] 
	bitmapData = fileBuffer + bitmapFileHeader->bfOffBits; // [ ��������ָ�� ]

    if( bitmapFileHeader->bfType != ((WORD) ('M' << 8) | 'B') ) // [ ��� BMP �ļ��ĺϷ��� ]
	{
		delete [] fileBuffer; // [ �ͷ�ͼ���ļ����� ]
	    bitmapFile.Close(); // [ �ر�ͼ���ļ� ]
		return; // [ �������� ]
	}

    long imageWidth = bitmapInfoHeader->biWidth; // [ ͼ����( ���� ) ]
	long imageHeight = bitmapInfoHeader->biHeight; // [ ͼ��߶�( ���� ) ]	
	imageHeight = ( imageHeight > 0 ) ? imageHeight : - imageHeight ; // [ ����ͼ��߶� ]
	bool isBottomUp = bitmapInfoHeader->biHeight > 0; // [ ͼ��洢˳�� ]
	long bitCount = bitmapInfoHeader->biBitCount; // [ ���ش洢λ�� ]
	long bytesPerMemoryRow = ( imageWidth * bitCount + 7 ) / 8 ; // [ �ڴ���ͼ���д洢�ֽ��� ]
	long bytesPerFileRow = ( ( bytesPerMemoryRow + 3 ) / 4 ) * 4 ; // [ �ļ���ͼ���д洢�ֽ��� ]

	switch( bitCount ) // [ ���ش洢λ�� ]
	{
	case 1: // [ ��ֵͼ�� ]
		ImportFrom_1_BmpFile( bitmapData, colorTemplate, isBottomUp,
			                  imageHeight, imageWidth,
							  bytesPerMemoryRow, bytesPerFileRow ); // [ ���� 1 λ BMP ͼ������ ]
		break;

	case 8: // [ �Ҷ�ͼ�� ]
		ImportFrom_8_BmpFile( bitmapData, colorTemplate, isBottomUp,
			                  imageHeight, imageWidth,
							  bytesPerMemoryRow, bytesPerFileRow ); // [ ���� 8 λ BMP ͼ������ ]
		break;

	case 24: // [ ��ɫͼ�� ]
		ImportFrom_24_BmpFile( bitmapData, isBottomUp, 
			                   imageHeight, imageWidth, 
							   bytesPerMemoryRow, bytesPerFileRow ); // [ ���� 24 λ BMP ͼ������ ]
		break;

	case 32: // [ ��ɫͼ�� ]
		ImportFrom_32_BmpFile( bitmapData, isBottomUp, 
			                   imageHeight, imageWidth, 
							   bytesPerMemoryRow, bytesPerFileRow ); // [ ���� 32 λ BMP ͼ������ ]
		break;
	}

	delete [] fileBuffer; // [ �ͷ�ͼ���ļ����� ]

	bitmapFile.Close(); // [ �ر�ͼ���ļ� ]
}

// [ *********************** ] ...........................................
// [ ���� 32 λ BMP ͼ������ ] ...........................................
// [ *********************** ] ...........................................
void CImage::ImportFrom_32_BmpFile( BYTE* bitmapData, bool isBottomUp,
		                            long imageHeight, long imageWidth, 
								    long bytesPerMemoryRow, long bytesPerFileRow )
{
	m_imageType = Color; // [ ��Ϊ��ɫͼ�� ]
	m_colorImage.Construction( imageHeight, imageWidth ); // [ ����ͼ�� ]

	BYTE* swapBuffer = new BYTE[ imageWidth * 3 * imageHeight ]; // [ ���뻺���� ]

	for( int row = 0; row < imageHeight; row++ )
		for( int column = 0; column < imageWidth; column ++ )
		{
			if( isBottomUp ) // [ ���¶���, ������ҵ�ͼ�����ݴ洢˳�� ]
			{
				swapBuffer[ row * imageWidth * 3 + column * 3     ] = bitmapData[ ( imageHeight - row - 1 ) * bytesPerFileRow + column * 4 ];
				swapBuffer[ row * imageWidth * 3 + column * 3 + 1 ] = bitmapData[ ( imageHeight - row - 1 ) * bytesPerFileRow + column * 4 + 1 ];
				swapBuffer[ row * imageWidth * 3 + column * 3 + 2 ] = bitmapData[ ( imageHeight - row - 1 ) * bytesPerFileRow + column * 4 + 2 ];
			}
			else // [ ���϶���, ������ҵ�ͼ�����ݴ洢˳�� ]
			{
				swapBuffer[ row * imageWidth * 3 + column * 3     ] = bitmapData[ row * bytesPerFileRow + column * 4 ];
				swapBuffer[ row * imageWidth * 3 + column * 3 + 1 ] = bitmapData[ row * bytesPerFileRow + column * 4 + 1 ];
				swapBuffer[ row * imageWidth * 3 + column * 3 + 2 ] = bitmapData[ row * bytesPerFileRow + column * 4 + 2 ];
			}
		}
		
	m_colorImage.ImportFrom( swapBuffer ); // [ ����ͼ������ ]

	delete [] swapBuffer; // [ �ͷŻ����� ]
}

// [ ***************** ] .................................................
// [ ���� RAW ͼ���ļ� ] .................................................
// [ ***************** ] .................................................
void CImage::Import_from_raw_file( const CString& file_name )
{
	// [ �� RAW ��ʽͼ���뺯����ֻ����һ�� RAW ��ʽ����ͼ�����ظ߶Ⱥ� ]
	// [ ��ȶ�Ϊ 512������ͼ�������ǰ��ա�BGR��BGR��...����˳����д�  ]
	// [ ��������������ʽ�� RAW ͼ���ļ�����һ�ɷ������ݶ�ȡ��          ]

	const long image_height = 512; // [ ͼ�����ظ߶� ]
	const long image_width = 512;  // [ ͼ�����ؿ�� ]

	CFile raw_file( file_name, CFile::modeRead ); // [ ���� RAW ͼ���ļ� ]

	if( raw_file.GetLength() != image_height * image_width * 3 ) // [ ���ͼ��ߴ粻ƥ�䣬��ô ... ]
	{
		raw_file.Close(); // [ �ر� RAW ͼ���ļ� ]
		return;           // [ �������� ]
	}

	m_imageType = Color;                                    // [ ��Ϊ��ɫͼ�� ]
	m_colorImage.Construction( image_height, image_width ); // [ ����ͼ�� ]

	raw_file.Read( &( m_colorImage[0][0] ), m_colorImage.GetSizeInBytes() ); // [ ��ȡ RAW ͼ���ļ����� ]

	raw_file.Close(); // [ �ر� RAW ͼ���ļ� ]
}

// [ *********************** ] ...........................................
// [ ���� 24 λ BMP ͼ������ ] ...........................................
// [ *********************** ] ...........................................
void CImage::ImportFrom_24_BmpFile( BYTE* bitmapData, bool isBottomUp, 
								    long imageHeight, long imageWidth, 
									long bytesPerMemoryRow, long bytesPerFileRow )
{
	m_imageType = Color; // [ ��Ϊ��ɫͼ�� ]
	m_colorImage.Construction( imageHeight, imageWidth ); // [ ����ͼ�� ]

	BYTE* swapBuffer = new BYTE[ bytesPerMemoryRow * imageHeight ]; // [ ���뻺���� ]

	if( isBottomUp ) // [ ���¶���, ������ҵ�ͼ�����ݴ洢˳�� ]
		for( int row = 0; row < imageHeight; row++ )
			memcpy( swapBuffer + row * bytesPerMemoryRow, 
			        bitmapData + ( imageHeight - row - 1 ) * bytesPerFileRow,
				    bytesPerMemoryRow); // [ ͼ�����·�ת ]
	else // [ ���϶���, ������ҵ�ͼ�����ݴ洢˳�� ]
		for( int row = 0; row < imageHeight; row++ )
			memcpy( swapBuffer + row * bytesPerMemoryRow,
			        bitmapData + row * bytesPerFileRow,
					bytesPerMemoryRow);
	
	m_colorImage.ImportFrom( swapBuffer ); // [ ����ͼ������ ]

	delete [] swapBuffer; // [ �ͷŻ����� ]
}

// [ ********************** ] ............................................
// [ ���� 8 λ BMP ͼ������ ] ............................................
// [ ********************** ] ............................................
void CImage::ImportFrom_8_BmpFile( BYTE* bitmapData, RGBQUAD* colorTemplate, bool isBottomUp,
		                           long imageHeight, long imageWidth,
							       long bytesPerMemoryRow, long bytesPerFileRow )
{
	m_imageType = Gray; // [ ��Ϊ�Ҷ�ͼ�� ]
	m_grayImage.Construction( imageHeight, imageWidth ); // [ ����ͼ�� ]

    BYTE* swapBuffer = new BYTE[ imageHeight * imageWidth ]; // [ ���뻺���� ]
	
	for( int row = 0; row < imageHeight; row++ )
		for( int column = 0; column < imageWidth; column++ )
		{
			BYTE colorIndex; // [ ��ɫ������ ]
			if( isBottomUp ) // [ ���¶���, ������ҵ�ͼ�����ݴ洢˳�� ]
				colorIndex = bitmapData[ ( imageHeight - row - 1 ) * bytesPerFileRow + column ];  
			else // [ ���϶���, ������ҵ�ͼ�����ݴ洢˳�� ]
				colorIndex = bitmapData[ row * bytesPerFileRow + column ];

			RGBQUAD quad = colorTemplate[ colorIndex ]; // [ ���ҵ�ɫ�� ]
			BYTE maxComponent = max( max( quad.rgbBlue, quad.rgbGreen ), quad.rgbRed ) ; // [ �����ɫ���� ]
			swapBuffer[ row * imageWidth + column ] = maxComponent ; // [ �Ҷ����� ]
		}

	m_grayImage.ImportFrom( swapBuffer ); // [ ����ͼ������ ]

	delete [] swapBuffer; // [ �ͷŻ����� ]
}

// [ ********************** ] ............................................
// [ ���� 1 λ BMP ͼ������ ] ............................................
// [ ********************** ] ............................................
void CImage::ImportFrom_1_BmpFile( BYTE* bitmapData, RGBQUAD* colorTemplate, bool isBottomUp,
		                           long imageHeight, long imageWidth,
							       long bytesPerMemoryRow, long bytesPerFileRow )
{
	m_imageType = Unicolor; // [ ��Ϊ��ֵͼ�� ]
	m_unicolorImage.Construction( imageHeight, imageWidth ); // [ ����ͼ�� ]

	BlackWhite* swapBuffer = new BlackWhite[ imageWidth * imageHeight ] ; // [ ���뻺���� ]
	
	for( int row = 0; row < imageHeight; row++ )
		for( int column = 0; column < imageWidth; column++ )
		{
			long indexByte = column / 8 ; // [ ���������ֽ����� ]
			long indexBit = 7 - column % 8 ; // [ ��������λ����( ������һλ ) ]

			BYTE entireByte; // [ ���������ֽ� ]
			if( isBottomUp ) // [ ���¶���, ������ҵ�ͼ�����ݴ洢˳�� ]
				entireByte = bitmapData[ ( imageHeight - row - 1 ) * bytesPerFileRow + indexByte ]; 
			else // [ ���϶���, ������ҵ�ͼ�����ݴ洢˳�� ]
				entireByte = bitmapData[ row * bytesPerFileRow + indexByte ];

			BYTE colorIndex = ( entireByte >> indexBit ) & 1 ; // [ ��ɫ������ ]
			RGBQUAD quad = colorTemplate[ colorIndex ]; // [ ���ҵ�ɫ�� ]
			BYTE maxComponent = max( max( quad.rgbBlue, quad.rgbGreen ), quad.rgbRed ) ; // [ �����ɫ���� ]
			swapBuffer[ row * imageWidth + column ] = ( maxComponent > 128 ) ? White : Black ; // [ ��ֵת�� ]
		}

	m_unicolorImage.ImportFrom( swapBuffer ); // [ ����ͼ������ ]

	delete [] swapBuffer; // [ �ͷŻ����� ]
}

// [ ************ ] ......................................................
// [ ��ʾ��ɫͼ�� ] ......................................................
// [ ************ ] ......................................................
void CImage::ShowImage( const CTMatrix< RGB_TRIPLE >& colorImage, CDC* pDC, CPoint leftTop, CSize displaySize )
{
	if( colorImage.IsNull() ) // [ �ж�ͼ���Ƿ�Ϊ�� ]
		return;

	long imageHeight = colorImage.GetRows( ); // [ ͼ��߶�( ���� ) ]
	long imageWidth = colorImage.GetColumns( ); // [ ͼ����( ���� ) ]
	long bytesPerMemoryRow = imageWidth * sizeof( RGB_TRIPLE ); // [ �ڴ���ͼ���д洢�ֽ��� ]
	long bytesPerFileRow = ( ( bytesPerMemoryRow + 3 ) / 4 ) * 4 ; // [ �ļ���ͼ���д洢�ֽ��� ]

	BITMAPINFO* bitmapInfo = new BITMAPINFO ; // [ ����λͼ��Ϣ�ڴ� ]
	BYTE* bitmapData = new BYTE[ colorImage.GetSizeInBytes() ]; // [ ����λͼ�����ڴ� ]
    BYTE* swapBuffer = ( bytesPerMemoryRow == bytesPerFileRow ) ? 
                       bitmapData : ( new BYTE[ imageHeight * bytesPerFileRow ] ); // [ ����ͼ����ʾ������ ]
	
	Construct_24_Info( bitmapInfo, imageHeight, imageWidth ); // [ ���� 24 λ��Ϣ ]
	colorImage.ExportTo( bitmapData ); // [ ����ͼ������ ]
	if( bytesPerMemoryRow != bytesPerFileRow ) 
		for( int row = 0; row < imageHeight; row++ )
			memcpy( swapBuffer + row * bytesPerFileRow, 
			        bitmapData + row * bytesPerMemoryRow, 
					bytesPerMemoryRow ); // [ ����ͼ����ʾ���������� ]

    if( displaySize == CSize(0, 0) ) // [ ������ʾ ]
	{
		::SetDIBitsToDevice( pDC->GetSafeHdc(), leftTop.x, leftTop.y,
		                     (DWORD)imageWidth, (DWORD)imageHeight,
		                     0, 0, 0, (UINT)imageHeight,
							 swapBuffer, bitmapInfo,
		                     DIB_RGB_COLORS);
	}
	else // [ ������ʾ ]
	{
		int oldMode = pDC->GetStretchBltMode( ); // [ ����ɵ�λͼ����ģʽ ]
		pDC->SetStretchBltMode( COLORONCOLOR ); // [ �����µ�λͼ����ģʽ ]

        ::StretchDIBits( pDC->GetSafeHdc(), leftTop.x, leftTop.y,
		                 displaySize.cx, displaySize.cy,
		                 0, 0, imageWidth, imageHeight,
						 swapBuffer, bitmapInfo,
		                 DIB_RGB_COLORS, SRCCOPY);

		pDC->SetStretchBltMode( oldMode ); // [ �ָ��ɵ�λͼ����ģʽ ]
	}

	if( bytesPerMemoryRow != bytesPerFileRow ) delete [] swapBuffer; // [ �ͷ�ͼ����ʾ������ ]
	delete [] bitmapData; // [ �ͷ�λͼ�����ڴ� ]
	delete bitmapInfo; // [ �ͷ�λͼ��Ϣ�ڴ� ]

}

// [ ************ ] ......................................................
// [ ��ʾ�Ҷ�ͼ�� ] ......................................................
// [ ************ ] ......................................................
void CImage::ShowImage( const CTMatrix< BYTE >& grayImage, CDC* pDC, CPoint leftTop, CSize displaySize )
{
	if( grayImage.IsNull() ) // [ �ж�ͼ���Ƿ�Ϊ�� ]
		return;

	long imageHeight = grayImage.GetRows(); // [ ͼ��߶�( ���� ) ]
	long imageWidth = grayImage.GetColumns(); // [ ͼ����( ���� ) ]
	long bytesPerFileRow = ( ( imageWidth + 3 ) / 4 ) * 4 ; // [ �ļ���ͼ���д洢�ֽ��� ]

	BITMAPINFO* bitmapInfo = ( BITMAPINFO* )( new BYTE[ sizeof( BITMAPINFOHEADER ) + 256 * sizeof( RGBQUAD ) ] ); // [ ����λͼ��Ϣ�ڴ� ]
	BYTE* bitmapData = new BYTE[ grayImage.GetSizeInBytes() ]; // [ ����λͼ�����ڴ� ]
	BYTE* swapBuffer = ( imageWidth == bytesPerFileRow ) ? 
                       bitmapData : ( new BYTE[ imageHeight * bytesPerFileRow ] ); // [ ����ͼ����ʾ������ ]

	Construct_8_Info( bitmapInfo, imageHeight, imageWidth ); // [ ���� 8 λ��Ϣ ]
	grayImage.ExportTo( bitmapData ); // [ ����ͼ������ ]
	if( imageWidth != bytesPerFileRow ) 
		for( int row = 0; row < imageHeight; row++ )
			memcpy( swapBuffer + row * bytesPerFileRow, 
			        bitmapData + row * imageWidth, 
					imageWidth ); // [ ����ͼ����ʾ���������� ]

	if( displaySize == CSize(0, 0) ) // [ ������ʾ ]
	{
		::SetDIBitsToDevice( pDC->GetSafeHdc(), leftTop.x, leftTop.y,
		                     (DWORD)imageWidth, (DWORD)imageHeight,
		                     0, 0, 0, (UINT)imageHeight,
							 swapBuffer, bitmapInfo,
		                     DIB_RGB_COLORS);
	}
	else // [ ������ʾ ]
	{
		int oldMode = pDC->GetStretchBltMode( ); // [ ����ɵ�λͼ����ģʽ ]
		pDC->SetStretchBltMode( COLORONCOLOR ); // [ �����µ�λͼ����ģʽ ]

        ::StretchDIBits( pDC->GetSafeHdc(), leftTop.x, leftTop.y,
		                 displaySize.cx, displaySize.cy,
		                 0, 0, imageWidth, imageHeight,
						 swapBuffer, bitmapInfo,
		                 DIB_RGB_COLORS, SRCCOPY);

		pDC->SetStretchBltMode( oldMode ); // [ �ָ��ɵ�λͼ����ģʽ ]
	}

	if( imageWidth != bytesPerFileRow ) delete [] swapBuffer; // [ �ͷ�ͼ����ʾ������ ]
	delete [] bitmapData; // [ �ͷ�λͼ�����ڴ� ]
	delete [] bitmapInfo; // [ �ͷ�λͼ��Ϣ�ڴ� ]
}

// [ ************ ] ......................................................
// [ ��ʾ��ֵͼ�� ] ......................................................
// [ ************ ] ......................................................
void CImage::ShowImage( const CTMatrix< BlackWhite >& unicolorImage, CDC* pDC, CPoint leftTop, CSize displaySize )
{
	if( unicolorImage.IsNull() ) // [ �ж�ͼ���Ƿ�Ϊ�� ]
		return;

	long imageHeight = unicolorImage.GetRows(); // [ ͼ��߶�( ���� ) ]
	long imageWidth = unicolorImage.GetColumns(); // [ ͼ����( ���� ) ]

	BITMAPINFO* bitmapInfo = new BITMAPINFO ; // [ ����λͼ��Ϣ�ڴ� ]
	BYTE* bitmapData = new BYTE[ unicolorImage.GetSizeInBytes() ]; // [ ����λͼ�����ڴ� ]

	Construct_32_Info( bitmapInfo, imageHeight, imageWidth ); // [ ���� 32 ��Ϣ ]
	unicolorImage.ExportTo( bitmapData ); // [ ����ͼ������ ]

	if( displaySize == CSize(0, 0) ) // [ ������ʾ ]
	{
		::SetDIBitsToDevice( pDC->GetSafeHdc(), leftTop.x, leftTop.y,
		                     (DWORD)imageWidth, (DWORD)imageHeight,
		                     0, 0, 0, (UINT)imageHeight,
							 bitmapData, bitmapInfo,
		                     DIB_RGB_COLORS);
	}
	else // [ ������ʾ ]
	{
		int oldMode = pDC->GetStretchBltMode( ); // [ ����ɵ�λͼ����ģʽ ]
		pDC->SetStretchBltMode( COLORONCOLOR ); // [ �����µ�λͼ����ģʽ ]

        ::StretchDIBits( pDC->GetSafeHdc(), leftTop.x, leftTop.y,
		                 displaySize.cx, displaySize.cy,
		                 0, 0, imageWidth, imageHeight,
						 bitmapData, bitmapInfo,
		                 DIB_RGB_COLORS, SRCCOPY);

		pDC->SetStretchBltMode( oldMode ); // [ �ָ��ɵ�λͼ����ģʽ ]
	}

	delete [] bitmapData; // [ �ͷ�λͼ�����ڴ� ]
	delete bitmapInfo; // [ �ͷ�λͼ��Ϣ�ڴ� ]
}

// [ ************* ] .....................................................
// [ ���� 1 λ��Ϣ ] .....................................................
// [ ************* ] .....................................................
void CImage::Construct_1_Info( BITMAPINFO* bitmapInfo, long imageHeight, long imageWidth )
{
	long bytesPerMemoryRow = ( imageWidth + 7 ) / 8 ; // [ �ڴ���ͼ���д洢�ֽ��� ]
	long bytesPerFileRow = ( ( bytesPerMemoryRow + 3 ) / 4 ) * 4 ; // [ �ļ���ͼ���д洢�ֽ��� ]

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
// [ ���� 1 λ�ļ�ͷ ] ...................................................
// [ *************** ] ...................................................
void CImage::Construct_1_FileHeader( BITMAPFILEHEADER* fileHeader, long imageHeight, long imageWidth )
{
	long bytesPerMemoryRow = ( imageWidth + 7 ) / 8 ; // [ �ڴ���ͼ���д洢�ֽ��� ]
	long bytesPerFileRow = ( ( bytesPerMemoryRow + 3 ) / 4 ) * 4 ; // [ �ļ���ͼ���д洢�ֽ��� ]

	fileHeader->bfType = ((WORD) ('M' << 8) | 'B') ;  
	fileHeader->bfReserved1 = 0 ;  
	fileHeader->bfReserved2 = 0 ;  
	fileHeader->bfOffBits = sizeof( BITMAPFILEHEADER ) + sizeof( BITMAPINFOHEADER ) + 2 * sizeof( RGBQUAD ) ;
	fileHeader->bfSize = fileHeader->bfOffBits + imageHeight * bytesPerFileRow ;
}

// [ ************* ] .....................................................
// [ ���� 8 λ��Ϣ ] .....................................................
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
// [ ���� 8 λ�ļ�ͷ ] ...................................................
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
// [ ���� 24 λ��Ϣ ] ....................................................
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
// [ ���� 24 λ�ļ�ͷ ] ..................................................
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
// [ ���� 32 λ��Ϣ ] ....................................................
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
// [ �����ɫͼ�� ] ......................................................
// [ ************ ] ......................................................
void CImage::SaveImage( const CTMatrix< RGB_TRIPLE >& colorImage, const CString& fileName, int jpeg_quality ) 
{
	CString postfix = PostfixToFileName( fileName ); // [ ��ȡ�ļ�����׺ ]

	if( postfix.CompareNoCase( "BMP" ) == 0 ) // [ BMP ͼ�� ]
	{
		SaveImageToBmpFile( colorImage, fileName ); // [ �����ɫͼ��Ϊ BMP �ļ� ]
		return; // [ �������� ]
	}
}   

// [ ************ ] ......................................................
// [ ����Ҷ�ͼ�� ] ......................................................
// [ ************ ] ......................................................
void CImage::SaveImage( const CTMatrix< BYTE >& grayImage, const CString& fileName, int jpeg_quality ) 
{
	CString postfix = PostfixToFileName( fileName ); // [ ��ȡ�ļ�����׺ ]

	if( postfix.CompareNoCase( "BMP" ) == 0 ) // [ BMP ͼ�� ]
	{
		SaveImageToBmpFile( grayImage, fileName ); // [ ����Ҷ�ͼ��Ϊ BMP �ļ� ]
		return; // [ �������� ]
	}
}

// [ ************ ] ......................................................
// [ �����ֵͼ�� ] ......................................................
// [ ************ ] ......................................................
void CImage::SaveImage( const CTMatrix< BlackWhite >& unicolorImage, const CString& fileName )
{
	CString postfix = PostfixToFileName( fileName ); // [ ��ȡ�ļ�����׺ ]

	if( postfix.CompareNoCase( "BMP" ) == 0 ) // [ BMP ͼ�� ]
	{
		SaveImageToBmpFile( unicolorImage, fileName ); // [ �����ֵͼ��Ϊ BMP �ļ� ]
		return; // [ �������� ]
	}
}

// [ *********************** ] ...........................................
// [ �����ɫͼ��Ϊ BMP �ļ� ] ...........................................
// [ *********************** ] ...........................................
void CImage::SaveImageToBmpFile( const CTMatrix< RGB_TRIPLE >& colorImage, const CString& fileName )
{
	if( colorImage.IsNull() ) // [ �ж�ͼ���Ƿ�Ϊ�� ]
		return;

	CFile bitmapFile; // [ Bmp �ļ� ]
	if( !bitmapFile.Open( fileName, CFile::modeCreate | CFile::modeWrite ) ) // [ ���ļ� ]
		return;

	long imageHeight = colorImage.GetRows( ); // [ ͼ��߶�( ���� ) ]
	long imageWidth = colorImage.GetColumns( ); // [ ͼ����( ���� ) ]
	long bytesPerMemoryRow = imageWidth * sizeof( RGB_TRIPLE ); // [ �ڴ���ͼ���д洢�ֽ��� ]
	long bytesPerFileRow = ( ( bytesPerMemoryRow + 3 ) / 4 ) * 4 ; // [ �ļ���ͼ���д洢�ֽ��� ]

	BITMAPFILEHEADER* fileHeader = new BITMAPFILEHEADER ; // [ �����ļ�ͷ�ڴ� ]
	BITMAPINFO* bitmapInfo = new BITMAPINFO ; // [ ����λͼ��Ϣ�ڴ� ]
	BYTE* bitmapData = new BYTE[ colorImage.GetSizeInBytes() ]; // [ ����λͼ�����ڴ� ]
    BYTE* swapBuffer = ( bytesPerMemoryRow == bytesPerFileRow ) ? 
                       bitmapData : ( new BYTE[ imageHeight * bytesPerFileRow ] ); // [ ����ͼ�񱣴滺���� ]
	
	Construct_24_FileHeader( fileHeader, imageHeight, imageWidth ); // [ ���� 24 λ�ļ�ͷ ]
	Construct_24_Info( bitmapInfo, imageHeight, imageWidth ); // [ ���� 24 λ��Ϣ ]
	colorImage.ExportTo( bitmapData ); // [ ����ͼ������ ]
	if( bytesPerMemoryRow != bytesPerFileRow ) 
		for( int row = 0; row < imageHeight; row++ )
			memcpy( swapBuffer + row * bytesPerFileRow, 
			        bitmapData + row * bytesPerMemoryRow, 
					bytesPerMemoryRow ); // [ ����ͼ�񱣴滺�������� ]

    bitmapFile.Write( fileHeader, sizeof( BITMAPFILEHEADER ) ); // [ �����ļ�ͷ ]
	bitmapFile.Write( bitmapInfo, sizeof( BITMAPINFOHEADER ) ); // [ ������Ϣͷ ]
	bitmapFile.Write( swapBuffer, bytesPerFileRow * imageHeight ); // [ ����ͼ������ ]

	if( bytesPerMemoryRow != bytesPerFileRow ) delete [] swapBuffer; // [ �ͷ�ͼ�񱣴滺���� ]
	delete [] bitmapData; // [ �ͷ�λͼ�����ڴ� ]
	delete bitmapInfo; // [ �ͷ�λͼ��Ϣ�ڴ� ]
	delete fileHeader; // [ �ͷ��ļ�ͷ�ڴ� ]

	bitmapFile.Close(); // [ �ر��ļ� ]
}

// [ *********************** ] ...........................................
// [ ����Ҷ�ͼ��Ϊ BMP �ļ� ] ...........................................
// [ *********************** ] ...........................................
void CImage::SaveImageToBmpFile( const CTMatrix< BYTE >& grayImage, const CString& fileName )
{
	if( grayImage.IsNull() ) // [ �ж�ͼ���Ƿ�Ϊ�� ]
		return;

	CFile bitmapFile; // [ Bmp �ļ� ]
	if( !bitmapFile.Open( fileName, CFile::modeCreate | CFile::modeWrite ) ) // [ ���ļ� ]
		return;

	long imageHeight = grayImage.GetRows(); // [ ͼ��߶�( ���� ) ]
	long imageWidth = grayImage.GetColumns(); // [ ͼ����( ���� ) ]
	long bytesPerFileRow = ( ( imageWidth + 3 ) / 4 ) * 4 ; // [ �ļ���ͼ���д洢�ֽ��� ]

	BITMAPFILEHEADER* fileHeader = new BITMAPFILEHEADER ; // [ �����ļ�ͷ�ڴ� ]
	BITMAPINFO* bitmapInfo = ( BITMAPINFO* )( new BYTE[ sizeof( BITMAPINFOHEADER ) + 256 * sizeof( RGBQUAD ) ] ); // [ ����λͼ��Ϣ�ڴ� ]
	BYTE* bitmapData = new BYTE[ grayImage.GetSizeInBytes() ]; // [ ����λͼ�����ڴ� ]
	BYTE* swapBuffer = ( imageWidth == bytesPerFileRow ) ? 
                       bitmapData : ( new BYTE[ imageHeight * bytesPerFileRow ] ); // [ ����ͼ�񱣴滺���� ]

	Construct_8_FileHeader( fileHeader, imageHeight, imageWidth ); // [ ���� 8 λ�ļ�ͷ ]
	Construct_8_Info( bitmapInfo, imageHeight, imageWidth ); // [ ���� 8 λ��Ϣ ]
	grayImage.ExportTo( bitmapData ); // [ ����ͼ������ ]
	if( imageWidth != bytesPerFileRow ) 
		for( int row = 0; row < imageHeight; row++ )
			memcpy( swapBuffer + row * bytesPerFileRow, 
			        bitmapData + row * imageWidth, 
					imageWidth ); // [ ����ͼ�񱣴滺�������� ]

	bitmapFile.Write( fileHeader, sizeof( BITMAPFILEHEADER ) ); // [ �����ļ�ͷ ]
	bitmapFile.Write( bitmapInfo, sizeof( BITMAPINFOHEADER ) + 256 * sizeof( RGBQUAD ) ); // [ ������Ϣͷ ]
	bitmapFile.Write( swapBuffer, bytesPerFileRow * imageHeight ); // [ ����ͼ������ ]

	if( imageWidth != bytesPerFileRow ) delete [] swapBuffer; // [ �ͷ�ͼ�񱣴滺���� ]
	delete [] bitmapData; // [ �ͷ�λͼ�����ڴ� ]
	delete [] bitmapInfo; // [ �ͷ�λͼ��Ϣ�ڴ� ]
	delete fileHeader; // [ �ͷ��ļ�ͷ�ڴ� ]

	bitmapFile.Close(); // [ �ر��ļ� ]
}

// [ *********************** ] ...........................................
// [ �����ֵͼ��Ϊ BMP �ļ� ] ...........................................
// [ *********************** ] ...........................................
void CImage::SaveImageToBmpFile( const CTMatrix< BlackWhite >& unicolorImage, const CString& fileName )
{
	if( unicolorImage.IsNull() ) // [ �ж�ͼ���Ƿ�Ϊ�� ]
		return; 

	CFile bitmapFile; // [ Bmp �ļ� ]
	if( !bitmapFile.Open( fileName, CFile::modeCreate | CFile::modeWrite ) ) // [ ���ļ� ]
		return;

	long imageHeight = unicolorImage.GetRows(); // [ ͼ��߶�( ���� ) ]
	long imageWidth = unicolorImage.GetColumns(); // [ ͼ����( ���� ) ]
    long bytesPerMemoryRow = ( imageWidth + 7 ) / 8 ; // [ �ڴ���ͼ���д洢�ֽ��� ]
	long bytesPerFileRow = ( ( bytesPerMemoryRow + 3 ) / 4 ) * 4 ; // [ �ļ���ͼ���д洢�ֽ��� ]

	BITMAPFILEHEADER* fileHeader = new BITMAPFILEHEADER ; // [ �����ļ�ͷ�ڴ� ]
	BITMAPINFO* bitmapInfo = ( BITMAPINFO* )( new BYTE[ sizeof( BITMAPINFOHEADER ) + 2 * sizeof( RGBQUAD ) ] ); // [ ����λͼ��Ϣ�ڴ� ]
	BYTE* swapBuffer = new BYTE[ imageHeight * bytesPerFileRow ]; // [ ����ͼ�񱣴滺���� ]

	Construct_1_FileHeader( fileHeader, imageHeight, imageWidth ); // [ ���� 1 λ�ļ�ͷ ]
	Construct_1_Info( bitmapInfo, imageHeight, imageWidth ); // [ ���� 1 λ��Ϣ ]
	for( int row = 0; row < imageHeight; row++ )
		for( int column = 0; column < imageWidth; column++ )
		{
			long indexByte = column / 8 ; // [ ���������ֽ����� ]
			long indexBit = 7 - column % 8 ; // [ ��������λ����( ������һλ ) ]

			if( unicolorImage[row][column] == White )
				swapBuffer[ row * bytesPerFileRow + indexByte ] |= ( 1 << indexBit ); // [ ���� 1 ]
			else
				swapBuffer[ row * bytesPerFileRow + indexByte ] &= ( 1 << indexBit ) ^ 0xFF; // [ ���� 0 ]
		}

	bitmapFile.Write( fileHeader, sizeof( BITMAPFILEHEADER ) ); // [ �����ļ�ͷ ]
	bitmapFile.Write( bitmapInfo, sizeof( BITMAPINFOHEADER ) + 2 * sizeof( RGBQUAD ) ); // [ ������Ϣͷ ]
	bitmapFile.Write( swapBuffer, bytesPerFileRow * imageHeight ); // [ ����ͼ������ ]

	delete [] swapBuffer; // [ �ͷ�ͼ�񱣴滺���� ]
	delete [] bitmapInfo; // [ �ͷ�λͼ��Ϣ�ڴ� ]
	delete fileHeader; // [ �ͷ��ļ�ͷ�ڴ� ]

	bitmapFile.Close(); // [ �ر��ļ� ]
}
