#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Global constants
const int boardSize = 4;
const int minValue = -10;
const int maxValue = 10;

// Global variables
vector<vector<int>> board(boardSize, vector<int>(boardSize));
pair<int, int> goalTile;
pair<int, int> startPosition;
vector<pair<int, int>> visitedTiles;

// Function prototypes
int generateRandomNumber();
void fillTheBoard();
void revealTile();
void getStartPosition();
pair<int, int> moveUp();
pair<int, int> moveDown();
pair<int, int> moveLeft();
pair<int, int> moveRight();
bool checkGoal();
void playGame();
void printOutcome();

int main() {
    // Seed the random number generator
    srand(static_cast<unsigned>(time(0)));

    string playAgain;
    do {
        fillTheBoard();
        getStartPosition();
        visitedTiles.clear();
        visitedTiles.push_back(startPosition);

        playGame();

        cout << "Do you want to play again? (yes/no): ";
        cin >> playAgain;
    } while (playAgain == "yes");

    printOutcome();
    return 0;
}

// Function to generate a random number between minValue and maxValue (inclusive)
int generateRandomNumber() {
    return rand() % (maxValue - minValue + 1) + minValue;
}

// Function to fill the board with random numbers and set the goal tile
void fillTheBoard() {
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            board[i][j] = generateRandomNumber();
        }
    }
    goalTile = make_pair(rand() % boardSize, rand() % boardSize);
    board[goalTile.first][goalTile.second] = generateRandomNumber() + 11;
}

// Function to reveal the board with only revealed tiles
void revealTile() {
    cout << "Board:" << endl;
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            if (make_pair(i, j) == goalTile) {
                cout << " G ";
            } else if (make_pair(i, j) == startPosition) {
                cout << " S ";
            } else if (find(visitedTiles.begin(), visitedTiles.end(), make_pair(i, j)) != visitedTiles.end()) {
                cout << " " << board[i][j] << " ";
            } else {
                cout << " ? ";
            }
        }
        cout << endl;
    }
}

// Function to get the start position from the user
void getStartPosition() {
    do {
        cout << "Enter the row number (0 to " << (boardSize - 1) << "): ";
        cin >> startPosition.first;
        cout << "Enter the column number (0 to " << (boardSize - 1) << "): ";
        cin >> startPosition.second;
        if (startPosition == goalTile || startPosition.first < 0 || startPosition.first >= boardSize || startPosition.second < 0 || startPosition.second >= boardSize) {
            cout << "Invalid position. Please choose a valid hidden tile." << endl;
        }
    } while (startPosition == goalTile || startPosition.first < 0 || startPosition.first >= boardSize || startPosition.second < 0 || startPosition.second >= boardSize);
}

// Function to move the position up
pair<int, int> moveUp() {
    int newRow = startPosition.first - 1;
    if (newRow >= 0 && find(visitedTiles.begin(), visitedTiles.end(), make_pair(newRow, startPosition.second)) == visitedTiles.end()) {
        return make_pair(newRow, startPosition.second);
    }
    return startPosition;
}

// Function to move the position down
pair<int, int> moveDown() {
    int newRow = startPosition.first + 1;
    if (newRow < boardSize && find(visitedTiles.begin(), visitedTiles.end(), make_pair(newRow, startPosition.second)) == visitedTiles.end()) {
        return make_pair(newRow, startPosition.second);
    }
    return startPosition;
}

// Function to move the position left
pair<int, int> moveLeft() {
    int newCol = startPosition.second - 1;
    if (newCol >= 0 && find(visitedTiles.begin(), visitedTiles.end(), make_pair(startPosition.first, newCol)) == visitedTiles.end()) {
        return make_pair(startPosition.first, newCol);
    }
    return startPosition;
}

// Function to move the position right
pair<int, int> moveRight() {
    int newCol = startPosition.second + 1;
    if (newCol < boardSize && find(visitedTiles.begin(), visitedTiles.end(), make_pair(startPosition.first, newCol)) == visitedTiles.end()) {
        return make_pair(startPosition.first, newCol);
    }
    return startPosition;
}

// Function to check if the total sum of visited tiles falls within the range of -2 to 2
bool checkGoal() {
    int totalSum = 0;
    for (const auto& tile : visitedTiles) {
        totalSum += board[tile.first][tile.second];
    }
    return totalSum >= -2 && totalSum <= 2;
}

// Function to play the game
void playGame() {
    while (true) {
        revealTile();
        if (startPosition == goalTile) {
            cout << "Congratulations! You reached the goal tile." << endl;
            if (checkGoal()) {
                cout << "Total sum of visited tiles is within the range of -2 to 2. You win!" << endl;
            } else {
                cout << "Total sum of visited tiles is not within the range of -2 to 2. Game over!" << endl;
            }
            break;
        }

        cout << "Enter a move direction (up, down, left, right): ";
        string moveDirection;
        cin >> moveDirection;
        pair<int, int> newPosition = startPosition;

        if (moveDirection == "up") {
            newPosition = moveUp();
        } else if (moveDirection == "down") {
            newPosition = moveDown();
        } else if (moveDirection == "left") {
            newPosition = moveLeft();
        } else if (moveDirection == "right") {
            newPosition = moveRight();
        } else {
            cout << "Invalid move. Please choose a valid direction." << endl;
            continue;
        }

        if (newPosition == startPosition) {
            cout << "Invalid move. Please choose a different direction." << endl;
        } else {
            visitedTiles.push_back(newPosition);
            startPosition = newPosition;
        }
    }
}

// Function to print the outcome of the game
void printOutcome() {
    cout << "Game Over. Here are the outcomes of your attempts:" << endl;
    int attempt = 1;
    for (const auto& tile : visitedTiles) {
        cout << "Attempt " << attempt << ": Start position: (" << tile;
    }}
