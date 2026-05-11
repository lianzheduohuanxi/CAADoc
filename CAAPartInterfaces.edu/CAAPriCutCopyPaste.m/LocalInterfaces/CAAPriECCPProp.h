#ifndef CAAPriECCPProp_H
#define CAAPriECCPProp_H

// Copyright © 1994-2000 Dassault Systèmes.
// All right reserved

//==========================================================================
//  Sample code for : Part Interfaces
//  Mission					: Implement interface CATIShapeFeatureProperties
//									
//		
//==========================================================================


#include "CATMmrShapeFeaturePropertiesAdapter.h"    // needed to derive from 

class CATListValCATISpecObject_var;

class CAAPriECCPProp : public CATMmrShapeFeaturePropertiesAdapter
{
  CATDeclareClass;

  public:
    
    CAAPriECCPProp ();
    virtual ~CAAPriECCPProp ();

    //-------------------------------------------------------------------------
    // GetPolarity
    // This method returns the polarity (Add/Remove) of the feature
    // The UserPad is of Add polarity
    //-------------------------------------------------------------------------
    CATUnicodeString GetPolarity () ;
	
    //-------------------------------------------------------------------------
    // GiveMeYourFavoriteSketches
    // This method returns the sketches not aggregated by feature.
    // The UserPad has a profile attribute that used a sketch. 
    // This sketch is not aggregated so it is returned.
    //-------------------------------------------------------------------------
    CATLISTV(CATISpecObject_var) GiveMeYourFavoriteSketches();

 private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAPriECCPProp (CAAPriECCPProp & ObjectToCopy);
    CAAPriECCPProp& operator=(CAAPriECCPProp &ObjectToCopy);

};
#endif
