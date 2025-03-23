#include "defs.h"
#include <unistd.h> 

/* This function gets called everytime a change to the file is made, this write the current state 
 * of the pets array into a file called, backupPets.txt
 *
 * @returns 0 if back up saved correctly
 * @returns 1 if there was an error
 *
*/
int backupBattlePets(struct BattlePet pets[]){
  int j = 0 ;
  while(strcmp(pets[j].name, "EMPTY-SLOT") != 0){ //this returns a j, 
    j++;                                          //where j = to the last pet of the array     
  }
  FILE *file = fopen("../backupPets.txt", "w");
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
/* If there are any changes done to the array, this function will be called for the changes to reflect on 
 * the text file right away
 * 
 * @param pets - an array of the pets
 * @return 0 if succesfully saved
 * @return 1 if there was a failure in saving
 *
*/
int save(struct BattlePet pets[]){
  int j = 0 ;
  while(strcmp(pets[j].name, "EMPTY-SLOT") != 0){
    j++;
  }
  FILE *file = fopen("../competdium.txt", "w");
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
      save(d);
    }
    else{
      printf("\nSorry, there was an error in saving a backup\n changes cannot be applied\n");
      return -1; 
    }

  }
  else{
    printf("Deletion cancelled");
    return 0;
  }
} 


void  clearScreen(){
  printf("\033[H\033[J"); //ascii escape sequence that clears the screen
}
void displayPet(struct BattlePet d[], int index)
{
    int nChoice = 1;
    int loop = 1;
    int deleteState;
  while(loop){
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Name:\t\t\t%-30s\n", d[index].name);
    printf("Element:\t\t%-10s\n", d[index].element);
    printf("Matches:\t\t%d\n", d[index].match_count);
    printf("%s\n", d[index].description);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Press: \n[0] - Go back \n[1] - Edit \n[2] - Delete\n" );
    scanf("%d", &nChoice);
    if(nChoice >= 0 && nChoice <= 2){
      switch(nChoice){
        case 0:
          loop = 0;
          break;
        case 1:
          //edit();
          break;
        case 2:
          deleteState = delete(d ,index);
          if(deleteState == 1){
            printf("\nsuccesfully delete battle pet");
            sleep(3);
          }
          else if(deleteState == 0){
            sleep(3);
          }
          else{
          }
          loop = 0;
          break;
        default:
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
    printf("Pet Names: \n");
    for(int i = 0; i < PAGE_SIZE; i++){
      if(index + i < 60){
        printf("%d]\t\t%-30s\t\t[%c]\n", i + 1, pets[index + i].name, pets[index + i].element[0]);
      }
    }
  
    printf("Page: %d", page);
    printf("\n");
    printf("Enter 'n' for Next page, 'p' for Previous page, 'q' to Quit, 's' for info and edit options: ");
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
        else if(choice == 's'){
          int nChoice;
          int loop = 1; 
          printf("From [1] - [4] select the pet that you wish to see the information for");
          while(loop){
          scanf("%d", &nChoice);
          if(nChoice >=1 && nChoice <= 4){
          displayPet(pets, index + (nChoice - 1));
          loop = 0;
        }
          else {
            printf("Invalid input");
          }
      }
    }
        else{
            printf("Invalid option or no more pages available!\n");
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
        printf("battle selected\n");
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
    FILE *file = fopen("../competdium.txt", "r"); //our file pointer variable carrying the address of our pet file, in read mode 
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
