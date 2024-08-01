#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits.h>
#include <string>
using namespace std;

/*
 *Tic Tac Toe: Created by Vivian Nguyen on December 30, 2022
 Updated July 22,2024 to implement single-player VS CPU mode
 and class encapsulation.

 Description-A 2-player Tic-Tac-Toe game, utilizing arrays to
 simulate the game-board
 *
*/

const static int BOARD_SIZE = 9;
class TicTacToe {
public:
  TicTacToe();
  /**
    plays the game.
    @param twoPlayers: true if 2 player game is selected, false if 1 player game
  is selected.
  **/
  void playGame(bool twoPlayers, int difficulty);

private:
  /**
    Prints the char c (X, O, or ' ') on the board.
    @param char c the board to print
    @param b if the char is to be printed or not. (' ' for false)
  **/
  void printLet(char c, bool b);
  /**
    Prints the board and pieces.
  **/
  void printGameGrid();
  /**
    prints a sample grid with designated numbers for each
    position.
  **/
  void printSampleGrid();
  /**
    Checks if the board is full.
    @return true if the board is full, false otherwise
  **/
  bool isFull();
  /**
    Checks if there is a winner.
    @return 1: Player 1 wins, 2: Player 2 wins, 0: no winner
  **/
  int checkWin();
  /**
    finds the best move for the computer player.
    @return the best position for the CPU player.
  **/
  int getBestPosition();
  /**
    searches through possible moves, returns the optimal
    position for the player.
    @param minMax, "max" if searching to maximize O's score,
    "min" if searching
    to minimize O's score (maximize X's)
    @param depth, the # of turns taken from the current state of
    the board. Increments by 1
    for each recursive iteration.
    @return the score for the current state of the board. A
    higher score is more favorable for the O player, and a lower
    score is more favorable for the X player.
  **/
  int getMinMax(string minMax, int depth);
  /**
    resets the game board and turn
  **/
  void resetGame();

  // charSpaces: contains the character at each position of the board.
  // Index=inputted position-1
  char charSpaces[BOARD_SIZE];
  // boolSpaces: contains the bool value of whether the space is occupied or
  // not. 
  //Index=inputted position-1
  bool filledSpaces[BOARD_SIZE];
  // turn: 0 for X, 1 for O
  int turn;
};
TicTacToe::TicTacToe() { resetGame(); }
void TicTacToe::resetGame() {
  for (int i = 0; i < BOARD_SIZE; i++) {
    filledSpaces[i] = false;
    charSpaces[i] = ' ';
  }
  turn = 0;
}
void TicTacToe::printLet(char c, bool b) {
  if (b) {
    cout << c << " ";
  } else {
    cout << "  ";
  }
}

void TicTacToe::printGameGrid() {
  for (int i = 0; i < BOARD_SIZE; i += 3) {
    cout << "  ";
    printLet(charSpaces[i], filledSpaces[i]);
    cout << "|";
    cout << " ";
    printLet(charSpaces[i + 1], filledSpaces[i + 1]);
    cout << "|";
    cout << " ";
    printLet(charSpaces[i + 2], filledSpaces[i + 2]);
    cout << endl;
    if (i != 6) {
      cout << "  ";
      cout << "- - - - -" << endl;
    }
  }
}

void TicTacToe::printSampleGrid() {
  cout << "  ";

  for (int i = 1; i < BOARD_SIZE; i += BOARD_SIZE/3) {
    for (int k = i; k < i + 3; k++) {
      cout << to_string(k) << " ";
      if (k != i + 2) {
        cout << "|";
        cout << " ";
      }
    }

    cout << endl;
    if (i != 7) {
      cout << "  ";
      cout << "- - - - -" << endl;
    }
    cout << "  ";
  }
}

bool TicTacToe::isFull() {
  // check for all spaces occupied
  bool toEnd = true;
  for (int i = 0; i < BOARD_SIZE; i++) {
    if (!filledSpaces[i]) {
      toEnd = false;
    }
  }
  return toEnd;
}

