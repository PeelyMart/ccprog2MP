#include "defs.h"
#include "utilities.c"
#include <unistd.h>
// Bubble sort for sorting BattlePets
void sortBattlePets(struct BattlePet pets[], int petCount) {
  int swapped;
  for (int i = 0; i < petCount - 1; i++) {
      swapped = 0;
      for (int j = 0; j < petCount - i - 1; j++) {
          // Sorting conditions
          if (pets[j].match_count < pets[j + 1].match_count || 
             (pets[j].match_count == pets[j + 1].match_count && strcmp(pets[j].name, pets[j + 1].name) > 0)) {
              
              // Swap BattlePets
              struct BattlePet temp = pets[j];
              pets[j] = pets[j + 1];
              pets[j + 1] = temp;
              
              swapped = 1;
          }
      }
      if (!swapped) break;  // Optimization: Stop if no swaps occurred
  }
}

// Function to display top 5 BattlePets
void displayTopBattlePets(struct BattlePet pets[], int petCount) {
  // Sort using bubble sort
  sortBattlePets(pets, petCount);

  printf("Top 5 BattlePets:\n");
  int top = (petCount < 5) ? petCount : 5;
  for (int i = 0; i < top; i++) {
      printf("%d. %s - Matches: %d\n", i + 1, pets[i].name, pets[i].match_count);
  }
}




// Bubble sort for sorting players
void sortPlayers(struct PlayerInfo p[], int playerCount) {
  int swapped;
  for (int i = 0; i < playerCount - 1; i++) {
      swapped = 0;
      for (int j = 0; j < playerCount - i - 1; j++) {
          // Sorting conditions
          if (p[j].win < p[j + 1].win || 
             (p[j].win == p[j + 1].win && p[j].loss > p[j + 1].loss) ||
             (p[j].win == p[j + 1].win && p[j].loss == p[j + 1].loss && p[j].draw > p[j + 1].draw) ||
             (p[j].win == p[j + 1].win && p[j].loss == p[j + 1].loss && p[j].draw == p[j + 1].draw && strcmp(p[j].name, p[j + 1].name) > 0)) {
              
              // Swap players
              struct PlayerInfo temp = p[j];
              p[j] = p[j + 1];
              p[j + 1] = temp;
              
              swapped = 1;
          }
      }
      if (!swapped) break;  // Optimization: Stop if no swaps occurred
  }
}

// Function to display top 5 players
void displayTopPlayers(struct PlayerInfo p[], int playerCount) {
  // Sort using bubble sort
  sortPlayers(p, playerCount);

  printf("Top 5 Players:\n");
  int top = (playerCount < 5) ? playerCount : 5;
  for (int i = 0; i < top; i++) {
      printf("%d. %s - Wins: %d, Losses: %d, Draws: %d\n", 
             i + 1, p[i].name, p[i].win, p[i].loss, p[i].draw);
  }
}

void viewStatistics(void){
  struct PlayerInfo players[MAX_PLAYERS];
  struct BattlePet pets[MAX_PETS];
  for(int i = 0; i < MAX_PLAYERS; i++){
    strcpy(players[i].name, "EMPTY-SLOT");
    players[i].win = 0;
    players[i].loss = 0;
    players[i]. draw =0;
  }
  for(int i = 0; i < MAX_PETS; i++){
    strcpy(pets[i].name, "EMPTY-SLOT");
  }
  loadBattlePetsFromFile(pets);
  loadPlayerFromFile(players);
  int petCount = getLastPet(pets);
  int playercount = getLastPlayer(players);
  displayTopPlayers(players, playercount);
  printf("\n");
  displayTopBattlePets(pets, petCount);
  fflush(stdout);
  sleep(10);
}


/* Returns the index of the chosen player
 * @param players - set of all players
*/
int rosterCreation(struct PlayerInfo players[])
{
  struct PlayerInfo chosen;
  int chosenIndex;
  for(int i = 0; i < MAX_PLAYERS; i++){
    strcpy(players[i].name, "EMPTY-SLOT");
  }
  loadPlayerFromFile(players);
  chosen = playerView(players, &chosenIndex, 500);
  printf("You have selected %s", chosen.name);
  return chosenIndex;
  fflush(stdout);
}
/* Reaads the file that has the data for how many matches has already occured
*/
int readMatchCount(void)
{
  FILE *file;
  int number;
  file = fopen("matchTracker.txt", "r");
  if (file == NULL) {
    return -999;  // Return 1 if the file cannot be opened
    }

  // Read the integer from the file
  if (fscanf(file, "%d", &number) != 1) {
    fclose(file);
    return -500;  // Return 2 if the integer couldn't be read
  }
  // Close the file
  fclose(file);
  return number;  // Return the integer read from the file
}
/*  Prints the board in the specific board pattern
 *  @param board is the board data 
*/
void printBoard(int board[][3])
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %d ", board[i][j]);
            if (j < 2) {
                printf("|");
            }
        }
        printf("\n");
        if (i < 2) {
            printf("---+---+---\n");
        }
    }
}

