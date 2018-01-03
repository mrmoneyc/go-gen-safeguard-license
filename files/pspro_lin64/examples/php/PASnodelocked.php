<?php

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

include ("psprolib.php");

      $email =       "bob@example.com";
      $component =   "monitor";
      $version =     "5.0";
      $licensefile = "pas-nodelocked.lic";
      $company =     "localhost";
      $serverline =    str_repeat(' ',512);
      $componentline = str_repeat(' ',1024);
      $szMessage =     str_repeat(' ',1024);

      // make this application use an external license file
      sgSetAttrInt(SG_ATTR_LICENSETYPE,SG_LICENSETYPE_EXTERNAL);

      print "Checking for a license to run $component.\n";

      // Are we already licensed?  
      $retVal = sgAuthorized($licensefile,$component,$version);
      if ($retVal != SG_AUTHORIZED) {
    
        // we are going to use the email address as the unique paid customer identifier
        // it can be anything.  But the email address "bob@example.com" must be in the
        // cust column of the paid_node table to identify the customer.

        print "Checking for a paid license to run $component.\n";
        $retVal = sgPaActivate($company, 29775, SG_ACTIVATE_PAID_NODE, $email,
                          $component, $version, $email, $serverline, $componentline);

        if (($retVal != SG_SUCCESS) && ($retVal != SG_AUTHORIZED)) {

          print "Checking for a demo license to run $component.\n";
          $retVal = sgPaActivate($company, 29775, SG_ACTIVATE_DEMO_NODE, '',
                                $component, $version, $email, $serverline, $componentline);

          if (($retVal != SG_SUCCESS) && ($retVal != SG_AUTHORIZED)) {
            $retVal = sgGetLastErrorString($szMessage);
            print "Problem with the activation server: " . rtrim($szMessage) . "\n";
            exit(1);
          } else {
            // create the license file
            $retVal = sgEnableComponentLine($licensefile,$componentline);
            if ($retVal != SG_SUCCESS) {
              $retVal = sgGetLastErrorString($szMessage);
              print "Problem installing the license: " . rtrim($szMessage) . "\n";
              exit(1);
            }
          }

        } else {

          // create the license file
          $retVal = sgEnableComponentLine($licensefile,$componentline);
          if ($retVal != SG_SUCCESS) {
            $retVal = sgGetLastErrorString($szMessage);
            print "Problem installing the license: " . rtrim($szMessage) . "\n";
            exit(1);
          }
        }
      }

      // check once again in case the PAS sent us a new license file
      $retVal = sgAuthorized($licensefile,$component,$version);
      if ($retVal != SG_SUCCESS) {
        $retVal = sgGetLastErrorString($szMessage);
        print rtrim($szMessage) . "\n";
        exit(1);
      }
    
      // create the int pointer
      $daysPtr = new_intp();
      $retVal = sgExpireDays($licensefile,$component,$version,$daysPtr);
      // dereference and delete the int pointer
      $daysRemaining = intp_value($daysPtr);
      delete_intp($daysPtr);
      print "Authorized to run the demo version of $component for $daysRemaining more days.\n";
      exit(0);
?>