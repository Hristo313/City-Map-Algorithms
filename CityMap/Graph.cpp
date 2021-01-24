#include "Graph.h"

int Graph::searchKeyInMap(std::string city)
{
	for (auto& it : nodes) {
		if (it.second == city) return it.first;
	}
	return -1;
}

std::list<std::pair<int, int>> Graph::searchInEdges(int toSearch)
{
	std::list<std::pair<int, int>> temp;
	for (int i = 0; i < V; i++)
	{
		if (i != toSearch) {
			std::list<std::pair<int, int>>::iterator it = edges[i].begin();
			for (; it != edges[i].end(); it++)
			{
				if (it->first == toSearch) {
					temp.push_back({ i,toSearch });
				}
			}
		}
	}
	return temp;
}

void Graph::shortestPathAlgorithm(int startNode, int endNode, bool* visited, std::vector<int> path, int& pathIndex, int& sumWeight, std::vector<std::pair<std::vector<int>, int>>& allPaths)
{
	visited[startNode] = true;
	path[pathIndex] = startNode;
	pathIndex++;

	if (startNode == endNode) {
		std::vector<int> temp(pathIndex);
		for (int i = 0; i < pathIndex; i++)
		{
			temp[i] = path[i];
		}
		allPaths.push_back({ temp, sumWeight });
		sumWeight = 0;
	}
	else {
		std::list<std::pair<int, int>>::iterator it = edges[startNode].begin();
		for (; it != edges[startNode].end(); it++) {
			if (!visited[it->first]) {
				sumWeight += it->second;
				shortestPathAlgorithm(it->first, endNode, visited, path, pathIndex, sumWeight, allPaths);
			}
		}
	}
	pathIndex--;
	visited[startNode] = false;

}

Graph::Graph(int n)
{
	V = n;
	this->edges = new std::list<std::pair<int, int>>[V];
}

Graph::Graph(int n, std::map<int, std::string> nodes, std::list<std::pair<int, int>>* edges)
{
	this->V = n;
	this->nodes = nodes;
	this->edges = new std::list<std::pair<int, int>>[V];
	this->edges = edges;
}

Graph::Graph(const Graph& rhs)
{
	this->V = rhs.V;
	this->edges = rhs.edges;
}

Graph& Graph::operator=(const Graph& rhs)
{
	if (this != &rhs) {
		this->V = rhs.V;
		this->edges = rhs.edges;
	}
	return *this;
}

Graph::~Graph()
{
	if (edges != NULL)
		delete[] edges;
}

void Graph::addNode(int i, std::string city)
{
	nodes.insert({ i, city });
}

void Graph::addPath(int a, int b, int weigth) {
	edges[a].push_back({ b, weigth });
}

void Graph::print()
{
	for (int i = 0; i < V; i++)
	{
		std::list<std::pair<int, int>>::iterator it;
		for (it = edges[i].begin(); it != edges[i].end(); it++)
		{
			int n = (*it).first;
			int weigth = (*it).second;
			std::cout << nodes[i];
			std::cout << " - > ";
			std::cout << nodes[n];
			std::cout << " The weight is: " << weigth << std::endl;
		}
	}
}

bool Graph::isReachable(std::string start, std::string end)
{
	int startN = searchKeyInMap(start);
	int endN = searchKeyInMap(end);
	bool* visited = new bool[V] {false};
	std::list<int> queue;
	visited[startN] = true;
	queue.push_back(startN);

	std::list<std::pair<int, int>>::iterator it;
	while (!queue.empty()) {
		startN = queue.front();
		queue.pop_front();
		for (it = edges[startN].begin(); it != edges[startN].end(); it++)
		{
			if (it->first == endN) return true;
			if (!visited[it->first]) {
				visited[it->first] = true;
				queue.push_back(it->first);
			}
		}
	}
	return false;
}

bool Graph::isReachableToAllNodes(std::string start)
{
	int startN = searchKeyInMap(start);
	for (int i = 0; i < V; i++)
	{
		if (i != startN) {
			if (!isReachable(start, nodes[i])) return false;
		}
	}
	return true;
}

