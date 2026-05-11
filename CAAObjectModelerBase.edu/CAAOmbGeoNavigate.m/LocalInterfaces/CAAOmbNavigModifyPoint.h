#ifndef CAAOmbNavigModifyPoint_h
#define CAAOmbNavigModifyPoint_h
// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract of the Use Case:
//  ------------------------
//
//  This is an implementation of the CATINavigModify interface.
//  to illustrate how to set a specific short help text. 
//  This implementation is done on the CAASysPoint object. It is an element
//  of a CAAGeometry's document. 
//
//******************************************************************************

// ObjectModelerBase Framework
#include "CATNodeExtension.h"             // Needed to derive from

// ObjectModelerBase Framework
class CATNavigInstance;

class CAAOmbNavigModifyPoint : public CATNodeExtension
{
   // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public :

    CAAOmbNavigModifyPoint();
    virtual ~CAAOmbNavigModifyPoint();

    // ModifyShortHelp
    // ---------------
    // To set the point' coordinates in the short help
    //
    virtual HRESULT ModifyShortHelp(CATUnicodeString & ioText) ;

  private :

    // Copy constructor, not implemented
    // Set as private to prevent the automatic creation as public by the compiler.
    CAAOmbNavigModifyPoint(const CAAOmbNavigModifyPoint &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAOmbNavigModifyPoint & operator = (const CAAOmbNavigModifyPoint &iObjectToCopy);
};

#endif
