 /******************************************
  This is the header file, intended for the defninition of the structs and commonly
  used values
*/


//---------------common variables-------------//
#define MAX_PLAYERS 50 //The program is designed only to have only up to  50 players 
#define MAX_USER_CHAR 37 //player usernames can handle up to 36 characters
#define MAX_PET_NAME 31 //maxmium character for the battle pet name
#define MAX_DESCRIPTION 241 //maximum description for battle pet, should not have newline;


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
  char element;
  BPDescription description;
}pet;



//funciton prototypes

void displayMainMenu();