std::map<std::string, std::string> Graph::findDeadEnds()
{
	std::map<std::string, std::string> temp;
	std::list<std::pair<int, int>> tempList;
	for (int i = 0; i < V; i++)
	{
		if (edges[i].size() == 0) {
			//std::string end = nodes[i];
			std::list<std::pair<int, int>> tempE = searchInEdges(i);
			std::list<std::pair<int, int>>::iterator it = tempE.begin();
			for (; it != tempE.end(); it++)
			{
				tempList.push_back({ it->first, it->second });
			}
		}
	}
	std::list<std::pair<int, int>>::iterator it = tempList.begin();
	for (; it != tempList.end(); it++)
	{
		temp.insert({ nodes[it->first], nodes[it->second] });
	}
	return temp;
}
void Graph::swap(std::pair<std::vector<int>, int>* a, std::pair<std::vector<int>, int>* b)
{
	std::pair<std::vector<int>, int> temp = *a;
	*a = *b;
	*b = temp;
}
void Graph::bubbleSort(std::vector<std::pair<std::vector<int>, int>>& arr)
{
	for (unsigned i = 0; i < arr.size() - 1; i++)
	{
		for (unsigned j = 0; j < arr.size() - i - 1; j++)
		{
			if (arr[j].second > arr[j + 1].second)
				swap(&arr[j], &arr[j + 1]);
		}
	}
}
void Graph::getShortestPaths(std::string startNode, std::string endNode)
{
	bool* visited = new bool[V] {false};
	std::vector<int> path(V);
	int pathIndex = 0;
	int sumWeight = 0;
	std::vector<std::pair<std::vector<int>, int>> allPaths;
	int startNodeIndex = searchKeyInMap(startNode);
	int endNodeIndex = searchKeyInMap(endNode);
	shortestPathAlgorithm(startNodeIndex, endNodeIndex, visited, path, pathIndex, sumWeight, allPaths);
	bubbleSort(allPaths);
	if (allPaths.size() < 4) {
		for (unsigned i = 0; i < allPaths.size(); i++)
		{
			std::vector<int> temp = allPaths[i].first;
			for (unsigned j = 0; j < temp.size(); j++)
			{
				std::cout << nodes[temp[j]] << " -> ";
			}
			std::cout << allPaths[i].second;
			std::cout << std::endl;
		}
	}
	else {
		for (int i = 0; i < 3; i++)
		{
			std::vector<int> temp = allPaths[i].first;
			for (unsigned j = 0; j < temp.size(); j++)
			{
				std::cout << nodes[temp[j]] << " -> ";
			}
			std::cout << allPaths[i].second;
			std::cout << std::endl;
		}
	}
	delete[] visited;
}
void Graph::deleteNodes(std::vector<int> closedNodes) {
	for (int i = 0; i < closedNodes.size(); i++)
	{
		nodes.erase(closedNodes[i]);
		for (int j = 0; j < V; j++)
		{
			std::list<std::pair<int, int>>::iterator it = edges[j].begin();
			for (; it != edges[j].end(); it++) {
				if (it->first == closedNodes[i]) {

					edges[j].erase(it);
					break;
				}
			}
		}
	}

}
void Graph::getShortestPaths(std::string startNode, std::string endNode, std::list<std::string> closedNodes)
{
	std::vector<int> nodesToDelete;
	std::list<std::string>::iterator it = closedNodes.begin();

	for (; it != closedNodes.end(); it++)
	{
		nodesToDelete.push_back(searchKeyInMap(*it));
	}
	deleteNodes(nodesToDelete);
	getShortestPaths(startNode, endNode);
}
bool Graph::isCyclicUtil(int v, bool* visited, bool* recStack)
{
	if (visited[v] == false) {
		visited[v] = true;
		recStack[v] = true;

		std::list<std::pair<int, int>>::iterator it = edges[v].begin();
		for (; it != edges[v].end(); it++) {
			if (!visited[it->first] && isCyclicUtil(it->first, visited, recStack)) {
				return true;
			}
			else if (recStack[it->first]) {
				return true;
			}
		}
	}
	recStack[v] = false;
	return false;
}
bool Graph::isCyclicFromNode(std::string startNode)
{
	bool* visited = new bool[V] {false};
	bool* recStack = new bool[V] {false};
	int node = searchKeyInMap(startNode);
	if (isCyclicUtil(node, visited, recStack)) {
		delete[] visited;
		delete[] recStack;
		return true;
	}
	delete[] visited;
	delete[] recStack;
	return false;
}
int Graph::countPaths()
{
	int br = 0;
	for (int i = 0; i < V; i++)
	{
		br += edges[i].size();
	}
	return br;
}

