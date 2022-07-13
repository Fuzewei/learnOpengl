#pragma once
#include<vector>
class Panel
{	
public:
	Panel(){}
	~Panel() {}
private:
	
	std::vector<Panel> subPanels;
};

