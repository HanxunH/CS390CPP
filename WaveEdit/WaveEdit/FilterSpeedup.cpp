#include "StdAfx.h"
#include "FilterSpeedup.h"

FilterSpeedup::FilterSpeedup(void)
{
}

FilterSpeedup::~FilterSpeedup(void)
{
}

WaveFile* FilterSpeedup::transform(WaveFile* target){
  WaveFile *w2 = target->changeSpeed(2);
  w2->updateHeader();
  return w2;
}
