#include "defs.h"
#include <unistd.h>
#include <string.h>



/* Checks the roster indexes if it is alredy picked
 * @param n - the array to be checked against
 * @return 1 if it is already picked
 * @return 0 if it is not picked
 */
int rosterSelectChecker(int n[], int key){
  for(int i = 0; i < 9; i++){
    if(key == n[i]){
      return 1;
    }
  }
  return 0;
}


/* This is the roster selection screen where you can pick your roster
 * @param d is the array of all the pets in the competdium
 * @param r is the roster array of each player
 */

void rosterSelect(struct BattlePet d[], int roster[]){
  int alreadyPicked[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1}; //stores the index of "already picked pets"
  int petChoice;
  int exitCondition = 1;
  int index = 0;
  int page = 1;
  char choice;
  int count = 0;
  while(exitCondition){
    clearScreen();
    printf("Amount of Pets: %d\n", getLastPet(d));
    for(int i = 0; i < PAGE_SIZE; i++){
      if(index + i < 60){
        printf("%d]\t\t%-30s\t\t[%c]\n", i + 1, d[index + i].name, d[index + i].element[0]);
      }
    }
  
    printf("Page: %d \t", page);
    printf("Count:%d", count );
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
        else if(choice == 'a')
        {
          if(count == 9){
            printf("your roster is already full you have to press c");
            fflush(stdout);
            sleep(2);
          }
          else{
            int loop = 1;
            while(loop){
              printf("Pick from [1] - [4] to add\n");
              scanf("%d", &petChoice);
              int adjusted = index + (petChoice - 1);
              if(rosterSelectChecker(alreadyPicked, adjusted) == 1){
              printf("It is already picked");
              fflush(stdout);
              }
              else{
              alreadyPicked[count] = adjusted;
              roster[count] = adjusted;
              count++;
              loop = 0;
            }
            }
          }
        }
        else if(choice == 'c'){
          for(int i = 0; i < 9; i++){
            printf("%s\n", d[roster[i]].name);
            fflush(stdout);
          }
          sleep(5);
          exitCondition = 0;
          }
          

  }

}




int savePlayer(struct PlayerInfo p[])
{
  int j = getLastPlayer(p);
  FILE *file = fopen("players.txt", "w");
  if (file == NULL){
    printf("Error opening file\n");
    return 1;
  }
  else{
    for(int i = 0; i < j; i++){
      fprintf(file, "%s\n", p[i].name);
      fprintf(file, "%d\n", p[i].win);
      fprintf(file, "%d\n", p[i].loss);
      fprintf(file, "%d\n", p[i].draw);
      fprintf(file, "\n");
    }
    printf("Back up completed");
    return 0;
  }
  fclose(file);
}


/*
 *
*/
void addPet(struct BattlePet d[])
{
  int index = getLastPet(d);
  int loop = 1; 
  int nChoice;
  char inputBuffer[500]; //buffer makes sure that we can check it before officially copying it over to the array.
  BattlePetName nameBuffer;
  BPDescription descriptionBuffer;
  int elementChoice;
  while(loop){
  printf("Name Here: \n");
  scanf("%s", inputBuffer);
  if(strlen(inputBuffer) > 30){
      printf("\n This is OVER the limit please try again");
    }
  else if(strlen(inputBuffer) <= 30){
    loop = 0;
  }
  }
  strcpy(nameBuffer, inputBuffer);
  loop = 1;
  while(loop){
    printf("Description Here: \n");
    scanf("%s", inputBuffer);
    if(strlen(inputBuffer) > 240){
        printf("\n This is OVER the limit please try again");
      }
    else if(strlen(inputBuffer) <= 240){
      loop = 0;
    }
    }
    strcpy(descriptionBuffer, inputBuffer);
    loop = 1; 
    while(loop){
      elementDisplay();
      printf("Element Here: \n");
      scanf(" %d", &elementChoice);
      loop = integerToElement(d[index].element, elementChoice);
      }
    strcpy(d[index].name, nameBuffer);
    strcpy(d[index].description, descriptionBuffer);
    d[index].match_count = 0;
    savePet(d);
    printf("write successful");
}

/* Finds the index of the last player of the array
 * @param *d contains all the players in the game
 * @returns the last index of the player 
*/

int getLastPlayer(struct PlayerInfo d[]){
  int j = 0;
  while(strcmp(d[j].name, "EMPTY-SLOT") != 0){
    if(j == 50){
      return 50;
    }
    j++;
   
  }
  return j;
}

/* Finds the index of the last pet of the array
 * @param *d contains all the pets in the game
 * @returns the last index of the pet
*/
int getLastPet(struct BattlePet d[]){
  int j = 0;
  while(strcmp(d[j].name, "EMPTY-SLOT") != 0){
    if(j == 60){
      return 60;
    }
    j++;
   
  }
  return j;
}

