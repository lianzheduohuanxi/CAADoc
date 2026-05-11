#ifndef CAAEMaiReplayToolPathCustomization_h
#define CAAEMaiReplayToolPathCustomization_h

// COPYRIGHT DASSAULT SYSTEMES 2002

//===========================================================================
//  Abstract of the sample:
//  -----------------------
//
//  Implementation of CATIMfgReplayToolPathCustom.
//     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the "MfgTPMultipleMotion" Late Type. 
//
//===========================================================================
//  Usage:
//  ------
//
//  Launch CATIA V5, Create a "Facing" operation inside Prismatic
//       Machining Programmer, then replay it. 
//  
//===========================================================================
//  Inheritance:
//  ------------
//
//  CATBaseUnknown (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//  CustomizeToolPathRep
//
//===========================================================================

// Infrastructure interfaces
#include "CATBaseUnknown.h"

// Visualization classes
class CATRep;

class CAAEMaiReplayToolPathCustomization : public CATBaseUnknown
{
  // Used in conjonction with CATImplementClass in the .cpp file
	CATDeclareClass;
  
public:
    CAAEMaiReplayToolPathCustomization();
    virtual ~CAAEMaiReplayToolPathCustomization();
 
    // CustomizeToolPathRep
	//=====================
	// Creates a graphic representation for the "MfgTPMultipleMotion" object
	// to add to the standard graphic representation in the "Tool Path Replay"
	// command.
	//
	//  iOperation  : Current machining operation
	//  iStartPoint : First point of the "MfgTPMultipleMotion" object to take
	//         into account
	//  iEndPoint   : Last point of the "MfgTPMultipleMotion" object to take
	//         into account
	CATRep* CustomizeToolPathRep (const CATBaseUnknown_var& iOperation,int iStartPoint,int iEndPoint);

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEMaiReplayToolPathCustomization
		(const CAAEMaiReplayToolPathCustomization &iObjectToCopy);
 
    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEMaiReplayToolPathCustomization & operator  = 
		(const CAAEMaiReplayToolPathCustomization &iObjectToCopy);
 
};
#endif


