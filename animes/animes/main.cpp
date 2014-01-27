//DEFINES
#define _WIN32_WINNT 0x0500

//#include <stdlib.h>
#include <iostream> //IO console
#include <conio.h>
#include <string> //using string vars
#include <time.h>
#include <fstream>  //file IO
#include <Windows.h> 

using namespace std;

//function prototypes
void Initialize(void);
void StaticTextLibrary(int);
int MainScreenOptions(void);
void MoveCursor(int, int);
char getKeyPress(void);
void ScreenWipe(int);
void DrawGame(char[]);
void ReadGameState(void);
void PrintGameState(void);
void ReadStaticScreen(string);
void PrintStaticScreen(void);
void ConsoleControl(void);
void InputParser(void);
int StringSize(void);
void TenController(void);

//Global main Variables
string gamestate[65];
string statebuffer[65]; //Contains required game screen
string phrasebuffer[7];

struct player {
	string Name;
	int Strength;
	int Agility;
	int Speed;
	int Health;
	int Mana;
	int Stamina;
	int Armor;
	int Attack;
	int Currency;
} Player;

struct enemy {
	string Name;
	int Health;
	int Mana;
	int Stamina;
	int Strength;
	int Agility;
	int Speed;
	int Armor;
	int Attack;
} test_enemy;

int main() {
	int MainOption = 0;

	Initialize();
	ReadStaticScreen("MainScreen.txt");
	PrintStaticScreen();
	MainOption = MainScreenOptions();

	if (MainOption == 0) {
		ReadGameState();
		PrintGameState();

		while(1) {//temp loop
			ConsoleControl();
			InputParser();
		}
	} else if (MainOption == 1) {
		//loadgame
	} else if (MainOption == 2) {//exit
		return(0);
	}
	
	system("PAUSE");
	return(0);
}

