// COPYRIGHT Dassault Systemes 2000
//===================================================================
//
// CAAAniADImport.h Provide implementation to interface CATISamImport
//
//===================================================================
#ifndef CAAAniADImport_H
#define CAAAniADImport_H

#include "CATBaseUnknown.h"
#include "CATString.h"              // Management of the CATString
#include "CATDocument.h"            // Management of CATDocument
#include "CATAnalysisExplicitTypes.h"            // Management of CATDocument

class CATISpecObject;
class CATIMSHMesh;
class CATIMSHMeshPart;
class CATIMSHMeshManager;
class CATMSHNode;
class CATMSHElement;
class CATISamAnalysisModel;
class CATAnalysisExplicitSet;
class CATAnalysisExplicitModel;
class CATAnalysisExplicitListUsr;

/**
 * Class Object modeler implementation class.
 * <br>
 * It implements the interfaces :
 *  <ol>
 *  <li>@see CAAAnalysisInterfaces.edu.CAAIAniAeroImport
 *  </ol>
 */
class CAAAniADImport: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     CAAAniADImport ();
     virtual ~CAAAniADImport ();

    /**
     * Implements a function from an interface.
     * @see CATAnalysisInterfaces.CAAIAniAeroImport #Import
     */
     HRESULT Import (CATDocument * idocument) ;


    /**
     * Implements a function from an interface.
     * @see CAAAnalysisInterfaces.edu.CAAIAniAeroImport #ImportFif
     */
     HRESULT ImportFif (CATIMSHMeshPart * ipMeshPart,
						            CATIMSHMesh * ipMesh);

    /**
     * Implements a function from an interface.
     * @see CAAAnalysisInterfaces.edu.CAAIAniAeroImport#ImportFif
     */
     HRESULT TranslateToFieldModel(CATISpecObject* iFeatToTranslate, 
                                   CATISamAnalysisModel* ipFEMModel, 
                                   CATAnalysisExplicitListUsr& iOldExplObjects, 
                                   CATAnalysisExplicitListUsr& oNewExplObjects);

	/**
     * Method that will be called at each renaming of the analysis document.
     */
	 void OnRenameCB(CATCallbackEvent,void*,CATNotification *notif,
                                    CATSubscriberData,CATCallback);
 
	/**
     * Method that will be called at each renaming of the fif document.
     */
	 void OnRenameCB2(CATCallbackEvent,void*,CATNotification *notif,
                                    CATSubscriberData,CATCallback);

  private:
      // The copy constructor and the equal operator must not be implemented
      // -------------------------------------------------------------------
      CAAAniADImport (CAAAniADImport &);
      CAAAniADImport& operator=(CAAAniADImport&);

     /**
      * Retreive This as CATDocument pointer.
      */ 
      CATDocument * GetDocument();
  

};
//-----------------------------------------------------------------------

#endif
