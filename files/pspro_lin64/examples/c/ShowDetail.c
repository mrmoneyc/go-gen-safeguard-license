#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../h/psprolib.h"

/******************************************************************
*
* This example demonstrates the sgShowServerDetail() function.
* It retrieves information from the license server about all 
* components that are checked out and by whom.  Plus some other 
* interesting information for immediate display purposes.
*
******************************************************************/
int main()
{
 int ret,thread_id,sockfd,pid,count;
 char msg[512],ip[16],process[256],user[64],host[256],component[33],version[12];

 sgSetAttrInt(SG_ATTR_LICENSETYPE,SG_LICENSETYPE_FLOATING);

 ret = sgConnect();
 if (ret != SG_SUCCESS) {
   sgGetLastErrorString(msg);
   printf("%s\n",msg);
   exit(0);
 }

 for (;;) {
     ret = sgShowServerDetail(&thread_id,&sockfd,ip,&pid,process,user,host,
                              component,version,&count);
     if (ret == SG_NO_MORE_SERVER_DETAIL) break;

     printf("(%d), %d, %d, %s, %d, %s, %s, %s, %s, %s, %d\n",ret,thread_id,sockfd,ip,pid,
			  process,user,host,component,version,count);
 }

 sgDisconnect();

exit(0);
}

