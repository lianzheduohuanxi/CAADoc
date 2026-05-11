#ifndef CAACafViewerFeedbackManager_h
#define CAACafViewerFeedbackManager_h

// COPYRIGHT DASSAULT SYSTEMES 2003

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  This class manages a visual feedback in the current viewer.  
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"      // Needed to derive from 
#include "CATEventSubscriber.h"  // To set callback
class CATUnicodeString ;         // 

// Visualization/VisualizationBase Frameworks
class CAT2DBagRep ;              // The graphic representation of the feedback
class CATViewer ;                // The viewer with the visual feedback
class CATNotification ;          // for callback methods
class CATPathElement ;           // 

class CAACafViewerFeedbackManager : public CATBaseUnknown
{
  public :

   CAACafViewerFeedbackManager ();

   virtual ~CAACafViewerFeedbackManager();  
	
   // This class has only one instance during the session
   //  
   static void GetManager(CAACafViewerFeedbackManager ** opManager);

   // Method to activate the visual feedback on the current viewer
   void SetViewerFeedbackOn();

   // Method to deactivate the visual feedback on the current viewer
   void SetViewerFeedbackOff();

  private : 

   // Copy constructor, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAACafViewerFeedbackManager(const CAACafViewerFeedbackManager &iObjectToCopy);

   // Assignment operator, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAACafViewerFeedbackManager & operator = (const CAACafViewerFeedbackManager &iObjectToCopy);

   // ViewerFeedbackCB
   // ----------------
   // It's callback to react at viewer interaction
   //
   void ViewerFeedbackCB          (CATCallbackEvent  iEventAlarm,
                           void             *iAlarm,
                           CATNotification  *iNotifAlarm,
                           CATSubscriberData iBurglarData,
                           CATCallback       iCallBack );

   // WindowActivatedCB/WindowDeactivatedCB
   // -----------------------------------------------
   // It's callbacks to react at window modifications
   // in the layout: window deletion, creation, activation,
   // deactication ...
   //
   void WindowActivatedCB          (CATCallbackEvent  iEventAlarm,
                           void             *iAlarm,
                           CATNotification  *iNotifAlarm,
                           CATSubscriberData iBurglarData,
                           CATCallback       iCallBack );

   void WindowDeactivatedCB          (CATCallbackEvent  iEventAlarm,
                           void             *iAlarm,
                           CATNotification  *iNotifAlarm,
                           CATSubscriberData iBurglarData,
                           CATCallback       iCallBack );

   // PathElementString
   // ------------------
   // This method transforms the path in a string
   //
   void  PathElementString(CATPathElement   * ipPath, 
                           CATUnicodeString & oPathName) ;
   // ChangeBagPosition
   // ------------------
   // This method sets the graphic representation bag near
   // of the mouse position. 
   void ChangeBagPosition(float Xpos, float Ypos) ;

  private :

   // The graphic representation bag to display
   // viewer feedback: mouse position, objects under the mouse, ...
   //
   CAT2DBagRep   * _pInformationsToDisplay;

   // This bag is displayed in the main 2D viewpoint of the current viewer
   //
   CATViewer     * _pCurrentViewer ;

   // Callback's identifiers
   //
   CATCallback     _ViewerFeedbackCB ;
   CATCallback     _WindowActivatedCB ;
   CATCallback     _WindowDeactivatedCB ;
   CATCallback     _WindowDeletedCB ;
};
#endif
