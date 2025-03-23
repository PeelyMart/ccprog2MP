
#include <stdio.h>
#include <string.h>

// Define the BattlePet structure
struct BattlePet {
    char name[30];             // Name of the battlepet (max 30 characters)
    char elemental_affinity[20];  // Elemental affinity (e.g., Fire, Water)
    char description[240];      // Short description (max 240 characters)
    int match_count;            // Number of matches (integer)
};

// Function to open the file and read the data into the array of structures
void loadBattlePetsFromFile(const char* filename, struct BattlePet pets[], int max_pets) {
    FILE *file = fopen("pets.txt", "r");
    
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int i = 0;
    while (i < max_pets && fscanf(file, "%[^\n]\n", pets[i].name) == 1) {
        fscanf(file, "%[^\n]\n", pets[i].elemental_affinity);
        
        // Read the description (handle cases where it might be missing)
        if (fscanf(file, "%[^\n]\n", pets[i].description) != 1) {
            strcpy(pets[i].description, "No description available.");
        }

        // Read the match count
        if (fscanf(file, "%d\n", &pets[i].match_count) != 1) {
            pets[i].match_count = 0;  // Default match count if missing
        }

        i++;
    }

    fclose(file);  // Close the file
}

// Function to print the data stored in the array of structures


int main() {
    struct BattlePet pets[10];  // Array of 10 battlepet structures
    // Load data from a file called "battlepets.txt" into the array
    loadBattlePetsFromFile("battlepets.txt", pets, 10);
       
    // Print the loaded data
    printBattlePets(pets, 10);

    return 0;
}
