// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAADegAnalysisNumericDlg.h"

// Dialog Framework
#include "CATDlgFrame.h"
#include "CATDlgLabel.h"
#include "CATDlgGridConstraints.h"

// C++ Standard Library
#include "iostream.h"


//-------------------------------------------------------------------
CAADegAnalysisNumericDlg::CAADegAnalysisNumericDlg(CATDialog * iParent): 
             CATDlgDialog (iParent, 
                           "AnalysisNumericDlgId", 
						   CATDlgWndBtnClose|CATDlgGridLayout),
						   _pPlaneVal(NULL),_pPointVal(NULL),_pLineVal(NULL),
						   _pCircleVal(NULL),_pEllipseVal(NULL)
{
  cout << "CAADegAnalysisNumericDlg::CAADegAnalysisNumericDlg" << endl; 
}

//------------------------------------------------------------------------------

CAADegAnalysisNumericDlg::~CAADegAnalysisNumericDlg()
{
  cout << "CAADegAnalysisNumericDlg::~CAADegAnalysisNumericDlg" << endl;
  _pPlaneVal = NULL ;
  _pPointVal = NULL ;
  _pLineVal = NULL ;  
  _pCircleVal = NULL ; 
  _pEllipseVal = NULL ;
}

//---------------------------------------------------------------------

void CAADegAnalysisNumericDlg::Build()
{
   cout << "CAADegAnalysisNumericDlg::Build" << endl;
  
   // Searchs the string to display in the Msg catalog  
   // One Sentence for all element

   CATDlgFrame * pFrame = new CATDlgFrame(this,"FrameId",CATDlgFraNoTitle|CATDlgGridLayout);
   pFrame->SetGridConstraints(0,0,1,1,CATGRID_CENTER);

   CATUnicodeString Zero("   0");

      _pPlaneVal = new CATDlgLabel(pFrame,"PlaneId");
      _pPlaneVal->SetGridConstraints(0,0,1,1,CATGRID_RIGHT);
      _pPlaneVal->SetTitle(Zero);

      CATDlgLabel * PlaneValText = new CATDlgLabel(pFrame,"PlaneTextId");
      PlaneValText->SetGridConstraints(0,1,1,1,CATGRID_RIGHT);

	  _pPointVal = new CATDlgLabel(pFrame,"PointId");
      _pPointVal->SetGridConstraints(1,0,1,1,CATGRID_RIGHT);
      _pPointVal->SetTitle(Zero);
	  
      CATDlgLabel * PointValText = new CATDlgLabel(pFrame,"PointTextId");
      PointValText->SetGridConstraints(1,1,1,1,CATGRID_RIGHT);

	  _pLineVal = new CATDlgLabel(pFrame,"LineId");
      _pLineVal->SetGridConstraints(2,0,1,1,CATGRID_RIGHT);
      _pLineVal->SetTitle(Zero);
	  
      CATDlgLabel * LineValText = new CATDlgLabel(pFrame,"LineTextId");
      LineValText->SetGridConstraints(2,1,1,1,CATGRID_RIGHT);

	  _pCircleVal = new CATDlgLabel(pFrame,"CircleId");
      _pCircleVal->SetGridConstraints(3,0,1,1,CATGRID_RIGHT);
      _pCircleVal->SetTitle(Zero);
	  
      CATDlgLabel * CircleValText = new CATDlgLabel(pFrame,"CircleTextId");
      CircleValText->SetGridConstraints(3,1,1,1,CATGRID_RIGHT);

	  _pEllipseVal = new CATDlgLabel(pFrame,"EllipseId");
      _pEllipseVal->SetGridConstraints(4,0,1,1,CATGRID_RIGHT);
      _pEllipseVal->SetTitle(Zero);
	  
      CATDlgLabel * EllipseValText = new CATDlgLabel(pFrame,"EllipseTextId");
      EllipseValText->SetGridConstraints(4,1,1,1,CATGRID_RIGHT);

}


//--------------------------------------------------------------------------------
void CAADegAnalysisNumericDlg::UpdateValues(int iNbplane, int iNbpoint,
											int iNbline,  int iNbcircle, int iNbellipse)
{
	cout << "CAADegAnalysisNumericDlg::UpdateValues" << endl;

	CATUnicodeString Text;

    Text.BuildFromNum(iNbplane,"%2d");
	_pPlaneVal->SetTitle(Text);

    Text.BuildFromNum(iNbpoint,"%2d");
	_pPointVal->SetTitle(Text);

	Text.BuildFromNum(iNbline,"%2d");
	_pLineVal->SetTitle(Text);

    Text.BuildFromNum(iNbcircle,"%2d");
	_pCircleVal->SetTitle(Text);

    Text.BuildFromNum(iNbellipse,"%2d");
	_pEllipseVal->SetTitle(Text);
}
