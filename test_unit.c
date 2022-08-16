#include "acutest.h"
#include "util.h"

void test_runSimulation(void)
{
    struct robot testObj; 

    const int N_TESTS = 5; 
    char *keyInput[N_TESTS] = {"dww",
                               "aww",
                               "awwawwawwaww",
                               "ss",
                               "wwddsas"};
    int min_x = 1; 
    int max_x[N_TESTS] = {3, 5, 8, 6, 1};
    int min_y = 1; 
    int max_y[N_TESTS] = {3, 8, 5, 4, 1};

    int xPos[N_TESTS] = {1, 2, 4, 3, 0};
    int yPos[N_TESTS] = {1, 3, 3, 3, 1};
    char cardinalDirection[N_TESTS] = {'n','e','s','w','n'};

    int result_x[N_TESTS] = {3, 2, 4, 5, 0};
    int result_y[N_TESTS] = {1, 5, 3, 3, 1};
    

    for(int i = 0; i < N_TESTS; i++)
    {
        testObj.xPos = xPos[i]; 
        testObj.yPos = yPos[i]; 
        testObj.direction = cardinalDirection[i]; 

        
        runSimulation(keyInput[i], &testObj, min_x, max_x[i], min_y, max_y[i]);
        TEST_CHECK_(testObj.xPos == result_x[i], "testOBJ.xPos = %i", result_x[i]);
        TEST_MSG("Produced: %i, Expected: %i", testObj.xPos, result_x[i]);

        TEST_CHECK_(testObj.yPos == result_y[i], "testOBJ.yPos = %i", result_y[i]);
        TEST_MSG("Produced: %i, Expected: %i", testObj.yPos, result_y[i]);
    }


}

void test_updatePosition(void)
{
    struct robot testObj;
    const int N_TESTS = 10; 
    char *keyInput[N_TESTS] = {"wwwdwwwdwwwdwww",
                      "wswsddw",
                      "assssddwwswwssswww",
                      "wwwwwaawwwwwddwwwwwawwwww",
                      "adadadadadadadadadadadadada",
                      "ddddddddwwwwwww",
                      "dddwwwaaawwwsswwwddd",
                      "wwwds",
                      "ssssswwddwwass",
                      "swswdddaaadddaaa"};
    int result_x[N_TESTS] = {0, 0, 7, -5, 0, 0, -3,-1, -2, 0};
    int result_y[N_TESTS] = {0,-1, 0, 5, 0, 7, 4, 3, -5, 0};

    for(int i = 0; i < N_TESTS; i++)
    {
        testObj.xPos = 0; 
        testObj.yPos = 0; 
        testObj.direction = 'n'; 
        for(int j = 0; keyInput[i][j] != '\0'; j++)
            updatePosition(&testObj, keyInput[i][j]);
        TEST_CHECK_(testObj.xPos == result_x[i], "testOBJ.xPos = %i", result_x[i]);
        TEST_MSG("Produced: %i, Expected: %i", testObj.xPos, result_x[i]);

        TEST_CHECK_(testObj.yPos == result_y[i], "testOBJ.yPos = %i", result_y[i]);
        TEST_MSG("Produced: %i, Expected: %i", testObj.yPos, result_y[i]);
    }

}

void test_updateDirection(void)
{
    struct robot testObj;
    testObj.direction = 'n';

    const int N_TESTS = 6; 
    char TESTS[N_TESTS] = {'s','w','w','n','s','e'};
    char resultClockwise[N_TESTS] = {'w','n','n','e','w','s'};
    char resultCounterClockwise[N_TESTS] = {'e','s','s','w','e','n'}; 

    for(int i = 0; i < N_TESTS; i++)
    {
        testObj.direction = TESTS[i]; 
        updateDirection(&testObj, 1);
        TEST_CHECK_(testObj.direction == resultClockwise[i], "testOBJ.direction = %c", resultClockwise[i]);

        testObj.direction = TESTS[i];
        updateDirection(&testObj, -1);
        TEST_CHECK_(testObj.direction == resultCounterClockwise[i], "testOBJ.direction = %c", resultCounterClockwise[i]);

    }


}

