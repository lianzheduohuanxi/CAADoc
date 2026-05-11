// COPYRIGHT Dassault Systemes 2002

#ifndef CAAEPstINFCSO_H
#define CAAEPstINFCSO_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAPstINFPoint, CAAPstINFLine and CAAPstINFWire components,
//  implementing the CATICSOFilter interface to enable the selection of the contextual
//  menu commands.
//
//  Illustrates programming the CSO Filter on an object by implementing the CATICSOFilter
//  interface of the ApplicationFrame framework.
//
//===========================================================================
//  Inheritance:
//  ------------
//            
//  CATBaseUnknown (System Framework) 
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"

// ObjectModelerBase Framework
#include "CATLISTV_CATBaseUnknown.h"

// ApplicationFrame Framework
class CATCSO;

class CAAEPstINFCSO: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     CAAEPstINFCSO ();
     virtual ~CAAEPstINFCSO ();

     // Defines what commands are available in the contextual menu for the Line object.
     HRESULT CommandIsAvailable (const char *ipHeaderID, const CATCSO *ipCSO);

     // Returns the available objects from the current selection.
     HRESULT AvailableElements (const char *ipHeaderID, const CATCSO *ipCSO, CATListValCATBaseUnknown_var **iospAvailableElements);


  private:
  // Copy constructor and equal operator, not implemented
  // Set as private to prevent the compiler from automatically creating them as public.
  // ----------------------------------------------------------------------------------
  CAAEPstINFCSO (CAAEPstINFCSO &);
  CAAEPstINFCSO& operator=(CAAEPstINFCSO&);

};

//-----------------------------------------------------------------------

#endif
