 /*
 * Copyright (c) 2002-2007, Communications and Remote Sensing Laboratory, Universite catholique de Louvain (UCL), Belgium
 * Copyright (c) 2002-2007, Professor Benoit Macq
 * Copyright (c) 2001-2003, David Janssens
 * Copyright (c) 2002-2003, Yannick Verschueren
 * Copyright (c) 2003-2007, Francois-Olivier Devaux and Antonin Descampe
 * Copyright (c) 2005, Herve Drolon, FreeImage Team
 * Copyright (c) 2006-2007, Parvatha Elangovan
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS `AS IS'
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef OPENJPEG_H
#define OPENJPEG_H

#define OPENJPEG_VERSION "1.3.0"

#include "..\..\DigitalImageProcessing\Image.h"
#include "..\..\DigitalImageProcessing\TArrayEx.h"

/* 
==========================================================
   Useful constant definitions
==========================================================
*/

#define OPJ_PATH_LEN 4096 /**< Maximum allowed size for filenames */

#define J2K_MAXRLVLS 33					/**< Number of maximum resolution level authorized */
#define J2K_MAXBANDS (3*J2K_MAXRLVLS-2)	/**< Number of maximum sub-band linked to number of resolution level */

/* UniPG>> */
#define JPWL_MAX_NO_TILESPECS	16 /**< Maximum number of tile parts expected by JPWL: increase at your will */
#define JPWL_MAX_NO_PACKSPECS	16 /**< Maximum number of packet parts expected by JPWL: increase at your will */
#define JPWL_MAX_NO_MARKERS	512 /**< Maximum number of JPWL markers: increase at your will */
#define JPWL_PRIVATEINDEX_NAME "jpwl_index_privatefilename" /**< index file name used when JPWL is on */
#define JPWL_EXPECTED_COMPONENTS 3 /**< Expect this number of components, so you'll find better the first EPB */
#define JPWL_MAXIMUM_TILES 8192 /**< Expect this maximum number of tiles, to avoid some crashes */
#define JPWL_MAXIMUM_HAMMING 2 /**< Expect this maximum number of bit errors in marker id's */
#define JPWL_MAXIMUM_EPB_ROOM 65450 /**< Expect this maximum number of bytes for composition of EPBs */
/* <<UniPG */

/* 
==========================================================
   enum definitions
==========================================================
*/
/** 
Rsiz Capabilities
*/
typedef enum RSIZ_CAPABILITIES {
	STD_RSIZ = 0,		/** Standard JPEG2000 profile*/
	CINEMA2K = 3,		/** Profile name for a 2K image*/
	CINEMA4K = 4		/** Profile name for a 4K image*/
} OPJ_RSIZ_CAPABILITIES;

/** 
Digital cinema operation mode 
*/
typedef enum CINEMA_MODE {
	OFF = 0,					/** Not Digital Cinema*/
	CINEMA2K_24 = 1,	/** 2K Digital Cinema at 24 fps*/
	CINEMA2K_48 = 2,	/** 2K Digital Cinema at 48 fps*/
	CINEMA4K_24 = 3		/** 4K Digital Cinema at 24 fps*/
}OPJ_CINEMA_MODE;

/** 
Progression order 
*/
typedef enum PROG_ORDER {
	PROG_UNKNOWN = -1,	/**< place-holder */
	LRCP = 0,		/**< layer-resolution-component-precinct order */
	RLCP = 1,		/**< resolution-layer-component-precinct order */
	RPCL = 2,		/**< resolution-precinct-component-layer order */
	PCRL = 3,		/**< precinct-component-resolution-layer order */
	CPRL = 4		/**< component-precinct-resolution-layer order */
} OPJ_PROG_ORDER;

/**
Supported image color spaces
*/
typedef enum COLOR_SPACE {
	CLRSPC_UNKNOWN = -1,	/**< place-holder */
	CLRSPC_SRGB = 1,		/**< sRGB */
	CLRSPC_GRAY = 2,		/**< grayscale */
	CLRSPC_SYCC = 3			/**< YUV */
} OPJ_COLOR_SPACE;

