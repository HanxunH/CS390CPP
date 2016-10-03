#include "StdAfx.h"
#include "FilterVolumeDown.h"

FilterVolumeDown::FilterVolumeDown(void)
{
}

FilterVolumeDown::~FilterVolumeDown(void)
{
}
WaveFile* FilterVolumeDown::transform(WaveFile* target){
  WaveFile *w2 = target->update_fragment(0.5,target);
  w2->updateHeader();
  return w2;
}