void TenController(void) {
	//Set generation
	//test
	int numbers[7][7] = {{0,1,2,3,4,5,6},{7,8,9,10,11,12,13},{14,15,16,17,18,19,20},{21,22,23,24,25,26,27},{28,29,30,31,32,33,34},{35,36,37,38,39,40,41},{42,43,44,45,46,47,48}};
	char key;
	int index_lin = 0;
	int index_col = 0;
	int old_lin = 0;
	int old_col = 0;
	int new_sum = 0;
	bool select = false;

	//Value printing
	// 9-- 9, 19
	//14--
	for (int lin = 0; lin < 7; lin++) {
		for (int col = 0; col < 7; col++) {
			MoveCursor(9 + (col * 10), 9 + (lin * 5));
			cout << numbers[lin][col];
		}
	}

	//Draw starting position
	MoveCursor(6,8); //ul
	cout << char(218);
	MoveCursor(14,8); //ur
	cout << char(191);
	MoveCursor(6, 11); //ll
	cout << char(192);
	MoveCursor(14, 11); //lr
	cout << char(217);

	//Movement control ll - 192, lr - 217, ul - 218, ur - 191
	//lls - 200, lrs - 188, uls - 201, urs - 187
	//start col 5, lin 8

	//Input controller
	while (1) {
		key = getKeyPress();

		if ((key == 72/*'u'*/) || (key == 'w')) {//Up arrow or w
			if (index_lin > 0) {//Do not allow movement past bounds
				MoveCursor(6 + (10 * index_col),8 + (5 * index_lin));
				cout << " ";
				MoveCursor(14 + (10 * index_col),8 + (5 * index_lin));
				cout << " ";
				MoveCursor(6 + (10 * index_col),11 + (5 * index_lin));
				cout << " ";
				MoveCursor(14 + (10 * index_col),11 + (5 * index_lin));
				cout << " ";

				index_lin--;

				MoveCursor(6 + (10 * index_col),8 + (5 * index_lin));
				cout << char(218);
				MoveCursor(14 + (10 * index_col),8 + (5 * index_lin));
				cout << char(191);
				MoveCursor(6 + (10 * index_col),11 + (5 * index_lin));
				cout << char(192);
				MoveCursor(14 + (10 * index_col),11 + (5 * index_lin));
				cout << char(217);
			}
		} else if ((key == 80/*'d'*/) || (key == 's')) {//Down arrow or s
			if (index_lin < 6) {//Do not allow movement past bounds
				MoveCursor(6 + (10 * index_col),8 + (5 * index_lin));
				cout << " ";
				MoveCursor(14 + (10 * index_col),8 + (5 * index_lin));
				cout << " ";
				MoveCursor(6 + (10 * index_col),11 + (5 * index_lin));
				cout << " ";
				MoveCursor(14 + (10 * index_col),11 + (5 * index_lin));
				cout << " ";

				index_lin++;

				MoveCursor(6 + (10 * index_col),8 + (5 * index_lin));
				cout << char(218);
				MoveCursor(14 + (10 * index_col),8 + (5 * index_lin));
				cout << char(191);
				MoveCursor(6 + (10 * index_col),11 + (5 * index_lin));
				cout << char(192);
				MoveCursor(14 + (10 * index_col),11 + (5 * index_lin));
				cout << char(217);
			}			
		} else if (key == 'a') {//left arrow or a
			if (index_col > 0) {//Do not allow movement past bounds
				MoveCursor(6 + (10 * index_col),8 + (5 * index_lin));
				cout << " ";
				MoveCursor(14 + (10 * index_col),8 + (5 * index_lin));
				cout << " ";
				MoveCursor(6 + (10 * index_col),11 + (5 * index_lin));
				cout << " ";
				MoveCursor(14 + (10 * index_col),11 + (5 * index_lin));
				cout << " ";

				index_col--;

				MoveCursor(6 + (10 * index_col),8 + (5 * index_lin));
				cout << char(218);
				MoveCursor(14 + (10 * index_col),8 + (5 * index_lin));
				cout << char(191);
				MoveCursor(6 + (10 * index_col),11 + (5 * index_lin));
				cout << char(192);
				MoveCursor(14 + (10 * index_col),11 + (5 * index_lin));
				cout << char(217);
			}
		} else if (key == 'd') {//right arrow or d
			if (index_col < 6) {//Do not allow movement past bounds
				MoveCursor(6 + (10 * index_col),8 + (5 * index_lin));
				cout << " ";
				MoveCursor(14 + (10 * index_col),8 + (5 * index_lin));
				cout << " ";
				MoveCursor(6 + (10 * index_col),11 + (5 * index_lin));
				cout << " ";
				MoveCursor(14 + (10 * index_col),11 + (5 * index_lin));
				cout << " ";

				index_col++;

				MoveCursor(6 + (10 * index_col),8 + (5 * index_lin));
				cout << char(218);
				MoveCursor(14 + (10 * index_col),8 + (5 * index_lin));
				cout << char(191);
				MoveCursor(6 + (10 * index_col),11 + (5 * index_lin));
				cout << char(192);
				MoveCursor(14 + (10 * index_col),11 + (5 * index_lin));
				cout << char(217);
			}
		} else if (key == 13) {//enter key
			if (select == true) {
				numbers[index_lin][index_col] += numbers[old_lin][old_col];
				numbers[old_lin][old_col] = 0;
				
				for (int lin = 0; lin < 7; lin++) {
					for (int col = 0; col < 7; col++) {
						MoveCursor(9 + (col * 10), 9 + (lin * 5));
						cout << "  ";
						MoveCursor(9 + (col * 10), 9 + (lin * 5));
						cout << numbers[lin][col];
					}
				}
				select = false;
			} else {
				MoveCursor(6 + (10 * index_col),8 + (5 * index_lin));
				cout << char(201);
				MoveCursor(14 + (10 * index_col),8 + (5 * index_lin));
				cout << char(187);
				MoveCursor(6 + (10 * index_col),11 + (5 * index_lin));
				cout << char(200);
				MoveCursor(14 + (10 * index_col),11 + (5 * index_lin));
				cout << char(188);

				old_lin = index_lin;
				old_col = index_col;
				select = true;
			}
		}
	}

	//col move by 7, lin move by 5
	return;
}

