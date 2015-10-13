/***************************************************************
 * <Brandon Bryant>
 * <Oct 12>
 *
 * <Game of Life>
 ***************************************************************/

#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

#define MAX_WIDTH 40

// function prototypes
void ParseCmdLine(int, char**);
void ShowUsage(char*);
int ReadGen0(bool[MAX_WIDTH][MAX_WIDTH]);
void DisplayBoard(bool[MAX_WIDTH][MAX_WIDTH], int, int);
bool computeBoard(bool[MAX_WIDTH][MAX_WIDTH], int, int);
void stateCheck(bool boardCp[MAX_WIDTH][MAX_WIDTH],bool board[MAX_WIDTH][MAX_WIDTH], int row, int col);
void copyBoard(bool boardCp[MAX_WIDTH][MAX_WIDTH],bool board[MAX_WIDTH][MAX_WIDTH],int len);

// command line parameters (default values)
int numGens = 10;
int genInt = 1;

/*******
 * MAIN
 *******/
int main(int argc, char **argv)
{
    // "*" => true, " " => false
    bool board[MAX_WIDTH][MAX_WIDTH];
    int len;

    // parse the command line, read gen0, and display the board
    ParseCmdLine(argc, argv);
    len = ReadGen0(board);
    DisplayBoard(board, 0, len); // board // generations // length

    // compute new generations
    computeBoard(board,numGens,len);

}

// parses the command line for parameters
void ParseCmdLine(int argc, char **argv)
{
    if (argc == 1) {
        ShowUsage(argv[0]);
        exit(0);
    }

    for (int i=1; i<argc; i++) {
        // default values
        if (!strcmp(argv[i], "-D")) {
            break;
        }
        // help/usage
        if (!strcmp(argv[i], "-h")) {
            ShowUsage(argv[0]);
            exit(0);
        }
        // number of generations to produce
        else if (strcmp(argv[i], "-n") > 0) {
            argv[i] += 2;
            numGens = atoi(argv[i]);
        }
        // display generation interval
        else if (strcmp(argv[i], "-i") > 0) {
            argv[i] += 2;
            genInt = atoi(argv[i]);
        }
    }
}

// displays help/usage
void ShowUsage(char *filename)
{
    cout << "Usage: " << filename << " [-h] -D [-(ni)<val>]\n";
    cout << " e.g.: " << filename << " -D < gen0\n";
    cout << "  -D\t\tUse default values\n";
    cout << "  -n<val>\tSet the number of generations to produce to <val> (=10)\n";
    cout << "  -i<val>\tSet the generation display interval to <val> (=1)\n";
    cout << "  -h\t\tShow this screen\n";
}

// reads the initial generation
int ReadGen0(bool board[MAX_WIDTH][MAX_WIDTH])
{
    char line[MAX_WIDTH];
    int i = 0;
    int len = 0;

    // we assume that the input contains a blank border as specified in class
    while (cin.getline(line, MAX_WIDTH)) {
        // grab each character of each line and make the board
        for (int j=0; j<strlen(line); j++) {
            board[i][j] = (line[j] == '*');
        }
        i++;
        // note the board size
        len = strlen(line);
    }

    return len;
}

// displays the current board
void DisplayBoard(bool board[MAX_WIDTH][MAX_WIDTH], int gen, int len)
{

    // display the generation number

    cout << "Gen" << gen << ":\n";
    cout << "  ";
    for(int h = 1,k=1; h < len-1; h++,k++) {
        if(k == 10) {
            k = 0;
        }
        cout << k << " " ;
    }
    cout << endl;
    for(int j = 1,l = 1; j < len -1; j++,l++) {
        if(l == 10) {
            l = 0;
        }
        cout << l << " ";
        for(int i = 1; i < len-1; i++) {
            cout << ((board[j][i]) ? "*" : " ")<< " ";
        }
        cout << endl;
    }
    cout <<endl;

}

bool computeBoard(bool board[MAX_WIDTH][MAX_WIDTH], int numGens, int len)
{

    bool boardCp[MAX_WIDTH][MAX_WIDTH];

    for(int currGen = 1; currGen < numGens+1; currGen++) { // ny generation

        for(int i = 0; i < len-1; i++) {
            for(int j = 0; j < len-1; j++) {
                boardCp[i][j] = board[i][j];
            }
        }
        //compute board
        for(int row = 1; row < len -1; row++) {
            for(int col = 1; col < len -1; col++) {
                stateCheck(boardCp,board,row,col);
            }
        }

        //display board
        DisplayBoard(boardCp,currGen,len);
        copyBoard(boardCp,board,len);

    }
}

void stateCheck(bool boardCp[MAX_WIDTH][MAX_WIDTH],bool board[MAX_WIDTH][MAX_WIDTH], int row, int col)
{
// row == current row, col == current col
//checks if cell should die, or come alive
// 0 1 2    |   a b c
// 3 * 4    |   d * e
// 5 6 7    |   f g h
// has 8 neighbors
    int a = board[row-1][col-1];
    int b = board[row-1][col];
    int c = board[row-1][col+1];
    int d = board[row][col-1];
    int e = board[row][col+1];
    int f = board[row+1][col-1];
    int g = board[row+1][col];
    int h = board[row+1][col+1];

    int numNeighborsAlive = a+b+c+d+e+f+g+h;
    int numNeighborsDead = 8-numNeighborsAlive;

    if(board[row][col]) {
        //cout<<"true";
        //    cout << " " << "("<< row << ","<< col << ") " << board[row][col] << " " << numNeighborsAlive  <<  " " << numNeighborsDead << " " << (numNeighborsAlive+numNeighborsDead)<<endl;
        if(numNeighborsAlive > 3) {
            boardCp[row][col] = 0;
        }
        if(numNeighborsAlive<2) {
            boardCp[row][col]=0;
        }

    }

    else {
        //cout<<"false";
        //  cout << " " << "("<< row << ","<< col << ") " << board[row][col] << " " << numNeighborsAlive  <<  " " << numNeighborsDead << " " << (numNeighborsAlive+numNeighborsDead)<<endl;
        if(numNeighborsAlive ==3) {
            boardCp[row][col] = 1;
        }
    }



}

void copyBoard(bool boardCp[MAX_WIDTH][MAX_WIDTH],bool board[MAX_WIDTH][MAX_WIDTH],int len)
{
    for(int i = 0; i < len-1; i++) {
        for(int j = 0; j < len-1; j++) {
            board[i][j] = boardCp[i][j];
        }
    }
}

