#include "functions.c"
#include <stdio.h>


void main(){
  int mainFlag = 1;//to keep loop going
  int mainChoice;
  while(mainFlag){
    displayMainMenu();
    scanf("%d", &mainChoice);

    switch(mainChoice){
      case 1: //battle case
        printf("battle selected\n");
        break;
      case 2: //ComPetDium
        printf("compet selected\n");
        break;
      case 3://view stats
        printf("stats selected\n");
        break;
      case 0: //exit
        mainFlag = 0;
        break;
      default:
        printf("Invalid Input Try again\n");
    }

  }

}