int TicTacToe::checkWin() {
  if (filledSpaces[0] && charSpaces[0] == charSpaces[1] &&
      charSpaces[1] == charSpaces[2]) {
    if (charSpaces[0] == 'X') {
      return 1;
    } else {
      return 2;
    }
  } else if (filledSpaces[3] && charSpaces[3] == charSpaces[4] &&
             charSpaces[4] == charSpaces[5]) {
    if (charSpaces[3] == 'X') {
      return 1;
    } else {
      return 2;
    }
  } else if (filledSpaces[6] && charSpaces[6] == charSpaces[7] &&
             charSpaces[7] == charSpaces[8]) {
    if (charSpaces[6] == 'X') {
      return 1;
    } else {
      return 2;
    }
  } else if (filledSpaces[0] && charSpaces[0] == charSpaces[4] &&
             charSpaces[4] == charSpaces[8]) {
    if (charSpaces[0] == 'X') {
      return 1;
    } else {
      return 2;
    }
  } else if (filledSpaces[2] && charSpaces[2] == charSpaces[4] &&
             charSpaces[4] == charSpaces[6]) {
    if (charSpaces[2] == 'X') {
      return 1;
    } else {
      return 2;
    }
  } else if (filledSpaces[0] && charSpaces[0] == charSpaces[3] &&
             charSpaces[3] == charSpaces[6]) {
    if (charSpaces[0] == 'X') {
      return 1;
    } else {
      return 2;
    }
  } else if (filledSpaces[1] && charSpaces[1] == charSpaces[4] &&
             charSpaces[4] == charSpaces[7]) {
    if (charSpaces[1] == 'X') {
      return 1;
    } else {
      return 2;
    }
  } else if (filledSpaces[2] && charSpaces[2] == charSpaces[5] &&
             charSpaces[5] == charSpaces[8]) {
    if (charSpaces[2] == 'X') {
      return 1;
    } else {
      return 2;
    }
  }
  return 0;
}

int TicTacToe::getMinMax(string minMax, int depth) {
  if (checkWin() == 1) {
    return depth - 10;
  } else if (checkWin() == 2) {
    return 10 - depth;
  } else if (isFull()) {
    return 0;
  }

  int best = 0;

  if (minMax == "max") {
    best = INT_MIN;
    for (int i = 0; i < BOARD_SIZE; i++) {
      if (!filledSpaces[i]) {
        filledSpaces[i] = true;
        charSpaces[i] = 'O';
        int spaceScore = getMinMax("min", depth + 1);
        if (spaceScore > best) {
          best = spaceScore;
        }
        filledSpaces[i] = false;
        charSpaces[i] = ' ';
      }
    }
  } else {
    best = INT_MAX;
    for (int i = 0; i < BOARD_SIZE; i++) {
      if (!filledSpaces[i]) {
        filledSpaces[i] = true;
        charSpaces[i] = 'X';
        int spaceScore = getMinMax("max", depth + 1);
        if (spaceScore < best) {
          best = spaceScore;
        }
        filledSpaces[i] = false;
        charSpaces[i] = ' ';
      }
    }
  }
  return best;
}

int TicTacToe::getBestPosition() {
  int bestPosition = -1;
  int bestScore = 0;
  if (turn % 2 == 1) {
    bestScore = INT_MIN; // we want to maximize O player's score
  } else {
    bestScore = INT_MAX; // we want to minimize O player's score (maximize X
                         // player's score)
  }
  for (int i = 0; i < BOARD_SIZE; i++) {
    if (!filledSpaces[i]) {
      if (turn % 2 == 1) {

        // temporarilly place "O" at position i+1 on the gameboard
        filledSpaces[i] = true;
        charSpaces[i] = 'O';
        // get the score for placing "O" at position i+1.

        int moveScore = getMinMax("min", 0);

        // remove the temporary piece
        filledSpaces[i] = false;
        charSpaces[i] = ' ';
        // check if moveScore is greater than maxScore
        if (moveScore > bestScore) {
          bestPosition = i;
          bestScore = moveScore;
        }
      } else {

        // temporarilly place "X" at position i+1 on the gameboard
        filledSpaces[i] = true;
        charSpaces[i] = 'X';
        // get the score for placing "X" at position i+1.

        int moveScore = getMinMax("max", 0);

        // remove the temporary piece
        filledSpaces[i] = false;
        charSpaces[i] = ' ';
        // check if moveScore is greater than maxScore
        if (moveScore < bestScore) {
          bestPosition = i;
          bestScore = moveScore;
        }
      }
    }
  }
  
  printGameGrid();
  return bestPosition + 1;
}

