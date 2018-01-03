#!/bin/bash
gfortran -m64 -I../../h -o Floating Floating.f ../../lib/libpsprolib_mac.a -framework IOKit -framework CoreFoundation
gfortran -m64 -I../../h -o Nodelocked Nodelocked.f ../../lib/libpsprolib_mac.a -framework IOKit -framework CoreFoundation
gfortran -m64 -I../../h -o PASfloating PASfloating.f ../../lib/libpsprolib_mac.a -framework IOKit -framework CoreFoundation
gfortran -m64 -I../../h -o PASNodelocked PASNodelocked.f ../../lib/libpsprolib_mac.a -framework IOKit -framework CoreFoundation
gfortran -m64 -I../../h -o ShowClient ShowClient.f ../../lib/libpsprolib_mac.a -framework IOKit -framework CoreFoundation
gfortran -m64 -I../../h -o ShowServer ShowServer.f ../../lib/libpsprolib_mac.a -framework IOKit -framework CoreFoundation
gfortran -m64 -I../../h -o ShowDetail ShowDetail.f ../../lib/libpsprolib_mac.a -framework IOKit -framework CoreFoundation

strip Floating Nodelocked PASfloating PASnodelocked ShowClient ShowServer ShowDetail
