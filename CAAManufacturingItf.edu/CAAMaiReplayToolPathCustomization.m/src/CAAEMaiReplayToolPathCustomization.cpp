// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAAEMaiReplayToolPathCustomization:
//
// Sample code for : Prismatic Machining Programmer
// Mission         : Customizes the graphic representation of tool path for
//                   "Tool Path Replay" command
//
//
// Type            : Interactive functionality
//
// Illustrates     : Use of manufacturing interfaces 
//
// How to run it   :  
//					In the file CAAManufacturingItf.dico, decomment the following line  
//						MfgTPMultipleMotion  CATIMfgReplayToolPathCustom libCAAMaiReplayToolPathCustomization
//
//					In Prismatic Machining Programmer, 
//                         create a Facing operation (for example) and replay the tool path
//
//
//=============================================================================

#include "CAAEMaiReplayToolPathCustomization.h"

// Manufacturing Interfaces
#include "CATIMfgTPMultipleMotion.h"

// Visualization
#include "CAT3DBagRep.h"
#include "CAT3DPointRep.h"

//-----------------------------------------------------------------------------
// Supported Interfaces
//-----------------------------------------------------------------------------


#include "TIE_CATIMfgReplayToolPathCustom.h"
TIE_CATIMfgReplayToolPathCustom(CAAEMaiReplayToolPathCustomization);
CATImplementClass (CAAEMaiReplayToolPathCustomization,
				   DataExtension,
				   CATBaseUnknown,
				   MfgTPMultipleMotion);

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------

CAAEMaiReplayToolPathCustomization::CAAEMaiReplayToolPathCustomization()
{
}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------

CAAEMaiReplayToolPathCustomization::~CAAEMaiReplayToolPathCustomization()
{
}

//-----------------------------------------------------------------------------
// CustomizeToolPathRep
//-----------------------------------------------------------------------------
CATRep* CAAEMaiReplayToolPathCustomization::CustomizeToolPathRep (const CATBaseUnknown_var& iOperation,int iStartPoint,int iEndPoint)
{
	// In this sample, no test is done on "iOperation" (current operation)
	// By testing "iOperation", it is possible to have a different behaviour for
	// each machining operation

	// Retrieves an handler on the current MfgTPMultipleMotion object
	CATIMfgTPMultipleMotion_var MultipleMotion (GetImpl());
	if (NULL_var == MultipleMotion) return NULL;

	// Creates a bag to store the several reps 
	CAT3DBagRep* BagRep = new CAT3DBagRep ();
	if (NULL == BagRep) return NULL;

	// Associates a graphic point to each tip point if the MfgTPMultipleMotion object
	CATMathPoint Pt;
	double x,y,z;
	for (int i=iStartPoint;i<=iEndPoint;i++)
	{
		if (MultipleMotion->GetTipPoint (i,x,y,z))
		{
			Pt.SetCoord (x,y,z);
			CAT3DPointRep* RepPoint = new CAT3DPointRep (Pt,FULLSQUARE);
			if (NULL != RepPoint) BagRep->AddChild (*RepPoint);
		}
	}

	// Returns bag rep
	return BagRep;
}
