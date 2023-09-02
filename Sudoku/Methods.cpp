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




//KORISTI WCOUT umesto cout kada je MOD POSTAVLJEN NA  _O_U16TEXT

//Template Klasa Potez
template <typename T> Potez<T>::Potez()
{

}
template<typename T>
Potez<T>::Potez(T value, int index)
{
	this->value = value;
	this->index = index;
}
template<typename T>
void Potez<T>::Set(T value, int index)
{
	this->value = value;
	this->index = index;
}
template<typename T>
T & Potez<T>::Value()
{
	return value;
}
template<typename T>
int & Potez<T>::Index()
{
	return index;
}
//Template Klasa Potez

//Template Klasa Polje
template <typename T> Polje<T>::Polje()
{
	this->read_only = false;
}

template <typename T> Polje<T>::Polje(T fieldValue)
{
	this->prev_value = NULL;
	this->value = fieldValue;
	this->read_only = false;
}

template <typename T> Polje<T>::Polje(T fieldValue, bool readOnly)
{
	this->prev_value = NULL;
	this->value = fieldValue;
	this->read_only = readOnly;
}

template <typename T> void Polje<T>::setField(T val)
{
	if (!this->read_only) {
		this->prev_value = this->value;
		this->value = val;
	}		
}

template <typename T> bool& Polje<T>::ReadOnly()
{
	return read_only;
}

template <typename T> void Polje<T>::setField(T val, bool ReadOnly)
{
	read_only = ReadOnly;
	prev_value = value;
	value = val;
}

template <typename T> T& Polje<T>::Value()
{
	return this->value;
}

template <typename T> T& Polje<T>::PrevValue()
{
	return this->prev_value;
}
//Template Klasa Polje

//Klasa SudokuBase
SudokuBase::SudokuBase() {
	printLineCount = 0;
	matrica.resize(81);
	for (int i = 0; i < 81; i++)
		matrica.at(i).setField('0', false);
	Undo.Value() = 'x';
}





bool SudokuBase::CheckSolved()
{
	bool isSolved = false;

	std::vector<char> vect[9];
	int j = 0;



	//provera horizontalno
	for (int i = 0; i < 81; i++) {
		vect[j].push_back(matrica.at(i).Value());
		if ((i + 1) % 9 == 0)
			j++;
		if (!(matrica.at(i).Value() >= '1' && matrica.at(i).Value() <= '9'))
			return false;
	}

	for (int i = 0; i < 9; i++) {
		std::sort(vect[i].begin(), vect[i].end());
		const bool hasDuplicates = std::adjacent_find(vect[i].begin(), vect[i].end()) != vect[i].end();
		if (hasDuplicates)
			return false;
	}
	//provera horizontalno

	//provera vertikalno
	j = 0;
	for (int i = 0; i < 9; i++) {
		vect[i].clear();
	}

	for (int i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++)
			vect[i].push_back(matrica.at(i + (9 * j)).Value());
	}

	for (int i = 0; i < 9; i++) {
		std::sort(vect[i].begin(), vect[i].end());
		const bool hasDuplicates = std::adjacent_find(vect[i].begin(), vect[i].end()) != vect[i].end();
		if (hasDuplicates)
			return false;
	}

	//provera vertikalno
	return true;
}
//Klasa SudokuBase

//Klasa SudokuPuzzle
SudokuPuzzle::SudokuPuzzle() {
	for (int i = 0; i < 81; i++)
			matrica.at(i).setField('X', false);
}

void SudokuPuzzle::Opcije()
{
	_setmode(_fileno(stdout), _O_U16TEXT); // UTF-8
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	std::wcout << "Opcije:  ";
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED); //Tamna pozadina, svetli tekst
	std::wcout << "(S)et";
	SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); //Svetla pozadina, tamni tekst
	std::wcout << "\t";
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED); //Tamna pozadina, svetli tekst
	std::wcout << "(U)ndo";
	SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); //Svetla pozadina, tamni tekst
	std::wcout << "\t";
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED); //Tamna pozadina, svetli tekst
	std::wcout << "(R)edo";
	SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); //Svetla pozadina, tamni tekst
	std::wcout << "\t";
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED); //Tamna pozadina, svetli tekst
	std::wcout << "(E)xit";
	SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); //Svetla pozadina, tamni tekst
	std::wcout << " ";
	std::wcout << std::endl << std::endl;
}