/* This function edits the name of the specified battle pet
 * @param *d this contains all the pets in the game
 * @param index this specifies what pet in the array
*/
void nameEdit(struct BattlePet d[], int index){
  displayPet(d[index]);
  int loop1 = 1; 
  int nChoice;
  char inputBuffer[500]; //buffer makes sure that we can check it before officially copying it over to the array.
  while(loop1){
  printf("This is your current name: \n%s\n", d[index].name);
  printf("YOUR NEW NAME MUST NOT BE LONGER THAN 30 characters and not contain any NEWLINE CHARACTERS: \n");
  printf("Type Here: \n");
  scanf("%s", inputBuffer);
  if(strlen(inputBuffer) > 30){
      printf("\n This is OVER the limit please try again");
    }
  else if(strlen(inputBuffer) <= 30){
            backupBattlePets(d);
            strcpy(d[index].name, inputBuffer);
            savePet(d);
            loop1 = 0;
            printf("save completed\n");
        }
  else{
      printf("Error");
  }
  }
}

/* This function edits the description of the specified battle pet
 * @param *d this contains all the pets in the game
 * @param index this specifies what pet in the array
*/
void descriptionEdit(struct BattlePet d[], int index){
  displayPet(d[index]);
  int loop1 = 1;
  int loop2 = 1; 
  int nChoice;
  char inputBuffer[500]; //buffer makes sure that we can check it before officially copying it over to the array.
  while(loop1){
  printf("This is your current description: \n%s\n", d[index].description);
  printf("YOUR NEW DESCRIPTION MUST NOT BE LONGER THAN 240 characters and not contain any NEWLINE CHARACTERS: \n");
  printf("Type Here: \n");
  scanf(" %[^\n]", inputBuffer);  // The space before % ensures any leading whitespace is ignored
  if(strlen(inputBuffer) > 240){
      printf("\n This is OVER the limit please try again");
    }
  else if(strlen(inputBuffer) <= 240){
            backupBattlePets(d);
            strcpy(d[index].description, inputBuffer);
            savePet(d);
            loop1 = 0;
            printf("save completed\n");
        }
  else{
      printf("Error");
  }
  }
}

/* 
 * This function will intake an integer oputput, which will then give an output of what element it is in
 * @pre output parameter fit all possible element string lengths
 * @param output writes the element in this parameter
 * @param input accepts integer and refers to table of equivalent elements to write the appropriate output
 * @return 0 if write was successful
 * @return 1 if write was unsuccessful
*/
int integerToElement(char* output, int input)
{
  switch(input){
    case 0:
      strcpy(output, "Fire");
      return 0;
      break;
    case 1:
      strcpy(output, "Water");
      return 0;
      break;
    case 2:
      strcpy(output, "Grass");
      return 0;
      break;
    case 3:
      strcpy(output, "Earth");
      return 0;
      break;
    case 4:
      strcpy(output, "Air");
      return 0;
      break;
    case 5:
      strcpy(output, "Electric");
      return 0;
      break;
    case 6:
      strcpy(output, "Ice");
      return 0;
      break;
    case 7:
      strcpy(output, "Metal");
      return 0;
      break;
    default:
      printf("Input was invalid");
      return 1;
  }
}

/* This function edits the battlepets element. It accepts the input of the user, takes account of what the user
 * wants to change it to
 * @param *SSd is the struct array of all pets
 * @param index is the specific index of the pet that you want to change it to
 * @pre the pet is in the array, and the index is less that 50SS
 */
void elementEdit(struct BattlePet d[], int index){
  int loop = 1;
  int elementChange;
  displayPet(d[index]);
  printf("\n\n Your pet is currently a %s type\n", d[index].element);
  elementDisplay();
  while(loop){
    printf("What would you want to change it to? [0] - [7]\n");
    scanf("%d", &elementChange);
    backupBattlePets(d);
    loop = integerToElement(d[index].element, elementChange);   
  }
  printf("\nchange successful\n");
  fflush(stdout);
  sleep(1);
  clearScreen();
  printf("This is your new pet");
  displayPet(d[index]);
  sleep(2);
  savePet(d);
}

/*Prints an ASCII value that clears the screen
 */
void  clearScreen(){
  printf("\033[H\033[J"); //ascii escape sequence that clears the screen
}

