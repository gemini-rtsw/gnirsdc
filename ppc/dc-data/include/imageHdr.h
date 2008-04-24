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
	int                 detail;
	char 				*pvname;
	VOIDFUNCPTR 		proc;
	int                 id;
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

#define DB_TOP "nirs:"
#define DC_TOP DB_TOP "dc:"
#define CC_TOP DB_TOP "cc:"
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


#define DHSDSHEADER (15)
#ifndef DUM_GBLSOURCE
extern dhsHeadersDef dhsDsHeader[];
extern HeaderVals dsHdr		[MAXCAPTBUFS][DHSDSHEADER];
#else
HeaderVals dsHdr			[MAXCAPTBUFS][DHSDSHEADER];
dhsHeadersDef dhsDsHeader[] =
{/*   keyword             type          timing   detail    pvname               proc     id #*/
	{"DEBUG", 	         DCASTRING,		NEVER,	 HDR_DC,   NULL,  	            NULL,    0},
	{"CTYPE1",        	 DCASTRING,  	NEVER, 	 HDR_DC,   DC_TOP WCS_CTYPE1,   NULL,    1	},			/*  the handling of the WCS	    */
	{"CRPIX1",	         DCADOUBLE,  	NEVER, 	 HDR_DC,   DC_TOP WCS_CRPIX1,   NULL,    2	},			/*  is somewhat different       */
	{"CRVAL1",	         DCADOUBLE,  	NEVER, 	 HDR_DC,   DC_TOP WCS_CRVAL1,   NULL,    3	},			/* and will need to be sorted out*/
	{"CTYPE2",        	 DCASTRING,  	NEVER, 	 HDR_DC,   DC_TOP WCS_CTYPE2,   NULL,    4	},			/*   for now it's got it's	    */
	{"CRPIX2",        	 DCADOUBLE,  	NEVER, 	 HDR_DC,   DC_TOP WCS_CRPIX2,   NULL,	 5},			/*      own         		    */
	{"CRVAL2",        	 DCADOUBLE,  	NEVER, 	 HDR_DC,   DC_TOP WCS_CRVAL2,   NULL,	 6},			/*      	getWCS				*/
	{"CD1_1",        	 DCADOUBLE,  	NEVER, 	 HDR_DC,   DC_TOP WCS_CD1_1,    NULL,	 7},			/*      and					    */
	{"CD1_2",        	 DCADOUBLE,  	NEVER, 	 HDR_DC,   DC_TOP WCS_CD1_2,    NULL,	 8},			/*      	getWCSinfo			*/
	{"CD2_1",	         DCADOUBLE,  	NEVER, 	 HDR_DC,   DC_TOP WCS_CD2_1,    NULL,	 9},			/*      routine					*/
	{"CD2_2",	         DCADOUBLE,  	NEVER, 	 HDR_DC,   DC_TOP WCS_CD2_2,    NULL,	 10},			/*  I flagged them as never    	*/
	{"MJD_OBS",	         DCADOUBLE,  	NEVER, 	 HDR_DC,   DC_TOP WCS_MJDOBS,   NULL,	 11},			/*  for this reason    			*/
	{"INTEGRITY",        DCASTRING,		AFTER,   HDR_DC,   NULL,  		       sethdrINTEGRITY, 12		},
	{"FRAME",          	 DCASTRING,  	AFTER,   HDR_DC,   TCS_SAD_TOP "sourceAInputFrame",	NULL, 13	},			/* here it's NOW or NEVER - so NOW */
	{NULL,  	         DCASTRING,     BEFORE,  HDR_DC,   NULL,	NULL, 14}
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



#define DHSFRAMEHEADER (DHSDSHEADER+58)

#ifndef DUM_GBLSOURCE
	extern dhsHeadersDef dhsFrameHeader[];
	extern HeaderVals frameHdr		[MAXCAPTBUFS][DHSFRAMEHEADER-DHSDSHEADER];
#else
	HeaderVals frameHdr		[MAXCAPTBUFS][DHSFRAMEHEADER-DHSDSHEADER];
	dhsHeadersDef dhsFrameHeader[] =
	{/*   keyword     type      timing   detail    pvname               proc      id #*/
    	{"CTYPE1",	DCASTRING,	NEVER,   HDR_DC,	DC_TOP WCS_CTYPE1, 	NULL, DHSDSHEADER	},			/*  the handling of the WCS	    */
    	{"CRPIX1",	DCADOUBLE, 	NEVER,   HDR_DC,	DC_TOP WCS_CRPIX1,	NULL, DHSDSHEADER+1	},			/*  is somewhat different       */
    	{"CRVAL1",	DCADOUBLE, 	NEVER,   HDR_DC, 	DC_TOP WCS_CRVAL1,	NULL, DHSDSHEADER+2	},			/* and will need to be sorted out*/
    	{"CTYPE2",	DCASTRING, 	NEVER,   HDR_DC,	DC_TOP WCS_CTYPE2,	NULL, DHSDSHEADER+3	},			/*   for now it's got it's	    */
    	{"CRPIX2",	DCADOUBLE, 	NEVER,   HDR_DC,	DC_TOP WCS_CRPIX2,	NULL, DHSDSHEADER+4	},			/*      own         		    */
    	{"CRVAL2",	DCADOUBLE, 	NEVER,   HDR_DC,	DC_TOP WCS_CRVAL2,	NULL, DHSDSHEADER+5	},			/*      	getWCS				*/
    	{"CD1_1",	DCADOUBLE,  NEVER,   HDR_DC,	DC_TOP WCS_CD1_1, 	NULL, DHSDSHEADER+6	},			/*      and					    */
    	{"CD1_2",	DCADOUBLE,  NEVER,   HDR_DC,	DC_TOP WCS_CD1_2, 	NULL, DHSDSHEADER+7	},			/*      	getWCSinfo			*/
    	{"CD2_1",	DCADOUBLE,  NEVER,   HDR_DC,	DC_TOP WCS_CD2_1, 	NULL, DHSDSHEADER+8	},			/*      routine					*/
    	{"CD2_2",	DCADOUBLE,  NEVER,   HDR_DC,	DC_TOP WCS_CD2_2, 	NULL, DHSDSHEADER+9	},			/*  I flagged them as never    	*/
    	{"MJD_OBS",	DCADOUBLE,  NEVER,   HDR_DC,	DC_TOP WCS_MJDOBS,	NULL, DHSDSHEADER+10	},			/*  for this reason    			*/
		{"FRAME",  	DCASTRING,  NOW,     HDR_DC,   TCS_SAD_TOP "sourceAInputFrame",	NULL, DHSDSHEADER+11	},	/* here it's NOW or NEVER - so NOW */
		{"BNCH_TMP",	     DCADOUBLE,     BEFORE,  HDR_ALL,  "nirs:sad:cc:benchTempPoint",	NULL, DHSDSHEADER+12},
		{"FW1_POS",  	     DCASTRING,     BEFORE,  HDR_ALL,  "nirs:sad:cc:fw1Position",	NULL, DHSDSHEADER+13},
		{"FW1_ENG",	         DCALONG,     BEFORE,  HDR_ALL,  "nirs:sad:cc:fw1Eng",	NULL, DHSDSHEADER+14},
		{"FW2_POS",  	     DCASTRING,     BEFORE,  HDR_ALL,  "nirs:sad:cc:fw2Position",	NULL, DHSDSHEADER+15},
		{"FW2_ENG",	         DCALONG,     BEFORE,  HDR_ALL,  "nirs:sad:cc:fw2Eng",	NULL, DHSDSHEADER+16},
		{"CAM_POS",  	     DCASTRING,     BEFORE,  HDR_ALL,  "nirs:sad:cc:cameraPosition",	NULL, DHSDSHEADER+17},
		{"CAM_ENG",	         DCALONG,     BEFORE,  HDR_ALL,  "nirs:sad:cc:cameraEng",	NULL, DHSDSHEADER+18},
		{"SLIT_POS",  	     DCASTRING,     BEFORE,  HDR_ALL,  "nirs:sad:cc:slitPosition",	NULL, DHSDSHEADER+19},
		{"SLIT_ENG",	     DCALONG,     BEFORE,  HDR_ALL,  "nirs:sad:cc:slitEng",	NULL, DHSDSHEADER+20},
		{"DKR_POS",       DCASTRING,     BEFORE,  HDR_ALL,  "nirs:sad:cc:deckerPosition",	NULL, DHSDSHEADER+21},
		{"DKR_ENG",	     DCALONG,     BEFORE,  HDR_ALL,  "nirs:sad:cc:deckerEng",	NULL, DHSDSHEADER+22},
		{"GR_POS",      DCASTRING,     BEFORE,  HDR_ALL,  "nirs:sad:cc:gratingPosition",	NULL, DHSDSHEADER+23},
		{"GR_ENG",	     DCALONG,     BEFORE,  HDR_ALL,  "nirs:sad:cc:gratingEng",	NULL, DHSDSHEADER+24},
		{"GR_WL",	 DCADOUBLE, BEFORE,  HDR_ALL,  "nirs:sad:cc:gratingWvlength",	NULL, DHSDSHEADER+25},
		{"GR_ORDER"    ,DCALONG,       BEFORE,  HDR_ALL,  "nirs:sad:cc:gratingOrder",	NULL, DHSDSHEADER+26},
		{"GR_TILT",     DCADOUBLE,     BEFORE,  HDR_ALL,  "nirs:sad:cc:gratingTilt",	NULL, DHSDSHEADER+27},
		{"PRSM_POS",  	     DCASTRING,     BEFORE,  HDR_ALL,  "nirs:sad:cc:xdispPosition",	NULL, DHSDSHEADER+28},
		{"PRSM_ENG",	     DCALONG,     BEFORE,  HDR_ALL,  "nirs:sad:cc:xdispEng",	NULL, DHSDSHEADER+29},
		{"ACQ_POS",  	     DCASTRING,     BEFORE,  HDR_ALL,  "nirs:sad:cc:acqPosition",	NULL, DHSDSHEADER+30},
		{"CVER_POS",  	     DCASTRING,     BEFORE,  HDR_ALL,  "nirs:sad:cc:coverPosition",	NULL, DHSDSHEADER+31},
		{"FCS_POS",  	     DCASTRING,     BEFORE,  HDR_ALL,  "nirs:sad:cc:focusPosition",	NULL, DHSDSHEADER+32},
		{"FCS_MODE",       DCASTRING,     BEFORE,  HDR_ALL,  "nirs:cc:focusPosCad.VALB",	NULL, DHSDSHEADER+33},
		{"FCS_ENG",	     DCALONG,     BEFORE,  HDR_ALL,  "nirs:sad:cc:focusEng",	NULL, DHSDSHEADER+34},
		{"UCODEPTH",       DCASTRING,     BEFORE,  HDR_DC,   "nirs:dc:arSetup.A",	NULL, DHSDSHEADER+35},
		{"UCODENAM",       DCASTRING,     BEFORE,  HDR_DC,   "nirs:dc:arSetup.B",	NULL, DHSDSHEADER+36},
		{"COADDS",        DCALONG,       BEFORE,  HDR_DC,   "nirs:dc:obsSetup.VALE",	NULL, DHSDSHEADER+37},
		{"LNRS",           DCALONG,       BEFORE,  HDR_DC,   "nirs:dc:obsSetup.VALD",	NULL, DHSDSHEADER+38},
		{"NDAVGS",            DCALONG,       BEFORE,  HDR_DC,   "nirs:dc:obsSetup.VALC",	NULL, DHSDSHEADER+39},
	{"ROWS",         DCALONG,       BEFORE,  HDR_DC,   "nirs:dc:curMaxRow.VAL",	NULL, DHSDSHEADER+40},
	{"P_MODE",  	 DCASTRING,     BEFORE,  HDR_DC,   "nirs:sad:dc:procMode.VAL",	NULL, DHSDSHEADER+41},
	{"COLS",         DCALONG,       BEFORE,  HDR_DC,   "nirs:dc:curMaxCol.VAL",	NULL, DHSDSHEADER+42},
	{"INT_TIME",	 DCADOUBLE,     BEFORE,  HDR_DC,   "nirs:dc:integTime.VAL",	NULL, DHSDSHEADER+43},
	{"MIN_INT",	 DCADOUBLE,     BEFORE,  HDR_DC,   "nirs:dc:minInt.VAL",	NULL, DHSDSHEADER+44},
	{"FRMS_EXP",     DCALONG,       BEFORE,  HDR_DC,   "nirs:dc:ucFrmsPCycle.VAL",	NULL, DHSDSHEADER+45},
	{"COMMENT",  	 DCASTRING,     BEFORE,  HDR_DC,   "nirs:dc:commStr.VAL",	NULL, DHSDSHEADER+46},
	{"TITLE",        DCASTRING,     BEFORE,  HDR_DC,   "nirs:dc:titleStr.VAL",	NULL, DHSDSHEADER+47},
	{"DSRDTEMP",     DCADOUBLE,     BEFORE,  HDR_DC,   "nirs:dc:C1.SETP",	        NULL, DHSDSHEADER+48},
	{"DC_TEMP",      DCADOUBLE,     BEFORE,  HDR_DC,   "nirs:dc:C1Tmp",	        NULL, DHSDSHEADER+49},
	{"TMP_ERROR",	 DCADOUBLE,     NEVER,  HDR_DC,   "nirs:dc:rdFootHGain",	NULL, DHSDSHEADER+50},
	{"FOOT_PWR",	 DCADOUBLE,     BEFORE,  HDR_DC,   "nirs:dc:C1Heat",	        NULL, DHSDSHEADER+51},
	{"MNT_PWR",	 DCADOUBLE,     NEVER,  HDR_DC,   "nirs:dc:mntHtrFB",	        NULL, DHSDSHEADER+52},
	{"IMG_NAME",  	 DCASTRING,     BEFORE,  HDR_DC,   "nirs:dc:imName.VAL",	NULL, DHSDSHEADER+53},
	{"IMG_NUM",  	     DCALONG,     BEFORE,  HDR_DC,   "nirs:dc:imNum.VAL",	NULL, DHSDSHEADER+54},
	{NULL,  	         DCASTRING,     BEFORE,  HDR_DC,   NULL,	        NULL, DHSDSHEADER+55}
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
#define NUM_HEADER (DHSFRAMEHEADER + DHSFRAMEROIHEADER)

#ifndef DUM_GBLSOURCE
	extern dhsHeadersDef dhsFrameRoiHeader[];
	extern HeaderVals frameRoiHdr	[MAXCAPTBUFS][DHSFRAMEROIHEADER];
#else
	HeaderVals frameRoiHdr	[MAXCAPTBUFS][DHSFRAMEROIHEADER];
	dhsHeadersDef dhsFrameRoiHeader[] =
	{/*   keyword     type    timing   detail    pvname   proc      id #*/
    	{"DROINUM",	DCALONG,   NOW,    NULL, 	 NULL,   NULL,  DHSFRAMEHEADER+0	},  /* only support NOW timing */
    	{"LOWROW",	DCALONG,   NOW,    NULL, 	 NULL,   NULL,  DHSFRAMEHEADER+1 },  /* only support NOW timing */
    	{"LOWCOL",	DCALONG,   NOW,    NULL, 	 NULL,   NULL,  DHSFRAMEHEADER+2 },  /* only support NOW timing */
    	{"HIROW",	DCALONG,   NOW,    NULL, 	 NULL,   NULL,  DHSFRAMEHEADER+3 },	/* only support NOW timing */
    	{"HICOL",	DCALONG,   NOW,    NULL, 	 NULL,   NULL,  DHSFRAMEHEADER+4 }, 	/* only support NOW timing */
		{NULL,  	         DCASTRING,     BEFORE,  HDR_DC,   NULL,	NULL, DHSDSHEADER+54}
	};
#endif
