// COPYRIGHT Dassault Systemes 2002

// Local Framework
#include "CAAEPstINFLCOPoint.h"

// ObjectModelerBase Framework
#include "CATIRedrawEvent.h"
#include "LifeCycleObject.h"

// Visualization Framework
#include "CATDelete.h"
#include "CATIModelEvents.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"
#include "CATISpecAttrAccess.h"
#include "CATListOfCATBaseUnknown.h"

// Others
#include "iostream.h"

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_LifeCycleObject.h"
TIE_LifeCycleObject( CAAEPstINFLCOPoint);

// To declare that the class is a data extension of "CAAPstINFPoint" 
//
CATImplementClass(CAAEPstINFLCOPoint,
                  DataExtension, 
                  CATBaseUnknown, 
                  CAAPstINFPoint);

// To declare that CAAEPstINFLCOPoint implements LifeCycleObject for the
// CAAPstINFPoint component, insert the following line in the interface dictionary:
//
//    CAAPstINFPoint   LifeCycleObject   libCAAINFModeler

//-----------------------------------------------------------------------------
// CAAEPstINFLCOPoint : constructor
//-----------------------------------------------------------------------------
CAAEPstINFLCOPoint::CAAEPstINFLCOPoint():
  CATSpecLifeCycleObjectExt()
{
}

//-----------------------------------------------------------------------------
// CAAEPstINFLCOPoint : destructor
//-----------------------------------------------------------------------------
CAAEPstINFLCOPoint::~CAAEPstINFLCOPoint()
{
}

//-----------------------------------------------------------------------------
// Implements LifeCycleObject::remove
//-----------------------------------------------------------------------------
void CAAEPstINFLCOPoint::remove (int forCloseContext )
{
  cout << "******CAAEPstINFLCOPoint::remove" << endl;

  HRESULT rc;

  // Retrieve a list of the objects pointing the object to be deleted: if it is a
  // line, it must also be deleted because its definition will no longer be
  // complete. In the case of the wire, in this particular case, we consider that
  // if any one of the points defining the wire is deleted, the wire is no longer valid
  // and we delete it as well. 

  CATISpecAttrAccess *piSpecAttrAccessOnSelf = NULL;
  rc = QueryInterface(IID_CATISpecAttrAccess, (void**) &piSpecAttrAccessOnSelf);

  if (SUCCEEDED(rc) && piSpecAttrAccessOnSelf)
  {
    // Retrieve a list of spec objects pointing the Point
    CATListValCATBaseUnknown_var *pList = piSpecAttrAccessOnSelf->ListPointingObjects(IID_CATISpecObject);
    piSpecAttrAccessOnSelf -> Release();
    piSpecAttrAccessOnSelf = NULL;
    if (NULL != pList)
    {
      for(int i=1; i<=pList->Size(); i++)
      {
        CATISpecObject_var spPointingObject = (*pList)[i];
        if (NULL_var != spPointingObject)
        {
          CATUnicodeString specType = spPointingObject -> GetType();
          // If the spec object is a "CAAPstINFLine" or "CAAPstINFWire",
          // it must also be deleted.
          if (specType == "CAAPstINFLine" || specType == "CAAPstINFWire")
          {
            // Retrieve the father of the Line or Wire because since it is aggregated, it must
            // be removed from the father level.
            CATISpecObject *piPointingObjFather = spPointingObject -> GetFather();
            if (NULL != piPointingObjFather)
            {
              piPointingObjFather -> Remove(spPointingObject);
              piPointingObjFather -> Release();
              piPointingObjFather = NULL;
            }
          }
        }
      }
    }
    delete pList;
    pList = NULL;
  }
  if (!forCloseContext)
  {
    // Update the navigation tree
    CATIRedrawEvent *piRedrawEventOnFeature = NULL;
    rc = QueryInterface(IID_CATIRedrawEvent, (void**) &piRedrawEventOnFeature);
    if (SUCCEEDED(rc) && piRedrawEventOnFeature)
    {
      piRedrawEventOnFeature -> RedrawParent();
      piRedrawEventOnFeature -> Release();
      piRedrawEventOnFeature = NULL;
    }

    // Force an update of the visualization process
    CATIModelEvents *piModelEventsOnFeature = NULL;
    rc = QueryInterface(IID_CATIModelEvents,(void**) &piModelEventsOnFeature);
    if (SUCCEEDED(rc) && piModelEventsOnFeature)
    {
      CATDelete delNotif (this);
      piModelEventsOnFeature -> Dispatch(delNotif);
      piModelEventsOnFeature -> Release();
      piModelEventsOnFeature = NULL;
    }
  }

  CATSpecLifeCycleObjectExt::remove(forCloseContext);
  return;
}