void TicTacToe::playGame(bool twoPlayers, int difficulty) {
  resetGame();
  int space = -1;

  /*keepPlaying: true if the game is still going, false if a player has won or
    all spaces are occupied and there's a tie play1Win: Set to true if player 1
    wins play2Win: Set to true if player 2 wins
  */

  bool keepPlaying = true;
  bool play1Win = false;
  bool play2Win = false;
  turn = rand() % 2 + 1;
  while (keepPlaying) {
    if (isFull()) {
      keepPlaying = false;
      break;
    }
    printSampleGrid();
    cout << endl;
    printGameGrid();

    if (twoPlayers) {
      // TWO PLAYER GAME
      // determine which player's turn it is
      if (turn % 2 == 0) {
        cout << "Player 1: Enter a space # : ";
      } else {
        cout << "Player 2: Enter a space # : ";
      }
      // Asks for input of number location to place piece in until valid
      do {
        cin >> space;
        if (space <= 0 || space >= 10 || filledSpaces[space - 1]) {
          cout << "Please enter a valid space #: ";
        }
        // if space is invalid, or is occupied, keep asking until valid input is
        // given.
      } while (space <= 0 || space >= 10 || filledSpaces[space - 1]);

      // determine which piece to place in the board, based on which player's
      // turn it is
      if (turn % 2 == 0) {
        charSpaces[space - 1] = 'X';
      } else {
        charSpaces[space - 1] = 'O';
      }

      filledSpaces[space - 1] = true;
    } else {
      // ONE PLAYER GAME
      srand(static_cast<unsigned int>(time(0)));

      if (turn % 2 == 0) {
        cout << "Player 1: Enter a space # : ";

        // Asks for input of number location to place piece in until valid
        do {
          cin >> space;
          if (space <= 0 || space >= 10 || filledSpaces[space - 1]) {
            cout << "Please enter a valid space #: ";
          }
          // if space is invalid, or is occupied, keep asking until valid input
          // is given.
        } while (space <= 0 || space >= 10 || filledSpaces[space - 1]);

        // determine which piece to place in the board, based on which player's
        // turn it is

        charSpaces[space - 1] = 'X';

        filledSpaces[space - 1] = true;
      }

      else {
        // CPU player's turn.

        /*
           position: the position the CPU will place its piece
           idealProb: the probability of the CPU's piece being placed in the
           optimal position. randomPosition: A random position to place its
           piece in.
        */
        cout << "CPU's turn" << endl;
        srand(static_cast<unsigned int>(time(0)));
        int position = 0;
        int idealProb = rand() % 100 + 1;
        int bestPosition = getBestPosition();

        int randomPosition = rand() % BOARD_SIZE + 1;
        while (filledSpaces[randomPosition - 1]) {
          randomPosition = rand() % BOARD_SIZE + 1;
        }

        bool determineIdeal = false;

        /*based on difficulty, determine if CPU should place its piece in the
          optimal position. Lower levels are less likely to place its piece in
          the optimal position.
        */

        if ((difficulty == 1 && idealProb < 40) ||
            (difficulty == 2 && idealProb < 70) ||
            (difficulty == 3 && idealProb < 90)) {
         
          determineIdeal = true;
        }

        if (determineIdeal) {
          position = bestPosition;
        } else {
          position = randomPosition;
        }

        if (checkWin() == 0) {
          charSpaces[position - 1] = 'O';
          filledSpaces[position - 1] = 'O';
        }
      }
    }

    // check for all spaces occupied, if so game is over.
    if (isFull()) {
      keepPlaying = false;
    }

    // check for a win, and if so which player won
    int winner = checkWin();
    if (winner == 1) {
      play1Win = true;
      keepPlaying = false;
    } else if (winner == 2) {
      play2Win = true;
      keepPlaying = false;
    }
    turn++;
    space = -1;
    cout << endl;
  }
  // print out winner, or tie if there's a tie
  if (play1Win) {
    cout << "Player 1 wins! " << endl;
  } else if (play2Win) {
    cout << "Player 2 wins! " << endl;
  }
  // tie if all spaces are filled and no one has won
  else {
    cout << "It's a tie " << endl;
  }
  printGameGrid();
}

int main() {

  TicTacToe tic_tac_toe = TicTacToe();
  cout << "Tic Tac Toe: " << endl;
  char cont = 'Y';
  // allows the player to play tic tac toe until the user decides to quit
  // playing
  while (toupper(cont) == 'Y') {
    int numPlayers;
    cout << "Would you like to play with 1 player or 2 player? (1/2): ";
    cin >> numPlayers;
    if (numPlayers == 2) {
      tic_tac_toe.playGame(true, 0);
    } else {
      int difficulty;
      cout << "What difficulty level? 1: Easy 2: Medium 3: Hard: ";
      cin >> difficulty;
      if (difficulty == 1 || difficulty == 2 || difficulty == 3) {
        tic_tac_toe.playGame(false, difficulty);
        //default to Medium difficulty
      } else {
        tic_tac_toe.playGame(false, 2);
      }
    }
    cout << "Play again? Y: yes N: no: ";
    cin >> cont;
  }
  cout << "Thanks for playing!" << endl;
  return 0;
}