void SudokuPuzzle::ReadOnlyPrint(bool isReadOnly, int i, HANDLE hConsole) {
	if (isReadOnly) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		std::wcout << matrica.at(i).Value();
		SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	}
	else
		std::wcout << matrica.at(i).Value();
}



void SudokuPuzzle::PrintMatrix() {
	_setmode(_fileno(stdout), _O_U16TEXT); // UTF-8
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int i = 0;
	char slovo = 'A';
	int tmp = 0;

	std::wcout << L"   1 2 3 4 5 6 7 8 9 " << std::endl;
	std::wcout << L"  ╔═╦═╦═╦═╦═╦═╦═╦═╦═╗" << std::endl;

	for (i = 0; i < 9; i++) {
		std::wcout << slovo << L" ║";


		for (int j = tmp; j < tmp+9; j++) {

			this->ReadOnlyPrint(matrica.at(j).ReadOnly(), j, hConsole);
			if( (j+1) % 3 == 0 )
				std::wcout << L"║";
			else
				std::wcout << L"│";

			if ((tmp + 9) - j == 1) {
				tmp = j + 1;
				break;
			}
		}

		std::wcout << std::endl; 
		if (printLineCount < 9) {
			printLineCount++;
			Sleep(135);
		}
		if (i == 2 || i == 5)
			std::wcout << L"  ╠═╬═╬═╬═╬═╬═╬═╬═╬═╣" << std::endl;
		slovo++;
	}
	std::wcout << L"  ╚═╩═╩═╩═╩═╩═╩═╩═╩═╝" << std::endl;
	Sleep(200);
}

void SudokuPuzzle::ReadFromFile() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	_setmode(_fileno(stdout), _O_U16TEXT);
	matrica.clear();

	system("cls");
	bool readCustom = false;
	char broj = ' ';
	
	std::fstream inStream;


	char confirm = ' ';
	while (confirm != 'y' && confirm != 'n') {
		std::wcout << "\nDa li zelite da ucitate sacuvanu matricu? (y/n)\n";
		confirm = _getch();
		confirm = tolower(confirm);
		if (confirm != 'y' && confirm != 'n')
			std::wcout << "Izaberite opciju Y ili N.\n";
		else if (confirm == 'n') {
			readCustom = false;
		}
		else {
			readCustom = true;
		}
			
	}
	system("cls");
	if (readCustom) {
		std::wcout << "Lista datoteka:\n--------------------------------------\n\n";
		std::string path = "./Tables/Custom/";
		for (const auto & entry : std::experimental::filesystem::directory_iterator(path))
			std::wcout << entry.path().filename() << std::endl;

		std::wcout << std::endl << std::endl;
		std::string tmpPath = "";
		std::wcout << "Unesite ime datoteke:\n";

		std::getline(std::cin, tmpPath);

		bool exists = std::experimental::filesystem::exists(path + tmpPath + ".csv");
		while (!exists) {
			std::cin.clear();

			_setmode(_fileno(stdout), _O_TEXT);
			std::cout << "Datoteka \"" << tmpPath << ".csv\" nije pronadjena.\nUnesite ime datoteke ponovo.\n\n";
			_setmode(_fileno(stdout), _O_U16TEXT);
			std::getline(std::cin, tmpPath);
			std::cin.clear();

			
			exists = std::experimental::filesystem::exists(path + tmpPath + ".csv");
		}
		inStream.open(path + tmpPath + ".csv");
	}
	else {
		std::wcout << "Izaberite tezinu: (1 do 3)\n" << std::endl << "1. ";
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		std::wcout << "Lako";
		SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); //set back to black background and white text
		std::wcout << "\n\n2. ";
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		std::wcout << "Srednje";
		SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); //set back to black background and white text
		std::wcout << "\n\n3. ";
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		std::wcout << "Tesko";
		SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); //set back to black background and white text
		std::wcout << " ";
		std::wcout << std::endl << std::endl;

		broj = ' ';

		broj = _getch();

		//For Debugging
		//std::wcout << std::to_wstring(broj) << "\n";
				
		while (broj <= '1' && broj >= '3' && broj != 's' && broj != 'S') {
			std::wcout << "Neispravan broj tezine! Unesite ponovo. (1 do 3)" << std::endl;
			broj = _getch();

		}
		stringPath.clear();
		stringPath.append("./Tables/");

		//For Debugging
		/*
		_setmode(_fileno(stdout), _O_TEXT);
		std::cout << stringPath << std::endl;
		_setmode(_fileno(stdout), _O_U16TEXT);
		*/
		//For Debugging

		switch (broj)
		{
		case '1':
			stringPath += "Easy/";
			break;
		case '2':
			stringPath += "Medium/";
			break;
		case '3':
			stringPath += "Hard/";
			break;
		case 's': case 'S':
			stringPath += "Solved/";
			break;
		default:
			break;
		}


		int count = 0;
		for (auto& p : std::experimental::filesystem::directory_iterator(stringPath)) {
			count++;
		}

		

		int fileNum = rand() % (count) + 1;
		;
		stringPath += std::to_string(fileNum);
		stringPath += ".csv";


		inStream.open(stringPath);

		
	}

	int i = 0;
	char c = inStream.get();
	while (!(inStream.eof())) {
		if (c == 'x') {
			matrica.push_back(Polje<char>(' ', false));

			i++;
		}
		else if (c != ',' && c != inStream.eof() && c != '\n') {
			matrica.push_back(Polje<char>(c, true));
			

			i++;
		}
		c = inStream.get();
	}

	inStream.close();

	system("cls");
}



