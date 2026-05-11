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
#include "CAAGSMFrmCtxMenuList.h" 
#include "CATError.h"



//---------------------------------------------------------------------
// CAAGSMFrmCtxMenu 
//---------------------------------------------------------------------
// -- Constructor 
CAAGSMFrmCtxMenu::CAAGSMFrmCtxMenu(int key ,CATUnicodeString Name, CATUnicodeString Info ,CATUnicodeString Startup, CATUnicodeString Icon,   int iModeInfo)
: _Key (key), _Startup(Startup), _Name(Name) , _Icon(Icon), _Info(Info), _imode (iModeInfo) 
{ }

// -- Destructor 
CAAGSMFrmCtxMenu::~CAAGSMFrmCtxMenu()
{ 
	_Key    = 0 ;
	_Name    = "";
	_Startup  = "";
	_Icon    = "";
	_Info    = "";
	_imode   = 0  ;
}

//---------------------------------------------------------------------
// CATListOfCAAGSMFrmCtxMenu 
//---------------------------------------------------------------------
#include "CATLISTP_Define.h"
CATLISTP_DEFINE(CAAGSMFrmCtxMenu);

//---------------------------------------------------------------------
// CAAGSMFrmCtxMenuList 
//---------------------------------------------------------------------

// -- Constructor 
//---------------------------------------------------------------------
CAAGSMFrmCtxMenuList::CAAGSMFrmCtxMenuList()
{

	Declare(   0,"None"	            ,"none"                     ," "                 ," "                          , 0 );   // 0 Id_NoMenu,					   
	Declare(   1,"Sketch"           ,"ItemSketch"               ,"GSMSketchStacked"  ,"I_Sketcher"                 , 0 );   // 1 Id_SketchMenu,					
	Declare(   2,"Point"            ,"ItemPoint"                ,"GSMPoint"          ,"I_Point"                    , 0 );   // 2 Id_PointMenu,					
	Declare(   3,"MidPoint"         ,"ItemMidPoint"             ,"GSMMidpoint"       ,"I_Midpoint"                 , 0 );   // 3 Id_MidpointMenu,				
	Declare(   4,"EndPoint"         ,"ItemEndPoint"             ,"GSMEndpoint"       ,"I_Endpoint"                 , 0 );   // 4 Id_EndpointMenu,				
	Declare(   5,"Line"             ,"ItemLine"                 ,"GSMLine"           ,"I_Line"                     , 0 );   // 5 Id_LineMenu,					
	Declare(   6,"Plane"            ,"ItemPlane"                ,"GSMPlane"          ,"I_Plane"                    , 0 );   // 6 Id_PlaneMenu,					
	Declare(   7,"Intersect"        ,"ItemIntersect"            ,"GSMIntersect"      ,"I_Intersection"             , 0 );   // 7 Id_IntersectMenu,				
	Declare(   8,"Project"          ,"ItemProject"              ,"GSMProject"        ,"I_Project"                  , 0 );   // 8 Id_ProjectMenu,					
	Declare(   9,"Join"             ,"ItemJoin"                 ,"GSMAssemble"       ,"I_AssembleBipar"            , 0 );   // 9 Id_AssembleMenu,				
	Declare(  10,"Boundary"         ,"ItemBoundary"             ,"GSMBoundary"       ,"I_Boundary"                 , 0 );   // 10 Id_BoundaryMenu,				
	Declare(  11,"Extract"          ,"ItemExtract"              ,"GSMExtract"        ,"I_Extract"                  , 0 );   // 11 Id_ExtractMenu,					
	Declare(  12,"ExtractC0"        ,"ItemExtractC0"            ,"GSMExtractC0"      ,"I_ExtractC0"                , 0 );   // 12 Id_ExtractC0Menu,				
	Declare(  13,"ExtractC1"        ,"ItemExtractC1"            ,"GSMExtractC1"      ,"I_ExtractC1"                , 0 );   // 13 Id_ExtractC1Menu,				
	Declare(  14,"ExtractMulti"     ,"ItemExtractMulti"         ,"GSMMultiExtract"   ,"I_MultiExtract"             , 0 );   // 14 Id_ExtractMultiMenu,			
	Declare(  15,"Extrapol"         ,"ItemExtrapol"             ,"GSMExtrapol"       ,"I_Extrapol"                 , 0 );   // 15 Id_ExtrapolMenu,				
	Declare(  16,"Law"              ,"ItemLaw"                  ,"GSMLaw"            ,"I_Law"                      , 0 );   // 16 Id_LawMenu,						
	Declare(  17,"Extremum"         ,"ItemExtremum"             ,"GSMExtremum"       ,"I_Extremum"                 , 0 );   // 17 Id_ExtremumMenu,				
	Declare(  18,"CurveSmooth"      ,"ItemCurveSmooth"          ,"GSMCurveSmooth"    ,"I_CurveSmooth"              , 0 );   // 18 Id_CurveSmoothMenu,				
	Declare(  19,"Spine"            ,"ItemSpine"                ,"GSMSpine"          ,"I_Spine"                    , 0 );   // 19 Id_SpineMenu,					
	Declare(  20,"Loft"             ,"ItemLoft"                 ,"GSMLoft"           ,"I_LoftOnCurveNetwork"       , 0 );   // 20 Id_LoftMenu,					
	Declare(  21,"Multiple Point"   ,"ItemMultiple Point"       ,"GSMMultiplePoint"  ,"I_MultiplePoint"            , 0 );   // 21 Id_MultiplePointMenu,			
	Declare(  22,"Trim"             ,"ItemTrim"                 ,"GSMTrim"           ,"I_TrimSurfaces"             , 0 );   // 22 Id_TrimMenu,					
	Declare(  23,"Affinity"         ,"ItemAffinity"             ,"GSMAffinity"       ,"I_Affinity"                 , 0 );   // 23 Id_AffinityMenu	,				
	Declare(  24,"Split"            ,"ItemSplit"                ,"GSMSplit"          ,"I_Split"                    , 0 );   // 24 Id_SplitMenu,					
	Declare(  25,"CurvePar"         ,"ItemCurvePar"             ,"GSMCurvePar"       ,"I_Parallel"                 , 0 );   // 25 Id_CurveParMenu,				
	Declare(  26,"AxisSystem"       ,"ItemAxisSystem"           ,"AxisSystem"        ,"I_3DAxisSystem"             , 0 );   // 26 Id_AxisSystemMenu,				
	Declare(  27,"Extrude"          ,"ItemExtrude"              ,"GSMExtrude"        ,"I_ExtrudeSurfaceFromCurve"  , 0 );   // 27 Id_ExtrudeMenu,					
	Declare(  28,"Offset"           ,"ItemOffset"               ,"GSMOffset"         ,"I_OffsetGeometry"           , 0 );   // 28 Id_OffsetMenu,					
	Declare(  29,"Inverse"          ,"ItemInverse"              ,"GSMInverse"        ,"I_Inverse"                  , 1 );   // 29 Id_InverseMenu,					
	Declare( 101,"XY Plane"         ,"ItemXYPlane"              ,"GSMAxisExplicit"   ,"I_Plane"                    , 1 );   // 0 Id_RefPlanesMenu				
	Declare( 102,"YZ Plane"         ,"ItemYZPlane"              ,"GSMAxisExplicit"   ,"I_Plane"                    , 1 );   // 1 Id_RefPlanesMenu				
	Declare( 103,"ZX Plane"         ,"ItemZXPlane"              ,"GSMAxisExplicit"   ,"I_Plane"                    , 1 );   // 2 Id_RefPlanesMenu				
	Declare( 104,"Local XY Plane"   ,"ItemLocalXYPlane"         ,"GSMAxisExplicit"   ,"I_Plane"                    , 1 );   // 3 Id_RefPlanesMenu				
	Declare( 105,"Local YZ Plane"   ,"ItemLocalYZPlane"         ,"GSMAxisExplicit"   ,"I_Plane"                    , 1 );   // 4 Id_RefPlanesMenu				
	Declare( 106,"Local ZX Plane"   ,"ItemLocalZXPlane"         ,"GSMAxisExplicit"   ,"I_Plane"                    , 1 );          // 5 Id_RefPlanesMenu				
	Declare( 201,"X_Axis"           ,"ItemX_Axis"               ,"GSMAxisExplicit"   ,"I_LineXAxis"                , 1 );   // 0 Id_RefAxisMenu					
	Declare( 202,"Y_Axis"           ,"ItemY_Axis"               ,"GSMAxisExplicit"   ,"I_LineYAxis"                , 1 );   // 1 Id_RefAxisMenu					
	Declare( 203,"Z_Axis"           ,"ItemZ_Axis"               ,"GSMAxisExplicit"   ,"I_LineZAxis"                , 1 );   // 2 Id_RefAxisMenu					
	Declare( 204,"LocalX_Axis"      ,"ItemLocalX_Axis"          ,"GSMAxisExplicit"   ,"I_LineXAxis"                , 1 );   // 3 Id_RefAxisMenu					
	Declare( 205,"LocalY_Axis"      ,"ItemLocalY_Axis"          ,"GSMAxisExplicit"   ,"I_LineYAxis"                , 1 );   // 4 Id_RefAxisMenu					
	Declare( 206,"LocalZ_Axis"      ,"ItemLocalZ_Axis"          ,"GSMAxisExplicit"   ,"I_LineZAxis"                , 1 );   // 5 Id_RefAxisMenu					
	Declare( 207,"CompassDirection" ,"ItemC_CompassDirection"   ,"GSMAxisExplicit"   ,"I_CompassDir"               , 1 );   // 6 Id_RefAxisMenu
	Declare( 300,""                 ,""                         ,""                  ,""                           , 0 );
}

