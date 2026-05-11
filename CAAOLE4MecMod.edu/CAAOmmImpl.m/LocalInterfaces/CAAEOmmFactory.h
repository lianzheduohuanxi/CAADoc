// COPYRIGHT DASSAULT SYSTEMES 1994-2000
//===================================================================
//
// CAAEOmmFactory.h
// Provides implementation to interface CAAIAOmmFactory
//
//===================================================================
#ifndef CAAEOmmFactory_H
#define CAAEOmmFactory_H

// System framework
#include "CATBaseUnknown.h"        // needed as base implementation class
#include "CATBSTR.h"               // needed to use OLE strings
class     CATBaseDispatch;         // needed as operating system independant IDispatch interface

// InfInterfaces framework
#include "CATIAApplication.h"      // needed as root interface for CATIA object
class CATIAReference;              // needed as a specification handle to OLE objects

// Local framework
#include "CAAIAOmmVerticalLine.h"  // needed as object created by the factory

//-----------------------------------------------------------------------
// Class extending the Part Root Feature - MechanicalPart - in order to
// provide a Custom Factory implementation
//-----------------------------------------------------------------------

class CAAEOmmFactory : public CATBaseUnknown
{
  CATDeclareClass;

  public:

    // Standard constructors and destructors
    CAAEOmmFactory ();
    virtual ~CAAEOmmFactory ();

    // CATIABase interface methods

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

    // CAAIAOmmFactory interface methods

    // Creates a new CAAOmmVerticalFeature on two mono-dim references
    // but does not append it in any tool
	HRESULT  __stdcall AddNewVerticalLine(
                CATIAReference          *  ipiReferenceOnPoint1,
                CATIAReference          *  ipiReferenceOnPoint2,
                CAAIAOmmVerticalLine    *& opiVerticalLineOnLine);

  private:
  // In order to avoid public implementation by compilers
  CAAEOmmFactory (CAAEOmmFactory &);
  CAAEOmmFactory& operator=(CAAEOmmFactory&);
};

#endif
