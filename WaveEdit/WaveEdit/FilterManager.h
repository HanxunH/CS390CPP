#pragma once
#include "Filter.h"
#include "WaveFile.h"
#include <map>
#include <vector>

class FilterManager
{
public:
	FilterManager(void);
	~FilterManager(void);
	int filterCount;
	WaveFile* FilterManager::getFilter(int i,WaveFile *w);
};