//returns integer value of linked number commands
int StringSize(void) {
	string value = "";
	int index = 0;

	//find where the number starts
	for (int i = 0; i <= phrasebuffer[0].length(); i++) {
		if (phrasebuffer[0].substr(i,1) == " ") {
			index = i + 1;
			i = phrasebuffer[0].length() + 1;
		}
	}
	//get the full number
	for (int i = index; i <= phrasebuffer[0].length(); i++) {
		if (phrasebuffer[0].substr(i,1) != "") {
			value += phrasebuffer[0].substr(i,1);
		}
	}
	return(atoi(value.c_str())); //string -> int
}

//Finds the command in the input
void InputParser(void) {
	int index = 0;

	if (phrasebuffer[0].find("test") != string::npos) {//text found
		MoveCursor(2, 61);
		cout << "Test Successful.";
	} else if (phrasebuffer[0].find("number") != string::npos) {
		MoveCursor(2, 61);
		cout << "The value of the input is: " << StringSize();
	} else if (phrasebuffer[0].find("player.") != string::npos) {
		if (phrasebuffer[0].find("player.health") != string::npos) {
			MoveCursor(2, 61);
			Player.Health = StringSize();
			cout << "Player health has been set to " << StringSize() << ".";
		}
	} else if (phrasebuffer[0].find("run 10") != string::npos) {
		ReadStaticScreen("Minigame-Ten.txt");
		PrintStaticScreen();
		TenController();
	} 

	return;
}

//Control console history and text input
void ConsoleControl(void) {
	//7 lines history, 8 total
	int exit = 0;
	char key = 0;
	char last_key = 0;
	int index = 0;
	phrasebuffer[0] = "";

	//Write console marker
	MoveCursor(2, 59);
	cout << ">>";

	//Loops until enter key is pressed
	while (exit == 0) {
		key = getKeyPress(); //get key char val
		
		if (key != 0) {//A key is waiting to be processed
			if (key == 13) {//If key is enter key
				//Print shifter history
				for (int i = 0; i < 7; i++) {
					MoveCursor(2, 58 - i); 
					cout << "                                                                            ";
					MoveCursor(2, 58 - i);
					cout << phrasebuffer[i];
				}
				
				//Shift console history back
				for (int i = 6; i > 0; i--) {
					phrasebuffer[i] = phrasebuffer[i - 1];
				}

				//Remove text on input line
				MoveCursor(4,59);
				for (int i = 0; i < index; i++) {
					cout << " ";
				}

				//Break loop
				exit = 1;
			} else {//If key is regular key or backspace
				if (key != 8) {//If key is not backpace
					if (index < 74) {//If input text in within console input bounds
						cout << key;
						phrasebuffer[0] += key;
						key = 0;
						index += 1;
					}
				} else if (key == 8) {//If key is backspace
					if (index != 0) {//If something is written on the line
						MoveCursor(3 + index, 59);
						cout << " ";
						MoveCursor(3 + index, 59);
						phrasebuffer[0] = phrasebuffer[0].substr(0,index - 1);
						index--;
					}
				}
			}
		}
	}

	return;
}

//Create the console window and set up variables
void Initialize(void) {
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores consoles current dimensions
	MoveWindow(console, r.left, r.top, 800, 800, TRUE); //redraw
	
	//Set up console history
	phrasebuffer[0] = "";
	phrasebuffer[1] = "";
	phrasebuffer[2] = "";
	phrasebuffer[3] = "";
	phrasebuffer[4] = "";
	phrasebuffer[5] = "";
	phrasebuffer[6] = "";

	//Set up enemies
	test_enemy.Name = "Test Enemy";
	test_enemy.Health = 10;
	test_enemy.Mana = 10;
	test_enemy.Stamina = 10;
	test_enemy.Strength = 5;
	test_enemy.Agility = 5;
	test_enemy.Speed = 5;
	test_enemy.Armor = 1;
	test_enemy.Attack = 1;
	return;
}

