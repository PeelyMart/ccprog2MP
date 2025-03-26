#include "defs.h"
#include "utilities.c"
#include <unistd.h>




void rosterScreen(struct BattlePet d[], int roster[], int player){
  int nChoice;
  printf("Player %d\n", player);
  printf("[1] - Create Roster\n");
  printf("[2] - Load Roster\n");
  switch(nChoice){
    case 1:
      rosterSelect(d, roster);
      break;
    case 2:
    default:
  }
}


int uniqueCheck(struct PlayerInfo p[], char key[]){
  printf("Entering Unique check");
  int i = 0;
  while(strcmp(p[i].name, "EMPTY-SLOT") != 0){
    if(strcmp(p[i].name, key) == 0){
      return 1;
    }
    i++;
  }
  return 0;
}


/* This funtion adds a new player and records the username
 *  
 *
 *
*/
void addPlayer(struct PlayerInfo p[], int addIndex)
{ 
  int loop = 1;
  char inputBuffer[500];
  while(loop){
    printf("Enter user name -> ");
    scanf("%s", inputBuffer);
    if(uniqueCheck(p, inputBuffer) == 1){
      printf("your username must be unique\n");
    }
    else if(strlen(inputBuffer) <= 36){
      strcpy(p[addIndex].name, inputBuffer);
      p[addIndex].win = 0;
      p[addIndex].loss= 0;
      p[addIndex].draw= 0;
      loop = 0;
    }
    else{
      printf("too long username");
    }
    
  }
  savePlayer(p);
}


/* This displays the players and returns the selected player
 * @param *p is the arrays of all players 
 * @param *saveindex is where the index of the player is saved to
 * @param *compare the index of the first player, to check for similarity; during player 1, it is set to a high number
 * @return the structure of the selected player
 *
*/
struct PlayerInfo playerView(struct PlayerInfo p[], int* saveindex, int compare) {
    int exitCondition = 1;
    int page = 1;
    int index = 0;
    int nChoice = 1;
    int loop = 1;
    
    char choice;
    while (exitCondition) {
        clearScreen();
        if (compare == 9999) {
            printf("PLAYER ONE\n");
        } else {
            printf("PLAYER TWO\n");
        }
        printf("Players: \n");
        for (int i = 0; i < PAGE_SIZE; i++) {
            if (index + i < MAX_PETS && p[index + i].name[0] != '\0') {
                printf("%d]\t\t%-30s\t\t\n", i + 1, p[index + i].name);
            }
        }
        printf("Page: %d\n", page);
        printf("Enter: \n [a] - add player [n] - Next page [p] - Previous page [q] to Quit [s] select mode\n");
        scanf(" %c", &choice);  // Space before %c to clear buffer

        // Clear the input buffer to avoid issues with leftover characters
        while (getchar() != '\n');  // This will discard any remaining characters in the input buffer

        if (choice == 'n' && index + PAGE_SIZE < MAX_PETS) {
            index += PAGE_SIZE;  // Move to next page
            page++;
        } else if (choice == 'p' && index - PAGE_SIZE >= 0) {
            index -= PAGE_SIZE;  // Move to previous page
            page--;
        } else if (choice == 's') {
            while (loop) {
                printf("From [1] - [4] select the player: ");
                scanf(" %d", &nChoice);

                // Clear the input buffer again
                while (getchar() != '\n'); // Clear the input buffer to avoid leftover characters

                if (nChoice >= 1 && nChoice <= 4) {
                    if (index + (nChoice - 1) != compare) {
                        *saveindex = index + (nChoice - 1);
                        loop = 0; // Exit the loop after a valid selection
                        return p[index + (nChoice - 1)];
                    } else {
                        printf("You cannot pick the same player\n");
                    }
                } else {
                    printf("Invalid input or you cannot select the same player\n");
                }
            savePlayer(p);
            }
        } else if (choice == 'a') {
            int addIndex = getLastPlayer(p);
            addPlayer(p, addIndex);
        }
        else if (choice == 'q') {
            exitCondition = 0;  // Set exit condition to 0 and exit the loop
        } 
    }
    struct PlayerInfo empty = {0};  // Empty player to return in case of failure
    return empty;
}




/* Governs the flow the the Battle game proper
 * @param d is the arrays of all pets
 * @param p is the array of all players 
*/
void battleMain(struct BattlePet d[], struct PlayerInfo p[]){
  struct PlayerInfo one;
  int rosterOne[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1,};
  int oneindex;
  struct PlayerInfo two;
  int rosterTwo[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1,};
  int twoindex;
  int count = 0;
  one = playerView(p, &oneindex, 9999);
  two = playerView(p, &twoindex, oneindex);
  rosterScreen(d, rosterOne, 1);
  rosterScreen(d, rosterTwo, 2);
  for(int x = 0; x < 3; x++){
    for(int y = 0; y < 3; y++){
      printf("[%d][%d] %s vs %s\n", x, y, d[rosterOne[count]].name, d[rosterTwo[count]].name);
      fflush(stdout);
      count++;
    }
  }
  sleep(10);

  
}
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

void battleDriver(){
  int loadState;
  struct BattlePet pets[MAX_PETS];
  struct PlayerInfo player[MAX_PLAYERS];
  for(int i = 0; i < MAX_PETS; i++){
    strcpy(pets[i].name, "EMPTY-SLOT");
  }
  for(int i = 0; i < MAX_PLAYERS; i++){
    strcpy(player[i].name, "EMPTY-SLOT");
  }
  loadState = loadBattlePetsFromFile(pets); //loading pet array
  if(loadState == 0){ //Makes sure it is loaded correctly first before loading players
    loadState = loadPlayerFromFile(player);
    if(loadState == 0){
      battleMain(pets, player);

    }
    else{
      printf("player load error");
    }
  }
  else{
    printf("pet load error");
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
          scanf(" %d", &nChoice);
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





