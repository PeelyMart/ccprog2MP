 /******************************************
  This is the header file, intended for the defninition of the structs and commonly
  used values
*/
#ifndef DEFS_H
#define DEFS_H 


//---------------common variables-------------//
#include <string.h>
#include <stdio.h>
#define MAX_PLAYERS 50 //The program is designed only to have only up to  50 players 
#define MAX_USER_CHAR 37 //player usernames can handle up to 36 characters
#define MAX_PET_NAME 31 //maxmium character for the battle pet name
#define MAX_DESCRIPTION 241 //maximum description for battle pet, should not have newline;
#define MAX_PETS 60 //maximum pets in pet array
#define PAGE_SIZE 4 //shows 4 names max per page used in view function for competdium

//type definitions
typedef char UserName[MAX_USER_CHAR];
typedef char BattlePetName[MAX_PET_NAME];
typedef char BPDescription[MAX_DESCRIPTION];

//player structure definition


typedef struct PlayerInfo
{
  UserName name;
  int win;
  int loss;
  int draw;
} Player;

//Battle Pet structure

typedef struct BattlePet{
  BattlePetName name;
  char element[15];
  BPDescription description;
  int match_count;
}pet;




//funciton prototypes
void displayPet(struct BattlePet d);
int loadBattlePetsFromFile(struct BattlePet pets[]);
int displayMainMenu();
void View(struct BattlePet pets[]);
void ComPetDiumDriver();
void fullInfo(struct BattlePet d[], int index);
void clearScreen(void);
int delete(struct BattlePet d[], int index);
int save(struct BattlePet pets[]);
int backupBattlePets(struct BattlePet pets[]);
void edit(struct BattlePet d[], int index);
void elementEdit(struct BattlePet d[], int index);
void elementDisplay();
int integerToElement(char* output, int input);
void descriptionEdit(struct BattlePet d[], int index);
void nameEdit(struct BattlePet d[], int index);
void addPet(struct BattlePet d[]);
int getLastPet(struct BattlePet d[]);
#endif
