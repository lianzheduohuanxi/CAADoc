// COPYRIGHT Dassault Systemes 2001
//===================================================================
//
// CAAIAniAeroImport.h
// Define the CAAIAniAeroImport interface
//
//===================================================================
//
// Usage notes:
//   New interface: describe its use here
//
//===================================================================
//
//===================================================================
#ifndef CAAIAniAeroImport_H
#define CAAIAniAeroImport_H

#include "CATBaseUnknown.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern IID IID_CAAIAniAeroImport;
#else
extern "C" const IID IID_CAAIAniAeroImport ;
#endif

class CATDocument;
class CATISpecObject;
class CATIMSHMeshPart;
class CATIMSHMesh;
class CATISamAnalysisModel;
class CATAnalysisExplicitListUsr;

//------------------------------------------------------------------

/**
 * Describe the functionality of your interface here
 * <p>
 * Using this prefered syntax will enable mkdoc to document your class.
 */

class CAAIAniAeroImport: public CATBaseUnknown
{
  CATDeclareInterface;

  public:

    virtual HRESULT Import (CATDocument * ipAnalysisDoc) = 0 ;


    virtual HRESULT ImportFif (CATIMSHMeshPart * MeshPart,CATIMSHMesh * ipMesh) = 0;

  // Create the field model objects
    virtual HRESULT TranslateToFieldModel(CATISpecObject* iFeatToTranslate, 
                                          CATISamAnalysisModel* iFEMModel, 
                                          CATAnalysisExplicitListUsr& iOldExplObjects, 
                                          CATAnalysisExplicitListUsr& oNewExplObjects) = 0;
};

CATDeclareHandler(CAAIAniAeroImport,CATBaseUnknown);
//------------------------------------------------------------------

#endif
