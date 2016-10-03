#pragma once
#include "Filter.h"

class FilterSlowdown:public Filter
{
public:
	FilterSlowdown(void);
	~FilterSlowdown(void);
	static WaveFile* transform(WaveFile* target);

};
