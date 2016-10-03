#pragma once
#include "Filter.h"

class FilterVolumeDown : public Filter
{
public:
	FilterVolumeDown(void);
	~FilterVolumeDown(void);
	static WaveFile* transform(WaveFile* target);
};