void test_incrementalPosition(void)
{
    struct robot testObj;
    const int N_TESTS = 4; 
    char TESTS[N_TESTS] = {'n','e','s','w'};
    int results_x[N_TESTS] = {0, 1, 1, 0};
    int results_y[N_TESTS] = {1, 1, 0, 0}; 
    for(int i = 0; i < N_TESTS; i++)
    {
        testObj.direction = TESTS[i]; 
        incrementPosition(&testObj, 1);
        TEST_CHECK_(testObj.xPos == results_x[i], "testOBJ.xPos = %i", results_x[i]);
        TEST_CHECK_(testObj.yPos == results_y[i], "testOBJ.xPos = %i", results_y[i]);
    }

}

void test_extractIntArgument(void)
{
    const int N_TESTS = 8; 
    char *input[N_TESTS] = {"5,4",
                            "10,4",
                            "150,45",
                            "532,200",
                            "22222135,421",
                            "11230,04",
                            "02120,42123125",
                            "002,200122"};
    int RESULTS_FIRST[N_TESTS] = {5,
                                 10,
                                 150,
                                 532,
                                 22222135,
                                 11230,
                                 2120,
                                 2};

    int RESULTS_LAST[N_TESTS] = {4,
                                 4,
                                 45,
                                 200,
                                 421,
                                 4,
                                 42123125,
                                 200122};

    int produced; 
    int expected; 

    for(int i = 0; i < N_TESTS; i++)
    {
        produced = extractIntArgument(input[i], 0);
        expected = RESULTS_FIRST[i];
        TEST_CHECK_(produced == expected, "extractIntArgument(%s) = %i", input[i], expected);
        TEST_MSG("Input %s, \t Produced: %i, \t Expected: %i", input[i], produced, expected);    

    }

    for(int i = 0; i < N_TESTS; i++)
    {
        produced = extractIntArgument(input[i], 1);
        expected = RESULTS_LAST[i];
        TEST_CHECK_(produced == expected, "extractIntArgument(%s) = %i", input[i], expected);
        TEST_MSG("Input %s, \t Produced: %i, \t Expected: %i", input[i], produced, expected);    

    }
}

void test_findSeparatorIndex(void)
{
    const int N_TESTS = 5; 
    char *TESTDATA[N_TESTS] = {"123,42",
                                "1,234",
                                "12345654321,2",
                                "123456,003",
                                "124526223,100000"};
    int expectedResult[N_TESTS] = {3, 1, 11, 6, 9}; 
    for(int i = 0; i < N_TESTS; i++)
    {
        int produced = findSeparatorIndex(TESTDATA[i], ',');
        TEST_CHECK_(produced == expectedResult[i], "findSeparatorIndex(%s, ',');", TESTDATA[i]);
        TEST_MSG("Produced: %i, Expected: %i", produced, expectedResult[i]);
    }

}

void test_updateSum(void)
{
    const int N_TESTS = 5; 
    char testData[N_TESTS] = {'1',
                               '2',
                               '4',
                               '2',
                               '1'};
    int currentSum[N_TESTS] = {5,
                              62,
                              623,
                              0,
                              23};

    int expectedResult[N_TESTS] = {51,
                                   622,
                                   6234,
                                   2,
                                   231};

    for(int i = 0; i < N_TESTS; i++)
    {
        int produced = updateSum(testData[i], currentSum[i]); 
        TEST_CHECK_(produced == expectedResult[i], "updateSum(%c, %i) = %i", testData[i], currentSum[i], expectedResult[i]);
        TEST_MSG("Produced: %i, Expected: %i", produced, expectedResult[i]);
    }      

                                


}

