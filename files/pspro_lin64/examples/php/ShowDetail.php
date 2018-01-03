<?php

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

include ("psprolib.php");

      $servername       = "localhost";
      $ip               = str_repeat(' ',20);
      $process          = str_repeat(' ',256);
      $user             = str_repeat(' ',64);
      $host             = str_repeat(' ',256);
      $component        = str_repeat(' ',20);
      $version          = str_repeat(' ',20);
      $szMessage        = str_repeat(' ',1024);


      // tell this program to use the floating license manager
      sgSetAttrInt(SG_ATTR_LICENSETYPE,SG_LICENSETYPE_FLOATING);

      $retVal = sgConnect();

      if ($retVal != SG_SUCCESS) {
        $retVal = sgGetLastErrorString($szMessage);
        print rtrim($szMessage) . "\n";
        exit(1);
      }

      // create the int pointers
      $thread_idPtr = new_intp();
      $sockfdPtr = new_intp();
      $pidPtr = new_intp();
      $countPtr = new_intp();

      for(;;) {

        $retVal = sgShowServerDetail($thread_idPtr,$sockfdPtr,$ip,$pidPtr,$process,$user,$host,
                                    $component,$version,$countPtr);
      
        if ($retVal == SG_NO_MORE_SERVER_DETAIL) break;

        // dereference the int pointer
        $thread_id = intp_value($thread_idPtr);
        $sockfd = intp_value($sockfdPtr);
        $pid = intp_value($pidPtr);
        $count = intp_value($countPtr);

        print $thread_id . ", " .
              $sockfd . ", " .
              rtrim($ip) . ", " .
              $pid . ", " .
              rtrim($process) . ", " .
              rtrim($user) . ", " .
              rtrim($host) . ", " .
              rtrim($component) . ", " .
              rtrim($version) . ", " .
              $count . "\n";
      }


      // delete the int pointers
      delete_intp($thread_idPtr);
      delete_intp($sockfdPtr);
      delete_intp($pidPtr);
      delete_intp($countPtr);

      $retVal = sgDisconnect();

      exit(0);
?>
