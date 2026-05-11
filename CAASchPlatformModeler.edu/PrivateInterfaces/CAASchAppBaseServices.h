// COPYRIGHT DASSAULT SYSTEMES  2001+ 
//=============================================================================
//

#ifndef CAASchAppBaseServices_H
#define CAASchAppBaseServices_H

#include "CAASchAppBase.h" 

// ProductStructure
#include "CATIProduct.h"

// System
#include "CATUnicodeString.h"

// ObjectModelerBase
#include "CATIContainer.h"
#include "CATDocument.h"

// ObjectSpecsModeler
#include "CATISpecObject.h"
#include "CATBooleanDef.h"

#include "CATLISTV_CATISpecObject.h"

class CATDocument;
class CATFrmEditor;
class CATFrmWindow;
class CATIConnector_var;

//-----------------------------------------------------------------------------
class ExportedByCAASchAppBase CAASchAppBaseServices 
{
  public:

  //---------------------------------------------------------------------------
  //  Find a document in session.  Does not assume an active CATFrmEditor.
  //  If the current session is an interactive session (as oppose to a batch)
  //  the document returned is the current document and iDocType is not used.
  //  If running batch and iDocType is NULL, the default type is returned.
  //  E.g. of iDocType: CATDrawing, CATProduct...
  //---------------------------------------------------------------------------
  static CATDocument *GetDocInSession (const char *iDocType = NULL);

  //---------------------------------------------------------------------------
  //  Find a feature object in a container by a specific name
  //---------------------------------------------------------------------------
  static CATISpecObject_var FindFeatureByName (
     const char *iObjectName, const CATIContainer_var &iCont);

  //---------------------------------------------------------------------------
  //  Find a route reference in a container by a specific class type
  //---------------------------------------------------------------------------
  static CATISpecObject_var FindRouteRefByClass (
     const CATUnicodeString &iUClass, const CATIContainer_var &iCont);


  //---------------------------------------------------------------------------
  //  Get Product Root object
  //---------------------------------------------------------------------------
  static CATIProduct_var GetProductRootObject (CATDocument *iDoc = NULL);

  //---------------------------------------------------------------------------
  //  Get product application object container
  //---------------------------------------------------------------------------
  static CATIContainer_var GetAppObjContainer (CATDocument *iDoc);   

  //---------------------------------------------------------------------------
  //  Get the schematic root object
  //---------------------------------------------------------------------------
  static CATISpecObject_var GetSchematicRoot (CATDocument *iDoc = NULL);    

  //---------------------------------------------------------------------------
  //  Get the schematic root object
  //---------------------------------------------------------------------------
  static CATISpecObject_var FindAppObjByClass (
    const CATUnicodeString &iUClass, const CATIContainer_var &iCont);

  static HRESULT FindAppObjByClass (
    const CATUnicodeString &iUClass, const CATIContainer_var &iCont,
    CATListValCATISpecObject_var &oLAppObjects);

  static HRESULT RemoveAppObjInstByClass (
   const CATUnicodeString &iUClass, CATDocument *iDoc);

};
#endif
