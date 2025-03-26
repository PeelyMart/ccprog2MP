#include "defs.h"
#include "utilities.c"
#include <unistd.h>



/* Displays all the elements and their respective numerical equivalent
 */
void elementDisplay(){
  printf("[0] Fire \n");
  printf("[1] Water\n");
  printf("[2] Grass\n");
  printf("[3] Earth\n");
  printf("[4] Air\n");
  printf("[5] Electric\n");
  printf("[6] Ice\n");
  printf("[7] Metal\n");
}


/* This function displays pet information
 * @param d[] is the battlepet to be displayed
*/
void displayPet(struct BattlePet d)
{
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Name:\t\t\t%-30s\n", d.name);
    printf("Element:\t\t%-10s\n", d.element);
    printf("Matches:\t\t%d\n", d.match_count);
    printf("%s\n", d.description);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void edit(struct BattlePet d[], int index){
  int loop = 1;
  int nChoice;
  int saveState = 0;
  while(loop){
    clearScreen();
    printf("\t\t\tEDIT MODE:");
    displayPet(d[index]);
    printf("What do you want to edit?: \n[0] - Go back \n[1] - Element \n[2] - Description\n[3] - Name" );
    scanf("%d", &nChoice);
    switch(nChoice){
      case 0: 
        loop = 0;
        break;
      case 1:
        elementEdit(d, index);
        break;
      case 2:
        descriptionEdit(d, index);
        break;
      case 3: 
        nameEdit(d, index);
        break; 
      default:
        printf("That is not a valid input");  
    }
 
  }
}

/*  
 *  This function is in charge of the CompetDium section, it is incharge of initializing 
 *  and loading data into the pet file and calling its view function
 */
void ComPetDiumDriver()
{
  int loadState;
  struct BattlePet pets[MAX_PETS];
  for(int i = 0; i < MAX_PETS; i++){
    strcpy(pets[i].name, "EMPTY-SLOT");
    strcpy(pets[i].element, "\0");
  }
  //initializing pet array
  loadState = loadBattlePetsFromFile(pets); //loading pet array
  if(loadState == 0){ //Makes sure it is loaded correctly first before opening view
    View(pets);
  }
  else{
    printf("Loading error");
  }
}

/* 
 * This function displays the full information of the pet 
 * and offers more options to do with such pet 
 * @param d is the array of all pets
 * @param index is the specific index that is being viewed
*/
void fullInfo(struct BattlePet d[], int index)
{
    int nChoice = 1;
    int loop = 1;
    int deleteState;
  while(loop){
    displayPet(d[index]);
   printf("Press: \n[0] - Go back \n[1] - Edit \n[2] - Delete \n" );
    scanf("%d", &nChoice);
    if(nChoice >= 0 && nChoice <= 2){
      switch(nChoice){
        case 0:
          clearScreen();
          printf("\nGoing Out");
          fflush(stdout); //this makes sure that it is printed out right away
          sleep(3);
          loop = 0;
          break;
        case 1:
          edit(d, index);
          break;
        case 2:
          deleteState = delete(d ,index);
          if(deleteState == 1){
            printf("\nsuccesfully delete battle pet");
            sleep(3);
          }
          else if(deleteState == 0){
            clearScreen();
            printf("\n User cancelled the deletion.");
            fflush(stdout);
            sleep(1);
          }
          else{
          }
          loop = 0;
          break;
        default:
            printf("Ivalid input");
            break;
        }
      }
    }
}


/* This function displays the pets name already, allows user to see more information by pressing 's'
 * in the s function, they can delete and view the file.
 */
void View(struct BattlePet pets[])
{
  int exitCondition = 1; //loop variable
  int index = 0; //page show
  char choice;
  int page = 1;
  while(exitCondition){
    clearScreen();
    printf("Amount of Pets: %d\n", getLastPet(pets));
    for(int i = 0; i < PAGE_SIZE; i++){
      if(index + i < 60){
        printf("%d]\t\t%-30s\t\t[%c]\n", i + 1, pets[index + i].name, pets[index + i].element[0]);
      }
    }
  
    printf("Page: %d", page);
    printf("\n");
    printf("Enter: \n [a] - add pet \n [n] - Next page \n [p] - Previous page\n [q] to Quit \n [s] for info and edit options: ");
    scanf(" %c", &choice);  // Space before %c to clear buffer
        if (choice == 'n' && index + PAGE_SIZE < MAX_PETS) {
            index += PAGE_SIZE;  // Move to next page
            page++;
        } else if (choice == 'p' && index - PAGE_SIZE >= 0) {
            index -= PAGE_SIZE;  // Move to previous page
            page--;
        } 
        else if (choice == 'q') {
            exitCondition = 0;  // Exit the loop
        }
        else if(choice == 'a'){
          addPet(pets);
        }
        else if(choice == 's'){
          int nChoice;
          int loop = 1; 
          while(loop){
          printf("From [1] - [4] select the pet that you wish to see the information for");
          printf("\nHere: ");
          scanf("%d", &nChoice);
          if(nChoice >=1 && nChoice <= 4){
          fullInfo(pets, index + (nChoice - 1));
          loop = 0;
        }
          else {
            printf("Invalid input\n");
          }
      }
    }
        else{
            printf("Invalid option or no more pages available!\n");
        }

  }
}


/* 
 * Basic Main Menu function 
 * @pre - while loop is handled in main
*/
int displayMainMenu()
{
  int mainChoice;
  printf("[1] Battle!\n");
  printf("[2] ComPetDium\n");
  printf("[3] View Statistics\n");
  printf("[0] Exit\n");
  scanf("%d", &mainChoice);

    switch(mainChoice){
      case 1: //battle case
        battleDriver();
        break;
      case 2://ComPetDium
        ComPetDiumDriver();
        break;
      case 3://view stats
        printf("stats selected\n");
        break;
      case 0: //exit
        return 0; //returns the value that terminates the loop 
        break;
      default:
        printf("Invalid Input Try again\n");
        return 1;  //keeps the loop going 
    }
}



