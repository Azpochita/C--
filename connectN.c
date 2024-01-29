#include <stdio.h>
#include <ctype.h> 
#include <stdlib.h> 

int InitializeBoard(int **connectNBoard, int numRowsInBoard);
int DisplayBoard(int **connectNBoard, int numRowsInBoard);
int MakeMove(int **connectNBoard, int numRowsInBoard, int playerID, int columnChosen);
int CheckWinner(int **connectNBoard, int numRowsInBoard, int numConnect, int columnChosen, int playerID);


const int MAXSIZE = 25;
const int MINSIZE = 8;
const int MINCONNECTNUM = 4;

int main() {

    int numRows;
    int numToConnect;
    int **myConnectNBoard;

    printf("Enter the number of squares along each edge of board\n");
    int test = scanf("%d", &numRows);
    while (test != 1 || numRows < MINSIZE || numRows > MAXSIZE)
    {
        if (test != 1) //if scanf doesnt return a value, it must not have been an integer
        {
            printf("ERROR: The value provided was not an integer\n");
            printf("Enter the number of squares along each edge of board\n");

            //these 2 lines will flush standard input
            char flush;
            while ((flush = getchar()) != '\n');

            test = scanf("%d", &numRows);
        }
        else if (numRows < MINSIZE)
        {
            printf("ERROR: Board size too small (<%d)\n", MINSIZE);
            printf("Enter the number of squares along each edge of board\n");
            char flush;
            while ((flush = getchar()) != '\n');
            test = scanf("%d", &numRows);
        }
        else if (numRows > MAXSIZE)
        {
            printf("ERROR: Board size too large (>%d)\n", MAXSIZE);
            printf("Enter the number of squares along each edge of board\n");
            char flush;
            while ((flush = getchar()) != '\n');
            test = scanf("%d", &numRows);
        }
    }
    // these 2 lines flush the standard input in case the user enters a non-integer after an integer value
    char flush;
    while ((flush = getchar()) != '\n');

    printf("Enter the number of pieces that must form a line to win\n");
    int test2 = scanf("%d", &numToConnect);
    while (test2 != 1 || numToConnect < MINCONNECTNUM || numToConnect > numRows - MINCONNECTNUM)
    {
        if (test2 != 1) //if scanf did not return value, it must not have been an integer
        {
            printf("ERROR: The value provided was not an integer\n");
            printf("Enter the number of pieces that must form a line to win\n");
            char flush;
            while ((flush = getchar()) != '\n');
            test2 = scanf("%d", &numToConnect);
        }
        else if (numToConnect < MINCONNECTNUM)
        {
            printf("ERROR: Number provided is too small (<%d)\n", MINCONNECTNUM);
            printf("Enter the number of pieces that must form a line to win\n");
            char flush;
            while ((flush = getchar()) != '\n');
            test2 = scanf("%d", &numToConnect);
        }
        else if (numToConnect > numRows - MINCONNECTNUM)
        {
            printf("ERROR: Number to connect is too large (>%d)\n", numRows - MINCONNECTNUM);
            printf("Enter the number of pieces that must form a line to win\n");
            char flush;
            while ((flush = getchar()) != '\n');
            test2 = scanf("%d", &numToConnect);
        }
    }
    char flush2;
    while ((flush2 = getchar()) != '\n');

    //creating board
    myConnectNBoard = (int**)malloc(numRows*sizeof(int*));
    myConnectNBoard[0] = (int*)malloc(numRows*numRows*sizeof(int));
    for (int a=1;a<numRows;a++) {
        myConnectNBoard[a] = myConnectNBoard[0] + a*numRows;
    }

    if (InitializeBoard(myConnectNBoard, numRows) == 0) {
        printf("ERROR: Could not initialize the game board\n");
        free(myConnectNBoard[0]);
        free(myConnectNBoard);
        myConnectNBoard = NULL;
        return 0;
    }
    printf("\n\n");
    if (DisplayBoard(myConnectNBoard, numRows) == 0) {
        printf("ERROR: Could not display the game board\n");
    }

    //arbitrary numbers chosen to represent Red and Black
    int Red = 2;
    int Black = 3;
    int player_tracker = 2; //game starts with Red

    int chosenColumn;
    int counter = 1; //to track the maximum 3 attempts of choosing a column
    int win_check = 0; //to check for a win

    while (win_check != 1) {
        if (player_tracker == 2) {
            printf("Red moves\n");
        } else if (player_tracker == 3) {
            printf("Black moves\n");
        }
        printf("Enter the column number where you want to put your piece\n");
        int test3 = scanf("%d", &chosenColumn);
        counter = 1;
        while (counter<4) {
            if (test3 != 1) {
                printf("ERROR: The value provided was not a number\n");
                char flush3;
                while((flush3 = getchar()) != '\n');
                if (counter == 3) {
                    printf("TOO MANY ILLEGAL MOVES\n");
                    if (player_tracker == 2) {
                        printf("Red has forfeited a turn\n");
                    } else if (player_tracker == 3) {
                        printf("Black has forfeited a turn\n");
                    }
                    break;
                }
                printf("Enter the column number where you want to put your piece\n");
                test3 = scanf("%d", &chosenColumn);                
            } else if (chosenColumn >= numRows || chosenColumn < 0) {
                printf("ERROR: Column %d is not on the board: try again\n", chosenColumn);
                printf("ERROR: Column number should be >=0 and < %d\n", numRows);
                char flush3;
                while((flush3 = getchar()) != '\n');
                if (counter == 3) {
                    printf("TOO MANY ILLEGAL MOVES\n");
                    if (player_tracker == 2) {
                        printf("Red has forfeited a turn\n");
                    } else if (player_tracker == 3) {
                        printf("Black has forfeited a turn\n");
                    }
                    break;
                }
                printf("Enter the column number where you want to put your piece\n");
                test3 = scanf("%d", &chosenColumn);
            } else if (myConnectNBoard[1][chosenColumn] != 0) {
                printf("ERROR: Column %d is already completely full try again\n", chosenColumn);
                char flush3;
                while((flush3 = getchar()) != '\n');
                if (counter == 3) {
                    printf("TOO MANY ILLEGAL MOVES\n");
                    if (player_tracker == 2) {
                        printf("Red has forfeited a turn\n");
                    } else if (player_tracker == 3) {
                        printf("Black has forfeited a turn\n");
                    }
                    break;
                }
                printf("Enter the column number where you want to put your piece\n");
                test3 = scanf("%d", &chosenColumn);
            } else if (MakeMove(myConnectNBoard, numRows, player_tracker, chosenColumn) == 0) {
                if (counter == 3) {
                    printf("TOO MANY ILLEGAL MOVES\n");
                    if (player_tracker == 2) {
                        printf("Red has forfeited a turn\n");
                    } else if (player_tracker == 3) {
                        printf("Black has forfeited a turn\n");
                    }
                    break;
                }
                printf("Enter the column number where you want to put your piece\n");
                char flush3;
                while((flush3 = getchar()) != '\n');
                test3 = scanf("%d", &chosenColumn);
            } else {
                counter = 1;
                char flush3; //make sure standard input is clear
                while((flush3 = getchar()) != '\n');
                break;
            }
            counter++;
        }
        if (counter != 3 && CheckWinner(myConnectNBoard, numRows, numToConnect, chosenColumn, Red) == 1) {
            printf("Red has won\n");
            DisplayBoard(myConnectNBoard, numRows);
            win_check = 1;
        } else if (counter != 3 && CheckWinner(myConnectNBoard, numRows, numToConnect, chosenColumn, Black) == 1) {
            printf("Black has won\n");
            DisplayBoard(myConnectNBoard, numRows);
            win_check = 1;
        } else if (player_tracker == 2) {
            printf("\n\n");
            DisplayBoard(myConnectNBoard, numRows);
            player_tracker = 3;
        } else if (player_tracker == 3) {
            printf("\n\n");
            DisplayBoard(myConnectNBoard, numRows);
            player_tracker = 2;
        }
    }

    free(myConnectNBoard[0]);
    free(myConnectNBoard);
    myConnectNBoard = NULL;


    return 1;
}

