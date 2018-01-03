
/*******************************************************************************************
*
* Check for a node-locked "monitor" license, version "5.0"
*
*******************************************************************************************/


import java.io.*;
import java.util.*;
import com.persistentsecurity.safeguardlm.*;

public class Nodelocked {
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
      int retVal;
      int daysRemaining;
      SWIGTYPE_p_int daysPtr;


      // make this application use an external license file
      PSProlibProxy.sgSetAttrInt(SG_ATTRTYPE.SG_ATTR_LICENSETYPE,SG_LICENSETYPE.SG_LICENSETYPE_EXTERNAL);

      // !!!!!!!!!!!!!!!!!!!!!!!! EXTREMELY IMPORTANT !!!!!!!!!!!!!!!!!!!!!!
      // If you look at Nodelocked.c in examples/c you will notice that the license filename
      // begins with @  in the sgAuthorized() call.   This tells the SafeGuard software the 
      // license file "monitor.lic" is side-by-side to the executable accessing it.  For the 
      // C example, this works great so you dont have to build a pathname to the license file 
      // in your software.  However this does not work well for Java, Python and other language 
      // interfaces, because the executable is actually the "java" binary which is typically 
      // /usr/bin/java.  Or for Python, /usr/local/bin/python.  So if you use the @ sign to 
      // find your license file in a java app, it will expect the monitor.lic license file is 
      // /usr/bin/monitor.lic or /usr/local/bin/monitor.lic (NOT GOOD!)
      // So you will have to find your license file some other way. In the case below, it will look
      // in the current working directory.

      if (PSProlibProxy.sgAuthorized("monitor.lic","monitor","5.0") != PSProlibProxy.SG_AUTHORIZED) {
         // tell the user they are not licensed for the application and exit gracefully
         PSProlibProxy.sgGetLastErrorString(szMessage);
         System.out.println(new String(szMessage,0,byteSys.byteLen(szMessage)));
         System.exit(1);
      }

      // create the int pointer
      daysPtr = PSProlibProxy.new_intPtr();

      retVal = PSProlibProxy.sgExpireDays("monitor.lic","monitor","5.0",daysPtr);

      // dereference and delete the int pointer
      daysRemaining = PSProlibProxy.intPtr_value(daysPtr);
      PSProlibProxy.delete_intPtr(daysPtr);

      System.out.println("Enabling the monitor functionality for " + daysRemaining + " days....");


      System.out.println("Running the monitor application....");
  }
}
