// Project3.cpp : Defines the entry point for the console application.
//This program creates a trie data structure and inputs the English dictionary into it
//Space complexity for the trie data structure is 26pn 
//	if p represents the byte size of each data value and n represents the number of nodes in the trie

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>

#include "Trie.h"

using namespace std;

void memoryTester();

int main()
{
	//test function used to test for memory leaks
	memoryTester();
	
	//constructing a trie and putting in the English dictionary from the text file
	Trie t;
	string s;
	fstream input("wordlist_windows.txt");
	if (!input.is_open()) 
		cout << "Could not open file" << endl;
	else {
		while (!input.eof()) {
			getline(input, s);
			t.insert(s);
		}
	}
	input.close();

	//while loop that asks for input and can display the word completions for that input
	int count;
	vector<string> vec;
	string typein;
	string answer;
	cout << "Please enter a word prefix (or enter a number to exit): ";
	cin >> typein;
	//while loop that checks for correct input
	if (isalpha(typein.at(0))) {
		bool b = false;
		while (!b) {
			b = true;
			for (int i = 1; i < typein.length(); i++) {
				if (isdigit(typein.at(i)))
					b = false;
			}
			if (!b) {
				cout << "Input Error:  Please enter a word prefix (or enter a number to exit): ";
				cin >> typein;
			}
			if (isdigit(typein.at(0)))
				b = true;
		}
	}
	//counts the number of words completions and asks to display them
	while (!isdigit(typein.at(0))) {
		count = t.completeCount(typein);
		cout << "There are " << count << " completions for the prefix '" << typein << "'.  Show completions? ";
		cin >> answer;
		if (answer == "Y" || answer == "y" || answer == "yes" || answer == "Yes") {
			vec = t.complete(typein);
			for (vector<string>::iterator i = vec.begin(); i != vec.end(); i++) {
				cout << *i << endl;
			}
			cout << endl;
		}
		//checks again for correct input
		cout << "Please enter a word prefix (or enter a number to exit): ";
		cin >> typein;
		if (isalpha(typein.at(0))) {
			bool b = false;
			while (!b) {
				b = true;
				for (int i = 1; i < typein.length(); i++) {
					if (isdigit(typein.at(i)))
						b = false;
				}
				if (!b) {
					cout << "Input Error:  Please enter a word prefix (or enter a number to exit): ";
					cin >> typein;
				}
				if (isdigit(typein.at(0)))
					b = true;
			}
		}
	}

	system("PAUSE");
    return 0;
}

//memory test function creates 3 tries and inputs the english language into them.
void memoryTester() {
	Trie t1;
	string s;
	fstream input("wordlist_windows.txt");
	if (!input.is_open())
		cout << "Could not open file" << endl;
	else {
		while (!input.eof()) {
			getline(input, s);
			t1.insert(s);
		}
	}
	input.close();

	Trie t2;
	fstream input1("wordlist_windows.txt");
	if (!input1.is_open())
		cout << "Could not open file" << endl;
	else {
		while (!input1.eof()) {
			getline(input1, s);
			t2.insert(s);
		}
	}
	input1.close();
	
	Trie t3;
	fstream input2("wordlist_windows.txt");
	if (!input2.is_open())
		cout << "Could not open file" << endl;
	else {
		while (!input2.eof()) {
			getline(input2, s);
			t3.insert(s);
		}
	}
	input2.close();
}