/**
Supported codec
*/
typedef enum CODEC_FORMAT {
	CODEC_UNKNOWN = -1,	/**< place-holder */
	CODEC_J2K = 0,		/**< JPEG-2000 codestream : read/write */
	CODEC_JPT = 1,		/**< JPT-stream (JPEG 2000, JPIP) : read only */
	CODEC_JP2 = 2		/**< JPEG-2000 file format : read/write */
} OPJ_CODEC_FORMAT;

/** 
Limit decoding to certain portions of the codestream. 
*/
typedef enum LIMIT_DECODING {
	NO_LIMITATION = 0,				  /**< No limitation for the decoding. The entire codestream will de decoded */
	LIMIT_TO_MAIN_HEADER = 1,		/**< The decoding is limited to the Main Header */
	DECODE_ALL_BUT_PACKETS = 2	/**< Decode everything except the JPEG 2000 packets */
} OPJ_LIMIT_DECODING;

/* 
==========================================================
   event manager typedef definitions
==========================================================
*/

/**
Callback function prototype for events
@param msg Event message
@param client_data 
*/
typedef void (*opj_msg_callback) (const char *msg, void *client_data);

/**
Message handler object
used for 
<ul>
<li>Error messages
<li>Warning messages
<li>Debugging messages
</ul>
*/
typedef struct opj_event_mgr 
{
	opj_msg_callback error_handler;  /** Error message callback if available, NULL otherwise */
	opj_msg_callback warning_handler;/** Warning message callback if available, NULL otherwise */
	opj_msg_callback info_handler;   /** Debug message callback if available, NULL otherwise */
} opj_event_mgr_t;


/* 
==========================================================
   codec typedef definitions
==========================================================
*/

/**
Progression order changes
*/
typedef struct opj_poc 
{
	int resno0, compno0;                        /** Resolution num start, Component num start, given by POC */
	int layno1, resno1, compno1;                /** Layer num end,Resolution num end, Component num end, given by POC */
	int layno0, precno0, precno1;               /** Layer num start,Precinct num start, Precinct num end */
	OPJ_PROG_ORDER prg1,prg;                    /** Progression order enum*/
	char progorder[5];                          /** Progression order string*/
	int tile;                                   /** Tile number */
	int tx0,tx1,ty0,ty1;                        /** Start and end values for Tile width and height*/
	int layS, resS, compS, prcS;                /** Start value, initialised in pi_initialise_encode*/
	int layE, resE, compE, prcE;                /** End value, initialised in pi_initialise_encode */
	int txS,txE,tyS,tyE,dx,dy;                  /** Start and end values of Tile width and height, initialised in pi_initialise_encode*/
	int lay_t, res_t, comp_t, prc_t,tx0_t,ty0_t;/** Temporary values for Tile parts, initialised in pi_create_encode */
} opj_poc_t;

