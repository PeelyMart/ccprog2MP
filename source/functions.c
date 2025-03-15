#include "defs.h"

void  clearScreen(){
  printf("\033[H\033[J");
}


void displayPet(struct BattlePet d){
    char cChoice;
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Name:\t\t%s\n", d.name);
    printf("Element:\t\t%s\n", d.element);
    printf("Matches:\t\t%d\n", d.match_count);
    printf("%s\n", d.description);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Press any letter to go back to go back");
    scanf("%d", cChoice);
}


void View(struct BattlePet pets[]){
  int exitCondition = 1; //loop variable
  int index = 0; //page show
  char choice;
  int page = 1;
  while(exitCondition){
    clearScreen();
    printf("Pet Names: \n");
    for(int i = 0; i < PAGE_SIZE; i++){
      if(index + i < 60){
        printf("%d]\t\t%s\t\t[%c]\n", i + 1, pets[index + i].name, pets[index + i].element[0]);
      }
    }
  
    printf("Page: %d", page);
    printf("\n");
    printf("Enter 'n' for Next page, 'p' for Previous page, 'q' to Quit, 's' to show full information: ");
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
          printf("\nType the number of the Pet that you wish to know more of");
          scanf("%d", &nChoice);
          displayPet(pets[index + (nChoice-1)]);
        }
        else{
            printf("Invalid option or no more pages available!\n");
        }

  }
}

void ComPetDium(){
  struct BattlePet pets[MAX_PETS];
  for(int i = 0; i < MAX_PETS; i++){
    strcpy(pets[i].name, "EMPTY-SLOT");
  }
  //initializing pet array
  loadBattlePetsFromFile(pets); //loading pet array
  int nChoice; //choice variable for the menu 

  printf("\n1] View\n");
  printf("coming soon\n");
  printf("coming soon\n");
  printf("coming soon\n");
  scanf(" %d", &nChoice);
  switch(nChoice){
    case 1:
      View(pets);
    default:
        printf("Invalid input\n");
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
        ComPetDium();
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
void loadBattlePetsFromFile(struct BattlePet pets[]) 
{
  printf("\ninitating file....\n");
    FILE *file = fopen("../pets.txt", "r"); //our file pointer variable carrying the address of our pet file, in read mode 
    
    if (file == NULL) {  //file opening error handling
        printf("Error opening file.\n");
        return;
    }
    else{
      int i = 0;
      printf("\nLoading file into program...\nfile succesfully opened");
      while (i < MAX_PETS && fscanf(file, "%s", pets[i].name) == 1) {
        // Read the element (affinity)
        fscanf(file, " %s", &pets[i].element);  // Space skips any leading whitespace/newlines
        
        // Read the description (up to the newline character)
        fscanf(file, " %[^\n]", pets[i].description);  // This will read everything up to a newline
        fscanf(file, "%d", &pets[i].match_count);    // Read the match count
        
        i++;
        }// Move to the next pet
    }
    fclose(file);  // Close the file
  
}
