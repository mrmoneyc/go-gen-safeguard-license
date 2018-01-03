#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../h/psprolib.h"

int AcquireDemoNode(char *company, char *licensefile, char *component, char *version, char *email, char *szMessage);
int AcquirePaidNode(char *company, char *licensefile, char *component, char *version, char *email, char *szMessage);

/********************************************************************
*
* This sample demonstrates a real life scenario of using the Product
* Activation Server (PAS) for a typical client application.  It first
* checks whether there is a paid license available, if there is, it will 
* retrieve it.  If not, then it will attempt to obtain a demo license.
* available and all criteria are met, then a demo license will be 
* installed on the client computer next to this running executable.
*
* This example checks for a license called "monitor" "5.0".
*
* If you are testing this on your local host you won't need to change
* the hostname in the two locations below.  If not, you will need to
* change "localhost" to either an IP address or Domain name.
*
* MySQL and the Prodcut Activation Server will need to be running,
* and either of the "paid_float" or "demo_float" records will need
* to be added. if you already ran /bin/create.sql following the
* instructions in PASInstallGuide.pdf, these records are already added
*
********************************************************************/
int main(int nargs, char *args[])
{

  int retVal, daysRemaining;
  char company[128],licensefile[257],email[128],component[33],version[33];
  char szMessage[1024];

  sgSetAttrInt(SG_ATTR_LANGUAGE,SG_LANGUAGE_ENG);

  // break up the domain name so that it can't easily be changed with a binary editor.
  // you can use an IP address, hostname or domain name
  sprintf(company,"%c%c%c%c%c%c%c%c%c",'l','o','c','a','l','h','o','s','t');

  // passing the email address is a good idea so that you know who to notify in the future

  strcpy(email,"bob@example.com");

  // the @ tells the software to look for license.lic side-by-side to this executable, not in the current directory
  // unless the executable is located in the current directory.  Or you can build a pathname to your desired
  // location.  Environment variables, relative pathnames are all accepted.

  strcpy(licensefile,"@pas-nodelocked.lic");

  // the name of the component (always a good idea to make it hard to change with binary editor)

  sprintf(component,"%c%c%c%c%c%c%c",'m','o','n','i','t','o','r');

  // Same with the version number

  sprintf(version,"%c%c%c",'5','.','0');

  printf("Checking for a license to run %s.\n",component);
  retVal = AcquirePaidNode(company, licensefile, component, version, email, szMessage);
  if ((retVal != SG_SUCCESS) && (retVal != SG_AUTHORIZED)) {

    printf("Checking for a demo license to run %s.\n",component);
    retVal = AcquireDemoNode(company, licensefile, component, version, email, szMessage);
    if ((retVal != SG_SUCCESS) && (retVal != SG_AUTHORIZED)) {

      // something else happened
      printf("%s\n",szMessage);
      exit(1);

    } else {

      sgExpireDays(licensefile,component,version,&daysRemaining);
      printf("Authorized to run the demo version of %s for %d more days\n",
             component,daysRemaining);

    }

  } else {

    sgExpireDays(licensefile,component,version,&daysRemaining);
    printf("Authorized to run %s for %d more days.\n",
           component,daysRemaining);

  }
 
  exit(0);
}


/****************************************************************************
*
* Get a demo license from the Product Activation Server
*
****************************************************************************/


int AcquireDemoNode(char *company, char *licensefile, char *component, char *version, char *email, char *szMessage)
{

  int retVal;
  char outsrv[257],componentline[1025];
  char msg[512];


  // Are we already licensed?  
  retVal = sgAuthorized(licensefile,component,version);
  if (retVal != SG_AUTHORIZED) {

    // not authorized yet, so contact the PAS server for a demo license
    // you an use a domain name or IP address.  Pick any port you want. 
    // 29775 is just the default

    retVal = sgPaActivate(company, 29775, SG_ACTIVATE_DEMO_NODE, NULL,
                          component, version, email, outsrv, componentline);
    if (retVal != SG_SUCCESS) {
      sgGetLastErrorString(msg);
      sprintf(szMessage,"Problem with the activation server: %s\n",msg);
      return (retVal);
    }
 
    // create the license file
    retVal = sgEnableComponentLine(licensefile,componentline);
    if (retVal != SG_SUCCESS) {
      sgGetLastErrorString(msg);
      sprintf(szMessage,"Problem installing the license: %s\n",msg);
      return (retVal);
    }

    // check once again for the demo license
    retVal = sgAuthorized(licensefile,component,version);
    sgGetLastErrorString(szMessage);
    return(retVal);

  } else {
  
    sgGetLastErrorString(szMessage);
    return(retVal);

  }
  return(SG_SUCCESS);
}


/****************************************************************************
*
* Get a paid license from the Product Activation Server
*
****************************************************************************/

int AcquirePaidNode(char *company, char *licensefile, char *component, char *version, char *email, char *szMessage)
{

  int retVal;
  char outsrv[257],componentline[1025];
  char msg[513];


  // Are we already licensed?  
  retVal = sgAuthorized(licensefile,component,version);
  if (retVal != SG_AUTHORIZED) {

    // not authorized yet, so contact the PAS server for a paid license
    // you an use a domain name or IP address.  Pick any port you want. 
    // 29775 is just the default

    // break up the domain name so that it can't easily be changed with a binary editor.
    // you can use an IP address, hostname or domain name
    sprintf(company,"%c%c%c%c%c%c%c%c%c",'l','o','c','a','l','h','o','s','t');

    // we are going to use the email address as the unique paid customer identifier
    // it can be anything.  But the email address "bob@example.com" must be in the
    // cust column of the paid_node table to identify the customer.

    retVal = sgPaActivate(company, 29775, SG_ACTIVATE_PAID_NODE, email,
                          component, version, email, outsrv, componentline);
    if (retVal != SG_SUCCESS) {
      sgGetLastErrorString(msg);
      sprintf(szMessage,"Problem with the activation server: %s\n",msg);
      return (retVal);
    }
 
    // create the license file
    retVal = sgEnableComponentLine(licensefile,componentline);
    if (retVal != SG_SUCCESS) {
      sgGetLastErrorString(msg);
      sprintf(szMessage,"Problem installing the license: %s\n",msg);
      return (retVal);
    }

    // check once again for the paid license
    retVal = sgAuthorized(licensefile,component,version);
    sgGetLastErrorString(szMessage);
    return(retVal);

  } else {
  
    sgGetLastErrorString(szMessage);
    return(retVal);

  }
  return(SG_SUCCESS);
}
