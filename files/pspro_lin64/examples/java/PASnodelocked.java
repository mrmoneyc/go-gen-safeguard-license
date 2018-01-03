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
//* and either of the "paid_node" or "demo_node" table records
//* will need to be updated to add the above component name, version, and
//* other information to enable this client app to get a license.  If you
//* use bin/create.sql to create the database and tables, these will be
//* populated for you.
//*
//********************************************************************/

public class PASnodelocked {
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
      String licensefile = "pas-nodelocked.lic";
      String company =     "localhost";
      byte componentline[] = new byte[1024];
      byte szMessage[] = new byte[1024];
      byte serverline[] = new byte[512];
      int retVal;
      int daysRemaining;
      SWIGTYPE_p_int daysPtr;


      // make this application use an external license file
      PSProlibProxy.sgSetAttrInt(SG_ATTRTYPE.SG_ATTR_LICENSETYPE,SG_LICENSETYPE.SG_LICENSETYPE_EXTERNAL);

      System.out.println("Checking for a license to run " + component + ".");

      // Are we already licensed?  
      retVal = PSProlibProxy.sgAuthorized(licensefile,component,version);
      if (retVal != PSProlibProxy.SG_AUTHORIZED) {

        // we are going to use the email address as the unique paid customer identifier
        // it can be anything.  But the email address "bob@example.com" must be in the
        // cust column of the paid_node table to identify the customer.

        System.out.println("Checking for a paid license to run " + component + ".");
        retVal = PSProlibProxy.sgPaActivate(company, 29775, SG_ACTIVATETYPE.SG_ACTIVATE_PAID_NODE, email,
                          component, version, email, serverline, componentline);

        if ((retVal != PSProlibProxy.SG_SUCCESS) && (retVal != PSProlibProxy.SG_AUTHORIZED)) {

          System.out.println("Checking for a demo license to run " + component + ".");
          retVal = PSProlibProxy.sgPaActivate(company, 29775, SG_ACTIVATETYPE.SG_ACTIVATE_DEMO_NODE, null,
                                component, version, email, serverline, componentline);

          if ((retVal != PSProlibProxy.SG_SUCCESS) && (retVal != PSProlibProxy.SG_AUTHORIZED)) {
            PSProlibProxy.sgGetLastErrorString(szMessage);
            System.out.println("Problem with the activation server: " + new String(szMessage,0,byteSys.byteLen(szMessage)));
            System.exit(1);
          } else {
            // create the license file
            retVal = PSProlibProxy.sgEnableComponentLine(licensefile,componentline);
            if (retVal != PSProlibProxy.SG_SUCCESS) {
              PSProlibProxy.sgGetLastErrorString(szMessage);
              System.out.println("Problem installing the license: " + new String(szMessage,0,byteSys.byteLen(szMessage)));
              System.exit(1);
            }
          }

        } else {

          // create the license file
          retVal = PSProlibProxy.sgEnableComponentLine(licensefile,componentline);
          if (retVal != PSProlibProxy.SG_SUCCESS) {
            PSProlibProxy.sgGetLastErrorString(szMessage);
            System.out.println("Problem installing the license: " + new String(szMessage,0,byteSys.byteLen(szMessage)));
            System.exit(1);
          }
        }
      }

      // check once again in case the PAS sent us a new license file
      retVal = PSProlibProxy.sgAuthorized(licensefile,component,version);
      if (retVal != PSProlibProxy.SG_SUCCESS) {
        PSProlibProxy.sgGetLastErrorString(szMessage);
        System.out.println(new String(szMessage,0,byteSys.byteLen(szMessage)));
        System.exit(1);
      }
    
      // create the int pointer
      daysPtr = PSProlibProxy.new_intPtr();
      retVal = PSProlibProxy.sgExpireDays(licensefile,component,version,daysPtr);
      // dereference and delete the int pointer
      daysRemaining = PSProlibProxy.intPtr_value(daysPtr);
      PSProlibProxy.delete_intPtr(daysPtr);
      System.out.println("Authorized to run the demo version of " + component + " for " + daysRemaining + " more days.");
      System.exit(0);
  }
}  
