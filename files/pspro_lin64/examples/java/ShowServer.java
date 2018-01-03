import java.io.*;
import java.util.*;
import java.util.Arrays;
import com.persistentsecurity.safeguardlm.*;

//********************************************************************
//*
//* This example demonstrates the sgShowServer() function.
//* It retrieves information from the license server about
//* components that the server is serving up.
//*
//********************************************************************

public class ShowServer {
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


      byte component[] = new byte[20];
      byte version[] = new byte[20];
      byte id[] = new byte[256];
      byte idtype[] = new byte[20];
      byte expires[] = new byte[20];
      byte certificate[] = new byte[128];
      int count,current;
      SWIGTYPE_p_int countPtr;
      SWIGTYPE_p_int currentPtr;
      byte szMessage[] = new byte[1024];
      int retVal;


      // tell this program to use the floating license manager
      PSProlibProxy.sgSetAttrInt(SG_ATTRTYPE.SG_ATTR_LICENSETYPE,SG_LICENSETYPE.SG_LICENSETYPE_FLOATING);

      retVal = PSProlibProxy.sgConnect();

      if (retVal != PSProlibProxy.SG_SUCCESS) {
        PSProlibProxy.sgGetLastErrorString(szMessage);
        System.out.println(new String(szMessage,0,byteSys.byteLen(szMessage)));
        System.exit(1);
      }

      // create the int pointers
      countPtr = PSProlibProxy.new_intPtr();
      currentPtr = PSProlibProxy.new_intPtr();

      for (;;) {

        retVal = PSProlibProxy.sgShowServer(component,version,id,idtype,countPtr,
                                            currentPtr,expires,certificate);
      
        if (retVal == PSProlibProxy.SG_NO_MORE_SERVER_COMPONENTS) break;

        // dereference the int pointers
        count = PSProlibProxy.intPtr_value(countPtr);
        current = PSProlibProxy.intPtr_value(currentPtr);

        System.out.println(new String(component,0,byteSys.byteLen(component)) + ", " 
             + new String(version,0,byteSys.byteLen(version)) + ", " 
             + new String(id,0,byteSys.byteLen(id)) + ", " 
             + new String(idtype,0,byteSys.byteLen(idtype)) + ", " 
             + count + ", " 
             + current + ", " 
             + new String(expires,0,byteSys.byteLen(expires)) + ", " 
             + new String(certificate,0,byteSys.byteLen(certificate)));

      }


      // delete the int pointers
      PSProlibProxy.delete_intPtr(countPtr);
      PSProlibProxy.delete_intPtr(currentPtr);

      retVal = PSProlibProxy.sgDisconnect();

      System.exit(0);

  }
}  
