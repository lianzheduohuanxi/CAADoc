#ifndef CAAEGSMSewSkinBasic_H
#define CAAEGSMSewSkinBasic_H
// COPYRIGHT Dassault Systemes 2006
//===================================================================
//
// CAAEGSMSewSkinBasic.h
// Provide implementation to interface
//    CAAISewSkin
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//   IMPLEMENTATION
//   TIE: CAAISewSkin
//===================================================================


#include "CATBaseUnknown.h"
#include "CATGSMOrientation.h"
#include "CATGSMContextDef.h"
//-----------------------------------------------------------------------

/**
 * Implement CAAISewSkin on CAASewSkinBasic LateType. 
 */

class CATISpecObject ; 
class CAAEGSMSewSkinBasic: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     CAAEGSMSewSkinBasic ();
     virtual ~CAAEGSMSewSkinBasic ();
	

    /**
     * Implements a function from an interface.
     * @see CAATestFw.CAAISewSkin#SetSurfaceToSew
     */
     HRESULT SetSurfaceToSew (CATISpecObject_var  ispSurfaceToSew ) ;

    /**
     * Implements a function from an interface.
     * @see CAATestFw.CAAISewSkin#GetSurfaceToSew
     */
    // HRESULT GetSurfaceToSew (CATISpecObject ** ioSurfaceToSew ) ;
    HRESULT GetSurfaceToSew (CATISpecObject_var & ospSurfaceToSew );
    
    /**
     * Implements a function from an interface.
     * @see CAATestFw.CAAISewSkin#SetSurfaceSupport
     */
     HRESULT SetSurfaceSupport (CATISpecObject_var ispSupport ) ;

    /**
     * Implements a function from an interface.
     * @see CAATestFw.CAAISewSkin#GetSurfaceSupport
     */
//     HRESULT GetSurfaceSupport (CATISpecObject ** ioSupport ) ;
    HRESULT GetSurfaceSupport (CATISpecObject_var & ospSupport);
    
 
    /**
     * Implements a function from an interface.
     * @see CAATestFw.CAAISewSkin#SetOrientation
     */
	  HRESULT SetOrientation(CATGSMOrientation iOrientation) ;


    /**
     * Implements a function from an interface.
     * @see CAATestFw.CAAISewSkin#GetOrientation
     */
     HRESULT GetOrientation(CATGSMOrientation & oOrientation);


    /**
     * Implements a function from an interface.
     * @see CAATestFw.CAAISewSkin#InvertOrientation
     */
	 HRESULT InvertOrientation() ;

  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAAEGSMSewSkinBasic (CAAEGSMSewSkinBasic &);
  CAAEGSMSewSkinBasic& operator=(CAAEGSMSewSkinBasic&);

};

//-----------------------------------------------------------------------

#endif
