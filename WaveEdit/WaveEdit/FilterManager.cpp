#include "StdAfx.h"
#include "FilterManager.h"
#include "FilterEcho.h"
#include "FilterSpeedup.h"
#include "FilterSlowdown.h"
#include "FilterVolumeUp.h"
#include "FilterVolumeDown.h"
#include "WaveFile.h"
FilterManager::FilterManager(void)
{
  CMenu *menu = new CMenu;
  menu->CreatePopupMenu();
  // Add items to the menu
  menu->AppendMenu(MF_STRING, 7000, _T("Echo"));
  menu->AppendMenu(MF_STRING, 7001, _T("SpeedUp"));
  menu->AppendMenu(MF_STRING, 7002, _T("SlowDown"));
  menu->AppendMenu(MF_STRING, 7003, _T("VolumeUp"));
  menu->AppendMenu(MF_STRING, 7004, _T("VolumeDown"));
  CMenu* pMenu = AfxGetMainWnd()->GetMenu();
  if(pMenu != NULL){
    TRACE("FilterManager: %d\n", pMenu->GetMenuItemCount());
    pMenu->AppendMenu(MF_POPUP, (UINT_PTR)menu->m_hMenu, _T("Filter"));
  }
  filterCount = 3;
}

WaveFile* FilterManager::getFilter(int i,WaveFile *w){
  if(i==7000){
    WaveFile* w2 = FilterEcho::transform(w);
    return w2;
  }else if(i==7001){
    WaveFile* w2 = FilterSpeedup::transform(w);
    return w2;
  }else if(i==7002){
    WaveFile* w2 = FilterSlowdown::transform(w);
    return w2;
  }else if(i==7003){
    WaveFile* w2 = FilterVolumeUp::transform(w);
    return w2;
  }else if(i==7004){
    WaveFile* w2 = FilterVolumeDown::transform(w);
    return w2;
  }
  return w;
}

FilterManager::~FilterManager(void)
{
}
