#include <string.h>
#include <stdio.h>
#define MAX_PLAYERS 50 //The program is designed only to have only up to  50 players 
#define MAX_USER_CHAR 37 //player usernames can handle up to 36 characters
#define MAX_PET_NAME 31 //maxmium character for the battle pet name
#define MAX_DESCRIPTION 241 //maximum description for battle pet, should not have newline;
#define MAX_PETS 60 //maximum pets in pet array
#define PAGE_SIZE 4 //shows 4 names max per page used in view function for competdium

typedef struct BattlePet{
  char name[31];
  char element[15];
  char description[241];
  int match_count;
};

int loadBattlePetsFromFile(struct BattlePet pets[]) 
{
  printf("\ninitating file....\n");
    FILE *file = fopen("../competdium.txt", "r"); //our file pointer variable carrying the address of our pet file, in read mode 
    
    if (file == NULL) {  //file opening error handling
        printf("Error opening file.\n"); 
        return 1;
    }
    else{
      int i = 0;
      printf("\nLoading file into program...\nfile succesfully opened");
      while (i < MAX_PETS && fscanf(file, "%s", pets[i].name) == 1) {
        // Read the element (affinity)
        fscanf(file, " %s", pets[i].element);  // Space skips any leading whitespace/newlines
        
        // Read the description (up to the newline character)
        fscanf(file, " %[^\n]", pets[i].description);  // This will read everything up to a newline
        fscanf(file, "%d", &pets[i].match_count);    // Read the match count
        
        i++;
        }// Move to the next pet
    }
    fclose(file); // Close the file
    return 0;
}

int backupBattlePets(struct BattlePet pets[]){
  int j = 0 ;
  while(strcmp(pets[j].name, "EMPTY-SLOT") != 0){
    j++;
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
  }
  fclose(file);
}

int testDeleteSave(struct BattlePet pets[]){
  int j = 0 ;
  while(strcmp(pets[j].name, "EMPTY-SLOT") != 0){
    j++;
  }
  FILE *file = fopen("../testDelete.txt", "w");
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
  }
  fclose(file);
}

int delete(struct BattlePet d[], int index){
  int i;
  int nConfirm;
  printf("This will delete the battle pet for ALL USERS confirm?\n");
  printf("\t\t[0]Confirm\t\t[1]Exit\n");
  scanf("%d", &nConfirm);
  if(nConfirm == 0){
    
    for(i = index; i < MAX_PETS-1; i++){
      d[i] = d[i+1];
    }
  }
  int test = testDeleteSave(d);

  
}





int main(void){
  int loadStatus;
  struct BattlePet d[MAX_PETS];
  for(int i = 0; i < MAX_PETS; i++){
    strcpy(d[i].name, "EMPTY-SLOT");
    strcpy(d[i].element, "\0");

  }
  loadStatus = loadBattlePetsFromFile(d);
  for(int i = 0; i < MAX_PETS; i++){
    printf("\n%s\n", d[i].name);
  }
  int backupStatus = backupBattlePets(d);
  int test = delete(d, 0);
}
