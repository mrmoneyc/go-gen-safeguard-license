#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../h/psprolib.h"

int main(int nargs,char *args[])

{

  char direction[32],key[128],string[256],result[512];
  int  whichway;

  if (nargs < 4) {
    fprintf(stdout,"Usage: sgarc4 <encrypt | decrypt> <key> <string>\n");
    exit(1);
  }

  strcpy(direction,args[1]);
  strcpy(key,args[2]);
  strcpy(string,args[3]);

  whichway = -1;
  if (direction[0] == 'e') whichway = 1;
  if (direction[0] == 'd') whichway = 0;
  if (whichway == -1) {
    fprintf(stdout,"Usage: sgarc4 <encrypt | decrypt> <key> <string>\n");
    exit(1);
  }

  // encrypt or decrypt the string
  sgArc4(whichway,key,string,result);

  fprintf(stdout,"%s\n",result);

  exit(0);
}

