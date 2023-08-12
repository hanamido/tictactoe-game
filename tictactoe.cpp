// Console window game of Tic Tac Toe

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

// Global variables
// space holds the game board
char space[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}}; 
std::string player1; 
std::string player2; 
char player1Symbol = 'X';
char player2Symbol = 'O';

// Function to draw n amount of symbol on the console.
void drawLines(int n, char symbol)
{
    int i = 0;
    for (i = 0; i <= n; i++)
    {
        std::cout << symbol; 
    }
    std::cout << '\n';
}

// Introduce the game and instructions
void gameIntro() 
{
    drawLines(20, '*'); 
    std::cout << "TIC TAC TOE\n";
    drawLines(20, '*');
    std::cout << "Instructions: \n";
    std::cout << "   1. Enter the two players' names.\n";
    std::cout << "   2. Wait as the system determines who is player1 (token is 'X') and player2 (token is 'O'). Player1 goes first, Player2 goes second.\n";
    std::cout << "  3. Player's Turn: pick a row and column to fill that spot in the board.\n";
}

// Function to create the gameboard
void createGameBoard()
{
    std::cout << "   |   |   \n";
    std::cout << " "<< space[0][0] << " | " << space[0][1] << " | " << space[0][2] << "   \n";
    std::cout << "___|___|___\n";
    std::cout << "   |   |   \n";
    std::cout << " "<< space[1][0] << " | " << space[1][1] << " | " << space[1][2] << "   \n";
    std::cout << "___|___|___\n";
    std::cout << "   |   |   \n";
    std::cout << " "<< space[2][0] << " | " << space[2][1]<< " | " << space[2][2] << "   \n";
    std::cout << "   |   |   \n\n";
}

// Function to determine which player goes first
void determinePlayerTurns(std::string playerName1, std::string playerName2)
{
    int player1Num;
    int player2Num; 

regenerateNums: 
    srand(time(NULL));
    player1Num = 1 + (rand() % 10); 
    player2Num = 1 + (rand() % 10); 

    if (player1Num > player2Num)
    {
        std::cout << playerName1 << " is Player 1. " << playerName1 << " goes first.\n\n"; 
        std::cout << playerName1 << "'s token is 'X'.\n";
        std::cout << playerName2 << "'s token is 'O'.\n\n";
        player1 = playerName1;
        player2 = playerName2; 
    }
    else if (player1Num < player2Num)
    {
        std::cout << playerName2 << " is Player 1. " << playerName2 << " goes first.\n\n";    
        std::cout << playerName2 << "'s token is 'X'.\n";
        std::cout << playerName1 << "'s token is 'O'.\n\n"; 
        player1 = playerName2;
        player2 = playerName1; 

    }
    else {
        goto regenerateNums; 
    }
}

// Function to check if it is a horizontal winning move
bool checkHorizontalWin(char playerSymbol, int row, int column, int rowLen) {
    for (int i = 0; i < rowLen; i++) {
        if (space[row][i] != playerSymbol) {
            return false;
        }
    }
    return true;
}

// Function to check if it is a vertical winning move
bool checkVerticalWin(char playerSymbol, int row, int column, int rowLen) {
    for (int i = 0; i < rowLen; i++) {
        if (space[i][column] != playerSymbol) {
            return false;
        }
    }
    return true;
}

// Function to check if we have a left diagonal win
bool checkLeftDiagonalWin(char playerSymbol, int row, int column) {
    // array of possible coordinates for left diagonal win
    int leftDiagonalCoords[3][2] = {{0, 0}, {1, 1}, {2, 2}};
    int leftCoordsLength = sizeof(leftDiagonalCoords) / sizeof(leftDiagonalCoords[0]);
    for (int i = 0; i < leftCoordsLength; i++) {
        int x = leftDiagonalCoords[i][0];
        int y = leftDiagonalCoords[i][1];
        if (space[x][y] != playerSymbol) {
            return false;
        }
    }
    return true;
}