void SudokuPuzzle::MakeMove()
{
	char slovo = 'a'; 
	char value = '1';
	char kolona;

	int multiplier = 0;

	std::wcout << "Unesite slovo reda: (A do I)" << std::endl;
	slovo = _getch(); 
	slovo = tolower(slovo);
	while (!(slovo >= 'a' && slovo <= 'i')) {
		std::wcout << "Neispravno slovo reda! Unesite ponovo. (A do I)" << std::endl;
		slovo = _getch();
		slovo = tolower(slovo);
	}

	std::wcout << "Unesite broj kolone: (1 do 9)" << std::endl;
	kolona = _getch();
	while (!(kolona - '0' >= 1 && kolona - '0' <= 9)) {
		std::wcout << "Neispravan broj kolone! Unesite ponovo. (1 do 9)" << std::endl;
		std::wcout << "Unesite broj kolone:" << std::endl;
		
		kolona = _getch(); 
	}
	
	
	
	switch (slovo) {
		case 'a':
			multiplier = 0;
			break;
		case 'b':
			multiplier = 1;
			break;
		case 'c':
			multiplier = 2;
			break;
		case 'd':
			multiplier = 3;
			break;
		case 'e':
			multiplier = 4;
			break;
		case 'f':
			multiplier = 5;
			break;
		case 'g':
			multiplier = 6;
			break;
		case 'h':
			multiplier = 7;
			break;
		case 'i':
			multiplier = 8;
			break;
		default:
			break;
	}

	multiplier = multiplier * 9 + ((kolona - '0') - 1);

	

	std::wcout << "Unesite novu vrednost za " << (char)toupper(slovo) << kolona << ":" << std::endl;
	value = _getch();
	while (!(value >= '1' && value <= '9')) {
		std::wcout << "Neispravna vrednost polja! Unesite ponovo (1 do 9)." << std::endl;
		value = _getch();
	}

	this->UndoStack.push(Potez<char>(matrica.at(multiplier).Value(), multiplier));

	this->matrica.at(multiplier).setField(value);

	
}
void SudokuPuzzle::UndoMove()
{
	if (UndoStack.empty())
		return;

	Potez<char> undoPotez = UndoStack.top();
	UndoStack.pop();

	while (!(RedoStack.empty()))
		RedoStack.pop();
	RedoStack.push(Potez<char>(matrica.at(undoPotez.Index()).Value(), undoPotez.Index()));

	matrica.at(undoPotez.Index()).PrevValue() = matrica.at(undoPotez.Index()).Value();
	matrica.at(undoPotez.Index()).Value() = undoPotez.Value();
}

