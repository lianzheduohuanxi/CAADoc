#ifndef CAAPriEBuildShapeToPattern_H
#define CAAPriEBuildShapeToPattern_H

// Copyright © 1994-2000 Dassault Systèmes.
// All right reserved

//==========================================================================
//  Sample code for : Part Interfaces
//  Mission					: Implement interface CATIBuildShape
//									
//	
//  Type				    : shared library
//  Inputs					: 
//  Outputs					:
//	 
//  Illustrates     : The Builshape method implementation to allow Mechanical 
//                  : Design Form Feature to be patterned.
//										
// Abstract of the sample	:
// ------------------------
//		
//	In this sample we have enriched the CATIBuilShape implementation described
//  in the CAAPriEBuildShape sample to allow the implemented feature to be patterned.
//
//	The differents steps are :
//	1- Defines if the BuildShape method is called in pattern context
//	2- In pattern context, you do not delete the scope
//	3- Sets the list of operands
//	4- Transform geometries generated from specifications 
//  5- Sets topological journal and the geometry performed.
// 
//
//  Return code of the BuildShape method:
//
//  0. Successful creation
//  1. Not closed profile
//  2. Problem on querying an Update Error interface on Pattern Pad
//==========================================================================


#include <CATBaseUnknown.h> // To derive from CATBaseUnknown

class CAAPriEBuildShapeToPattern : public CATBaseUnknown
{
  CATDeclareClass;

  public:
	
    // Constructor
    CAAPriEBuildShapeToPattern();
		
    // Destructor
    virtual ~CAAPriEBuildShapeToPattern();

    // Main method
    int BuildShape();

  private:

    // Copy constructor not implemented
    // Set as private to prevent from compiler automatic creation as public
    CAAPriEBuildShapeToPattern(const CAAPriEBuildShapeToPattern &ipObjectToCopy);
};
#endif