// Function to check if we have a right diagonal win
bool checkRightDiagonalWin(char playerSymbol, int row, int column) {
    // array of possible coordinates for right diagonal win
    int rightDiagonalCoords[3][2] = {{0, 2}, {1, 1}, {2, 0}};
    int rightCoordsLength = sizeof(rightDiagonalCoords) / sizeof(rightDiagonalCoords[0]);
    for (int i = 0; i < rightCoordsLength; i++) {
        int x = rightDiagonalCoords[i][0];
        int y = rightDiagonalCoords[i][1];
        if (space[x][y] != playerSymbol) {
            return false;
        }
    }
    return true;
}

// Function to check if it is a diagonal winning move
bool checkDiagonalWin(char playerSymbol, int row, int column) {
    bool checkLeftDiagonal = checkLeftDiagonalWin(playerSymbol, row, column); 
    bool checkRightDiagonal = checkRightDiagonalWin(playerSymbol, row, column);
    if (!checkLeftDiagonal && !checkRightDiagonal) {
        return false;
    }
    return true;
}

// Function to check if it is a winning move
bool checkWinningMove(std::string playerNum, int row, int column) {
    // It is a winning move if there are 3 of the same symbol
    // horizontally, vertically, or diagonally
    char playerSymbol; 
    int rowLen = sizeof(space[row]) / sizeof(space[row][0]);  
    if (playerNum == player1) { playerSymbol = 'X'; }
    else { playerSymbol = 'O'; }
    // check for horizontal win
    bool horizontalWin = checkHorizontalWin(playerSymbol, row, column, rowLen);
    // check for vertical win
    bool verticalWin = checkVerticalWin(playerSymbol, row, column, rowLen);
    // check for diagonal win
    bool diagonalWin = checkDiagonalWin(playerSymbol, row, column);
    if (!horizontalWin && !verticalWin && !diagonalWin) {
        std::cout << "No player has won yet...\n";
        return false;
    }
    return true;
}

// Function to make the move and update the gameboard
void makeMove(std::string playerNum, int row, int column)
{
    // update the specified space in the gameboard
    if (playerNum == player1) {
        // Player 1 is 'X'
        space[row][column] = 'X';
    }
    else {
        // Player 2 is 'O'
        space[row][column] = 'O';
    }
    createGameBoard();
}

// Function to check if it is a valid move
bool checkValidMove(int row, int column) {
    // if it is off the board or negative
    if (row < 0 || row > 2) {
        return false;
    }
    if (column < 0 || column > 2) {
        return false;
    }
    // if the row and column is already occupied
    if (space[row][column] == 'X' || space[row][column] == 'O') {
        return false;
    }
    return true;
}

// Function to check if it is a tie move
bool checkTieMove(int row, int column) {
    char playerSymbol1 = 'X';
    char playerSymbol2 = 'O'; 
    int rowLen = sizeof(space[row]) / sizeof(space[row][0]);

    // check if we have a win for player1
    bool checkPlayer1Horizontal = checkHorizontalWin(playerSymbol1, row, column, rowLen);
    bool checkPlayer1Vertical = checkVerticalWin(playerSymbol1, row, column, rowLen);
    bool checkPlayer1Diagonal = checkDiagonalWin(playerSymbol1, row, column);
    
    // check if we have a win for Player 2
    bool checkPlayer2Horizontal = checkHorizontalWin(playerSymbol2, row, column, rowLen);
    bool checkPlayer2Vertical = checkVerticalWin(playerSymbol2, row, column, rowLen);
    bool checkPlayer2Diagonal = checkDiagonalWin(playerSymbol2, row, column);

    // we have a tie move if there are no win's detected in any direction
    if (!checkPlayer1Horizontal && 
        !checkPlayer1Vertical && 
        !checkPlayer1Diagonal &&
        !checkPlayer2Horizontal &&
        !checkPlayer2Vertical &&
        !checkPlayer2Diagonal) {
            return true;
        }
    return false;
}

