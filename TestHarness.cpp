// Graphs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include "Graph.h"
#include <iostream>

using namespace std;


bool isOneCharApart(std::string string1, std::string string2)
{
	const int FIRST = 0;
	const int SECOND = 1;
	const int THIRD = 2;

	//If the string is the same, no need to add it to the list
	if (string1 == string2)
	{
		return false;
	}

	//If two letters of the word are the same, add this value
	else if ((string1.at(FIRST) == string2.at(FIRST) &&
		string1.at(SECOND) == string2.at(SECOND)) ||

		(string1.at(SECOND) == string2.at(SECOND) &&
			string1.at(THIRD) == string2.at(THIRD)) ||

		(string1.at(THIRD) == string2.at(THIRD) &&
			string1.at(FIRST) == string2.at(FIRST)))
	{
		return true;
	}

	return false;
}

void PrintShortestPath(vector<string> shortestPath, string startWord, string endWord)
{
	//Print out the shortest path if it exists
	if (shortestPath.size() > 0)
	{
		cout << "The shortest path between " << startWord << " and " << endWord << " is : ";
		for (unsigned int i = 0; i < shortestPath.size(); i++)
		{
			cout << shortestPath[i] << " ";
		}
		cout << endl;
	}
	else
	{
		cout << "No shortest path between " << startWord << " and " << endWord << " found" << endl;
	}
}

int main()
{
	//Add start and end words
	string startWord = "dog";
	string endWord = "hat";

	//Create dictionary
	const int DICTIONARY_SIZE = 17;
	string dictionary[] = {"dog", "log", "bog", "cog", "dig", "dot", "doc", "cob", 
						   "lag", "hot", "hat", "ham", "bag", "tag", "hag", "lob",
						   "cab"};

	//Create a graph with the dictionary supplied
	//NOTE - all strings in dictionary must be three characters long for this implementation
	Graph myGraph;

	//Create all the new nodes for each item in the dictionary
	for (int i = 0; i < DICTIONARY_SIZE; i++)
	{
		myGraph.addNode(dictionary[i]);
	}

	//Record the connections for all nodes in the dictionary

	//start by examining each string one at a time
	for (int j = 0; j < DICTIONARY_SIZE; j++)
	{
		//for each string provided, find all other strings that are seperated by only one letter
		for (int i = 0; i < DICTIONARY_SIZE; i++)
		{
			if ( isOneCharApart(dictionary[j], dictionary[i]) )
			{
				//Add the string to the map
				myGraph.addConnection(dictionary[j], dictionary[i]);
			}
		}
	}


	//Find shortest path between two words
	vector<string> shortestPath = myGraph.findShortestPath(startWord, endWord);

	cout << "New test should print: dog, dot, hot, hat" << endl;
	PrintShortestPath(shortestPath, startWord, endWord);

	//Check with bad data
	endWord = "boo";
	shortestPath = myGraph.findShortestPath(startWord, endWord);
	cout << endl << "New test should not find a path" << endl;
	PrintShortestPath(shortestPath, startWord, endWord);

	endWord = "bag";
	shortestPath = myGraph.findShortestPath(startWord, endWord);
	cout<<endl<<"New test should print: dog, bog, bag" << endl;
	PrintShortestPath(shortestPath, startWord, endWord);

	//Wait so we can read the word
	system("pause");

    return 0;
}

