#define NODBACCESS
#include "epCommon.h"



/*****************************************************************************
 * basic typedef
 *****************************************************************************/
typedef union HeaderTypedVals
{
	int	 ival;
	long lval;
	float fval;
	double dval;
	char sval[MAX_STRING_SIZE];
} HeaderTypedVals;

typedef struct HeaderVals
{
	HeaderTypedVals value;
	int             status;
}HeaderVals;

/*
 * header definition (will be static)
 */
typedef struct dhsHeadersDef {
	char 				*keyword;
	int 				type;
	int 				timing;
	char 				*pvname;
	VOIDFUNCPTR 		proc;
	} dhsHeadersDef;


/*****************************************************************************
 * user defined processing prototypes
 *****************************************************************************/
void sethdrINTEGRITY(HeaderVals *hdrval);
void sethdrDROINUM(HeaderVals *hdrval);
void sethdrLOWROW(HeaderVals *hdrval);
void sethdrLOWCOL(HeaderVals *hdrval);
void sethdrHIROW(HeaderVals *hdrval);
void sethdrHICOL(HeaderVals *hdrval);
void sethdrPrecision3Digits(HeaderVals *hdrval);
void sethdrPrecision4Digits(HeaderVals *hdrval);

STATUS setHeaderDEBUG(int captBuf,unsigned int xstart1,unsigned int xstart2 ,unsigned int vme);


/*=============================================================================
 * Top definition
 *============================================================================*/

#define NIRI_TOP "niri:"
#define NIRI_DC_TOP NIRI_TOP "dc:"
#define NIRI_CC_TOP NIRI_TOP "cc:"
#define TCS_SAD_TOP "tcs:sad:"
#define TCS_TOP "tcs:"



/*=============================================================================
 * Dataset headers definition
 *============================================================================*/

typedef enum {
	HDR_DEBUG,
	HDR_CTYPE1,
	HDR_CRPIX1,
	HDR_CRVAL1,
	HDR_CTYPE2,
	HDR_CRPIX2,
	HDR_CRVAL2,
	HDR_CD1_1,
	HDR_CD1_2,
	HDR_CD2_1,
	HDR_CD2_2,
	HDR_MJD_OBS,
	HDR_INTEGRITY,
	HDR_FRAME
} dhsDsHdrIndex ;

#define DHSDSHEADER (HDR_FRAME+1)

#ifndef DUM_GBLSOURCE
extern dhsHeadersDef dhsDsHeader[];
extern HeaderVals dsHdr		[MAXCAPTBUFS][DHSDSHEADER];
#else
HeaderVals dsHdr			[MAXCAPTBUFS][DHSDSHEADER];
dhsHeadersDef dhsDsHeader[] =
{
    {"DEBUG", 			DCASTRING,		NEVER,		NULL,  								  NULL     			},
    	{"CTYPE1",			DCASTRING,  	NEVER, 	NIRI_DC_TOP WCS_CTYPE1, 			NULL				},			/*  the handling of the WCS	    */
    	{"CRPIX1",			DCADOUBLE,  	NEVER, 	NIRI_DC_TOP WCS_CRPIX1,			  	NULL				},			/*  is somewhat different       */
    	{"CRVAL1",			DCADOUBLE,  	NEVER, 	NIRI_DC_TOP WCS_CRVAL1,			  	NULL				},			/* and will need to be sorted out*/
    	{"CTYPE2",			DCASTRING,  	NEVER, 	NIRI_DC_TOP WCS_CTYPE2,			  	NULL				},			/*   for now it's got it's	    */
    	{"CRPIX2",			DCADOUBLE,  	NEVER, 	NIRI_DC_TOP WCS_CRPIX2,			  	NULL				},			/*      own         		    */
    	{"CRVAL2",			DCADOUBLE,  	NEVER, 	NIRI_DC_TOP WCS_CRVAL2,			  	NULL				},			/*      	getWCS				*/
    	{"CD1_1",			DCADOUBLE,  	NEVER, 	NIRI_DC_TOP WCS_CD1_1, 			  	NULL				},			/*      and					    */
    	{"CD1_2",			DCADOUBLE,  	NEVER, 	NIRI_DC_TOP WCS_CD1_2, 			  	NULL				},			/*      	getWCSinfo			*/
    	{"CD2_1",			DCADOUBLE,  	NEVER, 	NIRI_DC_TOP WCS_CD2_1, 			  	NULL				},			/*      routine					*/
    	{"CD2_2",			DCADOUBLE,  	NEVER, 	NIRI_DC_TOP WCS_CD2_2, 			  	NULL				},			/*  I flagged them as never    	*/
    	{"MJD_OBS",			DCADOUBLE,  	NEVER, 	NIRI_DC_TOP WCS_MJDOBS,			  	NULL				},			/*  for this reason    			*/
      {"INTEGRITY",		DCASTRING,		AFTER,   NULL,  								   sethdrINTEGRITY		},
		{"FRAME",  	   	DCASTRING,  	AFTER,   TCS_SAD_TOP "sourceAInputFrame",	NULL				}			/* here it's NOW or NEVER - so NOW */
};
#endif

