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
//* and either of the "paid_float" or "demo_float" table records
//* will need to be updated to add the above component name, version, and
//* other information to enable this client app to get a license.  If you
//* use bin/create.sql to create the database and tables, these will be
//* populated for you.
//*
//********************************************************************

include ("psprolib.php");

      $email =         "bob@example.com";
      $component =     "monitor";
      $version =       "5.0";
      $licensefile =   "pas-floating.lic";
      $company =       "localhost";
      $serverline =    str_repeat(' ',512);
      $componentline = str_repeat(' ',1024);
      $szMessage =     str_repeat(' ',1024);

      // we are going to use the email address as the unique paid customer identifier
      // it can be anything.  But the email address "bob@example.com" must be in the
      // cust column of the paid_float table to identify the customer.

      print "Checking for a paid floating license to run $component.\n";
      $retVal = sgPaActivate($company, 29775, SG_ACTIVATE_PAID_FLOAT, $email,
                        $component, $version, $email, $serverline, $componentline);

      if ($retVal != SG_SUCCESS) {

        print "Checking for a demo floating license to run $component.\n";
        $retVal = sgPaActivate($company, 29775, SG_ACTIVATE_DEMO_FLOAT, '',
                        $component, $version, $email, $serverline, $componentline);

        if ($retVal != SG_SUCCESS) {
          $retVal = sgGetLastErrorString($szMessage);
          print "Problem with the activation server: " . rtrim($szMessage) . "\n";
          exit(1);
        }
      }

      
      print "Here is your floating license file for the $component application.\n";
      print rtrim($serverline) . "\n";
      print rtrim($componentline) . "\n";

      print "\nWe have saved it as pas-floating.lic\n";

      $file_fp = fopen("pas-floating.lic","w+");
      fputs($file_fp,rtrim($serverline));
      fputs($file_fp,"\n");
      fputs($file_fp,rtrim($componentline));
      fputs($file_fp,"\n");
      fclose ($file_fp);

// Using the PAS to get a floating license file is just as easy as getting a 
// node-locked license file.  Getting it set up so client applications can
// access the licese server and use the new license file, depends on several things.
//
// - Is the license server even running ?
// - If it is, where is it? On this machine or on a different system?
// - Depending on your Operating System (Windows, Linux, OS X, etc.), you will
//   want to set up the license server differently.  For example, on Windows, you
//   probably want to install sglmd.exe as a Windows Service.  On OS X, launchd.
//   
// - So at this point the process may become more manual.  Refer to the 
//   LicenseManagerGuide.pdf for instructions on setting up the floating 
//   license server.

      exit(0);
?>
