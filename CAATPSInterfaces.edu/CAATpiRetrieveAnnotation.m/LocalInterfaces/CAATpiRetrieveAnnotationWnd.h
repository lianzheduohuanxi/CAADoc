// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
//
// CAATpiRetrieveAnnotationWnd
//   Works with the state command CATTpiRetrieveAnnotationCmd.
//   Panel to display the list of Alias of the 3D annotations which are
//   linked to the geometry selected.
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Fev. 2002  Creation
//=============================================================================

#ifndef CAATpiRetrieveAnnotationWnd_H
#define CAATpiRetrieveAnnotationWnd_H

#include "CATDlgDialog.h"
#include "CATListOfCATUnicodeString.h"

class CATDlgMultiList;

//-----------------------------------------------------------------------------
class CAATpiRetrieveAnnotationWnd : public CATDlgDialog
{
  DeclareResource (CAATpiRetrieveAnnotationWnd, CATDlgDialog)

  public:

    CAATpiRetrieveAnnotationWnd( );
    virtual ~CAATpiRetrieveAnnotationWnd();

    HRESULT SetAliasList (CATListValCATUnicodeString &iAliasList);

  private:
    // must not be implemented 
    CAATpiRetrieveAnnotationWnd (CAATpiRetrieveAnnotationWnd &);
    CAATpiRetrieveAnnotationWnd& operator=(CAATpiRetrieveAnnotationWnd&);

    CATDlgMultiList * _pAliasList;
};
#endif