/**
Compression parameters
*/
typedef struct opj_cparameters 
{
	bool tile_size_on;                   /** size of tile: tile_size_on = false (not in argument) or = true (in argument) */
	int cp_tx0;                          /** XTOsiz */
	int cp_ty0;                          /** YTOsiz */
	int cp_tdx;                          /** XTsiz */
	int cp_tdy;                          /** YTsiz */
	int cp_disto_alloc;                  /** allocation by rate/distortion */
	int cp_fixed_alloc;                  /** allocation by fixed layer */
	int cp_fixed_quality;                /** add fixed_quality */
	CTArray< int > cp_matrice;           /** fixed layer */
	CTArray< char > cp_comment;          /** comment for coding */
	int csty;                            /** csty : coding style */
	OPJ_PROG_ORDER prog_order;           /** progression order (default LRCP) */
	opj_poc_t POC[32];                   /** progression order changes */
	int numpocs;                         /** number of progression order changes (POC), default to 0 */
	int tcp_numlayers;                   /** number of layers */
	float tcp_rates[100];                /** rates of layers */
	float tcp_distoratio[100];           /** different psnr for successive layers */
	int numresolution;                   /** number of resolutions */
 	int cblockw_init;                    /** initial code block width, default to 64 */
	int cblockh_init;                    /** initial code block height, default to 64 */
	int mode;                            /** mode switch (cblk_style) */
	int irreversible;                    /** 1 : use the irreversible DWT 9-7, 0 : use lossless compression (default) */
	int roi_compno;                      /** region of interest: affected component in [0..3], -1 means no ROI */
	int roi_shift;                       /** region of interest: upshift value */
	int res_spec;                        /* number of precinct size specifications */
	int prcw_init[J2K_MAXRLVLS];         /** initial precinct width */
	int prch_init[J2K_MAXRLVLS];         /** initial precinct height */
	
	char infile[OPJ_PATH_LEN];           /** input file name */
	char outfile[OPJ_PATH_LEN];          /** output file name */
	int index_on;                        /** DEPRECATED. Index generation is now handeld with the opj_encode_with_info() function. Set to NULL */
	char index[OPJ_PATH_LEN];            /** DEPRECATED. Index generation is now handeld with the opj_encode_with_info() function. Set to NULL */
	int image_offset_x0;                 /** subimage encoding: origin image offset in x direction */
	int image_offset_y0;                 /** subimage encoding: origin image offset in y direction */
	int subsampling_dx;                  /** subsampling value for dx */
	int subsampling_dy;                  /** subsampling value for dy */
	int decod_format;                    /** input file format 0: PGX, 1: PxM, 2: BMP 3:TIF*/
	int cod_format;                      /** output file format 0: J2K, 1: JP2, 2: JPT */
	
	bool jpwl_epc_on;                    /** enables writing of EPC in MH, thus activating JPWL */
	int jpwl_hprot_MH;                   /** error protection method for MH (0,1,16,32,37-128) */
	int jpwl_hprot_TPH_tileno[JPWL_MAX_NO_TILESPECS];  /** tile number of header protection specification (>=0) */
	int jpwl_hprot_TPH[JPWL_MAX_NO_TILESPECS];         /** error protection methods for TPHs (0,1,16,32,37-128) */
	int jpwl_pprot_tileno[JPWL_MAX_NO_PACKSPECS];      /** tile number of packet protection specification (>=0) */
	int jpwl_pprot_packno[JPWL_MAX_NO_PACKSPECS];      /** packet number of packet protection specification (>=0) */
	int jpwl_pprot[JPWL_MAX_NO_PACKSPECS];             /** error protection methods for packets (0,1,16,32,37-128) */
	int jpwl_sens_size;                  /** enables writing of ESD, (0=no/1/2 bytes) */
	int jpwl_sens_addr;                  /** sensitivity addressing size (0=auto/2/4 bytes) */
	int jpwl_sens_range;                 /** sensitivity range (0-3) */
	int jpwl_sens_MH;                    /** sensitivity method for MH (-1=no,0-7) */
	int jpwl_sens_TPH_tileno[JPWL_MAX_NO_TILESPECS];   /** tile number of sensitivity specification (>=0) */
	int jpwl_sens_TPH[JPWL_MAX_NO_TILESPECS];          /** sensitivity methods for TPHs (-1=no,0-7) */

	OPJ_CINEMA_MODE cp_cinema;           /** Digital Cinema compliance 0-not compliant, 1-compliant*/
	int max_comp_size;                   /** Maximum rate for each component. If == 0, component size limitation is not considered */
	OPJ_RSIZ_CAPABILITIES cp_rsiz;       /** Profile name*/
	char tp_on;                          /** Tile part generation*/
	char tp_flag;                        /** Flag for Tile part generation*/
	char tcp_mct;                        /** MCT (multiple component transform) */
} opj_cparameters_t;

