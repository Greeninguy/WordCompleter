//This program creates a trie data structure and inputs the English dictionary into it
//Space complexity for the trie data structure is 26pn 
//	if p represents the byte size of each data value and n represents the number of nodes in the trie

#include "stdafx.h"
#include <string>
#include <iostream>

#include "Trie.h"

using namespace std;

/*  
insert member function enters the word inputted into the alphabet trie
The asymptotic runtime for this function is Omega(n) where n represents the string length
*/
bool Trie::insert(string word)
{
	NODEPTR p = root;
	int answer;

	for (int i = 0; i < word.length(); i++) {
		char c = word.at(i);
		answer = c - 'a';
		if (p->nodeList[answer])
			p = p->nodeList[answer];
		else {
			p->nodeList[answer] = new TrieNode;
			p = p->nodeList[answer];
		}
	}
	if (p->nodeList[26] != nullptr) {
	cout << "This word is already in the trie" << endl;
	return false;
	}	
	else {
		p->nodeList[26] = new TrieNode;
		return true;
	}
}

/*
countHelper function used by the count function to recursively traverse the tree and count the words
The asymptotic runtime for this function is Omega(n) where n represents how many nodes are in the trie
*/
int Trie::countHelper(NODEPTR p)
{
	int count = 0;
	if (p->nodeList[26])
		count++;
	for (int i = 0; i < 26; i++) {
		if (p->nodeList[i])
			count += countHelper(p->nodeList[i]);
	}
	return count;
}

/*
count member function counts and returns the number of words in the trie
Uses the countHelper function
The asymptotic runtime for this is Omega(n) since it uses the countHelper function
*/
int Trie::count()
{
	int count = 0;
	for (int i = 0; i < 26; i++) {
		if (root->nodeList[i]) 
			count += countHelper(root->nodeList[i]);		
	}
	return count;
}

/*
getSizeHelper function is used by the getSize function to recursively traverse the trie
The asymptotic runtime for this function is Omega(n) where n represents the number of nodes in trie
*/
int Trie::getSizeHelper(NODEPTR p)
{
	int size = 1;
	if (p->nodeList[26])
		size++;
	for (int i = 0; i < 26; i++) {
		if (p->nodeList[i])
			size += getSizeHelper(p->nodeList[i]);
	}
	return size;
}

/*
getSize function counts and returns the number of nodes in the trie
Uses the getSizeHelper function
The asymptotic runtime for this function is Omega(n) since it uses the getSizeHelper
*/
int Trie::getSize()
{
	int size = 1;
	for (int i = 0; i < 26; i++) {
		if (root->nodeList[i])
			size += getSizeHelper(root->nodeList[i]);
	}
	return size;
}

/*
find function takes an inputted word and checks if it is in the tree
returns true if the word is found and returns false if otherwise
The asymptotic runtime for this function is Omega(n) where n represents the number of characters in the inputted string
*/
bool Trie::find(string word)
{
	NODEPTR p = root;
	int c, answer;
	for (int i = 0; i < word.length(); i++) {
		c = word.at(i);
		answer = c - 'a';
		if (p->nodeList[answer]) 
			p = p->nodeList[answer];
		else
			return false;		
	}
	if (p->nodeList[26])
		return true;
	return false;
}

/*
completeCountHelper function is used by the completeCount function to recursively traverse the subtree of inputted string
The asymptotic runtime for this function is Omega(n) for the worst case scenario where n represents the number of nodes in the trie
*/
int Trie::completeCountHelper(NODEPTR p)
{
	int count = 0;
	if (p->nodeList[26])
		count++;
	for (int i = 0; i < 26; i++) {
		if (p->nodeList[i])
			count += completeCountHelper(p->nodeList[i]);
	}
	return count;
}

/*
completeCount function counts and returns the number of words that stems off the inputted string
uses the completeCountHelper function
The asymptotic runtime for this function is Omega(n) since it uses the completeCountHelper function
*/
int Trie::completeCount(string word)
{
	NODEPTR p = root;
	int answer, c;
	int count = 0;
	for (int i = 0; i < word.length(); i++) {
		c = word.at(i);
		answer = c - 'a';
		if (p->nodeList[answer])
			p = p->nodeList[answer];
		else
			return 0;
	}
	if (p->nodeList[26])
		count++;
	for (int i = 0; i < 26; i++) {
		if (p->nodeList[i])
			count += completeCountHelper(p->nodeList[i]);
	}
	return count;
}

/*
completeHelper function is used by the complete function to recursively traverse the subtree of the inputed string
The asymptotic runtime for this function's worse case scenario is Omega(n) where n represents the number of nodes in the trie
*/
vector<string> Trie::completeHelper(NODEPTR p, string s, vector<string> v, char c)
{
	s += c;
	if (p->nodeList[26])
		v.push_back(s);
	for (int i = 0; i < 26; i++) {
		if (p->nodeList[i]) {
			char c = char(i + 97);
			v = completeHelper(p->nodeList[i], s, v, c);
		}
			
	}
	return v;
}

/*
complete function returns a vector of all of the words in the trie that stem off the inputted string
Uses the completeHelper function
The asymptotic runtime for this function's worst case scenario is Omega(n) since it uses the completeHelper function
*/
vector<string> Trie::complete(string word)
{
	char stringAdd;
	string s = word;
	vector<string> v;
	vector<string> *vecPointer;
	NODEPTR p = root;
	int answer, c;
	int count = 0;
	for (int i = 0; i < word.length(); i++) {
		c = word.at(i);
		answer = c - 'a';
		if (p->nodeList[answer])
			p = p->nodeList[answer];
		else
			return v;
	}
	if (p->nodeList[26]) 
		v.push_back(s);
	for (int i = 0; i < 26; i++) {
		if (p->nodeList[i]) {
			char c = char(i + 97);
			v = completeHelper(p->nodeList[i], s, v, c);
		}	
	}
	return v;
}

/*
The constructor for the trie creates a root node
*/
Trie::Trie()
{
	root = new TrieNode();
}

/*
destructorHelper function is used by the trie's destructor function to recursively traverse the tree
Deletes all of the nodes while traversing the tree
The asymptotic runtime for this function is Omega(n) where n represents the number of nodes in the tree
*/
void Trie::destructorHelper(NODEPTR p)
{
	NODEPTR d;
	if (p->nodeList[26]) {
		d = p->nodeList[26];
		delete d;
	}

	for (int i = 0; i < 26; i++) {
		if (p->nodeList[i])
			destructorHelper(p->nodeList[i]);
	}
	delete p;
}

/*
The trie's destructor function uses the destructorHelper function to delete all the nodes in the trie
The asymptotic runtime for this function is Omega(n) since it uses the detructorHelper function
*/
Trie::~Trie()
{
	for (int i = 0; i < 26; i++) {
		if (root->nodeList[i])
			destructorHelper(root->nodeList[i]);
	}
	delete root;
}

/*
The constructor for a node in the trie initializes the 26 array to have null pointers
*/
Trie::TrieNode::TrieNode()
{
	for (int i = 0; i < 27; i++) {
		this->nodeList[i] = nullptr;
	}
}
