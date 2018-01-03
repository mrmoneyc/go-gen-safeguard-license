<?php

/*******************************************************************************************
*
* Check out a "monitor" license, version "5.0" from the license server
*
* The server will have to be running and serving this license.
*
*******************************************************************************************/

include ("psprolib.php");

  $szMessage = str_repeat(' ',1024);

  // make this application use a floating license server
  sgSetAttrInt(SG_ATTR_LICENSETYPE,SG_LICENSETYPE_FLOATING);

  // set the LM callbacks for when the connection to the license server
  // is lost for any reason.

  if (sgCheckout("monitor","5.0") != SG_SUCCESS) {
    // tell the user they are not licensed for the application and exit gracefully
    $retVal = sgGetLastErrorString($szMessage);
    print rtrim($szMessage) . "\n";
    exit(1);
  }

  print "Running the monitor application....\n\n";

  print "Press return to release the license....";
  $line = stream_get_line(STDIN, 10, PHP_EOL);

  // app is finished, check in the license.  NOTE:  it is not necessary to do this
  // as the license server will detect the process terminating and do it for you.

  sgCheckin("monitor","5.0");

  exit(0);
?>