/**
Decompression parameters
*/
typedef struct opj_dparameters 
{
	/** 
	Set the number of highest resolution levels to be discarded. 
	The image resolution is effectively divided by 2 to the power of the number of discarded levels. 
	The reduce factor is limited by the smallest total number of decomposition levels among tiles.
	if != 0, then original dimension divided by 2^(reduce); 
	if == 0 or not used, image is decoded to the full resolution 
	*/
	int cp_reduce;
	/** 
	Set the maximum number of quality layers to decode. 
	If there are less quality layers than the specified number, all the quality layers are decoded.
	if != 0, then only the first "layer" layers are decoded; 
	if == 0 or not used, all the quality layers are decoded 
	*/
	int cp_layer;
	
	char infile[OPJ_PATH_LEN];    /** input file name */
	char outfile[OPJ_PATH_LEN];   /** output file name */
	int decod_format;             /** input file format 0: J2K, 1: JP2, 2: JPT */
	int cod_format;               /** output file format 0: PGX, 1: PxM, 2: BMP */
	bool jpwl_correct;            /** activates the JPWL correction capabilities */
	int jpwl_exp_comps;           /** expected number of components */
	int jpwl_max_tiles;           /** maximum number of tiles */

	/** 
	Specify whether the decoding should be done on the entire codestream, or be limited to the main header
	Limiting the decoding to the main header makes it possible to extract the characteristics of the codestream
	if == NO_LIMITATION, the entire codestream is decoded; 
	if == LIMIT_TO_MAIN_HEADER, only the main header is decoded; 
	*/
	OPJ_LIMIT_DECODING cp_limit_decoding;

} opj_dparameters_t;

/** Common fields between JPEG-2000 compression and decompression master structs. */

#define opj_common_fields \
	opj_event_mgr_t *event_mgr;	/**< pointer to the event manager */\
	void * client_data;			/**< Available for use by application */\
	bool is_decompressor;		/**< So common code can tell which is which */\
	OPJ_CODEC_FORMAT codec_format;	/**< selected codec */\
	void *j2k_handle;			/**< pointer to the J2K codec */\
	void *jp2_handle;			/**< pointer to the JP2 codec */\
	void *mj2_handle			/**< pointer to the MJ2 codec */
	
/* Routines that are to be used by both halves of the library are declared
 * to receive a pointer to this structure.  There are no actual instances of
 * opj_common_struct_t, only of opj_cinfo_t and opj_dinfo_t.
 */
typedef struct opj_common_struct 
{
  opj_common_fields;		/* Fields common to both master struct types */
  /* Additional fields follow in an actual opj_cinfo_t or
   * opj_dinfo_t.  All three structs must agree on these
   * initial fields!  (This would be a lot cleaner in C++.)
   */
} opj_common_struct_t;

typedef opj_common_struct_t * opj_common_ptr;

/**
Compression context info
*/
typedef struct opj_cinfo {
	/** Fields shared with opj_dinfo_t */
	opj_common_fields;	
	/* other specific fields go here */
} opj_cinfo_t;

/**
Decompression context info
*/
typedef struct opj_dinfo {
	/** Fields shared with opj_cinfo_t */
	opj_common_fields;	
	/* other specific fields go here */
} opj_dinfo_t;

/* 
==========================================================
   I/O stream typedef definitions
==========================================================
*/

/*
 * Stream open flags.
 */
/** The stream was opened for reading. */
#define OPJ_STREAM_READ	0x0001
/** The stream was opened for writing. */
#define OPJ_STREAM_WRITE 0x0002

/**
Byte input-output stream (CIO)
*/
typedef struct opj_cio 
{
	opj_common_ptr cinfo;   /** codec context */
	int openmode;           /** open mode (read/write) either OPJ_STREAM_READ or OPJ_STREAM_WRITE */
	unsigned char *buffer;  /** pointer to the start of the buffer */
	int length;             /** buffer size in bytes */
	unsigned char *start;   /** pointer to the start of the stream */
	unsigned char *end;     /** pointer to the end of the stream */
	unsigned char *bp;      /** pointer to the current position */
} opj_cio_t;

