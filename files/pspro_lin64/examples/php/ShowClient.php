<?php

//********************************************************************
//*
//* This example demonstrates the sgShowClient() function.
//* It retrieves information about what the current process
//* has checked out.
//*
//********************************************************************

include ("psprolib.php");

      $serverhost = str_repeat(' ',256);
      $clienthost = str_repeat(' ',256);
      $user = str_repeat(' ',64);
      $component = str_repeat(' ',20);
      $version = str_repeat(' ',20);
      $szMessage =     str_repeat(' ',1024);

      // tell this program to use the floating license manager
      sgSetAttrInt(SG_ATTR_LICENSETYPE,SG_LICENSETYPE_FLOATING);

      $retVal = sgCheckout("monitor","5.0");
      if ($retVal != SG_SUCCESS) {
        $retVal = sgGetLastErrorString($szMessage);
        print rtrim($szMessage) . "\n";
        exit(1);
      }

      // IMPORTANT:  Even thought the version for "widget" is 6.0 in the license file
      // if we check out an earlier version and only a 6.0 license is available it will
      // consume one of the 6.0 licenses

      $retVal = sgCheckout("widget","5.0");
      if ($retVal != SG_SUCCESS) {
        $retVal = sgGetLastErrorString($szMessage);
        print rtrim($szMessage) . "\n";
        exit(1);
      }

      // IMPORTANT!!  if you check out the same component again, the count will increment
      $retVal = sgCheckout("widget","5.0");
      if ($retVal != SG_SUCCESS) {
        $retVal = sgGetLastErrorString($szMessage);
        print rtrim($szMessage) . "\n";
        exit(1);
      }

      // create the int pointer
      $countPtr = new_intp();

      for(;;) {

        $retVal = sgShowClient($serverhost,$clienthost,$user,
                               $component,$version,$countPtr);
      
        if ($retVal == SG_NO_MORE_CLIENT_COMPONENTS) break;

        // dereference the int pointer
        $count = intp_value($countPtr);

        print rtrim($serverhost) . ", " .
              rtrim($clienthost) . ", " .
              rtrim($user) . ", " .
              rtrim($component) . ", " .
              rtrim($version) . ", " .
              $count . "\n";
      }


      // delete the int pointer
      delete_intp($countPtr);

      $retVal = sgCheckin("monitor","5.0");

      // NOTE:  Even if you don't check-in the second "widget", it will be
      // returned to the license pool when the process exits.
      $retVal = sgCheckin("widget","5.0");

      exit(0);
?>
