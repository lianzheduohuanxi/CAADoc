// COPYRIGHT DASSAULT SYSTEMES 1994-2000
//===================================================================
//
// CAAEOmmBuildVerticalLine.h
// Provides implementation to interface CATIBuild
//
//===================================================================
#ifndef CAAEOmmBuildVerticalLine_H
#define CAAEOmmBuildVerticalLine_H

// System framework
#include "CATBaseUnknown.h"        // needed as base implementation class

//-----------------------------------------------------------------------
// Class extending the Vertical Line Feature - in order to
// provide its geometrical evaluation
//-----------------------------------------------------------------------

class CAAEOmmBuildVerticalLine : public CATBaseUnknown
{
  CATDeclareClass;

  public:

     // Standard constructors and destructors
     CAAEOmmBuildVerticalLine ();
     virtual ~CAAEOmmBuildVerticalLine ();

     // CATIBuild method

     // Builds the geometrical result of the line according to the thow input points
     virtual HRESULT Build();

  private:
  // In order to avoid public implementation by compilers
  CAAEOmmBuildVerticalLine (CAAEOmmBuildVerticalLine &);
  CAAEOmmBuildVerticalLine& operator=(CAAEOmmBuildVerticalLine&);

};

#endif