/* 
==========================================================
   image typedef definitions
==========================================================
*/

/**
Defines a single image component
*/
typedef struct opj_image_comp 
{
	int dx;               /** XRsiz: horizontal separation of a sample of ith component with respect to the reference grid */
	int dy;               /** YRsiz: vertical separation of a sample of ith component with respect to the reference grid */
	int w;                /** data width */
	int h;                /** data height */
	int x0;               /** x component offset compared to the whole image */
	int y0;               /** y component offset compared to the whole image */
	int prec;             /** precision */
	int bpp;              /** image depth in bits */
	int sgnd;             /** signed (1) / unsigned (0) */
	int resno_decoded;    /** number of decoded resolution */
	int factor;           /** number of division by 2 of the out image compared to the original size of image */
	CTArray< int > data;  /** image component data */
} opj_image_comp_t;

/** 
Defines image data and characteristics
*/
typedef struct opj_image 
{
	int x0;                              /** XOsiz: horizontal offset from the origin of the reference grid to the left side of the image area */
	int y0;                              /** YOsiz: vertical offset from the origin of the reference grid to the top side of the image area */
	int x1;                              /** Xsiz: width of the reference grid */
	int y1;                              /** Ysiz: height of the reference grid */
	int numcomps;                        /** number of components in the image */
	OPJ_COLOR_SPACE color_space;         /** color space: sRGB, Greyscale or YUV */
	CTArrayEx< opj_image_comp_t > comps; /** image components */
} opj_image_t;

/**
Component parameters structure used by the opj_image_create function
*/
typedef struct opj_image_comptparm 
{
	int dx;     /** XRsiz: horizontal separation of a sample of ith component with respect to the reference grid */
	int dy;     /** YRsiz: vertical separation of a sample of ith component with respect to the reference grid */
	int w;      /** data width */
	int h;      /** data height */
	int x0;     /** x component offset compared to the whole image */
	int y0;     /** y component offset compared to the whole image */
	int prec;   /** precision */
	int bpp;    /** image depth in bits */
	int sgnd;   /** signed (1) / unsigned (0) */
} opj_image_cmptparm_t;

/* 
==========================================================
   Information on the JPEG 2000 codestream
==========================================================
*/

/**
Index structure : Information concerning a packet inside tile
*/
typedef struct opj_packet_info 
{
	int start_pos;   /** packet start position (including SOP marker if it exists) */
	int end_ph_pos;  /** end of packet header position (including EPH marker if it exists)*/
	int end_pos;     /** packet end position */
	double disto;    /** packet distorsion */
} opj_packet_info_t;

/**
Index structure : Information concerning tile-parts
*/
typedef struct opj_tp_info 
{
	int tp_start_pos;   /** start position of tile part */
	int tp_end_header;  /** end position of tile part header */
	int tp_end_pos;     /** end position of tile part */
	int tp_start_pack;  /** start packet of tile part */
	int tp_numpacks;    /** number of packets of tile part */
} opj_tp_info_t;

/**
Index structure : information regarding tiles 
*/
typedef struct opj_tile_info 
{
	CTArray< double > thresh;             /** value of thresh for each layer by tile cfr. Marcela   */
	int tileno;                           /** number of tile */
	int start_pos;                        /** start position */
	int end_header;                       /** end position of the header */
	int end_pos;                          /** end position */
	int pw[33];                           /** precinct number for each resolution level (width) */
	int ph[33];                           /** precinct number for each resolution level (height) */
	int pdx[33];                          /** precinct size (in power of 2), in X for each resolution level */
	int pdy[33];                          /** precinct size (in power of 2), in Y for each resolution level */
	CTArray< opj_packet_info_t > packet;  /** information concerning packets inside tile */
	int numpix;                           /** add fixed_quality */
	double distotile;                     /** add fixed_quality */
	int num_tps;                          /** number of tile parts */
	CTArray< opj_tp_info_t > tp;          /** information concerning tile parts */
} opj_tile_info_t;

