#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../h/psprolib.h"

// Prototypes for callbacks for lost connection to license server
int myRecon(char *server,int retrycount, int retries);
int myReconCheckoutFail(char *server,char *component,char *version);
int myReconComplete(char *server,int retrycount);
int myReconExit(char *server,int retrycount);


/*******************************************************************************************
*
* Check out a "monitor" license, version "5.0" from the license server
*
* The server will have to be running and serving this license.
*
*******************************************************************************************/


int main(int nargs, char *args[])
{

  char szMessage[1024];

  // make this application use a floating license server
  sgSetAttrInt(SG_ATTR_LICENSETYPE,SG_LICENSETYPE_FLOATING);

  // Set callbacks just in case we loose connection with the license server
  sgSetAttrFnC(SG_ATTR_VENDOR_RECONNECT,myRecon);
  sgSetAttrFnC(SG_ATTR_VENDOR_RECONNECT_COMPLETE,myReconComplete);
  sgSetAttrFnC(SG_ATTR_VENDOR_RECONNECT_CHECKOUT_FAIL,myReconCheckoutFail);
  sgSetAttrFnC(SG_ATTR_VENDOR_RECONNECT_EXIT,myReconExit);

  if (sgCheckout("monitor","5.0") != SG_SUCCESS) {
    // tell the user they are not licensed and exit gracefully
    (void)sgGetLastErrorString(szMessage);
    fprintf(stdout,"%s\n",szMessage);
    exit(1);
  }

  fprintf(stdout,"Running the monitor application....\n");

  fprintf(stdout,"\nPress return to release the license....\n");
  fgets (szMessage,10,stdin);

  // app is finished, check in the license.  NOTE:  it is not necessary to do this
  // as the license server will detect the process terminating and do it for you.

  sgCheckin("monitor","5.0");

  exit(0);
}

// These are the callback functions for when the client (this program) looses connection
// with the license server.  See the "ProgrammerGuide.pdf" for more information.
// This give you control over what to do when a connection is lost with the license server
// They are not necessary.  However, if you don't implement them, the default handlers behave
// almost the same as these in this example.  If you had a GUI program, you would want to 
// do something more than just calling fprintf()

/*********************************************************
* attempt to reconnect
*********************************************************/

int myRecon(char *server,int retrycount, int retries)
{
  fprintf (stdout,"myRecon: Lost connection with license server \"%s\".  Attempting to reconnect %d of %d ....\n",
                    server,retrycount,retries);
  return(0);
}

/*********************************************************
* reconnected, but one or more of the licenses cannot be re-checked out
*********************************************************/

int myReconCheckoutFail(char *server,char *component,char *version)
{
  char errstr[1024];
  fprintf (stdout,"myRecon: While reconnecting to license server \"%s\" unable to re-checkout the license for \"%s\" version \"%s\".\n",
                    server,component,version);
  sgGetLastErrorString(errstr);
  fprintf (stdout,"for the following reason: %s\n",errstr);
  fprintf (stdout,"Disabling \"%s\" functionality.\n",component);
  // TODO: Disable this license functionality in your application...
  return(0);
}

/*********************************************************
* called when successfully reconnected to the license server
*********************************************************/

int myReconComplete(char *server,int retrycount)
{
  fprintf (stdout,"myRecon: Reconnected to license server \"%s\" after %d attempts ....\n",server,retrycount);
  return(0);
}

/*********************************************************
* bad news.  could not reconnect to the license server
*********************************************************/

int myReconExit(char *server,int retrycount)
{
  fprintf (stdout,"myRecon: Failed to reconnect to license server \"%s\" after %d attempts .... Exiting.\n",server,retrycount);
  // Do what you want here, but right now, there is no license server to talk to and no licenses are checked out
  // if you just return(0), the app will continue to run.
  exit(-1);
}

