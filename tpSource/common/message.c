static char rcid[]="$Id$";
/******************************************************************************
 * Program:	common
 * File:	message.c
 * Purpose:	various message routines
 * Author:	David Koski
 * Copyright:   Aura Inc.  All rights reserved.
 * History:
 *		14Dec92	created						dak
 *
 *****************************************************************************/

#include "protocol.h"
#include "common.h"

int bad_msg(int header, int *buf)
{
    send_debug ("ERROR bad message number %d", MESSAGE(header));
    return 0;
}

