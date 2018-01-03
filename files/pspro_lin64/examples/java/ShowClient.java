import java.io.*;
import java.util.*;
import java.util.Arrays;
import com.persistentsecurity.safeguardlm.*;

//********************************************************************
//*
//* This example demonstrates the sgShowClient() function.
//* It retrieves information about what the current process
//* has checked out.
//*
//********************************************************************

public class ShowClient {
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


      int count;
      byte serverhost[] = new byte[256];
      byte clienthost[] = new byte[256];
      byte user[] = new byte[64];
      byte component[] = new byte[20];
      byte version[] = new byte[20];
      byte szMessage[] = new byte[1024];
      int retVal;
      SWIGTYPE_p_int countPtr;


      // tell this program to use the floating license manager
      PSProlibProxy.sgSetAttrInt(SG_ATTRTYPE.SG_ATTR_LICENSETYPE,SG_LICENSETYPE.SG_LICENSETYPE_FLOATING);

      retVal = PSProlibProxy.sgCheckout("monitor","5.0");
      if (retVal != PSProlibProxy.SG_SUCCESS) {
        PSProlibProxy.sgGetLastErrorString(szMessage);
        System.out.println(new String(szMessage,0,byteSys.byteLen(szMessage)));
        System.exit(1);
      }

      // IMPORTANT:  Even thought the version for "widget" is 6.0 in the license file
      // if we check out an earlier version and only a 6.0 license is available it will
      // consume one of the 6.0 licenses

      retVal = PSProlibProxy.sgCheckout("widget","5.0");
      if (retVal != PSProlibProxy.SG_SUCCESS) {
        PSProlibProxy.sgGetLastErrorString(szMessage);
        System.out.println(new String(szMessage,0,byteSys.byteLen(szMessage)));
        System.exit(1);
      }

      // IMPORTANT!!  if you check out the same component again, the count will increment
      retVal = PSProlibProxy.sgCheckout("widget","5.0");
      if (retVal != PSProlibProxy.SG_SUCCESS) {
        PSProlibProxy.sgGetLastErrorString(szMessage);
        System.out.println(new String(szMessage,0,byteSys.byteLen(szMessage)));
        System.exit(1);
      }

      // create the int pointer
      countPtr = PSProlibProxy.new_intPtr();

      for(;;) {

        retVal = PSProlibProxy.sgShowClient(serverhost,clienthost,user,
                                            component,version,countPtr);
      
        if (retVal == PSProlibProxy.SG_NO_MORE_CLIENT_COMPONENTS) break;

        // dereference the int pointer
        count = PSProlibProxy.intPtr_value(countPtr);

        System.out.println(new String(serverhost,0,byteSys.byteLen(serverhost)) + ", " 
          + new String(clienthost,0,byteSys.byteLen(clienthost)) 
          + new String(user,0,byteSys.byteLen(user)) + ", " 
          + new String(component,0,byteSys.byteLen(component)) + ", " 
          + new String(version,0,byteSys.byteLen(version)) + ", " + count);

      }


      // delete the int pointer
      PSProlibProxy.delete_intPtr(countPtr);

      retVal = PSProlibProxy.sgCheckin("monitor","5.0");

      // NOTE:  Even if you don't check-in the second "widget", it will be
      // returned to the license pool when the process exits.
      retVal = PSProlibProxy.sgCheckin("widget","5.0");

      System.exit(0);

  }
}  
