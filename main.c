#include <stdio.h>
#include "functions.c"
int main(){
  int loop = 1;
  while(loop){
    clearScreen();
    loop = displayMainMenu();   
  }
  return 0;
}

