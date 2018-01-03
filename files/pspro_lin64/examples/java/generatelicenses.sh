#!/bin/bash
# generate licenses for the sample code with 30 day timeouts from today and also use
# the customers ethernet address.

ID=`../../bin/pshostid -ethernet -x`
DT=`../../bin/sggendate 30`

# node-locked license
../../bin/pskeycode rc4 monitor 5.0 30-day-trial any $DT > monitor.lic

# floating license
../../bin/pskeycode rc4 monitor 5.0 $ID ethernet $DT 10 localhost 29750 > float.lic
../../bin/pskeycode rc4 process 5.0 $ID ethernet $DT 10 >> float.lic
../../bin/pskeycode rc4 widget 6.0 $ID ethernet $DT 10 >> float.lic
