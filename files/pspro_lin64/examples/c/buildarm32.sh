#!/bin/bash
gcc -Wall -o Floating Floating.c ../../lib/libpsprolib_lin.a -lm -ldl
gcc -Wall -o Nodelocked Nodelocked.c ../../lib/libpsprolib_lin.a -lm -ldl
gcc -Wall -o PASfloating PASfloating.c ../../lib/libpsprolib_lin.a -lm -ldl
gcc -Wall -o PASnodelocked PASnodelocked.c ../../lib/libpsprolib_lin.a -lm -ldl
gcc -Wall -o ShowClient ShowClient.c ../../lib/libpsprolib_lin.a -lm -ldl
gcc -Wall -o ShowServer ShowServer.c ../../lib/libpsprolib_lin.a -lm -ldl
gcc -Wall -o ShowDetail ShowDetail.c ../../lib/libpsprolib_lin.a -lm -ldl
gcc -Wall -o Vendorid Vendorid.c ../../lib/libpsprolib_lin.a -lm -ldl
gcc -Wall -o sgarc4 sgarc4.c ../../lib/libpsprolib_lin.a -lm -ldl

strip Floating Nodelocked PASfloating PASnodelocked ShowClient ShowServer ShowDetail Vendorid sgarc4
