#ifndef CAADlgElement_H
#define CAADlgElement_H

// COPYRIGHT DASSAULT SYSTEMES 2000

//==============================================================================
//  Abstract of the class:
//  ---------------------
// 
//  Element of the model (CATDlgModel) 
// 
//==============================================================================

// System Framework
#include "CATBaseUnknown.h"

class CAADlgElement: public CATBaseUnknown 
{
  public:

    CAADlgElement(char * iElementName);
    virtual ~CAADlgElement();

    char * GetElementName();


  private:

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgElement ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgElement(const CAADlgElement &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgElement & operator = (const CAADlgElement &iObjectToCopy);

  private:

    // Datum of the element
    char * _pElementName;
};

#endif
