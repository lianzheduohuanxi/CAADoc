#ifndef CAAGSMFrmCtxMenuList_H_
#define CAAGSMFrmCtxMenuList_H_
// -------------------------------------------------------------------
// Copyright Dassault Systemes 2006
//---------------------------------------------------------------------
// Shade Design And Styling 
//---------------------------------------------------------------------
// Responsable: BIW
//---------------------------------------------------------------------
// CAAGSMFrmSelectorCtx
//---------------------------------------------------------------------
// 
//  Contextual Item definition management 
//
//---------------------------------------------------------------------
// Historique:
// Creation     : 06/06/01 > PEY 
//---------------------------------------------------------------------

#include "IUnknown.h"
// Declare the list of lines
#include "CATUnicodeString.h"
  
#define iKey_NoMenu                  0
#define iKey_SketchBased             1
#define iKey_PointMenu               2
#define iKey_MidpointMenu            3
#define iKey_EndpointMenu            4
#define iKey_LineMenu                5
#define iKey_PlaneMenu               6
#define iKey_IntersectMenu           7
#define iKey_ProjectMenu             8
#define iKey_AssembleMenu            9
#define iKey_BoundaryMenu           10
#define iKey_ExtractMenu            11
#define iKey_ExtractC0Menu          12
#define iKey_ExtractC1Menu          13
#define iKey_ExtractMultiMenu       14
#define iKey_ExtrapolMenu           15
#define iKey_LawMenu                16
#define iKey_ExtremumMenu           17
#define iKey_CurveSmoothMenu        18
#define iKey_SpineMenu              19
#define iKey_LoftMenu               20
#define iKey_MultiplePointMenu      21
#define iKey_TrimMenu               22
#define iKey_AffinityMenu           23
#define iKey_SplitMenu              24
#define iKey_CurveParMenu           25
#define iKey_AxisSystemMenu         26
#define iKey_ExtrudeMenu            27
#define iKey_OffsetMenu             28
#define iKey_InverseMenu            29
#define iKey_RefPlanesMenu         100
#define iKey_RefAxisMenu           200

// ------------------------------------------------------------------------
// Class CAAGSMFrmCtxMenu / Declare the structure contextuel menu def 
// ------------------------------------------------------------------------
class CAAGSMFrmCtxMenu
{
public :
	CAAGSMFrmCtxMenu(int key ,CATUnicodeString Name, CATUnicodeString Info ,CATUnicodeString Startup, CATUnicodeString Icon,  int iModeInfo); 
	~CAAGSMFrmCtxMenu();
private :
	CAAGSMFrmCtxMenu(CAAGSMFrmCtxMenu&);
	CAAGSMFrmCtxMenu& operator= (CAAGSMFrmCtxMenu&);
public :
	int  _Key;	 
	CATUnicodeString _Name;
	CATUnicodeString _Startup;
	CATUnicodeString _Icon;
	CATUnicodeString _Info;
	int              _imode ;
};

// -------------------------------------------------------------------------------------------
// Class CATListOfCAAGSMFrmCtxMenu / list of CAAGSMFrmCtxMenu 
// -------------------------------------------------------------------------------------------
// Declare the list of lines
#include "CATLISTP_Clean.h"
#include "CATLISTP_AllFunct.h"
#include "CATLISTP_Declare.h"
CATLISTP_DECLARE(CAAGSMFrmCtxMenu)
typedef CATLISTP(CAAGSMFrmCtxMenu) CATListOfCAAGSMFrmCtxMenu;

// -------------------------------------------------------------------------------------------
// Class CAAGSMFrmCtxMenuList / Declare the list of CtxMenu
// -------------------------------------------------------------------------------------------
class CAAGSMFrmCtxMenuList
{
  public :
     ~CAAGSMFrmCtxMenuList();
     static CAAGSMFrmCtxMenuList* GetCtxMenuList();
     static CAAGSMFrmCtxMenuList* pCtxMenuList;

	int Size();
  	CAAGSMFrmCtxMenu* operator[] (int i);
	CAAGSMFrmCtxMenu* GetFromKey (int key) ; 
	HRESULT Declare(int key ,CATUnicodeString Name, CATUnicodeString Info ,CATUnicodeString Startup, CATUnicodeString Icon,  int iModeInfo); 


  protected :
	CAAGSMFrmCtxMenuList();
	CATListOfCAAGSMFrmCtxMenu listOfCtxMenu;
 
  private :
    CAAGSMFrmCtxMenuList(CAAGSMFrmCtxMenuList&);
    CAAGSMFrmCtxMenuList& operator=(CAAGSMFrmCtxMenuList&);

};

#endif