// -- Destructor 
//---------------------------------------------------------------------
CAAGSMFrmCtxMenuList::~CAAGSMFrmCtxMenuList()
{
  int size=listOfCtxMenu.Size(); 
  for(int i=1; i<=size; i++)
  {
   CAAGSMFrmCtxMenu* pCtxMenu = listOfCtxMenu[i];
	if(NULL!=pCtxMenu) {
		delete pCtxMenu;
	}
  }
  listOfCtxMenu.RemoveAll();
}

// -- Menu List 
//---------------------------------------------------------------------
CAAGSMFrmCtxMenuList* CAAGSMFrmCtxMenuList::pCtxMenuList=NULL;

// -- Get Menu List 
//---------------------------------------------------------------------
CAAGSMFrmCtxMenuList* CAAGSMFrmCtxMenuList::GetCtxMenuList()
{
	if(NULL==pCtxMenuList) {
		pCtxMenuList=new CAAGSMFrmCtxMenuList();
	}
	return pCtxMenuList;
}

// -- Declare Menu Item 
//---------------------------------------------------------------------
HRESULT CAAGSMFrmCtxMenuList::Declare (int key ,CATUnicodeString Name, CATUnicodeString Info , CATUnicodeString Startup, CATUnicodeString Icon,  int iModeInfo)
{
  CAAGSMFrmCtxMenu* pCtxMenu=new CAAGSMFrmCtxMenu( key , Name, Info, Startup, Icon, iModeInfo); 
  if(NULL==pCtxMenu) return CATReturnFailure;

  listOfCtxMenu.Append(pCtxMenu);
  return CATReturnSuccess;
}


// -- Size Menu List 
//---------------------------------------------------------------------
int CAAGSMFrmCtxMenuList::Size()
{
  return listOfCtxMenu.Size();
}

// -- [] 
//---------------------------------------------------------------------
CAAGSMFrmCtxMenu* CAAGSMFrmCtxMenuList::operator[] (int i)
{
  return listOfCtxMenu[i];
}
// -- GetMenu from Key 
//---------------------------------------------------------------------
CAAGSMFrmCtxMenu* CAAGSMFrmCtxMenuList::GetFromKey (int key) 
{
	int iFound = 0 ; 
	CAAGSMFrmCtxMenu* pCtxMenu = NULL; 
	int size=listOfCtxMenu.Size(); 
	for(int i=1; i<=size; i++)
	{
		pCtxMenu=listOfCtxMenu[i];
		if (NULL!=pCtxMenu ){
			if ( key == pCtxMenu->_Key ) iFound = 1 ; 
		}
		if (iFound) break;
	}
	if (iFound )  
		return pCtxMenu ;
	else 
		return NULL; 

}

