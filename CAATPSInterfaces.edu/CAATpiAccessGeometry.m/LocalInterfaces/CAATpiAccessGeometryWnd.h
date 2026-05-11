// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
//
// CAATpiAccessGeometryWnd
//   Works with the state command CATTpiAccessGeometryCmd.
//   Panel to display the geometry analysis of the selected 3D Annotation.
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Fev. 2002  Creation
//=============================================================================

#ifndef CAATpiAccessGeometryWnd_H
#define CAATpiAccessGeometryWnd_H

#include "CATDlgDialog.h"
#include "CATBoolean.h"
#include "CATListOfCATUnicodeString.h"

class CATDlgMultiList;
class CATDlgCheckButton;

//-----------------------------------------------------------------------------
class CAATpiAccessGeometryWnd : public CATDlgDialog
{
  DeclareResource (CAATpiAccessGeometryWnd, CATDlgDialog)

  public:

    CAATpiAccessGeometryWnd( );
    virtual ~CAATpiAccessGeometryWnd();

    HRESULT SetCompositionList (CATListValCATUnicodeString &iCompositionList);
    HRESULT GetRequiredDisplay (CATBoolean * oDisplay3DGrid,
                                CATBoolean * oDisplayTTRSRep);

  private:
    // must not be implemented 
    CAATpiAccessGeometryWnd (CAATpiAccessGeometryWnd &);
    CAATpiAccessGeometryWnd& operator=(CAATpiAccessGeometryWnd&);

    CATDlgMultiList * _pComposList;
    CATDlgCheckButton * _pDisplay3DGridCkB;
    CATDlgCheckButton * _pDisplayTTRSRepCkB;


};
#endif
