#ifndef CAAPriEBuildToPattern_H
#define CAAPriEBuildToPattern_H

// Copyright © 1994-2000 Dassault Systèmes.
// All right reserved

//==========================================================================
//  Sample code for : Part Interfaces
//  Mission					: Implement interface CATIBuild
//									
//	
//  Type					  : shared library
//  Inputs					: 
//  Outputs					:  
//	 
//  Illustrates     : The Build method implementation for Mechanical
//							    : Design form feature
//										
//
//  Abstract of the sample	:
//  ------------------------
//		
//  This interface is the same as defined in the CAAPriEBuildUserPad to implement
//  the Build method for PatternPad
// 
//
//  Return code of the Build method:
//
//  0. Successful creation
//  1. CATIBuildShape query interface problem
//  2. Problem during CATIBuildShape run
//  3. No shape built
//  4. No Previous feature
//  
//===========================================================================

#include <CATBaseUnknown.h> // To derive from CATBaseUnknown

class CAAPriEBuildToPattern : public CATBaseUnknown
{
  CATDeclareClass;

  public:

    // Constructor
    CAAPriEBuildToPattern();
    
    // Destructor
    virtual ~CAAPriEBuildToPattern();

    // Main method
    int Build();

  private:

    // Copy Constructor not implemented
    // Set as private to prevent from compiler automatic creation as public
    CAAPriEBuildToPattern(const CAAPriEBuildToPattern &ipObjectToCopy);
};
#endif