/* Makes you pick whether to create a roster or load a previously created roster
 * @param *d - set of all pets
 * @param *roster set of the indexes of the players roster
*/
void rosterScreen(struct BattlePet d[], int roster[], int player, char name[])
{
  int nChoice = 1;
  int whileLoop = 1;
  while(whileLoop){
  printf("Player %d\n", player);
  printf("[1] - Create Roster\n");
  printf("[2] - Load Roster\n");
  scanf("%d", &nChoice);
  switch(nChoice){
    case 1:
      rosterSelect(d, roster);
      whileLoop = 0;
      break;
    case 2:
      fflush(stdout);
      whileLoop = loadRoster(name, roster, d);
      fflush(stdout);
      sleep(2);
    default:
      break;
  }
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
struct PlayerInfo playerView(struct PlayerInfo p[], int* saveindex, int compare)
{
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
        } 
        else if(compare == 500){
            printf("Select What player to save this into");
          
        }
        else {
            printf("PLAYER TWO\n");
        }
        printf("Players: \n");
        for (int i = 0; i < PAGE_SIZE; i++) {
            if (index + i < MAX_PLAYERS && p[index + i].name[0] != '\0') {
                printf("%d]\t\t%-30s\t\t\n", i + 1, p[index + i].name);
            }
        }
        printf("Page: %d\n", page);
        printf("Enter: \n [a] - add player [n] - Next page [p] - Previous page [q] to Quit [s] select mode\n");
        scanf(" %c", &choice);  // Space before %c to clear buffer

        // Clear the input buffer to avoid issues with leftover characters
        while (getchar() != '\n');  // This will discard any remaining characters in the input buffer

        if (choice == 'n' && index + PAGE_SIZE < MAX_PLAYERS) {
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
void battleMain(struct BattlePet d[], struct PlayerInfo p[])
{
  int type; //type of win
  int winner; //winner 1 - p1, 2-p2, 0 - draw
  int matchCount = readMatchCount();
  matchCount++;
  saveMatchCount(matchCount);
  struct PlayerInfo one;
  int rosterOne[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1,}; //the indexes of the pets of the player
  int rosterOneElements[9]; //the elemets of the roster in integers of playerv
  int oneindex; //the index of the player
  struct PlayerInfo two;
  int rosterTwo[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1,};
  int rosterTwoElements[9];
  int twoindex;
  int board[3][3];
  int count = 0;
  one = playerView(p, &oneindex, 9999);
  two = playerView(p, &twoindex, oneindex);
  rosterScreen(d, rosterOne, 1, one.name);
  rosterScreen(d, rosterTwo, 2, two.name);
  for(int i = 0; i < 9; i++){
    rosterOneElements[i] = elementToInteger(d[rosterOne[i]].element);
    d[rosterOne[i]].match_count++;
  }
  for(int i = 0; i < 9; i++){
    rosterTwoElements[i] = elementToInteger(d[rosterTwo[i]].element);
    d[rosterTwo[i]].match_count++;
  }
  clearScreen();
  //printing screen//
  printf("%s (Player One) vs. %s (Player Two) Match: %d\n", p[oneindex].name, p[twoindex].name, matchCount);
  printf("\n\n");
  printf("BattlePets Fight!\n");
  for(int x = 0; x < 3; x++){
    for(int y = 0; y < 3; y++){
      printf("\t[%d][%d] %s vs %s\n", x, y, d[rosterOne[count]].name, d[rosterTwo[count]].name);
      count++;
    }
  }
  boardLogic(board, rosterOneElements, rosterTwoElements);
  printf("MATCH RESULTS\n");
  printBoard(board);
  fflush(stdout);
  winner = winCheck(board, &type);
  if(winner != 0){
    printf("Winner: ");
    switch(winner){
      case 1:
        printf("%s\n", p[oneindex].name);
        p[oneindex].win++;
        p[twoindex].loss++;
        break;
      case 2:
        printf("%s\n", p[twoindex].name);
        p[twoindex].win++;
        p[oneindex].loss++;
        break;
      default:
        printf("Peely");
        break;
    }
    switch(type){
      case 1: 
        printf("Lucky Win");
        break;
      case 2:
        printf("Majority Win");
        break;
      default:
        break;
    }
  }
  else{
    printf("DRAW\n");
    p[oneindex].draw++;
    p[twoindex].draw++;
  }
  saveMatchResults(matchCount, p, d, rosterOne, rosterTwo, oneindex, twoindex, board, winner, type);
  fflush(stdout);
  savePlayer(p);
  savePet(d);
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
/* Unlocks the edit mode of the pet, user is able to choose what part of the pet is to edit
 * @param d is the arrays of battlepets
 * @param index is the index of the specific pet to edit
*/
void edit(struct BattlePet d[], int index)
{
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
/* Initiatest the battle process, loads what ever file is needed
*/
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
  loadState = loadPlayerFromFile(player);
  
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
  char choice;//character choice
  int page = 1; //pages display
  int roster[9]; //FOR ROSTER CREATION
  char name[MAX_USER_CHAR]; //FOR ROSTER CREATION
  struct PlayerInfo players[MAX_PLAYERS]; //FOR ROSTER CREATION:
  int playerIndex;
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
    printf("Enter: \n [r] - rosterCreation [a] - add pet \n [n] - Next page \n [p] - Previous page\n [q] to Quit \n [s] for info and edit options: ");
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
      else if(choice == 'r'){
          playerIndex = rosterCreation(players);
          rosterSelect(pets, roster);
          strcpy(name, players[playerIndex].name);
          saveRoster(roster, name, pets);

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
int displayMainMenu(void)
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
      case 3:
        viewStatistics();
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





