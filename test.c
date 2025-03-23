#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define PAGE_SIZE 4//per page how much is seen 
#define SIZE 10
struct ComPetDium{
  char name[31];
  char element[15]; 
  char description[241];
  int match;
};

struct simplifiedCompPetDium{
  char name[31];
};

void search(){
  char searchField[31];
  printf("Warning CASE SENSITIVE:");
  printf("Search: ");
  scanf("%s", searchField);
}


void View(struct simplifiedCompPetDium d[]){
  int exitCondition = 1;
  int index = 0;
  char choice;
  while(exitCondition){
    printf("Pet Names: \n");
    for(int i = 0; i < PAGE_SIZE; i++){
      if(index + i < 10){
        printf("%s", d->name[index + 1]);
      }
    }
    printf("\n");
    
    printf("Enter 'n' for Next page, 'p' for Previous page, 'q' to Quit: ");
    scanf(" %c", &choice);  // Space before %c to clear buffer
        if (choice == 'n' && index + PAGE_SIZE < SIZE) {
            index += PAGE_SIZE;  // Move to next page
        }
        else if (choice == 'p' && index - PAGE_SIZE >= 0) {
            index -= PAGE_SIZE;  // Move to previous page
        } 
        else if (choice == 'q') {
            exitCondition = 0;  // Exit the loop
        } 
        else if(choice == 's'){
          search();
    }
        else {
            printf("Invalid option or no more pages available!\n");
        }

  }
} 

void compMain(struct ComPetDium p[]){
  struct simplifiedCompPetDium simplified[10];
  for(int i = 0; i < 10; i++){
    strcpy(simplified[i].name, p[i].name); //copy name of each 
  }

  int nChoice;
  //copy the simplified////
  printf("1] View\n");
  printf("coming soon\n");
  printf("coming soon\n");printf("coming soon\n");
  scanf(" %d", &nChoice);
  switch(nChoice){
    case 1:
      View(simplified);
    default:
        printf("Invalid input\n");
  }
  
}

struct ComPetDium encoder(){
  struct ComPetDium b;
  scanf("%s", b.name);
  scanf("%s", b.element);
  scanf("%s", b.description);
  scanf("%d", b.match);
  return b;
}


int main(){
  struct ComPetDium allPets[10] = {0}; //it will initalize then set all values to either null or an equivalent to it
  for(int i = 0;i < 10; i++){
    allPets[i] = encoder();
  }
  compMain(allPets);
}