/* If there are any changes done to the array, this function will be called for the changes to reflect on 
 * the text file right away
 * 
 * @param pets - an array of the pets
 * @return 0 if succesfully saved
 * @return 1 if there was a failure in saving
 *
*/
int savePet(struct BattlePet pets[])
{
  int j = getLastPet(pets);
  FILE *file = fopen("competdium.txt", "w");
  if (file == NULL){
    printf("Error opening file\n");
    return 1;
  }
  else{
    for(int i = 0; i < j; i++){
      fprintf(file, "%s\n", pets[i].name);
      fprintf(file, "%s\n", pets[i].element);
      fprintf(file, "%s\n", pets[i].description);
      fprintf(file, "%d\n", pets[i].match_count);
      fprintf(file, "\n");
    }
    printf("Back up completed");
    return 0;
  }
  fclose(file);
}

/* This function gets called everytime a change to the file is made, this write the current state 
 * of the pets array into a file called, backupPets.txt
 *
 * @returns 0 if back up saved correctly
 * @returns 1 if there was an error
 *
*/
int backupBattlePets(struct BattlePet pets[])
{
  int j = getLastPet(pets);
  FILE *file = fopen("backupPets.txt", "w");
  if (file == NULL){
    printf("Error opening file\n");
    return 1;
  }
  else{
    for(int i = 0; i < j; i++){
      fprintf(file, "%s\n", pets[i].name);
      fprintf(file, "%s\n", pets[i].element);
      fprintf(file, "%s\n", pets[i].description);
      fprintf(file, "%d\n", pets[i].match_count);
      fprintf(file, "\n");
    }
    printf("Back up completed");
    return 0;
  }
  fclose(file);
}

/* This program will shift the index of battlepets to the left 
 *  'i' = 'i + 1';
 *  before any changes are made, a backup of the previous roster will be made and saved to a file
 *  
 *  @param struct BattlePet d[] - The current set of battlePets
 *  @param index - the index of the battlepet that the user wishes to delete; 
 *  @return 1 - if deletion was successful 
 *  @return 0 - if user canceled
 *  @return -1 - if there was an error
*/
int delete(struct BattlePet d[], int index)
{
  int i;
  int nConfirm;
  int backupState = 0;
  clearScreen();
  printf("This will delete the battle pet for ALL USERS confirm?\n");
  printf("\t\t[0]Confirm\t\t[1]Exit\n");
  scanf("%d", &nConfirm);
  if(nConfirm == 0){
    backupState = backupBattlePets(d);
    if(backupState == 0){
      for(i = index; i < MAX_PETS-1; i++){
        d[i] = d[i+1];
      }
    }
    else{
      printf("\nSorry, there was an error in saving a backup\n changes cannot be applied\n");
      return -1; 
    }

  }
  else{
    return 0;
  }
}

int loadPlayerFromFile(struct PlayerInfo p[]){
   printf("\ninitating file....\n");
  sleep(1); //allows previous messages to be seen before clear screen operations
  clearScreen();
    FILE *file = fopen("players.txt", "r"); //our file pointer variable carrying the address of our pet file, in read mode 
    if (file == NULL) 
    {  //file opening error handling
        printf("Error opening file.\n"); 
        return 1;
    }
    else
    {
      int i = 0;
      printf("\nLoading file into program...\nfile succesfully opened");
      sleep(2);
      clearScreen();
      while (i < MAX_PLAYERS && fscanf(file, "%s", p[i].name) == 1) {
        fscanf(file, "%d", &p[i].win);    // Read the match count
        fscanf(file, "%d", &p[i].loss);    // Read the match count
        fscanf(file, "%d", &p[i].draw);    // Read the match count
        i++;
        }// Move to the next pet
    }
    fclose(file); // Close the file
    return 0;

}

/*
  * This function fills in the pets[] array with the saved data from the txt file containing all the pets information
  * @param pets[] - this the universal pet structure array
  * @return - No return value, but fills in the pet[] array using pointers and pointer arithmetic
  * @pre - it assumed that pets is initated with pet[maxarray], txt file is correctly formatted, txt file exists
*/
int loadBattlePetsFromFile(struct BattlePet pets[]) 
{
  printf("\ninitating file....\n");
  sleep(1); //allows previous messages to be seen before clear screen operations
  clearScreen();
    FILE *file = fopen("competdium.txt", "r"); //our file pointer variable carrying the address of our pet file, in read mode 
    if (file == NULL) 
    {  //file opening error handling
        printf("Error opening file.\n"); 
        return 1;
    }
    else
    {
      int i = 0;
      printf("\nLoading file into program...\nfile succesfully opened");
      sleep(2);
      clearScreen();
      while (i < MAX_PETS && fscanf(file, "%s", pets[i].name) == 1) {
        fscanf(file, " %s", pets[i].element);  // Space skips any leading whitespace/newlines
        fscanf(file, " %[^\n]", pets[i].description);  // This will read everything up to a newline
        fscanf(file, "%d", &pets[i].match_count);    // Read the match count
        i++;
        }// Move to the next pet
    }
    fclose(file); // Close the file
    return 0;
}



