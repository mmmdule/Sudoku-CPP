#include "Klase.h"
#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <windows.h>
#include <wincon.h>
#include <iosfwd>
#include <fstream>
#include <vector>
#include <stack>
#include <ctype.h>
#include <cstdio>
#include <conio.h>
#include <algorithm>
#include <string>
#include <filesystem>     
#include <stdlib.h>     /* srand, rand */
#include <time.h>		/* time */

void TitleScreen();
void MenuOption();
void Puzzle(SudokuBase* SP);
void Custom(SudokuBase* SC);

int main(int argc, char* argv[]) {
	SetWindowLongPtr(GetConsoleWindow(), GWL_STYLE, WS_POPUP); //Uklanja Top Bar
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE); //Maximize za prozor
	system("Color F0"); //Bela pozadina, crni tekst
	
	TitleScreen();
	

	srand(time(NULL)); //seed za random citanje

	SudokuBase* Sudoku = NULL;

	
	while (true) {
		MenuOption();
		char opcija;
		opcija = _getch();
		opcija = tolower(opcija);

		switch (opcija) {
		case '1':
			Puzzle(Sudoku);
			break;
		case '2':
			Custom(Sudoku);
			break;
		case '3':
			return 0;
			break;
		default:
			std::wcout << "Neispravan unos. Izaberite opciju 1, 2 ili 3." << std::endl;
			_getch();
			break;
		}

	}
	

	return 0;
}

void TitleScreen() {
	std::wcout << " ######  ##     ## ########   #######  ##    ## ##     ## \n";	Sleep(200);
	std::wcout << "##    ## ##     ## ##     ## ##     ## ##   ##  ##     ## \n";	Sleep(200);
	std::wcout << "##       ##     ## ##     ## ##     ## ##  ##   ##     ## \n";	Sleep(200);
	std::wcout << " ######  ##     ## ##     ## ##     ## #####    ##     ## \n";	Sleep(200);
	std::wcout << "      ## ##     ## ##     ## ##     ## ##  ##   ##     ## \n";	Sleep(200);
	std::wcout << "##    ## ##     ## ##     ## ##     ## ##   ##  ##     ## \n";	Sleep(200);
	std::wcout << " ######   #######  ########   #######  ##    ##  #######  \n\n"; Sleep(200);

	system("pause");
}

void MenuOption() {
	system("cls");
	

	std::wcout << "Glavni Meni\n-----------\n\n";
	Sleep(150);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	std::wcout << "Opcije:  \n1. ";
	Sleep(150);
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	std::wcout << "Igra";
	Sleep(150);
	SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); //set back to black background and white text
	std::wcout << "\t\n\n2. ";
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	Sleep(150);
	std::wcout << "Kreiranje";
	SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); //set back to black background and white text
	std::wcout << "\t\n\n3. ";
	Sleep(150);
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	std::wcout << "Izlaz" << std::endl << std::endl;
	SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); //set back to black background and white text
}

void Puzzle(SudokuBase* SP) {

	int exit = -1;


	//SudokuPuzzle SP;
	delete SP;
	SP = new SudokuPuzzle();
	while (exit != 0) {
		SP->Loop();

		std::wcout << std::endl << "Nova igra? (y/n)" << std::endl;
		int input = 0;
		while (input == 0) {
			char slovo;
			slovo = _getch();
			slovo = tolower(slovo);

			switch (slovo) {
			case 'y':
				input = 1;
				break;
			case 'n':
				input = 1;
				exit = 0;
				break;
			default:
				std::wcout << "Neispravan unos. Izaberite opciju Y ili N.\n\nNova igra? (y/n)" << std::endl;
				break;
			}
		}

	}
	;	//SudokuPuzzle

	delete SP;
}

void Custom(SudokuBase* SC) {
	int exit = -1;

	delete SC;
	SC = new SudokuCustom();
	
	SC->Loop();

	;
	delete SC;
}