/*=============================================================================
 * Frame definition
 *============================================================================*/

/* WCS is replicated in the dataset and the frame header */

typedef enum {
	FRHDR_CTYPE1,
	FRHDR_CRPIX1,
	FRHDR_CRVAL1,
	FRHDR_CTYPE2,
	FRHDR_CRPIX2,
	FRHDR_CRVAL2,
	FRHDR_CD1_1,
	FRHDR_CD1_2,
	FRHDR_CD2_1,
	FRHDR_CD2_2,
	FRHDR_MJD_OBS,
	FRHDR_FRAME
} dhsFrameHdrIndex ;

/*
 * there is no frame header for now, keep a 'NONE' definition
 * as a skeleton and stay ANSI compliant
 */


#define DHSFRAMEHEADER (FRHDR_FRAME+1)


#ifndef DUM_GBLSOURCE
	extern dhsHeadersDef dhsFrameHeader[];
	extern HeaderVals frameHdr		[MAXCAPTBUFS][DHSFRAMEHEADER];
#else
	HeaderVals frameHdr		[MAXCAPTBUFS][DHSFRAMEHEADER];
	dhsHeadersDef dhsFrameHeader[] =
	{
    	{"CTYPE1",			DCASTRING,  	NEVER, 	NIRI_DC_TOP WCS_CTYPE1, 			NULL				},			/*  the handling of the WCS	    */
    	{"CRPIX1",			DCADOUBLE,  	NEVER, 	NIRI_DC_TOP WCS_CRPIX1,			  	NULL				},			/*  is somewhat different       */
    	{"CRVAL1",			DCADOUBLE,  	NEVER, 	NIRI_DC_TOP WCS_CRVAL1,			  	NULL				},			/* and will need to be sorted out*/
    	{"CTYPE2",			DCASTRING,  	NEVER, 	NIRI_DC_TOP WCS_CTYPE2,			  	NULL				},			/*   for now it's got it's	    */
    	{"CRPIX2",			DCADOUBLE,  	NEVER, 	NIRI_DC_TOP WCS_CRPIX2,			  	NULL				},			/*      own         		    */
    	{"CRVAL2",			DCADOUBLE,  	NEVER, 	NIRI_DC_TOP WCS_CRVAL2,			  	NULL				},			/*      	getWCS				*/
    	{"CD1_1",			DCADOUBLE,  	NEVER, 	NIRI_DC_TOP WCS_CD1_1, 			  	NULL				},			/*      and					    */
    	{"CD1_2",			DCADOUBLE,  	NEVER, 	NIRI_DC_TOP WCS_CD1_2, 			  	NULL				},			/*      	getWCSinfo			*/
    	{"CD2_1",			DCADOUBLE,  	NEVER, 	NIRI_DC_TOP WCS_CD2_1, 			  	NULL				},			/*      routine					*/
    	{"CD2_2",			DCADOUBLE,  	NEVER, 	NIRI_DC_TOP WCS_CD2_2, 			  	NULL				},			/*  I flagged them as never    	*/
    	{"MJD_OBS",			DCADOUBLE,  	NEVER, 	NIRI_DC_TOP WCS_MJDOBS,			  	NULL				},			/*  for this reason    			*/
		{"FRAME",  	   	DCASTRING,  	NOW,     TCS_SAD_TOP "sourceAInputFrame",	NULL				}			/* here it's NOW or NEVER - so NOW */
	};
#endif

/*=============================================================================
 * FrameRoi definition
 *============================================================================*/

typedef enum {
	HDR_DROINUM,
	HDR_LOWROW,
	HDR_LOWCOL,
	HDR_HIROW,
	HDR_HICOL
} dhsFrameRoiHdrIndex ;

#define DHSFRAMEROIHEADER (HDR_HICOL+1)

#ifndef DUM_GBLSOURCE
	extern dhsHeadersDef dhsFrameRoiHeader[];
	extern HeaderVals frameRoiHdr	[MAXCAPTBUFS][DHSFRAMEROIHEADER];
#else
	HeaderVals frameRoiHdr	[MAXCAPTBUFS][DHSFRAMEROIHEADER];
	dhsHeadersDef dhsFrameRoiHeader[] =
	{
    	{"DROINUM",			DCALONG,   NOW, 	 NULL, 							  NULL  			  },		  /* only support NOW timing */
    	{"LOWROW",			DCALONG,	  NOW,    NULL, 							  NULL  			  },		  /* only support NOW timing */
    	{"LOWCOL",			DCALONG,	  NOW,    NULL, 							  NULL  			  },		  /* only support NOW timing */
    	{"HIROW",			DCALONG,	  NOW,    NULL, 							  NULL  			  },		  /* only support NOW timing */
    	{"HICOL",			DCALONG,	  NOW,    NULL, 							  NULL  			  } 		  /* only support NOW timing */
	};
#endif
