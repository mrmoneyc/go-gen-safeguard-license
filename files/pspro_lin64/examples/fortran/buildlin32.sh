#!/bin/bash
gfortran -m32 -I ../../h -o Floating Floating.f ../../lib/libpsprolib_lin.a -lm -ldl
gfortran -m32 -I ../../h -o Nodelocked Nodelocked.f ../../lib/libpsprolib_lin.a  -lm -ldl
gfortran -m32 -I ../../h -o PASfloating PASfloating.f ../../lib/libpsprolib_lin.a  -lm -ldl
gfortran -m32 -I ../../h -o PASnodelocked PASnodelocked.f ../../lib/libpsprolib_lin.a -lm -ldl
gfortran -m32 -I ../../h -o ShowClient ShowClient.f ../../lib/libpsprolib_lin.a  -lm -ldl
gfortran -m32 -I ../../h -o ShowServer ShowServer.f ../../lib/libpsprolib_lin.a  -lm -ldl
gfortran -m32 -I ../../h -o ShowDetail ShowDetail.f ../../lib/libpsprolib_lin.a  -lm -ldl

strip Floating Nodelocked PASfloating PASnodelocked ShowClient ShowServer ShowDetail
