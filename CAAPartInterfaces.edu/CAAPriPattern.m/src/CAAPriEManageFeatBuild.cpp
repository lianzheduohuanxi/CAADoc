// Copyright © 1994-2000 Dassault Systèmes.
// All right reserved

// Local Framework
#include "CAAPriEManageFeatBuild.h"


// To declare that the class 
// is a DataExtension of (late type) CAAPriPatternPad
CATImplementClass(CAAPriEManageFeatBuild, 
                  DataExtension,
                  CATBaseUnknown, 
                  CAAPriPatternPad);

#include "TIE_CATIPrtManageFeatBuild.h" // needed to tie the implementation to its interface
TIE_CATIPrtManageFeatBuild(CAAPriEManageFeatBuild);

// To declare that PatternPad implements CATIPrtManageFeatBuild, insert 
// the following line in the interface dictionary:
//
// CAAPriPatternPad  CATIPrtManageFeatBuild  libCAAPriPattern

CAAPriEManageFeatBuild::CAAPriEManageFeatBuild():CATPrtManageFeatBuildExt()
{
}

CAAPriEManageFeatBuild::~CAAPriEManageFeatBuild()
{
}
