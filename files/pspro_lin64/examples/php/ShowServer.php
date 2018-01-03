<?php

//********************************************************************
//*
//* This example demonstrates the sgShowServer() function.
//* It retrieves information from the license server about
//* components that the server is serving up.
//*
//********************************************************************

include ("psprolib.php");

      $component        = str_repeat(' ',20);
      $version          = str_repeat(' ',20);
      $id               = str_repeat(' ',20);
      $idtype           = str_repeat(' ',20);
      $expires          = str_repeat(' ',20);
      $certificate      = str_repeat(' ',128);
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
      $countPtr = new_intp();
      $currentPtr = new_intp();

      for (;;) {

        $retVal = sgShowServer($component,$version,$id,$idtype,$countPtr,
                                    $currentPtr,$expires,$certificate);
      
        if ($retVal == SG_NO_MORE_SERVER_COMPONENTS) break;

        // dereference the int pointers
        $count = intp_value($countPtr);
        $current = intp_value($currentPtr);

        print rtrim($component) . ", " .
             rtrim($version). ", " .
             rtrim($id) . ", " .
             rtrim($idtype) . ", " .
             $count . ", " .
             $current . ", " .
             rtrim($expires) . ", " .
             rtrim($certificate) . "\n";

      }


      // delete the int pointers
      delete_intp($countPtr);
      delete_intp($currentPtr);

      $retVal = sgDisconnect();

      exit(0);
?>
