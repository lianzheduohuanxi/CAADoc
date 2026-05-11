// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAAfrDumpCommandHeader.h"

// model objects 
#include "CAAISysAccess.h"
#include "CAAISysCollection.h"

// ApplicationFrame Framework
#include "CATFrmEditor.h"

// C++ standrad Library
#include <iostream.h>    

// To declare that the class is an implementation
CATImplementClass(CAAAfrDumpCommandHeader, Implementation, CATCommandHeader, CATNull);

//-----------------------------------------------------------------------
// Resource file definition 
//
CATImplementHeaderResources(CAAAfrDumpCommandHeader, // Command header class name
			    CATCommandHeader,                    // Its base class
			    CAAAfrDumpCommandHeader);            // Resource file name 

//-----------------------------------------------------------------------

CAAAfrDumpCommandHeader::CAAAfrDumpCommandHeader(const CATString &iHeaderName):
      CATCommandHeader(iHeaderName,   // Command header Id
	               "CAAAfrGeoCommands", // Command lib name		
		       "CAAAfrDumpCmd",       // Command class Name
		       (void*) NULL)  ,   // No argument
		       _pCollection(NULL)
{
  cout << " CAAAfrDumpCommandHeader constructor" << endl ;

  CATFrmEditor * pEditor = CATFrmEditor::GetCurrentEditor();
   
  if ( NULL != pEditor ) 
  {
    CATPathElement path = pEditor->GetUIActiveObject() ;
    if ( 0 != path.GetSize() ) 
    {
      CATBaseUnknown * pUIActiveObject = NULL ;
      pUIActiveObject = path[path.GetSize()-1] ;
      if ( NULL != pUIActiveObject )
      {
        CAAISysAccess * piSysAccess = NULL;                
        HRESULT rc = pUIActiveObject->QueryInterface(IID_CAAISysAccess, (void**)&piSysAccess);
        if (SUCCEEDED(rc))
        {
          CATBaseUnknown * pContainer = NULL ;
          piSysAccess->GetContainer(&pContainer) ;

          piSysAccess-> Release();
          piSysAccess= NULL ;

          if ( NULL != pContainer)
          {
            CAAISysCollection * piSysCollection = NULL;                
            rc = pContainer->QueryInterface(IID_CAAISysCollection, (void**)&piSysCollection);
            if (SUCCEEDED(rc))
            {
              _pCollection = piSysCollection ;
              //Release done in the destructor 
            } 
            pContainer -> Release();
            pContainer= NULL ;
          }
        }
      }
    }
  }
  
  if ( NULL != _pCollection)
  {
    // Subscribes to CAASysCollectionEmptyNotif and CAASysCollectionFilledNotif
    ::AddCallback(this,   //subscriber
                 _pCollection,  // publisher
                "CAASysCollectionEmptyNotif",  // notification name
		(CATSubscriberMethod)&CAAAfrDumpCommandHeader::AnalyseEmptyCB, // method to call
                NULL);  // parameter for the method to call
    ::AddCallback(this, //subscriber
                _pCollection, // publisher
                "CAASysCollectionFilledNotif",  // notification name 
		(CATSubscriberMethod)&CAAAfrDumpCommandHeader::AnalyseFilledCB, // method to call
                NULL); // parameter for the method to call
   
    int nbobject = 0 ;
    _pCollection->GetNumberOfObjects(&nbobject);
    // the first object is the UIActive object 
    if ( nbobject > 1 )
      BecomeAvailable();
    else
      BecomeUnavailable();
  }
  else
    BecomeUnavailable();

}

//-----------------------------------------------------------------------					   

CAAAfrDumpCommandHeader::~CAAAfrDumpCommandHeader()                     
{
  cout << " CAAAfrDumpCommandHeader destructor" << endl ;

  if ( NULL != _pCollection)
  {
     RemoveSubscriberCallbacks(_pCollection);
     _pCollection->Release();
     _pCollection = NULL ;
  }

}

//-----------------------------------------------------------------------

CATCommandHeader * CAAAfrDumpCommandHeader::Clone() 
{
  cout << " CAAAfrDumpCommandHeader Clone " << endl ;
  return new CAAAfrDumpCommandHeader(this);
}

//-----------------------------------------------------------------------

CAAAfrDumpCommandHeader::CAAAfrDumpCommandHeader(CATCommandHeader * iHeaderToCopy):
                          CATCommandHeader(iHeaderToCopy),
                          _pCollection(NULL)
{
   cout << " CAAAfrDumpCommandHeader Copy const " << endl ;
   
   // Nothing to do 
}					  					  
	
// -----------------------------------------------------------------------
void CAAAfrDumpCommandHeader::AnalyseFilledCB(CATCallbackEvent iPublishedEvent ,
		                          void   * iPublishingObject , 
		                          CATNotification   * iNotif,
				          CATSubscriberData   iUsefulData,
					  CATCallback         iCallbackId)
{
  cout << "Someone has sent a notification to CAAAfrDumpCommandHeader" << endl ;
  
  BecomeAvailable();
} 

// -----------------------------------------------------------------------
	
void CAAAfrDumpCommandHeader::AnalyseEmptyCB(CATCallbackEvent iPublishedEvent ,
		                          void   * iPublishingObject , 
		                          CATNotification   * iNotif,
				          CATSubscriberData   iUsefulData,
					  CATCallback         iCallbackId)
{
  cout << "Someone has sent a notification to CAAAfrDumpCommandHeader" << endl ;
  
  BecomeUnavailable();
} 





