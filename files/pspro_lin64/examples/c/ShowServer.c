#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../h/psprolib.h"

/******************************************************************
*
* This example demonstrates the sgShowServer() function.
* It retrieves information from the license server about
* components that the server is serving up.
*
******************************************************************/
int main()
{
 int ret,count,current;
 char msg[1024],component[20],version[20],id[256],idtype[20],expires[20],certificate[128];

 sgSetAttrInt(SG_ATTR_LICENSETYPE,SG_LICENSETYPE_FLOATING);

 ret = sgConnect();
 if (ret != SG_SUCCESS) {
   sgGetLastErrorString(msg);
   printf("%s\n",msg);
   exit(0);
 }

 for(;;) {
     ret = sgShowServer(component,version,id,idtype,&count,&current,expires,certificate);
     if (ret == SG_NO_MORE_SERVER_COMPONENTS) break;

     printf("%s, %s, %s, %s, %d, %d, %s, %s\n",component,version,id,idtype,
			  count,current,expires,certificate);
 }

 sgDisconnect();

exit(0);
}

