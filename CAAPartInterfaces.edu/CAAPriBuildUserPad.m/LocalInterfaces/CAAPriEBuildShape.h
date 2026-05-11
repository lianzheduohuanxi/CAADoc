#ifndef CAAPriEBuildShape_H
#define CAAPriEBuildShape_H

// Copyright © 1994-2000 Dassault Systèmes.
// All right reserved

//==========================================================================
//	Sample code for : Part Interfaces
//	Mission					: Implement interface CATIBuildShape
//									
//	
//	Type				    : shared library
//	Inputs					: 
//	Outputs					:
//	 
//	Illustrates             : The Buildshape method implementation for Mechanical
//                          : Design form feature
//										
// Abstract of the sample	:
// ------------------------
//		
//	The method described here shows how to implemented the CATIBuildShape interface
//  for a Mechanical Design form feature on a simplified pad named UserPad
//	The UserPad specifications are:
//		- a sketch that defines the profile. The sketch must be closed. 
//		- the direction is perpedicular to the sketch plane.
//		- the limits of the pad are defined by offset values:
//		 	the first limit offset value is 30.
//			the second limit offset value is 0, so the pad starts from the sketch plane.
//
//	The differents steps are:
//	1- Retrieving the containers
//	2- Retrieving and defining the specifications of the UserPad operation
//	3- Creating the procedural report
//	4- Performing the shape building
//	5- Storing the procedural report
//
//
//==========================================================================

#include "CATBaseUnknown.h"

class CAAPriEBuildShape : public CATBaseUnknown
{
  CATDeclareClass;

  public:

    CAAPriEBuildShape();
    virtual ~CAAPriEBuildShape();

    // CATIBuildShape
    int BuildShape();

  private:

   // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAPriEBuildShape (CAAPriEBuildShape & iObjectToCopy);
    CAAPriEBuildShape& operator=(CAAPriEBuildShape & iObjectToCopy);

};
#endif
