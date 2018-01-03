#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../h/psprolib.h"

void sg_crypt(char *string, int direction);
static int GetMyVendorID(char *id);

/*******************************************************************************************

Description:

*******************************************************************************************/


int main(int nargs, char *args[])
{

  char szMessage[1024];

  // make this application use an external license file
  sgSetAttrInt(SG_ATTR_LICENSETYPE,SG_LICENSETYPE_EXTERNAL);

  // set the vendor function via function pointer
  sgSetVendor(GetMyVendorID);

  fprintf(stdout,"Note: if you are running the demo version of SafeGuard LM, the only idtype supported is \"any\"\n");

  if (sgAuthorized("vendor.lic","monitor","5.0") != SG_AUTHORIZED) {
    // tell the user they are not licensed for the application and exit gracefully
    (void)sgGetLastErrorString(szMessage);
    fprintf(stdout,"%s\n",szMessage);
    exit(1);
  }

  fprintf(stdout,"Running the monitor application....\n");
  exit(0);
}


/***********************************************
*
* The vendor hostid function
*
***********************************************/


static int GetMyVendorID(char *id)
{

  char hostname[256],username[64];
  char key[32],in[512],out[512];

  // this is an example of a 'composite' ID where we use more than
  // one ID type to build a unique 'hostid'.

  // allow these just in case they have been disabled somewhere else
  sgSetAttrInt(SG_ATTR_ALLOW_IDTYPE,SG_IDTYPE_USERNAME);
  sgSetAttrInt(SG_ATTR_ALLOW_IDTYPE,SG_IDTYPE_HOSTNAME);

  sgGetAttrStr(SG_ATTR_USERNAME_ID,username);
  sgGetAttrStr(SG_ATTR_HOSTNAME_ID,hostname);
  sprintf(in,"%s-%s",username,hostname);

  // use RC4 to encrypt the hostid so that it is not obvious what it
  // consists of.  This RC4 encrypted string *is* the unique hostid

  // pick your own encryption key.
  sprintf(key,"%c%c%c%c%c%c",'q','w','e','r','t','y');
  sgArc4(1,key,in,out);

  // always encrypt the ID between function calls.  The receiving
  // code will decrypt it.

  sg_crypt(out,1);

  strcpy(id,out);
  return(0);
}