/* UniPG>> */
/**
Marker structure
*/
typedef struct opj_marker_info_t 
{
	unsigned short int type;  /** marker type */
	int pos;                  /** position in codestream */
	int len;                  /** length, marker val included */
} opj_marker_info_t;
/* <<UniPG */

/**
Index structure of the codestream
*/
typedef struct opj_codestream_info 
{
	double D_max;                         /** maximum distortion reduction on the whole image (add for Marcela) */
	int packno;                           /** packet number */
	int index_write;                      /** writing the packet in the index with t2_encode_packets */
	int image_w;                          /** image width */
	int image_h;                          /** image height */
	OPJ_PROG_ORDER prog;                  /** progression order */
	int tile_x;                           /** tile size in x */
	int tile_y;                           /** tile size in y */
	int tile_Ox;                          /** */
	int tile_Oy;                          /** */
	int tw;                               /** number of tiles in X */
	int th;                               /** number of tiles in Y */
	int numcomps;                         /** component numbers */
	int numlayers;                        /** number of layer */
	int *numdecompos;                     /** number of decomposition for each component */
	int marknum;                          /** number of markers */
	CTArray< opj_marker_info_t > marker;  /** list of markers */
	int maxmarknum;                       /** actual size of markers array */
	int main_head_start;                  /** main header position */
	int main_head_end;                    /** main header position */
	int codestream_size;                  /** codestream's size */
	CTArrayEx< opj_tile_info_t > tile;    /** information regarding tiles inside image */
} opj_codestream_info_t;



/* 
==========================================================
   openjpeg version
==========================================================
*/

 const char *  opj_version(void);

/* 
==========================================================
   image functions definitions
==========================================================
*/

/**
Create an image
@param numcmpts number of components
@param cmptparms components parameters
@param clrspc image color space
@return returns a new image structure if successful, returns NULL otherwise
*/
void opj_image_create(int numcmpts, opj_image_cmptparm_t *cmptparms, OPJ_COLOR_SPACE clrspc, CTArrayEx< opj_image_t >& image ) ;

/* 
==========================================================
   stream functions definitions
==========================================================
*/

/**
Open and allocate a memory stream for read / write. 
On reading, the user must provide a buffer containing encoded data. The buffer will be 
wrapped by the returned CIO handle. 
On writing, buffer parameters must be set to 0: a buffer will be allocated by the library 
to contain encoded data. 
@param cinfo Codec context info
@param buffer Reading: buffer address. Writing: NULL
@param length Reading: buffer length. Writing: 0
@return Returns a CIO handle if successful, returns NULL otherwise
*/
 opj_cio_t*  opj_cio_open(opj_common_ptr cinfo, unsigned char *buffer, int length);

/**
Close and free a CIO handle
@param cio CIO handle to free
*/
 void  opj_cio_close(opj_cio_t *cio);

/**
Get position in byte stream
@param cio CIO handle
@return Returns the position in bytes
*/
 int  cio_tell(opj_cio_t *cio);
/**
Set position in byte stream
@param cio CIO handle
@param pos Position, in number of bytes, from the beginning of the stream
*/
 void  cio_seek(opj_cio_t *cio, int pos);

/* 
==========================================================
   event manager functions definitions
==========================================================
*/

 opj_event_mgr_t*  opj_set_event_mgr(opj_common_ptr cinfo, opj_event_mgr_t *event_mgr, void *context);

/* 
==========================================================
   codec functions definitions
==========================================================
*/
/**
Creates a J2K/JPT/JP2 decompression structure
@param format Decoder to select
@return Returns a handle to a decompressor if successful, returns NULL otherwise
*/
 opj_dinfo_t*  opj_create_decompress(OPJ_CODEC_FORMAT format);
/**
Destroy a decompressor handle
@param dinfo decompressor handle to destroy
*/
 void  opj_destroy_decompress(opj_dinfo_t *dinfo);
