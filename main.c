#include "util.h"
#include <stdio.h>

#define INPUT_SIZE 50

int main(int argc, char **argv)
{
    char roomSize[INPUT_SIZE];
    char startPos[INPUT_SIZE];
    char movement[INPUT_SIZE];
    char cardinalDirection;


    printf("What sixe of room should be simulated? (Format: w,h): ");
    scanf("%49s", roomSize);

    printf("Select a starting positon: (Format: x,y): ");
    scanf("%49s", startPos);

    
    printf("Select initial chardinal direction (Valid directions: n,e,s, or w) ");
    scanf(" %c", &cardinalDirection);  

    printf("Enter key combo: (Valid characters: w, s, a, or d) ");
    scanf("%49s", movement);

    int MIN_X = 1;
    int MAX_X = extractIntArgument(roomSize, 0);
    int MIN_Y = 1;
    int MAX_Y = extractIntArgument(roomSize, 1);

    struct robot vacuum; 
    vacuum.direction = cardinalDirection; 
    vacuum.xPos = extractIntArgument(startPos, 0); 
    vacuum.yPos = extractIntArgument(startPos, 1);


    runSimulation(movement, &vacuum, MIN_X, MAX_X, MIN_Y, MAX_Y);


    
 return 0; 
}
