#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../h/psprolib.h"

int AcquireDemoFloat(char *company, char *email, char *component, char *version, 
                     char *serverline, char *componentline, char *szMessage);
int AcquirePaidFloat(char *company, char *email, char *component, char *version, 
                     char *serverline, char *componentline, char *szMessage);

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
* and either of the "paid_node" or "demo_node" records will need
* to be added. if you already ran /bin/create.sql following the
* instructions in PASInstallGuide.pdf, these records are already added
*
********************************************************************/
int main(int nargs, char *args[])
{

  int retVal;
  char serverline[257],componentline[1024],email[128],component[33],version[33];
  char company[256];
  char szMessage[1024];
  FILE *file_fp = (FILE *)0;

  sgSetAttrInt(SG_ATTR_LANGUAGE,SG_LANGUAGE_ENG);

  // break up the domain name so that it can't easily be changed with a binary editor.
  // you can use an IP address, hostname or domain name
  sprintf(company,"%c%c%c%c%c%c%c%c%c",'l','o','c','a','l','h','o','s','t');

  // passing the email address is a good idea so that you know who to notify in the future
  strcpy(email,"bob@example.com");

  // the name of the component (always a good idea to make it hard to change with binary editor)
  sprintf(component,"%c%c%c%c%c%c%c",'m','o','n','i','t','o','r');

  // Same with the version number
  sprintf(version,"%c%c%c",'5','.','0');

  printf("Checking for a paid floating license to run %s.\n",component);

  retVal = AcquirePaidFloat(company, email, component, version, serverline, componentline, szMessage);
  if (retVal != SG_SUCCESS) {

    printf("Checking for a demo floating license to run %s.\n",component);
    retVal = AcquireDemoFloat(company, email, component, version, serverline, componentline, szMessage);
    if (retVal != SG_SUCCESS) {

      // something else happened
      printf("%s\n",szMessage);
      exit(1);
    }
  }

  printf("Here is your floating license file for the %s application.\n\n",component);
  printf("%s\n",serverline);
  printf("%s\n",componentline);

  printf("We have saved it as pas-floating.lic\n");

  file_fp = fopen("pas-floating.lic","w+");
  fputs(serverline,file_fp);
  fputs("\n",file_fp);
  fputs(componentline,file_fp);
  fputs("\n",file_fp);
  fclose (file_fp);

// Using the PAS to get a floating license file is just as easy as getting a
// node-locked license file.  Getting it set up so client applications can
// access the licese server and use the new license file, depends on several things.
//
// - Is the license server even running ?
// - If it is, where is it? On this machine or on a different system?
// - Depending on your Operating System (Windows, Linux, OS X, etc.), you will
//   want to set up the license server differently.  For example, on Windows, you
//   probably want to install sglmd.exe as a Windows Service.  On OS X, launchd.
//   
// - So at this point the process may become more manual.  Refer to the 
//   LicenseManagerGuide.pdf for instructions on setting up the floating 
//   license server.

  exit(0);
}


/****************************************************************************
*
* Get a demo floating license from the Product Activation Server
*
****************************************************************************/


int AcquireDemoFloat(char *company, char *email, char *component, char *version, 
                     char *serverline, char *componentline, char *szMessage)
{

  int retVal;
  char msg[512];

  retVal = sgPaActivate(company, 29775, SG_ACTIVATE_DEMO_FLOAT, NULL,
                          component, version, email, serverline, componentline);
  if (retVal != SG_SUCCESS) {
    sgGetLastErrorString(msg);
    sprintf(szMessage,"Problem with the activation server: %s\n",msg);
    return (retVal);
  }
 
  return(SG_SUCCESS);
}

/****************************************************************************
*
* Get a paid floating license from the Product Activation Server
*
****************************************************************************/


int AcquirePaidFloat(char *company, char *email, char *component, char *version, 
                     char *serverline, char *componentline, char *szMessage)
{

  int retVal;
  char msg[512];

  // we are going to use the email address as the unique paid customer identifier
  // it can be anything.  But the email address "bob@example.com" must be in the
  // cust column of the paid_float table to identify the customer.

  retVal = sgPaActivate(company, 29775, SG_ACTIVATE_PAID_FLOAT, email,
                          component, version, email, serverline, componentline);
  if (retVal != SG_SUCCESS) {
    sgGetLastErrorString(msg);
    sprintf(szMessage,"Problem with the activation server: %s\n",msg);
    return (retVal);
  }
 
  return(SG_SUCCESS);
}