int InitializeBoard(int **connectNBoard, int numRowsInBoard) {
    if (connectNBoard == NULL) {
        printf("ERROR: cannot initialize the board because the pointer to the board is NULL");
        free(connectNBoard[0]);
        free(connectNBoard);
        connectNBoard = NULL;
        return 0;
    }
    if (numRowsInBoard > MAXSIZE || numRowsInBoard < MINSIZE) {
        printf("ERROR: illegal number of rows in board");
        free(connectNBoard[0]);
        free(connectNBoard);
        connectNBoard = NULL;
        return 0;
    }
    for (int i=0;i<numRowsInBoard; i++) {
        for (int j=0;j<numRowsInBoard; j++) {
            connectNBoard[i][j] = 0;
        }
    }
    return 1;
}

int DisplayBoard(int **connectNBoard, int numRowsInBoard) {
    if (connectNBoard == NULL) {
        printf("ERROR: cannot initialize the board because the pointer to the board is NULL\n");
        return 0;
    }
    if (numRowsInBoard > MAXSIZE || numRowsInBoard < MINSIZE) {
        printf("ERROR: illegal number of rows in board\n");
        return 0;
    }
    printf("   ");
    for (int t=0;t<numRowsInBoard;t++) {
        printf("%3d", t);
    }
    printf("\n");

    int rowCounter = 0;
    for (int c=0;c<numRowsInBoard;c++) {
        printf("%3d", c);
        for (int d=0;d<numRowsInBoard;d++) {
            if (connectNBoard[c][d] == 0) {
                printf("  o");
            } else if (connectNBoard[c][d] == 1) {
                printf("  R");
            } else if (connectNBoard[c][d] == 2) {
                printf("  B");
            }
        }
        printf("\n");
    }
    
    return 1;
}

