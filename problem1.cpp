/*
	EECS 348 Lab 6 Problem 1
	Name: Theodore Athon
	ID: 3117304
	Creation Date: 10/18/2023
	This lab prints various matrix operations depending on an input file.
*/
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

vector<int> split(string str, string delimiter) {
	/* This function takes in a string, a delimeter, and returns an array of that string split by the delimter*/
	vector<int> v;
	if (!str.empty()) {
		int start = 0;
		do {
			int idx = str.find(delimiter, start);
			if (idx == string::npos) {
				break;
			}

			int length = idx - start;
			v.push_back(std::stoi(str.substr(start, length)));
			start += (length + delimiter.size());
		} while (true);
		v.push_back(std::stoi(str.substr(start)));
	}

	return v;
}

void printMatrix(vector<vector<int>> matrix) {
	/* This function prints a matrix to the terminal neatly. */
	int size = matrix.size();
	for (int j=0; j<size; j++) {
		for (int k=0; k<size; k++) {
			printf("%-5d", matrix[j].at(k));
		}
		std::cout << "\n";
	}
}

void addMatrix (vector<vector<int>> matrixOne, vector<vector<int>> matrixTwo) {
	/* This function takes in two matrices, adds them, and returns the sum as a matrix */
	vector<vector<int>> answer;
	if (matrixOne.size() != matrixTwo.size() || matrixOne[0].size() != matrixTwo[0].size()) {
		throw std::invalid_argument("Input arrays must be the same size and dimensions!");
	}
	for (int i=0; i<matrixOne.size(); i++) {
		vector<int> row;
		for (int j=0; j<matrixOne.size(); j++) {
			int sum = matrixOne[i].at(j) + matrixTwo[i].at(j);
			row.push_back(sum);
		}
		answer.push_back(row);
	}
	printMatrix(answer);
}

void subtractMatrix (vector<vector<int>> matrixOne, vector<vector<int>> matrixTwo) {
	/* This function takes in two matrices, adds them, and returns the difference as a matrix*/
	vector<vector<int>> answer;
	if (matrixOne.size() != matrixTwo.size() || matrixOne[0].size() != matrixTwo[0].size()) {
		throw std::invalid_argument("Input arrays must be the same size and dimensions!");
	}
	for (int i=0; i<matrixOne.size(); i++) {
		vector<int> row;
		for (int j=0; j<matrixOne.size(); j++) {
			int sum = matrixOne[i].at(j) - matrixTwo[i].at(j);
			row.push_back(sum);
		}
		answer.push_back(row);
	}
	printMatrix(answer);
}

void multiplyMatrix (vector<vector<int>> matrixOne, vector<vector<int>> matrixTwo) {
	/* this function takes in two matriecs, multiplies them, and then returns the matrix product as a matrix*/
	vector<vector<int>> answer;
	if (matrixOne.size() != matrixTwo.size() || matrixOne[0].size() != matrixTwo[0].size()) {
		throw std::invalid_argument("Input arrays must be the same size and dimensions!");
	}
	for (int i=0; i<matrixOne.size(); i++) {
		vector<int> rowVector;
		for (int j=0; j<matrixOne.size(); j++) {
			// new matrix (x,y)
			int product = 0;
			for (int k=0; k<matrixOne.size(); k++) {
				product = product + (matrixOne[i].at(k) * matrixTwo[k].at(j));
			}
			rowVector.push_back(product);
		}
		answer.push_back(rowVector);
	}
	printMatrix(answer);
}

int main (){
	/* The below logic reads the file and puts the data into two matrices. */
	std::ifstream inputFile;
	inputFile.open("matrix_input.txt");
	std::string line;
	static int size = 100; // size of square matrix NxN
	vector<vector<int>> matrixOne;
	vector<vector<int>> matrixTwo;
	if (inputFile.is_open()) {
		int i = 0;
		while (inputFile) {
			std::getline (inputFile, line);
			if (i == 0) {
				size = std::stoi(line);
			} else if (i > 0 && i <= size) { // first matrix
				vector<int> lineAsVector = split(line, " ");
				matrixOne.push_back(lineAsVector);
			} else if (i > size && i <= 2 * size) { // second matrix
				vector<int> lineAsVector = split(line, " ");
				matrixTwo.push_back(lineAsVector);
			}
			i++;
		}
	}

	std::cout << "\nTed Athon\n" << "Lab #6: Matrix Manipulation\n" "\nMatrix A:\n";
	printMatrix(matrixOne); // print first matrix
	std::cout << "\nMatrix B:\n";
	printMatrix(matrixTwo); // print second matrix
	std::cout << "\nMatrix Sum (A+B):\n";
	addMatrix(matrixOne, matrixTwo); // add the two matrices
	std::cout << "\nMatrix Product (A*B):\n";
	multiplyMatrix(matrixOne, matrixTwo); // multiply the two matrices
	std::cout << "\nMatrix Difference (A-B):\n";
	subtractMatrix(matrixOne, matrixTwo); // subtract the two matrices


	return 0;
}