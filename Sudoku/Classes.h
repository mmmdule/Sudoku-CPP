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
	std::vector<Square<char>> matrix;
	int printLineCount;
	Move<char> Undo;

	// Pure virtual functions
	virtual void PrintMatrix() = 0;
	virtual void Options() = 0;
	virtual void UndoMove() = 0;
	virtual void MakeMove() = 0;

	bool CheckSolved(); // Check if the puzzle is solved (first, whether each square has a value, and then if it's all correct)
public:
	SudokuBase();
	virtual void Loop() = 0; // Pure virtual function
};

class SudokuCustom : public SudokuBase { // This class is used for creating and saving to a file
private:
protected:
	// Overridden virtual functions from SudokuBase
	void PrintMatrix();
	void Options(); // Basic options for setField and undo
	void UndoMove(); // Undo the previous move without using a stack
	void MakeMove();

	void SaveToFile();
public:
	SudokuCustom();
	void Loop();
};

class SudokuPuzzle : public SudokuBase {
	// This class reads from a file and then solves the puzzle
private:
	std::stack<Move<char>> UndoStack;
	std::stack<Move<char>> RedoStack;

	std::string stringPath = "";

protected:

	// Overridden virtual functions from SudokuBase
	void PrintMatrix(); // Read-only fields - black background with white text 
	void Options();
	void UndoMove();
	void MakeMove();

	void ReadFromFile();
	void ReadOnlyPrint(bool isReadOnly, int i, HANDLE hConsole); // Check if the field is Read-Only. Called within PrintMatrix
	void RedoMove();
	void PrintUndoStack();

public:
	SudokuPuzzle();

	void Loop();
};
