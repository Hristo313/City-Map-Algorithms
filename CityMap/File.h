#pragma once
#include <string>
#include <list>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include "EdgeInfo.h"
#include "Graph.h"
class File
{
private:
	std::ifstream file;
	std::map<int, std::string> nodes;
	std::list<std::pair<int, int>>* edges;

	void loadNodes(std::string city);
	int parseToInt(std::string weightStr);
	void loadEdges(std::vector<EdgeInfo> edgesInfo);
	int searchKeyInMap(std::string city);
public:
	File(std::string fileName);
	Graph loadTextToGraph();
	~File();
};

