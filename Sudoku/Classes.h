#pragma once
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

template <typename T> class Move {
private:
	T value;
	int index;
public:
	Move();
	Move(T value, int index);

	void Set(T value, int index);

	T& Value();
	int& Index();
};

template <typename T> class Square {
private:
	T value;
	T prev_value;
	bool read_only;

public:
	Square();
	Square(T fieldValue);
	Square(T fieldValue, bool readOnly);

	void setField(T val);
	void setField(T val, bool readOnly);

	T& Value();
	T& PrevValue();
	bool& ReadOnly();
};


class SudokuBase {
private:
protected:
	std::vector<Square<char>> matrica;
	int printLineCount;
	Move<char> Undo;

	//pure virtual
	virtual void PrintMatrix() = 0;
	virtual void Opcije() = 0; 
	virtual void UndoMove() = 0; 
	virtual void MakeMove() = 0;

	bool CheckSolved(); //provera (najpre da li svaki ima vrednost, a ako ima onda se ide u proveru da li je sve tacno)
public:
	SudokuBase();
	virtual void Loop() = 0; //pure virtual
};

class SudokuCustom : public SudokuBase { //Ova klasa sluzi za kreiranje i cuvanje u datoteci
private:
	//std::string tableName;
protected:
	//preklopljene virtual iz SudokuBase
	void PrintMatrix();
	void Opcije(); //Ima osnovne opcije za setField i undo
	void UndoMove(); //Samo undo prethodnog poteza, bez stack-a
	void MakeMove();
	//preklopljene virtual iz SudokuBase

	void SaveToFile();
public:
	SudokuCustom();
	void Loop();
};

class SudokuPuzzle : public SudokuBase {
	//Ova klasa cita iz fajla i onda se resava
private:
	std::stack<Move<char>> UndoStack;
	std::stack<Move<char>> RedoStack;

	std::string stringPath = "";

protected:

	//preklopljene virtual iz SudokuBase
	void PrintMatrix(); //Read-only polja - crna sa belim tekstom 
	void Opcije();
	void UndoMove();
	void MakeMove();
	//preklopljene virtual iz SudokuBase

	void ReadFromFile();
	void ReadOnlyPrint(bool isReadOnly, int i, HANDLE hConsole); //Proverava da li je polje Read-Only. Poziva se unutar PrintMatrix
	void RedoMove();
	void PrintUndoStack();

public:
	SudokuPuzzle();

	void Loop();
};
