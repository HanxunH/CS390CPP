#pragma once
#include "Filter.h"

class FilterVolumeUp :  public Filter
{
public:
	FilterVolumeUp(void);
	~FilterVolumeUp(void);
	static WaveFile* transform(WaveFile* target);
};
