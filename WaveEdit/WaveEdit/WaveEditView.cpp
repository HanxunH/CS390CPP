// WaveEditView.cpp : implementation of the CWaveEditView class
//

#include "stdafx.h"
#include "WaveEdit.h"

#include "WaveEditDoc.h"
#include "WaveEditView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CWaveEditView

IMPLEMENT_DYNCREATE(CWaveEditView, CScrollView)

BEGIN_MESSAGE_MAP(CWaveEditView, CScrollView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_EDIT_COPY, &CWaveEditView::OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, &CWaveEditView::OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, &CWaveEditView::OnEditPaste)
	ON_COMMAND(ID_VIEW_ZOOMIN, &CWaveEditView::OnViewZoomin)
	ON_COMMAND(ID_VIEW_ZOOMOUT, &CWaveEditView::OnViewZoomout)
	ON_COMMAND(ID_EDIT_REDO, &CWaveEditView::OnEditRedo)
	ON_COMMAND(ID_EDIT_UNDO, &CWaveEditView::OnEditUndo)
	ON_COMMAND(ID_TOOLS_SPEEDUP, &CWaveEditView::OnToolsSpeedup)
	ON_COMMAND(ID_TOOLS_SLOWDOWN, &CWaveEditView::OnToolsSlowdown)
	ON_COMMAND(ID_TOOLS_ECHO, &CWaveEditView::OnToolsEcho)
END_MESSAGE_MAP()

// CWaveEditView construction/destruction

CWaveEditView::CWaveEditView()
{
	// TODO: add construction code here
	mousePressed = false;
	selectionStart = 0;
	selectionEnd = 0;
	scaleNumber = 1;
}


void emptyStack(std::stack<WaveFile> &stack){
	while (stack.empty() != true) {
		stack.pop();
	}
}

CWaveEditView::~CWaveEditView()
{
	emptyStack(Stack_redo);
	emptyStack(Stack_undo);
}


BOOL CWaveEditView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CWaveEditView drawing

int helper_width(unsigned int maxSamples,unsigned long sampleRate, int scaleNumber){
	return (maxSamples/sampleRate)*scaleNumber;
}

void CWaveEditView::OnDraw(CDC* pDC)
{

	CWaveEditDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	if (!pDoc)
					return;
	WaveFile * wave = &pDoc->wave;
	if (wave->hdr==NULL) {
					return;
	}
	// Get dimensions of the window.
	CRect rect;
	GetClientRect(rect);

	// Set color in pen and brush for selection
 	COLORREF color = RGB( 255, 200, 200 );
 	CPen pen1( PS_SOLID, 0, color );
 	pDC->SelectObject( &pen1 );
 	CBrush brush1(color);
 	pDC->SelectObject( &brush1 );
 	// Draw selection if any
 	if (selectionStart != selectionEnd) {
				 pDC->Rectangle(selectionStart, 0, selectionEnd, rect.Height());
 	}

	// Set color in pen and brush for wave
	color = RGB( 0, 255, 0 );
	CPen pen2( PS_SOLID, 0, color );
	pDC->SelectObject( &pen2 );
	CBrush brush2(color);
	pDC->SelectObject( &brush2 );
	// Draw the wave
	pDC->MoveTo(0,0);
	int x;
	for (x=0; x < rect.Width()*scaleNumber; x++) {
					// Assuming the whole file will be fit in the window, for every x value in the window
					// we need to find the equivalent sample in the wave file.
					float val = wave->get_sample((int) (x*wave->lastSample/(rect.Width()*scaleNumber)) );
					// We need to fit the sound also in the y axis. The y axis goes from 0 in the
					// top of the window to rect.Height at the bottom. The sound goes from -32768 to 32767
					// we scale it in that way.
					int y = (int) ((val+32768) * (rect.Height()-1) / (32767+32768));
					pDC->LineTo(x,rect.Height() - y);
	}
	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = x;
	sizeTotal.cy = 0;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CWaveEditView printing

BOOL CWaveEditView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWaveEditView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CWaveEditView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void
CWaveEditView::OnInitialUpdate()
{
        CScrollView::OnInitialUpdate();
        // Initial scroll sizes
        CSize sizeTotal;
        sizeTotal.cx = 10000;
        sizeTotal.cy = 0;
        SetScrollSizes(MM_TEXT, sizeTotal);
}

// CWaveEditView diagnostics

#ifdef _DEBUG
void CWaveEditView::AssertValid() const
{
	CView::AssertValid();
}

void CWaveEditView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWaveEditDoc* CWaveEditView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWaveEditDoc)));
	return (CWaveEditDoc*)m_pDocument;
}
#endif //_DEBUG


// CWaveEditView message handlers

void CWaveEditView::OnLButtonDown(UINT nFlags, CPoint point)
{
	mousePressed = true;
	selectionStart = point.x + GetScrollPosition().x;
	selectionEnd = point.x + GetScrollPosition().x;
	CScrollView::OnLButtonDown(nFlags, point);
}

