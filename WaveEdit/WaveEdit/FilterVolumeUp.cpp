#include "StdAfx.h"
#include "FilterVolumeUp.h"

FilterVolumeUp::FilterVolumeUp(void)
{
}

FilterVolumeUp::~FilterVolumeUp(void)
{
}
WaveFile* FilterVolumeUp::transform(WaveFile* target){
  WaveFile *w2 = target->update_fragment(2,target);
  w2->updateHeader();
  return w2;
}
