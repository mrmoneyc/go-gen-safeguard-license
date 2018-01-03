#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../h/psprolib.h"

/*******************************************************************************************
*
* Check for a node-locked "monitor" license, version "5.0" 
*
*******************************************************************************************/


int main(int nargs, char *args[])
{

  int daysRemaining;
  char szMessage[1024];

  // make this application use an external license file
  sgSetAttrInt(SG_ATTR_LICENSETYPE,SG_LICENSETYPE_EXTERNAL);

  // the @ symbol tells the software the license file is next to this executable.

  if (sgAuthorized("@monitor.lic","monitor","5.0") != SG_AUTHORIZED) {
    // tell the user they are not licensed for the application and exit gracefully
    (void)sgGetLastErrorString(szMessage);
    fprintf(stdout,"%s\n",szMessage);
    exit(1);
  }

  sgExpireDays("@monitor.lic","monitor","5.0",&daysRemaining);

  fprintf(stdout,"Enabling the monitor functionality for %d days....\n",daysRemaining);

  fprintf(stdout,"Running the monitor application....\n");

  exit(0);
}
