#ifndef CAAPriEManageFeatBuild_H
#define CAAPriEManageFeatBuild_H

// Copyright © 1994-2000 Dassault Systèmes.
// All right reserved

//==========================================================================
//  Sample code for : Part Interfaces
//  Mission					: Implement interface CATIPrtManageFeatBuild
//									
//  CATPrtManageFeatBuildExt	
//
//  Type				    : shared library
//  Inputs					: 
//  Outputs					:
//	 
//  Illustrates     : The way to be able to drive the BuildShape method
//                  : of the feature to be patterned 
//										
// Abstract of the sample	:
// ------------------------
//		
//  In this sample we derived from CATPrtManageFeatBuildExt class that is 
//  an adapter to provide PatternPad feature the way to be patterned
//==========================================================================


#include <CATPrtManageFeatBuildExt.h> // To derive from CATPrtManageFeatBuildExt

class CAAPriEManageFeatBuild : public CATPrtManageFeatBuildExt
{
	CATDeclareClass;

public :

    CAAPriEManageFeatBuild();
	virtual ~CAAPriEManageFeatBuild();

};
#endif
