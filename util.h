#ifndef UTIL_H
#define UTIL_H

struct robot
{
    int xPos = 0;
    int yPos = 0; 

    char direction; 
};
void runSimulation(const char *movements, struct robot *obj, int minX, int maxX, int minY, int maxY);
int withinLimits(struct robot *obj, int minX, int maxX, int minY, int maxY);
void updatePosition(struct robot *obj, char keyStroke);
void updateDirection(struct robot *obj, int dir); 
void incrementPosition(struct robot *obj, int increment);
int extractIntArgument(const char *input, const int TYPE);
int findSeparatorIndex(const char *data, char separator);
int updateSum(char characterNumber, int currentSum);
int checkValidFormatType(const char *input); 
int checkValidCardinalDirection(const char input); 
int isInt(const char input); 
int charToInt(char input);


#endif
