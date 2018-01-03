#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../h/psprolib.h"

/******************************************************************
*
* This example demonstrates the sgShowClient() function.
* It retrieves information about what the current process
* has checked out.
*
******************************************************************/
int main()
{
 int ret,count;
 char msg[1024],serverhost[256],clienthost[256],user[64],component[20],version[20];

 sgSetAttrInt(SG_ATTR_LICENSETYPE,SG_LICENSETYPE_FLOATING);

 ret = sgCheckout("Monitor","5.0");
 if (ret != SG_SUCCESS) {
   sgGetLastErrorString(msg);
   printf("%s\n",msg);
   exit(0);
 }

 // IMPORTANT:  Even thought the version for "widget" is 6.0 in the license file
 // if we check out an earlier version and only a 6.0 license is available it will
 // consume one of the 6.0 licenses
 ret = sgCheckout("widget","5.0");
 if (ret != SG_SUCCESS) {
   sgGetLastErrorString(msg);
   printf("%s\n",msg);
   exit(0);
 }

 // IMPORTANT!!  if you check out the same component again, the count will increment
 ret = sgCheckout("widget","5.0");
 if (ret != SG_SUCCESS) {
   sgGetLastErrorString(msg);
   printf("%s\n",msg);
   exit(0);
 }

 for(;;) {
     ret = sgShowClient(serverhost,clienthost,user,component,version,&count);
     if (ret == SG_NO_MORE_CLIENT_COMPONENTS) break;

     printf("%s, %s, %s, %s, %s, %d\n",serverhost,clienthost,user,component,version,count);
 }

 sgCheckin("monitor","5.0");

 // NOTE:  Even if you don't check-in the second "widget", it will be 
 // returned to the license pool when the process exits.
 sgCheckin("widget","5.0");

exit(0);
}

