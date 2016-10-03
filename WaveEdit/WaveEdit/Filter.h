#pragma once
#include "WaveFile.h"


class Filter
{
	friend class WaveFile;
public:
	Filter();
	~Filter();
  virtual WaveFile* transform() = 0;
};
