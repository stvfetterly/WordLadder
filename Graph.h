#pragma once
#include "stdafx.h"
#include <string>
#include <vector>
#include <list>
#include <map>

using namespace std;

class Node
{
	vector<Node*> m_connections;
	string m_data;
	bool m_found;				//used for searches, returns true if this node has already been found
	int m_distance;
	Node* m_parent;

public:
	const static int INFINITE = -1;

	Node();
	Node(string& data);

	//Accessor methods
	void found(const bool& newVal) { m_found = newVal; }
	bool found() const { return m_found; }

	void distance(const int& newVal) { m_distance = newVal; }
	int distance() const { return m_distance; }

	void parent(Node* newVal) { m_parent = newVal; }
	Node* parent() const { return m_parent; }

	void data(string& newVal) { m_data = newVal; }
	string data() const { return m_data; }

	void addConnection(Node* newVal) { m_connections.push_back(newVal); }
	vector<Node*> getConnection() const { return m_connections; }
};

class Graph
{
public:

	~Graph();

	vector<string> findShortestPath(string start, string end);
	
	bool isStringInGraph(string& data);

	void addNode(string& data);
	void addConnection(string& string1, string& string2);

private:
	vector<Node*> m_graphVector;

	Node* findNode(string& data);
};