#pragma once
#include "Filter.h"

class FilterSpeedup : public Filter
{
public:
	FilterSpeedup(void);
	~FilterSpeedup(void);
  static WaveFile* transform(WaveFile* target);
};