void SudokuPuzzle::RedoMove()
{
	if (RedoStack.empty())
		return;

	Potez<char> redoPotez = RedoStack.top();
	RedoStack.pop();
	UndoStack.push(Potez<char>(matrica.at(redoPotez.Index()).Value(), redoPotez.Index()));
	matrica.at(redoPotez.Index()).PrevValue() = matrica.at(redoPotez.Index()).Value();
	matrica.at(redoPotez.Index()).Value() = redoPotez.Value();
}
void SudokuPuzzle::PrintUndoStack()
{
	std::wcout << UndoStack.size();
	std::wcout << "\n" << UndoStack.top().Value() << " " << UndoStack.top().Index() << "\n";
	std::wcout << "\n\n";
	system("pause");
}
void SudokuPuzzle::Loop()
{
	this->ReadFromFile();
	bool reseno = false;
	while (true)
	{
		
		system("cls");
		this->PrintMatrix();
		std::wcout << std::endl;
		this->Opcije();
		char opcija = _getch();
		opcija = tolower(opcija);
		switch (opcija) {
			case 's':
				this->MakeMove();
				reseno = this->CheckSolved();
				if (reseno) {
					system("cls");
					this->PrintMatrix();
					std::wcout << std::endl;
					std::wcout << "Uspesno reseno!\n\n"; 
					printLineCount = 0;
					system("pause");
					return; //0;
				}
				break;
			case 'u': //undo
				this->UndoMove();
				//SP.PrintUndoStack();
				break;
			case 'r':
				this->RedoMove();
				break;
			case 'e':
				std::wcout << std::endl << "EXITING" << std::endl;
				printLineCount = 0;
				system("pause");
				return; //0;
			default:
				break;
		}
		
	}
}
//Klasa SudokuPuzzle

//Klasa SudokuCustom
void SudokuCustom::PrintMatrix()
{
	

	_setmode(_fileno(stdout), _O_U16TEXT); // UTF-8
	

	int i = 0;
	char slovo = 'A';
	int tmp = 0;

	std::wcout << L"   1 2 3 4 5 6 7 8 9 " << std::endl;
	std::wcout << L"  ┌─┬─┬─┬─┬─┬─┬─┬─┬─┐" << std::endl;


	bool slovoPrint = false;
	for (i = 0; i < 81; i++) {
		if (!slovoPrint) {
			std::wcout << slovo << L" │";
			slovoPrint = true;
		}

		std::wcout << matrica.at(i).Value();
		std::wcout << L"│";


		if ((i + 1) % 9 == 0) {
			std::wcout << std::endl;
			slovoPrint = false;
			slovo++; 
			if (printLineCount < 9) {
				printLineCount++;
				Sleep(135);
			}
		}

		if ((i + 1) % 9 == 0 && ((i + 1) / 9 == 3 || (i + 1) / 9 == 6))
			std::wcout << L"  ├─┼─┼─┼─┼─┼─┼─┼─┼─┤" << std::endl;
	}
	std::wcout << L"  └─┴─┴─┴─┴─┴─┴─┴─┴─┘" << std::endl;
}


void SudokuCustom::Opcije()
{
	_setmode(_fileno(stdout), _O_U16TEXT); // UTF-8
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);



	std::wcout << "Opcije:  ";
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED); //Tamna pozadina, svetli tekst
	std::wcout << "(S)et";
	SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); //Svetla pozadina, tamni tekst
	std::wcout << " " << " ";
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED); //Tamna pozadina, svetli tekst
	std::wcout << "(F)inish";
	SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); //Svetla pozadina, tamni tekst
	std::wcout << " " << " ";
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED); //Tamna pozadina, svetli tekst
	std::wcout << "(U)ndo";
	SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); //Svetla pozadina, tamni tekst
	std::wcout << " " << " "; 
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED); //Tamna pozadina, svetli tekst
	std::wcout << "(E)xit" << std::endl << std::endl;
	SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); //Svetla pozadina, tamni tekst
}

