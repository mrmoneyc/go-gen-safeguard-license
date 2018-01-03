<?php

/*******************************************************************************************
*
* Check for a node-locked "monitor" license, version "5.0"
*
*******************************************************************************************/

include("psprolib.php");

  $szMessage = str_repeat(' ',1024);

  // make this application use an external license file
  sgSetAttrInt(SG_ATTR_LICENSETYPE,SG_LICENSETYPE_EXTERNAL);

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
  
  if (sgAuthorized("monitor.lic","monitor","5.0") != SG_AUTHORIZED) {
    // tell the user they are not licensed for the application and exit gracefully
    $retVal = sgGetLastErrorString($szMessage);
    print "$szMessage\n";
    exit(1);
  }
  
  // create the int pointer
  $daysPtr = new_intp();

  $retVal = sgExpireDays("monitor.lic","monitor","5.0",$daysPtr);

  // dereference and delete the temporary pointer
  $daysRemaining = intp_value($daysPtr);
  delete_intp($daysPtr);
  
  print "Enabling the monitor functionality for $daysRemaining days....\n";
  
  print "Running the monitor application....\n";
  
?>