void test_checkValidFormatType(void)
{
    const int N_TESTS = 12;
    char *input[N_TESTS] = {"5,4",
                            "4,a",
                            "2,q",
                            "4,-",
                            "5,5",
                            "100,8",
                            "16,4",
                            ",,,",
                            "4223,2",
                            "-1,9",
                            "0",
                            "000"};
    int RESULTS[N_TESTS] = {TRUE,
                           FALSE,
                           FALSE,
                           FALSE,
                           TRUE,
                           TRUE,
                           TRUE,
                           FALSE,   
                           TRUE,
                           FALSE,
                           FALSE,
                           FALSE};

    for(int i = 0; i < N_TESTS; i++)
    {
        int produced = checkValidFormatType(input[i]); 
        int expected = RESULTS[i];
        TEST_CHECK_(produced == expected, "checkValidFormatType(%s) = %i", input[i], expected);
        TEST_MSG("Input %s, \t Produced: %i, \t Expected: %i", input[i], produced, expected);    
    }

    
}

void test_checkValidCardinalDirection(void)
{
    const int N_TESTS = 12;
    char input[N_TESTS] = {'n',
                            'N',
                            '5',
                            'E',
                            'x',
                            'e',
                            's',
                            'S',
                            'Q',
                            'w',
                            '0',
                            'W'};

    int RESULTS[N_TESTS] = {TRUE,
                           FALSE,
                           FALSE,
                           FALSE,
                           FALSE,
                           TRUE,
                           TRUE,
                           FALSE,   
                           FALSE,
                           TRUE,
                           FALSE,
                           FALSE};

    for(int i = 0; i < N_TESTS; i++)
    {
        int produced = checkValidCardinalDirection(input[i]); 
        int expected = RESULTS[i];
        TEST_CHECK_(produced == expected, "checkValidCardinalDirection(%c) = %i", input[i], expected);
        TEST_MSG("Input %c, \t Produced: %i, \t Expected: %i", input[i], produced, expected);    
    }

}

void test_isInt(void)
{
    for(int i = 0; i < 10; i++)
    {
        int produced = isInt(i+'0');
        TEST_CHECK_(produced == TRUE, "isInt(%c) = %i", i+'0', TRUE);
        TEST_MSG("Produced: %i, \t Expected: %i", produced, TRUE);
        
    }

    for(int i = 10; i < 80; i++)
    {
        int produced = isInt(i+'0');
        TEST_CHECK_(produced == FALSE, "isInt(%c) = %i", i+'0', FALSE);
        TEST_MSG("Produced: %i, \t Expected: %i", produced, FALSE);
    }


}

void test_charToInt(void)
{
    char charInput[10] = {'0','1','2','3','4','5','6','7','8','9'};
    for(int i = 0; i < 10; i++)
    {
        int produced = charToInt(charInput[i]);
        TEST_CHECK_(produced == i, "charToInt(%c) = %i", charInput[i], i);
        TEST_MSG("Produced: %i, \t Expected: %i", produced, i);
    }

}

TEST_LIST = 
{
    {"charToInt(char input);", test_charToInt},
    {"checkValidFormatType(char *input);", test_checkValidFormatType}, 
    {"int findSeparatorIndex(const char *data, char separator);", test_findSeparatorIndex},
    {"updateSum(char characterNumber, int currentSum)", test_updateSum},
    {"checkCardinalDirection(char input);", test_checkValidCardinalDirection},
    {"isInt(char input);", test_isInt},
    {"extractIntArgument(const char *input, const int TYPE);", test_extractIntArgument},
    {"void incrementPosition(struct robot *obj, int increment);", test_incrementalPosition},
    {"void updateDirection(struct robot *obj, int dir);", test_updateDirection},
    {"void updatePosition(struct robot *obj, char keyStroke);", test_updatePosition},
    {"void runSimulation(const char *movements, struct robot *obj, int minX, int maxX, int minY, int maxY);", test_runSimulation},
    {0}
};