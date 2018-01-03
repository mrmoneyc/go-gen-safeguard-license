
/*******************************************************************************************
*
* Check out a "monitor" license, version "5.0" from the license server
*
* The server will have to be running and serving this license.
*
*******************************************************************************************/

import java.io.*;
import java.util.*;
import com.persistentsecurity.safeguardlm.*;

public class Floating {
  public static void main(String[] args){
      try {
        // this forces java.library.path to get updated at runtime
        addToPath.addIt(".");
        if (System.getProperty("os.name").toLowerCase().indexOf("windows") > -1) {
            System.loadLibrary("psprolibjni_win");
        } else if (System.getProperty("os.name").toLowerCase().indexOf("linux") > -1) {
            System.loadLibrary("psprolibjni_lin");
        } else if (System.getProperty("os.name").toLowerCase().indexOf("mac") > -1) {
            System.loadLibrary("psprolibjni_mac");
        }
      } catch (IOException e) {
        System.err.println(e);
        System.exit(1);
      } catch (UnsatisfiedLinkError e) {
        System.err.println("Native code library failed to load.\n" + e);
        System.exit(1);
      }


      byte szMessage[] = new byte[1024];
      Scanner scanner = new Scanner(System.in);

      // make this application use a floating license server
      PSProlibProxy.sgSetAttrInt(SG_ATTRTYPE.SG_ATTR_LICENSETYPE,SG_LICENSETYPE.SG_LICENSETYPE_FLOATING);

      // set the LM callbacks for when the connection to the license server
      // is lost for any reason.

      // check every 1 minute (default is every 2 minutes)
      PSProlibProxy.sgSetAttrInt(SG_ATTRTYPE.SG_ATTR_RETRY_INTERVAL,1);

      // actual methods at the end of this source
      PSProlibProxy.sgSetAttrFnJ(SG_ATTRTYPE.SG_ATTR_VENDOR_RECONNECT,"vendor_reconnect");
      PSProlibProxy.sgSetAttrFnJ(SG_ATTRTYPE.SG_ATTR_VENDOR_RECONNECT_COMPLETE,"vendor_reconnect_complete");
      PSProlibProxy.sgSetAttrFnJ(SG_ATTRTYPE.SG_ATTR_VENDOR_RECONNECT_EXIT,"vendor_reconnect_exit");
      PSProlibProxy.sgSetAttrFnJ(SG_ATTRTYPE.SG_ATTR_VENDOR_RECONNECT_CHECKOUT_FAIL,"vendor_reconnect_checkout_fail");

      if (PSProlibProxy.sgCheckout("monitor","5.0") != PSProlibProxy.SG_SUCCESS) {
         // tell the user they are not licensed for the application and exit gracefully
         PSProlibProxy.sgGetLastErrorString(szMessage);
         System.out.println(new String(szMessage,0,byteSys.byteLen(szMessage)));
         System.exit(1);
      }

      System.out.println("Running the monitor application....");

      System.out.println("");
      System.out.print("Press return to release the license....");
      String response = scanner.nextLine();

      // app is finished, check in the license.  NOTE:  it is not necessary to do this
      // as the license server will detect the process terminating and do it for you.

      PSProlibProxy.sgCheckin("monitor","5.0");

      System.exit(0);
  }
}


//*********************************************************************
//*
//* The sgLMCallbacks class is the mandatory class name for the functions
//* that deal with the condition when the connection to the LM has been
//* lost.  If you don't define these, then default handlers are instaled
//* which look just like these !!
//*
//* To see this in action...
//*
//* Start the license manager (first run generatelicenses.sh/bat)
//*
//* ../../bin/sglmserver float.lic (or for Windows) ..\..\bin\sglmserver float.lic
//*
//* from another Terminal window or CMD prompt run Floating.java
//*
//* java Floating
//*
//* Leave it running (don't press return to end the program)
//*
//* Then CTL-C the license server (stop it).  And wait 1 minute or two minutes.
//* After you see the "Lost..." messages, restart the license server again and
//* wait another minute to see "Floating.java" "Reconnect...."
//*
//* In real life, you will probably want to do more with these routines. But it 
//* is a good start.
//*
//*********************************************************************

class sgLMCallbacks {

    // Warn the user that the connection to the LM has been lost.
    private static void vendor_reconnect( String server, int retries, int count) {
      System.out.println();
      System.out.print("Lost connection with server " + server + " attempting to reconnect " + retries + " of " + count + " ...");
    }

    // We have reconnected to the LM and all is good again
    private static void vendor_reconnect_complete( String server, int retries) {
      System.out.println();
      System.out.println("Reconnected with server " + server + " after " + retries + " attempts ...");
    }

    // We have reconnected, but this license cannot be checked out (probably someone else beat us too it)
    private static void vendor_reconnect_checkout_fail( String server, String component, String version) {
      System.out.println();
      System.out.print("Unable to check out license " + component + ", version " + version + " from server " + server + " ...");
      /* disable that functionality or pause and make another attempt here */
    }

    // Bad news.. we were not able to reconnect to the LM after the allocated number of retries.
    private static void vendor_reconnect_exit( String server, int retries) {
      System.out.println();
      System.out.println("Maximum reconnect attempts of " + retries + " to server " + server + " ...");
      System.exit(1);
    }
}