void CWaveEditView::OnLButtonUp(UINT nFlags, CPoint point)
{
	mousePressed = false;
	this->selectionEnd = point.x + GetScrollPosition().x;
	if(this->selectionEnd < this->selectionStart){
		//swap
		int temp = this->selectionEnd;
		this->selectionEnd = this->selectionStart;
		this->selectionStart = temp;
	}
	this->RedrawWindow();
	CScrollView::OnLButtonUp(nFlags, point);
}

void CWaveEditView::OnMouseMove(UINT nFlags, CPoint point)
{

	CScrollView::OnMouseMove(nFlags, point);
	if (mousePressed) {
				selectionEnd = point.x + GetScrollPosition().x;
				RedrawWindow();
	}
}

void CWaveEditView::OnEditCopy()
{
	// TODO:
	CWaveEditDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	WaveFile * wave = &pDoc->wave;
	if (wave->hdr==NULL) {
		return;
	}
	CRect rect;
	GetClientRect(rect);
	Stack_undo.push(*wave);
	emptyStack(Stack_redo);
	// Scale the start and end of the selection.
	double startms = (1000.0 * wave->lastSample /wave->sampleRate) * this->selectionStart/(rect.Width()*scaleNumber);
	// Scale the start and end of the selection.
	double endms = (1000.0 * wave->lastSample /wave->sampleRate) * this->selectionEnd/(rect.Width()*scaleNumber);
	CWaveEditApp* app = dynamic_cast<CWaveEditApp*>(AfxGetApp());
	app->clipboard = new WaveFile(wave->numChannels, wave->sampleRate, wave->bitsPerSample);
	app->clipboard = wave->get_fragment(startms, endms);
	// Update window
	selectionStart = 0;
	selectionEnd = 0;
	this->RedrawWindow();
}

void CWaveEditView::OnEditCut()
{
	// TODO:
	CWaveEditDoc* pDoc = GetDocument();

        ASSERT_VALID(pDoc);
        if (!pDoc)
                return;
        WaveFile * wave = &pDoc->wave;
        if (wave->hdr==NULL) {
                return;
        }
        // Get dimensions of the window.
        CRect rect;
        GetClientRect(rect);
				Stack_undo.push(*wave);
				emptyStack(Stack_redo);
        // Scale the start and end of the selection.
        double startms = (1000.0 * wave->lastSample /wave->sampleRate) * this->selectionStart/(rect.Width()*scaleNumber);
        // Scale the start and end of the selection.
        double endms = (1000.0 * wave->lastSample /wave->sampleRate) * this->selectionEnd/(rect.Width()*scaleNumber);

        // Copy first the fragment

				CWaveEditApp* app = dynamic_cast<CWaveEditApp*>(AfxGetApp());
				app->clipboard = new WaveFile(wave->numChannels, wave->sampleRate, wave->bitsPerSample);
        app->clipboard = wave->get_fragment(startms, endms);
        // Copy the clipboard
        WaveFile * w2 = wave->remove_fragment(startms, endms);
        // Remove old wave
        //delete wave;
        // Substitute old wave with new one
        pDoc->wave = *w2;
        // Update window
				selectionStart = 0;
				selectionEnd = 0;
        this->RedrawWindow();
}

void CWaveEditView::OnEditPaste()
{
	// TODO:
	CWaveEditApp* app = dynamic_cast<CWaveEditApp*>(AfxGetApp());
	if(app->clipboard==NULL){
		TRACE("OnEditPaste() empty clipboard");
		return;
	}
	CWaveEditDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	WaveFile * wave = &pDoc->wave;
	if (wave->hdr==NULL) {
		return;
	}

	CRect rect;
	GetClientRect(rect);
	Stack_undo.push(*wave);
	emptyStack(Stack_redo);
	int startms = (1000.0 * wave->lastSample /wave->sampleRate) * this->selectionStart/(rect.Width()*scaleNumber);
	WaveFile * w2 = wave->add_fragment(startms, app->clipboard);
	pDoc->wave = *w2;
	wave->updateHeader();
	this->RedrawWindow();
}

void CWaveEditView::OnViewZoomin()
{
	// TODO:
	scaleNumber = scaleNumber*2;
	this->RedrawWindow();
}

void CWaveEditView::OnViewZoomout()
{
	// TODO:
	scaleNumber = scaleNumber/2;
	this->RedrawWindow();
}

void CWaveEditView::OnEditRedo()
{
	// TODO:
	CWaveEditDoc* pDoc = GetDocument();
	if(Stack_redo.empty()){
		return;
	}
	Stack_undo.push(pDoc->wave);
	pDoc->wave = Stack_redo.top();
	Stack_redo.pop();
	pDoc->wave.updateHeader();
	this->RedrawWindow();
}

void CWaveEditView::OnEditUndo()
{
	// TODO:
	CWaveEditDoc* pDoc = GetDocument();
	if(Stack_undo.empty()){
		return;
	}
	Stack_redo.push(pDoc->wave);
	pDoc->wave = Stack_undo.top();
	Stack_undo.pop();
	pDoc->wave.updateHeader();
	this->RedrawWindow();
}

