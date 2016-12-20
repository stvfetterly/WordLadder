#include "stdafx.h"
#include "Graph.h"
#include <queue>
#include <algorithm>

//Checks for a node of particular name in the graph, returns the node if it exists otherwise returns NULL
Node* Graph::findNode(string& data)
{
	for (unsigned int i = 0; i < m_graphVector.size(); i++)
	{
		if (m_graphVector[i]->data() == data)
		{
			return m_graphVector[i];
		}
	}
	
	return NULL;
}

//returns true if a given string has already been added to the graph
bool Graph::isStringInGraph(string& data)
{
	for (unsigned int i = 0; i < m_graphVector.size(); i++)
	{
		if (m_graphVector[i]->data() == data)
		{
			return true;
		}
	}

	return false;
}

//Adds a new node into the graph
void Graph::addNode(string& data)
{
	Node* newNode = new Node();

	newNode->data(data);

	m_graphVector.push_back(newNode);
}

//
void Graph::addConnection(string& string1, string& string2)
{
	bool bool1 = true;
	bool bool2 = true;

	Node* node1 = findNode(string1);
	Node* node2 = findNode(string2);

	//if either string fails to exist in the graph, do nothing
	if (NULL == node1 || NULL == node2)
	{
		return;
	}

	//strings exist, check if they have already been linked to the first node
	vector<Node*>& vector1 = node1->getConnection();
	for (unsigned int i = 0; i < vector1.size(); i++)
	{
		if (vector1[i]->data() == string2)
		{
			//connection has already been found, no need to add again
			i = vector1.size();
			bool1 = false;
		}
	}

	//strings exist, check if they have already been linked to the second node
	vector<Node*>& vector2 = node2->getConnection();
	for (unsigned int i = 0; i < vector2.size(); i++)
	{
		if (vector2[i]->data() == string1)
		{
			//connection has already been found, no need to add again
			i = vector2.size();
			bool2 = false;
		}
	}

	if (bool1)
	{
		node1->addConnection(node2);
	}
	if (bool2)
	{
		node2->addConnection(node1);
	}
}

// Implements breadth first search of graph.
// The first path a match is found for is returned as a vector

vector<string> Graph::findShortestPath(string start, string end)
{
	vector<string> retVal;
	Node* startNode = findNode(start);

	//if we don't have the nodes we're supposed to start from and end on, then return no path
	if (NULL == startNode || NULL == findNode(end))
	{
		return retVal;
	}

	//reset all distance, parent, and found values
	for (unsigned int i = 0; i < m_graphVector.size(); i++)
	{
		m_graphVector[i]->distance(Node::INFINITE);
		m_graphVector[i]->parent(NULL);
		m_graphVector[i]->found(false);
		m_graphVector[i]->parent(NULL);
		m_graphVector[i]->found(false);
	}
	
	//the start node has a distance of zero
	startNode->distance(0);

	//create a queue
	queue<Node*> myQ;

	//enqueue the first 
	myQ.push(startNode);

	while (myQ.size() > 0)
	{
		Node* current = myQ.front();
		myQ.pop();

		vector<Node*> connections = current->getConnection();

		for (unsigned int i = 0; i < connections.size(); i++)
		{
			Node* newNode = connections[i];
			if (newNode->distance() == Node::INFINITE)
			{
				newNode->distance(current->distance() + 1);
				newNode->parent(current);
				myQ.push( newNode );
			}

			//if we've found the end value, save the path found and break out
			if (newNode->data() == end)
			{
				//fill up the return vector
				retVal.push_back(newNode->data() );
				Node* nextNode = newNode->parent();
				while (nextNode != NULL)
				{
					retVal.push_back( nextNode->data() );
					nextNode = nextNode->parent();
				}

				//break from loop
				i = connections.size();

				//pop everything off of the queue
				unsigned int size = myQ.size();
				for (unsigned int j = 0; j < size; j++)
				{
					myQ.pop();
				}
			}
		}
	}
	
	//the vector will have values returned in reverse order, reverse them here
	reverse(retVal.begin(), retVal.end());

	return retVal;
}

Graph::~Graph()
{
	//clean up all the created nodes
	for (unsigned int i = 0; i < m_graphVector.size(); i++)
	{
		delete m_graphVector[i];
	}
}


//NODE STUFF

//Default constructor
Node::Node()
{
	string m_data = "";
	bool m_found = false;
	int m_distance = INFINITE;
	Node* m_parent = NULL;
}