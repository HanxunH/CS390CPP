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
	// TODO: 在此添加命令处理程序代码
	wave.play();
}

void CWaveEditDoc::OnToolsEcho()
{
	// TODO: 在此添加命令处理程序代码
	float attenuation = .2;
	float delay = 100; // In MS

	wave = *(wave.echo(attenuation, delay));
	wave.updateHeader();
}