/**
Set decoding parameters to default values
@param parameters Decompression parameters
*/
 void  opj_set_default_decoder_parameters(opj_dparameters_t *parameters);
/**
Setup the decoder decoding parameters using user parameters.
Decoding parameters are returned in j2k->cp. 
@param dinfo decompressor handle
@param parameters decompression parameters
*/
 void  opj_setup_decoder(opj_dinfo_t *dinfo, opj_dparameters_t *parameters);
/**
Decode an image from a JPEG-2000 codestream 
@param dinfo decompressor handle
@param cio Input buffer stream
@return Returns a decoded image if successful, returns NULL otherwise
*/
void  opj_decode(opj_dinfo_t *dinfo, opj_cio_t *cio, CTArrayEx< opj_image_t >& image ) ;

/**
Decode an image from a JPEG-2000 codestream and extract the codestream information
@param dinfo decompressor handle
@param cio Input buffer stream
@param cstr_info Codestream information structure if needed afterwards, NULL otherwise
@return Returns a decoded image if successful, returns NULL otherwise
*/
 void  opj_decode_with_info(opj_dinfo_t *dinfo, opj_cio_t *cio, opj_codestream_info_t *cstr_info,  CTArrayEx< opj_image_t >& image ) ;
/**
Creates a J2K/JP2 compression structure
@param format Coder to select
@return Returns a handle to a compressor if successful, returns NULL otherwise
*/
 opj_cinfo_t*  opj_create_compress(OPJ_CODEC_FORMAT format);
/**
Destroy a compressor handle
@param cinfo compressor handle to destroy
*/
 void  opj_destroy_compress(opj_cinfo_t *cinfo);
/**
Set encoding parameters to default values, that means : 
<ul>
<li>Lossless
<li>1 tile
<li>Size of precinct : 2^15 x 2^15 (means 1 precinct)
<li>Size of code-block : 64 x 64
<li>Number of resolutions: 6
<li>No SOP marker in the codestream
<li>No EPH marker in the codestream
<li>No sub-sampling in x or y direction
<li>No mode switch activated
<li>Progression order: LRCP
<li>No index file
<li>No ROI upshifted
<li>No offset of the origin of the image
<li>No offset of the origin of the tiles
<li>Reversible DWT 5-3
</ul>
@param parameters Compression parameters
*/
 void  opj_set_default_encoder_parameters(opj_cparameters_t *parameters);
/**
Setup the encoder parameters using the current image and using user parameters. 
@param cinfo Compressor handle
@param parameters Compression parameters
@param image Input filled image
*/
 void  opj_setup_encoder(opj_cinfo_t *cinfo, opj_cparameters_t *parameters, CTArrayEx< opj_image_t >& image);
/**
Encode an image into a JPEG-2000 codestream
@param cinfo compressor handle
@param cio Output buffer stream
@param image Image to encode
@param index Depreacted -> Set to NULL. To extract index, used opj_encode_wci()
@return Returns true if successful, returns false otherwise
*/
 bool  opj_encode(opj_cinfo_t *cinfo, opj_cio_t *cio, CTArrayEx< opj_image_t >& image, char *index);
/**
Encode an image into a JPEG-2000 codestream and extract the codestream information
@param cinfo compressor handle
@param cio Output buffer stream
@param image Image to encode
@param cstr_info Codestream information structure if needed afterwards, NULL otherwise
@return Returns true if successful, returns false otherwise
*/
 bool  opj_encode_with_info(opj_cinfo_t *cinfo, opj_cio_t *cio, CTArrayEx< opj_image_t >& image, opj_codestream_info_t *cstr_info);
/**
Destroy Codestream information after compression or decompression
@param cstr_info Codestream information structure
*/
 void  opj_destroy_cstr_info(opj_codestream_info_t *cstr_info);

 /**
 Create an empty image
 @todo this function should be removed
 @return returns an empty image if successful, returns NULL otherwise
 */
 void opj_image_create0( CTArrayEx< opj_image_t >& image ) ;

#endif /* OPENJPEG_H */
