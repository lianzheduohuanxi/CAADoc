// COPYRIGHT Dassault Systemes 2002
//===================================================================
//
// CAAMfgTPECutAreasUserHeader.cpp
// Provide implementation to interface
//    CATIMfgToolPathEditorUserHeader
//    CATIMfgTPECutAreasUserHeader
//
// Sample code for : CAA Manufacturing
// Mission         : Create an implementation of interface CATIMfgTPECutAreasUserHeader.
//                   
//
// Type            : Interactive functionality
//
// How to run it   : 1-Build the CAAMfgTPEAddCmdInCutAreaToolBar.
//                     In this library there is the code that add two commands in the cut area tool bar.
//                   2-Create the runtime view.
//					      3-Launch CATIA.
//                   4-Enter in Surfacic machining workbench in NC Manufacturing workshop.
//                   5-Create a new activity and do the replay.
//                   6-Click on the "Tool Path" contextual menu and choose item "Cut Area"
//                   7-Two new commands are available
//							8-Choose commands to cut area by a point or by polyline.
//===================================================================
//
//========================================================================
// October 2002 Creation                                       C.RIMBAUD 
//========================================================================
//
#include "CAAMfgTPECutAreasUserHeader.h"
#include "CATString.h"
#include "CATListOfCATString.h"
 
CATImplementClass( CAAMfgTPECutAreasUserHeader,
                   CodeExtension,
                   CATBaseUnknown,
                   CATM3xAreaModificationAlgoDriver );
 
//-----------------------------------------------------------------------------
// CAAMfgTPECutAreasUserHeader : constructor
//-----------------------------------------------------------------------------
CAAMfgTPECutAreasUserHeader::CAAMfgTPECutAreasUserHeader():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAAMfgTPECutAreasUserHeader : destructor
//-----------------------------------------------------------------------------
CAAMfgTPECutAreasUserHeader::~CAAMfgTPECutAreasUserHeader()
{
}
 
// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIMfgTPECutAreasUserHeader.h"
TIE_CATIMfgTPECutAreasUserHeader( CAAMfgTPECutAreasUserHeader);
//-----------------------------------------------------------------------------
// Implements CATIMfgTPECutAreasUserHeader::GetHeaders
//-----------------------------------------------------------------------------
HRESULT CAAMfgTPECutAreasUserHeader::GetHeaders (CATListValCATString & ioHeadersList )
{
	HRESULT hRes= S_OK;

	// User's list of Headers of command.
	ioHeadersList.Append(CATString("TPEPolylineSelectionUser"));
	ioHeadersList.Append(CATString("TPEOnePointSelectionUser"));
	return hRes;
}

