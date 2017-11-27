#pragma once

//This program creates a trie data structure and inputs the English dictionary into it
//Space complexity for the trie data structure is 26pn 
//	if p represents the byte size of each data value and n represents the number of nodes in the trie

#include "stdafx.h"
#include <string>
#include <vector>

#define NODEPTR TrieNode*

using namespace std;

class Trie
{
public:

	class TrieNode {
	public:
		TrieNode *nodeList[27];
		TrieNode();
	};

	bool insert(string word);
	int countHelper(NODEPTR p);
	int count();
	int getSizeHelper(NODEPTR p);
	int getSize();
	bool find(string word);
	int completeCountHelper(NODEPTR p);
	int completeCount(string word);
	vector<string> completeHelper(NODEPTR p, string s, vector<string> v, char c);
	vector<string> complete(string word);
	Trie();
	void destructorHelper(NODEPTR p);
	~Trie();

private:
	NODEPTR root;
};