// Function to reset the space variable to its original value
void resetSpaceVariable() {
    int c = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int newValue = ++c;
            char newCh = '0' + newValue;
            space[i][j] = newCh;
        }
    }
    createGameBoard();
}

int main()
{
    char localSpace[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}}; 
    std::string playerName1;
    std::string playerName2; 
    std::string row;
    std::string column;
    char replayChoice = 'y';
    bool filledBoard = false;  // checks if the board is filled
    gameIntro();
    createGameBoard();

    std::cout << "Enter the first player's name: ";
    std::getline(std::cin, playerName1);  // load first player's name into cin
    std::cout << "Hello " << playerName1 << "\n\n"; 
    std::cout << "Enter the second player's name: "; 
    std::getline(std::cin, playerName2); 
    std::cout << "Hello " << playerName2 << "\n\n"; 
    determinePlayerTurns(playerName1, playerName2);

    // continue looping between players while we don't have a tie at the end
    while (1) {
    playerMoves:
        std::cout << player1 << ", please pick the row to move to: ";
        std::cin >> row;
        std::cout << player1 << '\n';
        std::cout << player1 << ", please pick the column to move to: ";
        std::cin >> column;
        int rowInt = stoi(row);
        int colInt = stoi(column);
        // first validate the move
        if (!checkValidMove(rowInt, colInt)) {
            std::cout << "Invalid move, please try again\n\n";
            goto playerMoves;
        }
        // make the move
        makeMove(player1, rowInt, colInt);
        // check that the move is not a winning or tie move
        if (checkWinningMove(player1, rowInt, colInt)) {
            std::cout << player1 << " has won!\n";
            break;
        }
        // TODO: check if it is a tie move...
        // tie can only be determined if all tiles on board are filled
        int spaceLen = sizeof(space) / sizeof(space[0]);

        for (int i = 0; i < spaceLen; i++) {
            // if each row is filled
            if (isalpha(space[i][0]) && 
                isalpha(space[i][1]) && 
                isalpha(space[i][2])) {
                filledBoard = true;
            } 
            else { filledBoard = false; }
        }

        if (filledBoard) {
            if (checkTieMove(rowInt, colInt)) {
                std::cout << "Tied Match!\n";
                break;
            }
        }
        // move on to next player
        std::cout << player2 << ", please pick the row to move to: ";
        std::cin >> row; 
        std::cout << player2 << ", please pick the column to move to: ";
        std::cin >> column;
        int rowInt2 = stoi(row);
        int colInt2 = stoi(column);
        // first validate the move
        if (!checkValidMove(rowInt2, colInt2)) {
            std::cout << "Invalid move, please try again\n\n";
            goto playerMoves;
        }
        makeMove(player2, rowInt2, colInt2);
        // check that the move is not a winning or tie move
        if (checkWinningMove(player2, rowInt2, colInt2)) {
            std::cout << player2 << " has won!\n";
            break;
        } 
        for (int i = 0; i < spaceLen; i++) {
            // if each row is filled
            if (isalpha(space[i][0]) && 
                isalpha(space[i][1]) && 
                isalpha(space[i][2])) {
                filledBoard = true;
            } 
            else { filledBoard = false; }
        }
        if (filledBoard) {
            if (checkTieMove(rowInt2, colInt2)) {
                std::cout << "Tied Match!\n";
                break;
            }
        }
    }

    // Ask a player if they would like to play again
    std::cout << "Would you like to play again? Enter 'y' for yes, 'n' for no. ";
    std::cin >> replayChoice;
    if (replayChoice == 'y') {
        resetSpaceVariable();
        goto playerMoves;
    }

    exit: 
        std::cout << "Thanks for playing!\n";
        return EXIT_SUCCESS; 
}

