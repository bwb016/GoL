/***************************************************************
 * <your name>
 * <the date>
 *
 * <a description>
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
	DisplayBoard(board, 0, len);

	// compute new generations
	// ...
}

// parses the command line for parameters
void ParseCmdLine(int argc, char **argv)
{
	if (argc == 1)
	{
		ShowUsage(argv[0]);
		exit(0);
	}

	for (int i=1; i<argc; i++)
	{
		// default values
		if (!strcmp(argv[i], "-D"))
			break;
		// help/usage
		if (!strcmp(argv[i], "-h"))
		{
			ShowUsage(argv[0]);
			exit(0);
		}
		// number of generations to produce
		else if (strcmp(argv[i], "-n") > 0)
		{
			argv[i] += 2;
			numGens = atoi(argv[i]);
		}
		// display generation interval
		else if (strcmp(argv[i], "-i") > 0)
		{
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
	while (cin.getline(line, MAX_WIDTH))
	{
		// grab each character of each line and make the board
		for (int j=0; j<strlen(line); j++)
			board[i][j] = (line[j] == '*');
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

	// display the board
	// ...
}
