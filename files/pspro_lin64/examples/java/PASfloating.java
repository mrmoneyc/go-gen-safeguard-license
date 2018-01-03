import java.io.*;
import java.util.*;
import java.util.Arrays;
import com.persistentsecurity.safeguardlm.*;

//********************************************************************
//*
//* This sample demonstrates a real life scenario of using the Product
//* Activation Server for a typical client application.  It first checks
//* whether there is a paid license available, if there is, it will 
//* retrieve it.  If not, then it will attempt to obtain a demo license.
//* available and all criteria are met, then a demo license will be 
//* installed on the client computer next to this running executable.
//*
//* This example checks for a license called "monitor" "5.0".
//*
//* If you are testing this on your local host you won't need to change
//* the hostname in the two locations below.  If not, you will need to
//* change "localhost" to either an IP address or Domain name.
//*
//* MySQL and the Prodcut Activation Server will need to be running,
//* and either of the "paid_float" or "demo_float" table records
//* will need to be updated to add the above component name, version, and
//* other information to enable this client app to get a license.  If you
//* use bin/create.sql to create the database and tables, these will be
//* populated for you.
//*
//********************************************************************

public class PASfloating {
  public static void main(String[] args) {
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


      String email =       "bob@example.com";
      String component =   "monitor";
      String version =     "5.0";
      String licensefile = "pas-floating.lic";
      String company =     "localhost";
      byte serverline[] = new byte[512];
      byte componentline[] = new byte[1024];
      byte szMessage[] = new byte[1024];
      PrintStream ps;
      int retVal;
      int daysRemaining;
      SWIGTYPE_p_int daysPtr;

      // we are going to use the email address as the unique paid customer identifier
      // it can be anything.  But the email address "bob@example.com" must be in the
      // cust column of the paid_float table to identify the customer.

      System.out.println("Checking for a paid floating license to run " + component + ".");
      retVal = PSProlibProxy.sgPaActivate(company, 29775, SG_ACTIVATETYPE.SG_ACTIVATE_PAID_FLOAT, email,
                        component, version, email, serverline, componentline);

      if (retVal != PSProlibProxy.SG_SUCCESS) {

        System.out.println("Checking for a demo floating license to run " + component + ".");
        retVal = PSProlibProxy.sgPaActivate(company, 29775, SG_ACTIVATETYPE.SG_ACTIVATE_DEMO_FLOAT, null,
                                component, version, email, serverline, componentline);

        if (retVal != PSProlibProxy.SG_SUCCESS) {
          PSProlibProxy.sgGetLastErrorString(szMessage);
          System.out.println("Problem with the activation server: " + new String(szMessage,0,byteSys.byteLen(szMessage)));
          System.exit(1);
        }
      }

      
      System.out.println("Here is your floating license file for the " + component + " application.");
      System.out.println(new String(serverline,0,byteSys.byteLen(serverline)));
      System.out.println(new String(componentline,0,byteSys.byteLen(componentline)));

      System.out.println("We have saved it as pas-floating.lic");

      String sl = new String(serverline,0,byteSys.byteLen(serverline));
      String cl = new String(componentline,0,byteSys.byteLen(componentline));
      try {
        ps = new PrintStream("pas-floating.lic");
        ps.println(sl);
        ps.println(cl);
        ps.close();
      } catch (IOException e) {
          System.out.println("save exception");
      }

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


      System.exit(0);

  }
}  
