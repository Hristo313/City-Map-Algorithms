#include "File.h"

void File::loadNodes(std::string city)
{
	if (nodes.empty()) {
		nodes.insert({ 0,city });
	}
	else {
		int size = nodes.size();
		bool flag = true;
		for (int i = 0; i < size; i++)
		{
			if (nodes[i] == city) flag = false;
		}
		if (flag) {
			nodes.insert({ size, city });
		}
	}
}

int File::parseToInt(std::string weightStr)
{
	int weight = 0;
	int size = weightStr.size();
	for (int i = 0; i < size; i++)
	{
		weight += (int)pow(10, size - i - 1) * ((int)weightStr[i] - 48);
	}
	return weight;
}

void File::loadEdges(std::vector<EdgeInfo> edgesInfo)
{
	for (unsigned i = 0; i < edgesInfo.size(); i++)
	{
		int a = searchKeyInMap(edgesInfo[i].getNodeStart());
		int b = searchKeyInMap(edgesInfo[i].getNodeEnd());
		int weight = edgesInfo[i].getWeight();
		edges[a].push_back({ b, weight });
	}
}

int File::searchKeyInMap(std::string city)
{
	for (auto& it : nodes) {
		if (it.second == city) return it.first;
	}
	return -1;
}

File::File(std::string fileName)
{
	edges = new std::list<std::pair<int, int>>[1];
	file.open(fileName);
}

Graph File::loadTextToGraph()
{

	if (file.is_open()) {
		std::string line;
		std::vector<std::string> wordsONLine;
		std::vector<EdgeInfo> edgesOnLine;
		while (getline(file, line)) {
			std::stringstream stream(line);
			std::string temp;
			while (getline(stream, temp, ' ')) {
				wordsONLine.push_back(temp);
			}
			loadNodes(wordsONLine[0]);
			for (unsigned i = 1; i < wordsONLine.size(); i += 2)
			{
				loadNodes(wordsONLine[i]);
				EdgeInfo edgeTemp(wordsONLine[0], wordsONLine[i], parseToInt(wordsONLine[i + 1]));
				edgesOnLine.push_back(edgeTemp);
			}
			wordsONLine.clear();
		}
		edges = new std::list<std::pair<int, int>>[nodes.size()];
		loadEdges(edgesOnLine);
		edgesOnLine.clear();
	}

	return Graph(nodes.size(), nodes, edges);
}

File::~File()
{
	//delete[] edges;
	file.close();
}
