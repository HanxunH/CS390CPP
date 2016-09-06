// WaveEditDoc.h : interface of the CWaveEditDoc class
//


#pragma once
#include "WaveFile.h"

class CWaveEditDoc : public CDocument
{
	friend class CWaveEditView;
    WaveFile wave;
protected: // create from serialization only
	CWaveEditDoc();
	DECLARE_DYNCREATE(CWaveEditDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CWaveEditDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnToolsPlay();
	afx_msg void OnToolsEcho();
};


