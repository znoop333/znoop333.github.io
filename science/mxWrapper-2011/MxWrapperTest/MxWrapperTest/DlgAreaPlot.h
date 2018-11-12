#pragma once


// CDlgAreaPlot

class CDlgAreaPlot : public CStatic
{
	DECLARE_DYNAMIC(CDlgAreaPlot)

public:
	CDlgAreaPlot();
	virtual ~CDlgAreaPlot();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
};


