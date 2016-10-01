// WaveEditDoc.cpp : implementation of the CWaveEditDoc class
//

#include "stdafx.h"
#include "WaveEdit.h"
#include "WaveEditDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWaveEditDoc

IMPLEMENT_DYNCREATE(CWaveEditDoc, CDocument)

BEGIN_MESSAGE_MAP(CWaveEditDoc, CDocument)
	ON_COMMAND(ID_TOOLS_PLAY, &CWaveEditDoc::OnToolsPlay)
	ON_COMMAND(ID_TOOLS_ECHO, &CWaveEditDoc::OnToolsEcho)
	ON_COMMAND(ID_TOOLS_SPEEDUP, &CWaveEditDoc::OnToolsSpeedup)
	ON_COMMAND(ID_TOOLS_SLOWDOWN, &CWaveEditDoc::OnToolsSlowdown)
END_MESSAGE_MAP()


// CWaveEditDoc construction/destruction

CWaveEditDoc::CWaveEditDoc()
{
	// TODO: add one-time construction code here

}

CWaveEditDoc::~CWaveEditDoc()
{
}

BOOL CWaveEditDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CWaveEditDoc serialization

void CWaveEditDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
		wave.read(ar.GetFile());
        wave.play();
	}
}


// CWaveEditDoc diagnostics

#ifdef _DEBUG
void CWaveEditDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWaveEditDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CWaveEditDoc commands

void CWaveEditDoc::OnToolsPlay()
{
	// TODO:
	wave.updateHeader();
	wave.play();
}

void CWaveEditDoc::OnToolsEcho()
{
	// TODO:
	float attenuation = .5;
	float delay = 100; // In MS

	wave = *(wave.echo(attenuation, delay));
	wave.updateHeader();
	wave.play();
}

void CWaveEditDoc::OnToolsSpeedup()
{
	// TODO:
	wave = *(wave.changeSpeed(2));
	wave.updateHeader();
	wave.play();
}

void CWaveEditDoc::OnToolsSlowdown()
{
	// TODO:

	wave = *(wave.changeSpeed(0.5));
	wave.updateHeader();
	wave.play();
}