//Reads current content of gamestate.txt
void ReadGameState(void) {
	ifstream myfile ("gamestate.txt"); //File stream
	int index = 0; //current file line from file to array

	while (myfile) { //reads file line by lune with $ end character
		getline(myfile, gamestate[index], '$');
		index++;
	}
	
	myfile.close();
	return;
}

//Prints current content of gamestate.txt to the console
void PrintGameState(void) {
	for (int i = 0; i < 61; i++) {//prints to console line by line, with offset fix
		if (i == 0) {
			MoveCursor(0,i);
		} else {
			MoveCursor(79,i-1);
		}
		cout << gamestate[i]; 		
	}

	return;
}

//Reads required text source
void ReadStaticScreen(string Screen) {
	ifstream file (Screen);

	for(int i = 0; i < 62; i++) {
		getline(file, statebuffer[i], '$');
	} 

	file.close();
	return;
}

//Prints from required text source
void PrintStaticScreen(void) {
	for (int i = 0; i < 61; i++) {//prints to console line by line, with offset fix
		if (i == 0) {
			MoveCursor(0,i);
		} else {
			MoveCursor(79,i-1);
		}
		cout << statebuffer[i]; 	
		statebuffer[i] = ""; //blank state buffer
	}



	return;
}

void ScreenWipe(int NewTextIndex) {
	//800x800, 80x61
	//int col_off = 0;

	//x wipe
	/*for (int exp = 0; exp < 40; exp--) {
		for (int lin = 0; lin < 61; lin++) {
			MoveCursor(40 - col_off, 
		}
	}
	*/

	for (int col = 0; col < 80; col++) {//current col
		for (int lin = 0; lin < 61; lin++) {//current lin
			MoveCursor(col,lin);
			cout << "|";
			
			if (col > 0) {
				MoveCursor(col - 1, lin);
				cout << "|";
				if (col > 1) {
					MoveCursor(col - 2, lin);
					cout << "-";
				}
			}
		}

		Sleep(1);
	}
	
	return;
}

//Control main options choice/start game
int MainScreenOptions(void) {
	int exit = 0;
	char key;
	int cur_col = 32;
	int cur_lin = 7;
	MoveCursor(cur_col, cur_lin);
	cout << ">";

	while (exit == 0) {
		key = getKeyPress();


		if ((key == 72/*'u'*/) || (key == 'w')) {//Up arrow or w
			if (cur_lin > 7) {
				MoveCursor(cur_col, cur_lin);
				cout << " ";
				MoveCursor(cur_col, cur_lin - 2);
				cur_lin -= 2;
				cout << ">";
			}
		} else if ((key == 80/*'d'*/) || (key == 's')) {//Down arrow or s
			if (cur_lin < 11) {
				MoveCursor(cur_col, cur_lin);
				cout << " ";
				MoveCursor(cur_col, cur_lin + 2);
				cur_lin += 2;
				cout << ">";
			}
		} else if (key == 13) {
			exit = 1;

			if (cur_lin == 7) {//start
				return(0);
			} else if (cur_lin == 9) {//load
				return(1);
			} else if (cur_lin == 11) {//exit
				return(2);
			}
		}
	}
}

//Move console cursor to specific spot
void MoveCursor(int col, int lin) {
	COORD coord;
	coord.X = col;
	coord.Y = lin;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	return;
}

//Check keyboard for key press
char getKeyPress() {
	char key = 127;
	key = _getch();
	/*
		if (key == 72) {//up arrow
			key = 'u';
		} else if (key == 75) {//left arrow
			key = 'l';
		} else if (key == 77) {//right arrow
			key = 'r';
		} else if (key == 80) {//down arrow
			key = 'd';
		}
	*/
	return key;
}