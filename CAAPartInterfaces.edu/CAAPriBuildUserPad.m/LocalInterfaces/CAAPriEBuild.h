#ifndef CAAPriEBuild_H
#define CAAPriEBuild_H

// Copyright © 1994-2000 Dassault Systèmes.
// All right reserved

//==========================================================================
//  Sample code for : Part Interfaces
//  Mission         : Implement interface CATIBuild
//                  
//  
//  Type                    : shared library
//  Inputs          : 
//  Outputs         :  
//   
//  Illustrates             : The Build method implementation for Mechanical
//                          : Design form feature
//                    
//
//  Abstract of the sample  :
//  ------------------------
//    
//  The method described here shows how to implemented the CATIBuild interface
//  for a Mechanical Design form feature on a simplified pad named UserPad
//  
//
//  
//===========================================================================

#include "CATBaseUnknown.h"

class CAAPriEBuild : public CATBaseUnknown
{
  CATDeclareClass;

  public:

    CAAPriEBuild ();
    virtual ~CAAPriEBuild ();

    // CATIBuild
    HRESULT Build ();

  private:

    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAPriEBuild (CAAPriEBuild & iObjectToCopy);
    CAAPriEBuild& operator=(CAAPriEBuild & iObjectToCopy);

};
#endif
