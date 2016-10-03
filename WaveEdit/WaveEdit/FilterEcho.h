#pragma once
#include "Filter.h"

class FilterEcho : public Filter
{
public:
	FilterEcho(void);
	~FilterEcho(void);
	static WaveFile* transform(WaveFile* target);
};
