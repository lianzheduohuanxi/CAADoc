// COPYRIGHT Dassault Systemes 2002

#ifndef CAAEPstINFCSORoot_H
#define CAAEPstINFCSORoot_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAPstINFRoot component, implementing the CATICSOFilter 
//  interface to enable the selection of the contextual menu commands.
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

class CAAEPstINFCSORoot: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     CAAEPstINFCSORoot ();
     virtual ~CAAEPstINFCSORoot ();

     // Defines what commands are available in the contextual menu for the Root object.
     HRESULT CommandIsAvailable (const char *ipHeaderID, const CATCSO *ipCSO ) ;

     
	 // Returns the available objects from the current selection.
     HRESULT AvailableElements (const char *ipHeaderID, const CATCSO *ipCSO, CATListValCATBaseUnknown_var **iospAvailableElements);

  private:
  // Copy constructor and equal operator, not implemented
  // Set as private to prevent the compiler from automatically creating them as public.
  // ----------------------------------------------------------------------------------
  CAAEPstINFCSORoot (CAAEPstINFCSORoot &);
  CAAEPstINFCSORoot& operator=(CAAEPstINFCSORoot&);

};

//-----------------------------------------------------------------------

#endif
