import java.io.*;
import java.util.*;
import java.util.Arrays;
import com.persistentsecurity.safeguardlm.*;

//********************************************************************
//*
//* This demonstrates one way how to query the license server for 
//* specific information about each connected client and what they
//* have checked out, such as:
//*
//* thread ID
//* socket file descriptor
//* IP address
//* Process ID (PID)
//* Process name (pathname to the remote process)
//* Username
//* Hostname
//* Component
//* Version
//* Count
//*
//*
//********************************************************************

public class ShowDetail {
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


      String servername =     "localhost";
      int thread_id;
      int sockfd;
      byte ip[] = new byte[20];
      int pid;
      byte process[] = new byte[1024];
      byte user[] = new byte[128];
      byte host[] = new byte[256];
      byte component[] = new byte[20];
      byte version[] = new byte[20];
      int count;
      SWIGTYPE_p_int thread_idPtr;
      SWIGTYPE_p_int sockfdPtr;
      SWIGTYPE_p_int pidPtr;
      SWIGTYPE_p_int countPtr;
 
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
      thread_idPtr = PSProlibProxy.new_intPtr();
      sockfdPtr = PSProlibProxy.new_intPtr();
      pidPtr = PSProlibProxy.new_intPtr();
      countPtr = PSProlibProxy.new_intPtr();

      for(;;) {

        retVal = PSProlibProxy.sgShowServerDetail(thread_idPtr,sockfdPtr,ip,pidPtr,process,user,host,
                                    component,version,countPtr);
      
        if (retVal == PSProlibProxy.SG_NO_MORE_SERVER_DETAIL) break;

        // dereference the int pointers
        thread_id = PSProlibProxy.intPtr_value(thread_idPtr);
        sockfd = PSProlibProxy.intPtr_value(sockfdPtr);
        pid = PSProlibProxy.intPtr_value(pidPtr);
        count = PSProlibProxy.intPtr_value(countPtr);

        System.out.println(thread_id + ", " 
          + sockfd + ", " 
          + new String(ip,0,byteSys.byteLen(ip)) + ", " 
          + pid + ", " 
          + new String(process,0,byteSys.byteLen(process)) + ", " 
          + new String(user,0,byteSys.byteLen(user)) + ", " 
          + new String(host,0,byteSys.byteLen(host)) + ", " 
          + new String(component,0,byteSys.byteLen(component)) + ", " 
          + new String(version,0,byteSys.byteLen(version)) + ", " 
          + count);

      }


      // delete the int pointers
      PSProlibProxy.delete_intPtr(thread_idPtr);
      PSProlibProxy.delete_intPtr(sockfdPtr);
      PSProlibProxy.delete_intPtr(pidPtr);
      PSProlibProxy.delete_intPtr(countPtr);

      retVal = PSProlibProxy.sgDisconnect();

      System.exit(0);

  }
}  
