#!/bin/bash
gcc -m32 -Wall -o Floating Floating.c ../../lib/libpsprolib_lin.a -lm -ldl
gcc -m32 -Wall -o Nodelocked Nodelocked.c ../../lib/libpsprolib_lin.a -lm -ldl
gcc -m32 -Wall -o PASfloating PASfloating.c ../../lib/libpsprolib_lin.a -lm -ldl
gcc -m32 -Wall -o PASnodelocked PASnodelocked.c ../../lib/libpsprolib_lin.a -lm -ldl
gcc -m32 -Wall -o ShowClient ShowClient.c ../../lib/libpsprolib_lin.a -lm -ldl
gcc -m32 -Wall -o ShowServer ShowServer.c ../../lib/libpsprolib_lin.a -lm -ldl
gcc -m32 -Wall -o ShowDetail ShowDetail.c ../../lib/libpsprolib_lin.a -lm -ldl
gcc -m32 -Wall -o Vendorid Vendorid.c ../../lib/libpsprolib_lin.a -lm -ldl
gcc -m32 -Wall -o sgarc4 sgarc4.c ../../lib/libpsprolib_lin.a -lm -ldl

strip Floating Nodelocked PASfloating PASnodelocked ShowClient ShowServer ShowDetail Vendorid sgarc4
