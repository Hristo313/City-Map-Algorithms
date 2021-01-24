#include "EdgeInfo.h"

EdgeInfo::EdgeInfo()
{
	nodeStart = "";
	nodeEnd = "";
	weight = 0;
}

EdgeInfo::EdgeInfo(std::string nodeStart, std::string nodeEnd, int weight)
{
	this->nodeStart = nodeStart;
	this->nodeEnd = nodeEnd;
	this->weight = weight;
}

EdgeInfo& EdgeInfo::operator=(const EdgeInfo& rhs)
{
	if (this != &rhs) {
		this->nodeStart = nodeStart;
		this->nodeEnd = nodeEnd;
		this->weight = weight;
	}
	return *this;
}

EdgeInfo::~EdgeInfo()
{
}

void EdgeInfo::setNodeStart(std::string cityName)
{
	this->nodeStart = cityName;
}

void EdgeInfo::setNodeEnd(std::string cityName)
{
	this->nodeEnd = cityName;
}

void EdgeInfo::setWeight(int weight)
{
	this->weight = weight;
}

std::string EdgeInfo::getNodeStart()
{
	return this->nodeStart;
}

std::string EdgeInfo::getNodeEnd()
{
	return this->nodeEnd;
}

int EdgeInfo::getWeight()
{
	return this->weight;
}
