#include "defs.h"
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



