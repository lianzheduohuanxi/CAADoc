// COPYRIGHT DASSAULT SYSTEMES 1994-2000
//===================================================================
//
// CAAEOmmVerticalLine.h
// Provide implementation to interface CAAIAOmmVerticalLine
//
//===================================================================
#ifndef CAAEOmmVerticalLine_H
#define CAAEOmmVerticalLine_H

// System framework
#include "CATBaseUnknown.h"        // needed as base implementation class
#include "CATBSTR.h"               // needed to use OLE strings
class     CATBaseDispatch;         // needed as operating system independant IDispatch interface

// InfInterfaces framework
#include "CATIAApplication.h"      // needed as root interface for CATIA object
class CATIAReference;              // needed as a specification handle to OLE objects

// MecModInterfaces framework
#include "CATIAHybridShape.h"      // needed to localize the vertical line in the CATIA exposed model

// SketcherInterfaces framework
#include "CATGeometricType.h"      // needed to identify the vertical line among other geometric objects 

//-----------------------------------------------------------------------
// Class extending the Vertical Line sample feature - CAAOmmVerticalLine
// in order to implement attribute access methods
//-----------------------------------------------------------------------
class  CAAEOmmVerticalLine: public CATBaseUnknown
{
  CATDeclareClass;

  public:

    // Standard constructors and destructors
    CAAEOmmVerticalLine ();
    virtual ~CAAEOmmVerticalLine ();

    // Returns CATIA as an application
    HRESULT  get_Application(CATIAApplication *& opiApplicationOnCATIA);
    // Returns the parent class as regards the exposed modelization
    HRESULT __stdcall get_Parent(CATBaseDispatch *& opiBaseOnOLEParent);

    // Returns the entity name
    HRESULT           get_Name(CATBSTR         & oName);
    // Sets the entity name
    HRESULT           put_Name(const CATBSTR   & iName);

    // Gives an child exposed object when this object is considered as a container
    HRESULT GetItem(const CATBSTR & iName, CATBaseDispatch *& opiBaseOnChildObject);


    // CATIAGeometricalElement Interface method

    // Returns the type of the underlying geometrical element
	HRESULT __stdcall get_GeometricType(CatGeometricType & oType);

    // CATIAHybridShape interface methods

    // Builds the feature geometrical result according to its specifications
    HRESULT __stdcall Compute();

    // Appends a hybrid shape to another hybrid shape
	HRESULT __stdcall AppendHybridShape (CATIAHybridShape *ipiHybridShapeOnShape);

    HRESULT __stdcall get_Thickness(CATIAHybridShape * oThickness);


    // CAAIAOmmVerticalLine interface methods

    // get and set first point line attribute as a reference
    HRESULT __stdcall get_Point1(CATIAReference *& opiReferenceOnPoint1);
    HRESULT __stdcall put_Point1(CATIAReference *  ipiReferenceOnPoint1);

    // get and set second point line attribute as a reference
    HRESULT __stdcall get_Point2(CATIAReference *& opiReferenceOnPoint2);
    HRESULT __stdcall put_Point2(CATIAReference *  ipiReferenceOnPoint2);

  private:
  // In order to avoid public implementation by compilers
  CAAEOmmVerticalLine (CAAEOmmVerticalLine &);
  CAAEOmmVerticalLine& operator=(CAAEOmmVerticalLine&);

};

//-----------------------------------------------------------------------

#endif
