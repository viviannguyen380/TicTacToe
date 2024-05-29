#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
/*
 *Tic Tac Toe: Created by Vivian Nguyen on December 30, 2022
 Description-A 2-player Tic-Tac-Toe game, utilizing arrays to 
 simulate the game-board
 *
*/
//Prints the character if bool b is true, otherwise print an empty space in the board
void printLet(char c, bool b){
    if (b){
        cout<<c<<" ";
    }
    else{
        cout<<"  ";
    }
}
//prints the grid and the markers (X/O) placed on the board
void printGameGrid(char c [9], bool b [9]){
    for (int i=0; i<9; i+=3){
        cout<<"  ";
        //letter?
        printLet(c[i],b[i]);
        cout<<"|";
        cout<<" ";
        printLet(c[i+1],b[i+1]);
        cout<<"|";
        cout<<" ";
        printLet(c[i+2],b[i+2]);
        cout<<endl;
        if (i!=6){
            cout<<"  ";
            cout<<"- - - - -"<<endl;
        }
    }
}

//prints the game grid with numbers corresponding to the place on the gameboard where the piece will be placed if selected
void printSampleGrid(){
     cout<<"  ";

    for (int i=1; i<9; i+=3){
        for (int k=i; k<i+3; k++){
            cout<<to_string(k)<<" ";
            if (k!=i+2){
                cout<<"|";
                cout<<" ";
            }  
        }
     
        cout<<endl;
        if (i!=7){
            cout<<"  ";
            cout<<"- - - - -"<<endl;
        }
        cout<<"  ";
    }


}
//plays the game.
/*
    filledSpaces: Tracks if a piece is placed in the corresponding location (0-8), iterating from upper left hand 
    corner to the right, then moves down, until the bottom right hand corner is reached
    charSpaces: Indicates which char the location (0-8) has, X, O, or empty space
    turn: incremented by 1 each time the do loop runs, determines which player (X/O) is playing in the current turn
    space: the inputted number corresponding to the location on the gameboard where the piece (based on turn) will be     placed
*/ 
void playGame(){
    bool filledSpaces [9]={};
    char charSpaces [9]={};
    int turn=0;
    int space=-1;

    /*keepPlaying: true if the game is still going, false if a player has won or all spaces are 
    occupied and there's a tie
    play1Win: Set to true if player 1 wins
    play2Win: Set to true if player 2 wins
        */
    bool keepPlaying=true;

    bool play1Win=false;
    bool play2Win=false;
    
    while (keepPlaying){
        printSampleGrid();
        cout<<endl;
        printGameGrid(charSpaces,filledSpaces);

        //determine which player's turn it is
        if (turn%2==0){
            cout<<"Player 1: Enter a space # : ";
        }
        else{
            cout<<"Player 2: Enter a space # : ";
        }
        //Asks for input of number location to place piece in until valid
            do{
                cin>>space;
                if (space<=0 || space >=10 || filledSpaces[space-1]){
                    cout<<"Please enter a valid space #: " ;
                 } 
            //if space is invalid, or is occupied, keep asking until valid input is given.
            } while (space<=0 || space >=10 || filledSpaces[space-1]);

        //determine which piece to place in the board, based on which player's turn it is
        if (turn%2==0){
            charSpaces[space-1]='X';
        }
        else{
            charSpaces[space-1]='O';
        }

        filledSpaces[space-1]=true;
        //check for all spaces occupied
        bool toEnd=true;
        for (int i=0; i<9; i++){
            if (!filledSpaces[i]){
                toEnd=false;
            }
        }
        if (toEnd){
            keepPlaying=false;
        }


        //check for a win, and if so which player won
        if (filledSpaces[0] && charSpaces[0]==charSpaces[1] && charSpaces[1]==charSpaces[2]){
            if (turn%2==0){
                play1Win=true;
            }
            else{
                play2Win=true;
            }
            keepPlaying=false;
        }
        else if (filledSpaces[3] && charSpaces[3]==charSpaces[4] && charSpaces[4]==charSpaces[5]){
            if (turn%2==0){
                play1Win=true;
            }
            else{
                play2Win=true;
            }
            keepPlaying=false;
        }
        else if (filledSpaces[6] && charSpaces[6]==charSpaces[7] && charSpaces[7]==charSpaces[8]){
            if (turn%2==0){
                play1Win=true;
            }
            else{
                play2Win=true;
            }
            keepPlaying=false;
        }
         else if (filledSpaces[0] && charSpaces[0]==charSpaces[4] && charSpaces[4]==charSpaces[8]){
             if (turn%2==0){
                 play1Win=true;
             }
             else{
                 play2Win=true;
             }
             keepPlaying=false;
        }
         else if (filledSpaces[2] && charSpaces[2]==charSpaces[4] && charSpaces[4]==charSpaces[6]){
             if (turn%2==0){
                 play1Win=true;
             }
             else{
                 play2Win=true;
             }
             keepPlaying=false;
        }
         else if (filledSpaces[0] && charSpaces[0]==charSpaces[3] && charSpaces[3]==charSpaces[6]){
             if (turn%2==0){
                 play1Win=true;
             }
             else{
                 play2Win=true;
             }
             keepPlaying=false;
        }
         else if (filledSpaces[1] && charSpaces[1]==charSpaces[4] && charSpaces[4]==charSpaces[7]){
             if (turn%2==0){
                 play1Win=true;
             }
             else{
                 play2Win=true;
             }
             keepPlaying=false;
        }
         else if (filledSpaces[2] && charSpaces[2]==charSpaces[5] && charSpaces[5]==charSpaces[8]){
             if (turn%2==0){
                 play1Win=true;
             }
             else{
                 play2Win=true;
             }
             keepPlaying=false;
        }
        //change player's turn and reset space input
        turn++;
        space=-1;
        cout<<endl;
}
//print out winner, or tie if there's a tie                
  if (play1Win){
      cout<<"Player 1 wins! "<<endl;
  }     
  else if (play2Win){
      cout<<"Player 2 wins! "<<endl;
  }
//tie if all spaces are filled and no one has won
  else{
      cout<<"It's a tie "<<endl;
  }
    printGameGrid(charSpaces, filledSpaces);
}
int main()
{
    //allows the player to play tic tac toe until the user decides to quit playing
    cout<<"Tic Tac Toe: "<<endl;
    char cont='Y';
    while (toupper(cont)=='Y'){
        playGame();
        cout<<"Play again? Y: yes N: no: ";
        cin>>cont;

    }
    cout<<"Thanks for playing!"<<endl;
    return 0;
}