void SudokuCustom::UndoMove()
{
	if (Undo.Value() == 'x')
		return;

	Potez<char> undoPotez = Undo;


	matrica.at(undoPotez.Index()).PrevValue() = matrica.at(undoPotez.Index()).Value();
	matrica.at(undoPotez.Index()).Value() = undoPotez.Value();

	Undo.Value() = 'x';
}
void SudokuCustom::MakeMove()
{
	char slovo = 'a';
	char value = '1';
	char kolona;

	int multiplier = 0;

	std::wcout << "Unesite slovo reda: (A do I)" << std::endl;
	slovo = _getch();
	slovo = tolower(slovo);
	while (!(slovo >= 'a' && slovo <= 'i')) {
		std::wcout << "Neispravno slovo reda! Unesite ponovo. (A do I)" << std::endl;
		slovo = _getch();
		slovo = tolower(slovo);
	}

	std::wcout << "Unesite broj kolone: (1 do 9)" << std::endl;
	kolona = _getch();
	while (!(kolona - '0' >= 1 && kolona - '0' <= 9)) {
		std::wcout << "Neispravan broj kolone! Unesite ponovo. (1 do 9)" << std::endl;
		std::wcout << "Unesite broj kolone:" << std::endl;

		kolona = _getch();
	}



	switch (slovo) {
	case 'a':
		multiplier = 0;
		break;
	case 'b':
		multiplier = 1;
		break;
	case 'c':
		multiplier = 2;
		break;
	case 'd':
		multiplier = 3;
		break;
	case 'e':
		multiplier = 4;
		break;
	case 'f':
		multiplier = 5;
		break;
	case 'g':
		multiplier = 6;
		break;
	case 'h':
		multiplier = 7;
		break;
	case 'i':
		multiplier = 8;
		break;
	default:
		break;
	}

	multiplier = multiplier * 9 + ((kolona - '0') - 1);



	std::wcout << "Unesite novu vrednost za " << (char)toupper(slovo) << kolona << ":" << std::endl;
	value = _getch();
	while (!(value >= '1' && value <= '9')) {
		std::wcout << "Neispravna vrednost polja! Unesite ponovo (1 do 9)." << std::endl;
		value = _getch();
	}

	Undo = Potez<char>(matrica.at(multiplier).Value(), multiplier);

	this->matrica.at(multiplier).setField(value);

}

void SudokuCustom::SaveToFile()
{
	_setmode(_fileno(stdout), _O_TEXT);

	char confirm = ' ';
	while (confirm != 'y' && confirm != 'n') {
		std::cout << "Da li zelite da sacuvate? (y/n)\n";
		confirm = _getch();
		confirm = tolower(confirm);
		if (confirm != 'y' && confirm != 'n')
			std::cout << "Izaberite opciju Y ili N.\n";
		else if (confirm == 'n')
			return;
	}

	_setmode(_fileno(stdout), _O_U16TEXT);

	std::string saveName = "./Tables/Custom/";

	std::string fileName = "";
	while (fileName.length() == 0) {
		std::wcout << "\nUnesite ime datoteke:\n";
		std::getline(std::cin, fileName);
	}


	saveName += fileName;
	saveName += ".csv";
	std::fstream inStream;
	inStream.open(saveName, std::fstream::out);

	for (int i = 0; i < 81; i++) {
		if (matrica.at(i).Value() == ' ')
			inStream.put('x');
		else
			inStream.put(matrica.at(i).Value());

		if (i < 80 && ((i + 1) % 9 != 0))
			inStream.put(',');

		if ((i + 1) % 9 == 0)
			inStream.put('\n');
	}

	inStream.close();

	std::wcout << "Uspesno sacuvano!\n";
	_getch();
	for (int i = 0; i < 81; i++)
		matrica.at(i).setField(' ', false);
	system("cls");

	Sleep(200);
}

SudokuCustom::SudokuCustom() {
	for (int i = 0; i < 81; i++)
		matrica.at(i).setField(' ', false);
}

void SudokuCustom::Loop()
{
	system("cls");
	



	_setmode(_fileno(stdout), _O_U16TEXT);
	

	while (true)
	{

		system("cls");

		this->PrintMatrix();
		std::wcout << std::endl;

		this->Opcije();

		char opcija = _getch();
		opcija = tolower(opcija);
		switch (opcija) {
		case 's':
			this->MakeMove();
			break;
		case 'u':
			this->UndoMove();
			break;
		case 'f':
			this->SaveToFile();
			break;
		case 'e':
			std::wcout << std::endl << "EXITING" << std::endl;
			printLineCount = 0;
			system("pause");
			return; //0;
		default:
			break;
		}

	}
	return; //0;
}
//Klasa SudokuCustom