int MakeMove(int **connectNBoard, int numRowsInBoard, int playerID, int columnChosen) {
    if (connectNBoard == NULL) {
        printf("ERROR: cannot print the board because the pointer to the board is NULL\n");
        return 0;
    }
    if (columnChosen >= numRowsInBoard || connectNBoard[1][columnChosen] != 0 || columnChosen < 0) {
        printf("Illegal move\n");
        return 0;
    }
    for (int k=numRowsInBoard-1;k>=0;k--) {
        if (connectNBoard[k][columnChosen] == 0) {
            if (playerID == 2) {
                connectNBoard[k][columnChosen] = 1;
                printf("Red has moved\n");
                return 1;
            } else if (playerID == 3) {
                connectNBoard[k][columnChosen] = 2;
                printf("Black has moved\n");
                return 1;
            }
        }
    }

}

int CheckWinner(int **connectNBoard, int numRowsInBoard, int numConnect, int columnChosen, int playerID) {
    if (connectNBoard == NULL) {
        printf("ERROR: cannot print the board because the pointer to the board is NULL\n");
        return 0;
    }
    if (columnChosen >= numRowsInBoard || connectNBoard[1][columnChosen] != 0 || columnChosen < 0) {
        printf("Illegal move\n");
        return 0;
    }
    int afterCount = 0;
    int beforeCount = 0;
    int left = columnChosen-1;
    int right = columnChosen+1;
    for (int j=0;j<numRowsInBoard;j++) {
        int bottom = j+1;
        int top = j-1;
        if (connectNBoard[j][columnChosen] == 1 && playerID == 2) { //to check for Red
            while (left>=0 && connectNBoard[j][left] == 1) {
                beforeCount++;
                left--;
            }
            while (right<numRowsInBoard && connectNBoard[j][right] == 1) {
                afterCount++;
                right++;
            }
            if (afterCount+beforeCount+1>=numConnect) {
                return 1;
            } else {
                //reset all variables for next check
                afterCount = 0;
                beforeCount = 0;
                left = columnChosen-1;
                right = columnChosen+1;
            }
            while (top>=0 && connectNBoard[top][columnChosen] == 1) {
                beforeCount++;
                top--;
            }
            while (bottom<numRowsInBoard && connectNBoard[bottom][columnChosen] == 1) {
                afterCount++;
                bottom++;
            }
            if (afterCount+beforeCount+1>=numConnect) {
                return 1;
            } else {
                //reset all variables for next check
                afterCount = 0;
                beforeCount = 0;
                top = j-1;
                bottom = j+1;
            }
            while (left>=0 && top>= 0 && connectNBoard[top][left] == 1) {
                beforeCount++;
                top--;
                left--;
            }
            while (bottom<numRowsInBoard && right<numRowsInBoard && connectNBoard[bottom][right] == 1) {
                afterCount++;
                bottom++;
                right++;
            }
            if (afterCount+beforeCount+1>=numConnect) {
                return 1;
            } else {
                //reset all variables for next check
                afterCount = 0;
                beforeCount = 0;
                top = j-1;
                bottom = j+1;
                left = columnChosen-1;
                right = columnChosen+1;
            }
            while (top>=0 && right<numRowsInBoard && connectNBoard[top][right] == 1) {
                afterCount++;
                top--;
                right++;
            }
            while (left>=0 && bottom<numRowsInBoard && connectNBoard[bottom][left] == 1) {
                beforeCount++;
                bottom++;
                left--;
            }
            if (afterCount+beforeCount+1>=numConnect) {
                return 1;
            } else {
                //reset variables for next check
                afterCount = 0;
                beforeCount = 0;
                left = columnChosen-1;
                right = columnChosen+1;
                if (j==numRowsInBoard-1) {
                    return 0; //all checks done now for Red, so return false if no win
                }
            }
        } else if (connectNBoard[j][columnChosen] == 2 && playerID == 3) { //to check for Black
            while (left>=0 && connectNBoard[j][left] == 2) {
                beforeCount++;
                left--;
            }
            while (right<numRowsInBoard && connectNBoard[j][right] == 2) {
                afterCount++;
                right++;
            }
            if (afterCount+beforeCount+1>=numConnect) {
                return 1;
            } else {
                //reset all variables for next check
                afterCount = 0;
                beforeCount = 0;
                left = columnChosen-1;
                right = columnChosen+1;
            }
            while (top>=0 && connectNBoard[top][columnChosen] == 2) {
                beforeCount++;
                top--;
            }
            while (bottom<numRowsInBoard && connectNBoard[bottom][columnChosen] == 2) {
                afterCount++;
                bottom++;
            }
            if (afterCount+beforeCount+1>=numConnect) {
                return 1;
            } else {
                //reset all variables for next check
                afterCount = 0;
                beforeCount = 0;
                top = j-1;
                bottom = j+1;
            }
            while (top>=0 && left>=0 && connectNBoard[top][left] == 2) {
                beforeCount++;
                top--;
                left--;
            }
            while (bottom<numRowsInBoard && right<numRowsInBoard && connectNBoard[bottom][right] == 2) {
                afterCount++;
                bottom++;
                right++;
            }
            if (afterCount+beforeCount+1>=numConnect) {
                return 1;
            } else {
                //reset all variables for next check
                afterCount = 0;
                beforeCount = 0;
                top = j-1;
                bottom = j+1;
                left = columnChosen-1;
                right = columnChosen+1;
            }
            while (top>=0 && right<numRowsInBoard && connectNBoard[top][right] == 2) {
                afterCount++;
                top--;
                right++;
            }
            while (bottom<numRowsInBoard && left>=0 && connectNBoard[bottom][left] == 2) {
                beforeCount++;
                bottom++;
                left--;
            }
            if (afterCount+beforeCount+1>=numConnect) {
                return 1;
            } else {
                afterCount = 0;
                beforeCount = 0;
                left = columnChosen-1;
                right = columnChosen+1;
                if (j==numRowsInBoard-1) {
                    return 0; //all checks done now for Black, so return false if no win
                }
            }

        }
    }
}