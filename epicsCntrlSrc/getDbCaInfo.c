#include "cadef.h"
#include "db_access.h"

long getDbCaInfo (char *pvname, char *errMess, unsigned short type, void *outVal) {
	chid chid;
	float timeout=2.0;
	union db_access_val buff;
    long status;
    
	/* not in the local database? try a channel access */
	if ( (status = ca_search (pvname,&chid)) != ECA_NORMAL) {
		return -1;
		}
	if ( (status = ca_pend_io (timeout)) != ECA_NORMAL) {
		return -1;
		}
	if ( (status =  ca_get(dbf_type_to_DBR(ca_field_type (chid)),chid, &buff)) != ECA_NORMAL) {
		return -1;
		}

	if ( (status = ca_pend_io (timeout)) != ECA_NORMAL) {
		return -1;
		}
	
	
	switch (ca_field_type (chid)) {
		case DBR_STRING:
			strcpy(outVal,buff.strval);
		    break;
		case DBR_DOUBLE:
			*(double*)outVal = buff.doubleval;
		    break;
		case DBR_LONG:
			*(long*)outVal = buff.longval;
		    break;
		case DBR_SHORT:
			*(int*)outVal = buff.shrtval;
		    break;
		case DBR_CHAR:
			*(char*)outVal = buff.charval;
		    break;
		case DBR_ENUM:
			*(int*)outVal = buff.enmval;
			break;
		case DBR_FLOAT:
			*(float*)outVal = buff.fltval;
			break;
		default:
			return -1;
			break;
		}
	return 0;
	}
