#include "util.h"
#include <stdio.h>

#define FALSE 0 
#define TRUE 1 
#define FIRST 0 
#define LAST 1 
#define SEPARATOR ','
#define CLOCKWISE 1
#define COUNTERCLOCKWISE -1
#define INCREMENTAL_SIZE 1

struct robot; 



int withinLimits(struct robot *obj, int minX, int maxX, int minY, int maxY)
{
	return (obj->xPos < minX || obj->xPos > maxX || obj->yPos < minY || obj->yPos > maxY) ? FALSE : TRUE;
}

void updatePosition(struct robot *obj, char keyStroke)
{
	switch(keyStroke)
    {
        case 'w':
            incrementPosition(obj, INCREMENTAL_SIZE);
        break; 

        case 's':
            incrementPosition(obj, -INCREMENTAL_SIZE);
        break; 

        case 'a': 
            updateDirection(obj, COUNTERCLOCKWISE); 
        break; 

        case 'd':
            updateDirection(obj, CLOCKWISE);

        break;

        default:
			// Ignore errornous input
        break;
    }
}

void updateDirection(struct robot *obj, int dir)
{
	switch(obj->direction)
	{
		case 'n':
			obj->direction = (dir == CLOCKWISE ? 'e' : 'w');
		break;

		case 'e':
			obj->direction = (dir == CLOCKWISE ? 's' : 'n');
		break;

		case 's':
			obj->direction = (dir == CLOCKWISE ? 'w' : 'e');
		break;

		case 'w':
			obj->direction = (dir == CLOCKWISE ? 'n' : 's');
		break;

		default: 
			// Ignore errornous input
		break; 
	}


}

void incrementPosition(struct robot *obj, int increment)
{
	switch(obj->direction)
	{
		case 'n':
			obj->yPos += increment;
		break;

		case 'e':
			obj->xPos += increment;	
		break; 

		case 's':
			obj->yPos -= increment; 
		break;

		case 'w':
			obj->xPos -= increment;
		break;

		default: 

		break;
	}
}

int extractIntArgument(const char *cNumber, const int Argument)
{

	int sum = 0; 

	if(Argument == FIRST)
	{
		for(int j = 0; cNumber[j] != SEPARATOR; j++)
			sum = updateSum(cNumber[j], sum);
	}
	else
	{
		int separatorPosition = findSeparatorIndex(cNumber, SEPARATOR);

		for(int j = (separatorPosition+1); cNumber[j] != '\0'; j++)
			sum = updateSum(cNumber[j], sum);
	}
	
	return sum; 
}

int findSeparatorIndex(const char *data, char separator)
{
	int i = 0; 
	for(i = 0; data[i] != separator; i++);

	return i; 
}

int updateSum(char characterNumber, int currentSum)
{
	currentSum *= 10;
	currentSum += charToInt(characterNumber);
	return currentSum;
}

int checkValidFormatType(const char *input)
{
	
	int hasSeparator = FALSE; 

	int i; 

	for(i = 0; input[i] != '\0'; i++)
	{
		if(input[i] == SEPARATOR && hasSeparator == TRUE)
			return FALSE;
		else if(isInt(input[i]) == FALSE && input[i] != SEPARATOR)
			return FALSE;
		
		if(input[i] == SEPARATOR)
			hasSeparator = TRUE; 
	}
	
	return (i < 3 || hasSeparator == FALSE)  ? FALSE: TRUE;
}

int checkValidCardinalDirection(const char CD)
{
	return (CD == 'n' || CD =='e' || CD =='s' || CD =='w') ? TRUE : FALSE; 
}

int isInt(char cINT)
{
	return (charToInt(cINT) >= 0 && charToInt(cINT) <= 9) ? TRUE : FALSE; 
}

int charToInt(char cINT)
{
	return cINT - '0';	
}

void printRobotPosition(struct robot *obj)
{
    printf("(%i, %i)(%c)\n", obj->xPos, obj->yPos, obj->direction);
}

void runSimulation(const char *movements, struct robot *obj, int minX, int maxX, int minY, int maxY)
{
	printRobotPosition(obj);
    for(int i = 0; movements[i] != '\0'; i++)
    {
        if(withinLimits(obj, minX, maxX, minY, maxY))
        {
			updatePosition(obj, movements[i]);
            printRobotPosition(obj);
        }
        else
        {
            printf("Out of boundary! ");
            printRobotPosition(obj);
            break; 
        }              
    }
}
