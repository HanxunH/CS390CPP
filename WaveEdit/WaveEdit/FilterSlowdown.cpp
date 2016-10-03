#include "StdAfx.h"
#include "FilterSlowdown.h"

FilterSlowdown::FilterSlowdown(void)
{
}

FilterSlowdown::~FilterSlowdown(void)
{
}

WaveFile* FilterSlowdown::transform(WaveFile* target){
  WaveFile *w2 = target->changeSpeed(0.5);
  w2->updateHeader();
  return w2;
}
