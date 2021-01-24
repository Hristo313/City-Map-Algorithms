#pragma once
#include <string>

class EdgeInfo
{
private:
	std::string nodeStart;
	std::string nodeEnd;
	int weight;
public:
	EdgeInfo();
	EdgeInfo(std::string, std::string, int);
	EdgeInfo& operator=(const EdgeInfo&);
	~EdgeInfo();
	void setNodeStart(std::string);
	void setNodeEnd(std::string);
	void setWeight(int);
	std::string getNodeStart();
	std::string getNodeEnd();
	int getWeight();
};