void CWaveEditView::OnToolsSpeedup()
{
	// TODO:
	CWaveEditDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	WaveFile * wave = &pDoc->wave;
	if (wave->hdr==NULL) {
		return;
	}
	// Get dimensions of the window.
	CRect rect;
	GetClientRect(rect);
	double startms = (1000.0 * wave->lastSample /wave->sampleRate) * this->selectionStart/(rect.Width()*scaleNumber);
	double endms = (1000.0 * wave->lastSample /wave->sampleRate) * this->selectionEnd/(rect.Width()*scaleNumber);
	Stack_undo.push(*wave);
	emptyStack(Stack_redo);


	if(startms==endms){
		TRACE("OnToolsSpeedup() no selection\n");
		wave = wave->changeSpeed(2);
		wave->updateHeader();
		pDoc->wave = *wave;
		pDoc->wave.play();
		this->RedrawWindow();
		return;
	}
	WaveFile * targetWaveFile = new WaveFile(wave->numChannels, wave->sampleRate, wave->bitsPerSample);
	targetWaveFile = wave->get_fragment(startms,endms);
	targetWaveFile->updateHeader();
	WaveFile * w2 = new WaveFile(wave->numChannels, wave->sampleRate, wave->bitsPerSample);
	w2 = wave->remove_fragment(startms,endms);
	w2->updateHeader();
	targetWaveFile = targetWaveFile->changeSpeed(2);
	targetWaveFile->updateHeader();
	w2 = w2->add_fragment(startms,targetWaveFile);
	w2->updateHeader();
	pDoc->wave = *w2;
	pDoc->wave.play();
	this->RedrawWindow();
	return;
}

void CWaveEditView::OnToolsSlowdown()
{
	// TODO:
	CWaveEditDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	WaveFile * wave = &pDoc->wave;
	if (wave->hdr==NULL) {
		return;
	}
	// Get dimensions of the window.
	CRect rect;
	GetClientRect(rect);
	double startms = (1000.0 * wave->lastSample /wave->sampleRate) * this->selectionStart/(rect.Width()*scaleNumber);
	double endms = (1000.0 * wave->lastSample /wave->sampleRate) * this->selectionEnd/(rect.Width()*scaleNumber);
	Stack_undo.push(*wave);
	emptyStack(Stack_redo);


	if(startms==endms){
		TRACE("OnToolsSlowdown() no selection\n");
		wave = wave->changeSpeed(0.5);
		wave->updateHeader();
		pDoc->wave = *wave;
		pDoc->wave.play();
		this->RedrawWindow();
		return;
	}
	WaveFile * targetWaveFile = new WaveFile(wave->numChannels, wave->sampleRate, wave->bitsPerSample);
	targetWaveFile = wave->get_fragment(startms,endms);
	targetWaveFile->updateHeader();
	WaveFile * w2 = new WaveFile(wave->numChannels, wave->sampleRate, wave->bitsPerSample);
	w2 = wave->remove_fragment(startms,endms);
	w2->updateHeader();
	targetWaveFile = targetWaveFile->changeSpeed(0.5);
	targetWaveFile->updateHeader();
	w2 = w2->add_fragment(startms,targetWaveFile);
	w2->updateHeader();
	pDoc->wave = *w2;
	pDoc->wave.play();
	this->RedrawWindow();
	return;
}

void CWaveEditView::OnToolsEcho()
{
	// TODO:
	CWaveEditDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
  if (!pDoc)
    return;
  WaveFile * wave = &pDoc->wave;
  if (wave->hdr==NULL) {
    return;
  }
  // Get dimensions of the window.
  CRect rect;
  GetClientRect(rect);
	float attenuation = .5;
	float delay = 100; // In MS
	double startms = (1000.0 * wave->lastSample /wave->sampleRate) * this->selectionStart/(rect.Width()*scaleNumber);
	double endms = (1000.0 * wave->lastSample /wave->sampleRate) * this->selectionEnd/(rect.Width()*scaleNumber);
	Stack_undo.push(*wave);
	emptyStack(Stack_redo);
	if(startms==endms){
		TRACE("OnToolsEcho() no selection\n");
		wave = wave->echo(attenuation, delay);
		wave->updateHeader();
		pDoc->wave = *wave;
		pDoc->wave.play();
		this->RedrawWindow();
		return;
	}
	WaveFile * targetWaveFile = new WaveFile(wave->numChannels, wave->sampleRate, wave->bitsPerSample);
	targetWaveFile = wave->get_fragment(startms,endms);
	targetWaveFile->updateHeader();
	WaveFile * w2 = new WaveFile(wave->numChannels, wave->sampleRate, wave->bitsPerSample);
	w2 = wave->remove_fragment(startms,endms);
	w2->updateHeader();
	targetWaveFile = targetWaveFile->echo(attenuation, delay);
	targetWaveFile->updateHeader();
	w2 = w2->add_fragment(startms,targetWaveFile);
	w2->updateHeader();
	pDoc->wave = *w2;
	pDoc->wave.play();
	this->RedrawWindow();
	return;
}
