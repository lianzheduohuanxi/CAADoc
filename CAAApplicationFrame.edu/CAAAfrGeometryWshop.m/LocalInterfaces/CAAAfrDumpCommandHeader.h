#ifndef CAAAfrDumpCommandHeader_h
#define CAAAfrDumpCommandHeader_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//
//  Application using a new document (CAAGeometry) with its own workshop and 
//  commands.
//     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Command header of the Dump command.
//  It is customized in order to manage the command availability:
//  the command is available when the document contains objects other
//  than the UIActive object. 
//  The header subscribes to the notification sent by the document 
//  container to be informed when objects are created.
//
//  Illustrates:
//     - customizing a command header
//     - subscribing to notifications
//
//  Usually, you use the macro
//
//       #include <CATCommandHeader.h>
//        MacDeclareHeader(MyHeaderClassName) ;
//
//  to define a command header. But it cannot be customized.
//  In order to customize a command header, you must create a new
//  class derived from CATCommandHeader.
//
//===========================================================================
//  Inheritance:
//  ------------
//           CATCommandHeader (ApplicationFrame Framework)    
//             CATEventSubscriber  (System Framework)
//               CATBaseUnknown (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//  constructor 
//     Subscribes to the container's notification
//
//  AnalyseFilledCB  
//  AnalyseEmptyCB
//     callbacks. Change the command availability.  
//
//===========================================================================

#include <CATCommandHeader.h>  //  Needed to derive from CATCommandHeader

class CAAISysCollection; // to store the container.    

class CAAAfrDumpCommandHeader : public CATCommandHeader
{
  // Used in conjunction with CATImplementHeaderResources in the .cpp file
  CATDeclareHeaderResources;

  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass ;

  public:
   
    // Constructor
    // ------------
    //
    // In CAAApplicationFrame.edu samples, each document contains:
    //    a container which has 
    //       a UI Active which has 0, 1, .... Geometrical Elements
    //  
    // The container collection sends a notification whenever it 
    // is emptied or a first element is added.
    // So this collection is retrieved here to set a callback for this    
    // notification
    // 
    // Finally, the command availability is initialized
    //
    CAAAfrDumpCommandHeader( const CATString & iHeaderName) ;

    virtual ~CAAAfrDumpCommandHeader();

    // Replaces (and uses) the copy constructor 
    CATCommandHeader * Clone() ;
      
  private:

    // Used by the Clone method 
    CAAAfrDumpCommandHeader(CATCommandHeader *iHeaderToCopy);

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrDumpCommandHeader(const CAAAfrDumpCommandHeader &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrDumpCommandHeader & operator = (const CAAAfrDumpCommandHeader &iObjectToCopy);

    // Callbacks to manage the command availability
    //
    void AnalyseFilledCB(CATCallbackEvent     iPublishedEvent,		
                         void              *  iPublishingObject, 
                         CATNotification   *  iPublishNotification,
			             CATSubscriberData    iUsefulData,
			             CATCallback          iCallbackId); 

    void AnalyseEmptyCB(CATCallbackEvent     iPublishedEvent,		
                        void              *  iPublishingObject, 
                        CATNotification   *  iPublishNotification,
			            CATSubscriberData    iUsefulData,
			            CATCallback          iCallbackId); 

  private:

    // Object which sends the event when the document is empty or 
    // when the first element is created. 
    CAAISysCollection *      _pCollection ;
};

#endif




