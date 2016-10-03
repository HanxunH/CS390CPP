#include "StdAfx.h"
#include "FilterEcho.h"

FilterEcho::FilterEcho(void)
{
}

FilterEcho::~FilterEcho(void)
{
}
WaveFile* FilterEcho::transform(WaveFile* target){
  WaveFile *w2 = target->echo(0.5,100);
  w2->updateHeader();
  return w2;
}
