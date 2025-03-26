#include "defs.h"
#include <unistd.h>

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

/*
 *
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
  save(d);
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
    return 0;
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



