---
```vbscript
title: "Viewer Feedback"
category: "use case"
module: "CAAVisUseCases"
tags: ["CAAAfrGeneralWksAddin", "CAAApplicationFrame", "CAACafViewerFeedback", "CATIWorkbenchAddin", "CAACafViewerFeedbackCmd", "CAACATIAApplicationFrm", "CATIAlias", "CAACafViewerFeedbackManager", "CATIAfrGeneralWksAddin"]
source_file: "Doc/online/CAAVisUseCases/CAAVisViewerFeedback.htm"
converted: "2026-05-11T17:31:52.253960"
```

---
# 3D PLM Enterprise Architecture

|
## 3D Visualization

|
### Viewer Feedback

_How to retrieve information on interactions coming from viewers_
---|---|---
Use Case

* * *
### Abstract

This article shows how to retrieve and analyze information on interactions coming from viewers. These interactions can be mouse motion or press/release button.

  * **What You Will Learn With This Use Case**
  * **The CAACafViewerFeedback Use Case**
    * What Does CAACafViewerFeedback Do
    * How to Launch CAACafViewerFeedback
    * Where to Find the CAACafViewerFeedback Code
  * **Step-by-Step**
  * **In Short**
  * **References**

* * *
### What You Will Learn With This Use Case

This use case is intended to show you how to retrieve and analyze information on interactions coming from viewers. You will learn how to:

  * Activate or deactivate the sending of event when interactions occur in a viewer
This use case is intended to show you how to retrieve and analyze information on interactions coming from viewers. You will learn how to:
The activation/deactivation mode is called the **feedback** mode.

  * Analyze the notification associated with the event
This use case is intended to show you how to retrieve and analyze information on interactions coming from viewers. You will learn how to:
The activation/deactivation mode is called the **feedback** mode.
The notification is a _CATVisViewerFeedbackEvent_ notification class.

  * Display on the screen information contained in the notification
The activation/deactivation mode is called the **feedback** mode.
The notification is a _CATVisViewerFeedbackEvent_ notification class.
Information will be displayed in the main 2D viewpoint of the viewer.

[Top]
### The CAACafViewerFeedback Use Case

CAACafViewerFeedback is a use case of CAACATIAApplicationFrm.edu and CAAApplicationFrame.edu frameworks that illustrates Visualization framework capabilities. [Top]
#### What Does CAACafViewerFeedback Do

CAACafViewerFeedback use case enables you to activate or deactivate the feedback mode on the current viewer. This switch is possible thanks to a command set in an add-in of the General workshop [1]. The Viewer Feedback demonstrator command, see pictures below, is represented by a check button. When the button is "ON" (right picture), the feedback mode is active. When the button is "OFF" (left picture), the feedback mode is not active.
---|---

When the feedback mode is active in the current viewer you can see:

  * Only the mouse position, if there is no element under the mouse  ![](images/CAAAfrCheckHeaderMouseCoord.jpg)
---
  * The mouse position, the intersection point coordinates, and the path of all elements under the mouse.  ![](images/CAAVisViewerFeedbackAll.jpg)
---

On this picture you can see that there is only one selected element.

[Top]
#### How to Launch CAACafViewerFeedback

On this picture you can see that there is only one selected element.
To launch CAACafViewerFeedback, you will need to set up the build time environment, then compile CAACafViewerFeedback along with its prerequisites, set up the run time environment, and then execute the use case [2].

But just before launching the execution, edit the CAAApplicationFrame.edu.dico interface dictionary file in the dictionary directory of your runtime view:

    **InstallRootDirectory** \**OS** \code\dictionary\

But just before launching the execution, edit the CAAApplicationFrame.edu.dico interface dictionary file in the dictionary directory of your runtime view:
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed and **OS** is a directory the name of which depends on the operating system. Refer to [2] to get the list of the currently supported operating systems and their associated directory names..

In this file, remove the "**#** " character before the two following lines:

    ...
    #CAAAfrGeneralWksAddin       CATIWorkbenchAddin          libCAAAfrGeneralWksAddin
    #CAAAfrGeneralWksAddin       CATIAfrGeneralWksAddin      libCAAAfrGeneralWksAddin
    ...

---

The two line deal with the General workshop add-in described in the CAAAfrGeneralWksAddin use case [1] located in the CAAAfrGeneralWksAddin.m module (CAAApplicationFrame.edu framework)

Then, in the window where you run the mkrun command, do not type the module name on the command line, but type CNEXT instead. When the application is ready, do the following:

  * On the **File** menu, click **New**
  * In the **New** box, select any kind of document type and click **OK**
  * On the **View** menu, click **Viewer Feedback Demonstrator**
  * **Move** the mouse on the viewer
  * **Create** elements
  * **Move** the mouse on the viewer and **pass over** the newly elements
  * On the **View** menu, click **Viewer Feedback Demonstrator**
  * **Move** the mouse on the viewer and **pass over** the newly elements

[Top]
#### Where to Find the CAACafViewerFeedback Code

The CAACafViewerFeedback use case is made of several classes located:

  * In the CAAAfrGeneralWksAddin.m module of the CAAApplicationFrame.edu framework:

The CAACafViewerFeedback use case is made of several classes located:
This module contains an add-in of the general workshop which defines a toolbar with the "Viewer Feedback Demonstrator" command. This part of the use case is not explained in this article. You can you refer to the add-in article [1] for more details.

Windows | `InstallRootDirectory\CAAApplicationFrame.edu\CAAAfrGeneralWksAddin.m\`

This module contains an add-in of the general workshop which defines a toolbar with the "Viewer Feedback Demonstrator" command. This part of the use case is not explained in this article. You can you refer to the add-in article [1] for more details.
Windows | `InstallRootDirectory\CAAApplicationFrame.edu\CAAAfrGeneralWksAddin.m\`
Unix | `InstallRootDirectory/CAAApplicationFrame.edu/CAAAfrGeneralWksAddin.m/`

  * In the CAACafViewerFeedback.m module of the CAACATIAApplicationFrm.edu framework:

Windows | `InstallRootDirectory\CAAApplicationFrame.edu\CAAAfrGeneralWksAddin.m\`
Unix | `InstallRootDirectory/CAAApplicationFrame.edu/CAAAfrGeneralWksAddin.m/`
This module contains _CAACafViewerFeedbackManager_ and _CAACafViewerFeedbackCmd_ classes.

Windows | `InstallRootDirectory\CAACATIAApplicationFrm.edu\CAACafViewerFeedback.m\`

This module contains _CAACafViewerFeedbackManager_ and _CAACafViewerFeedbackCmd_ classes.
Windows | `InstallRootDirectory\CAACATIAApplicationFrm.edu\CAACafViewerFeedback.m\`
Unix | `InstallRootDirectory/CAACATIAApplicationFrm.edu/CAACafViewerFeedback.m/`

Only one instance of the _CAACafViewerFeedbackManager_ class is created during the session. This class manages the current viewer and the feedback mode on the current viewer. It means how to receive notifications sent by the viewer, and once received, how to decode it to display some information in the 2D Viewpoint of the viewer. The _CAACafViewerFeedbackCmd_ command, explained in the "Creating a Command with Options in the "Tools Palette" Toolbar" article [3], informs the __unique _CAACafViewerFeedbackManager_ class instance to activate or deactivate the feedback mode.

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.
There are four logical steps in the CAACafViewerFeedback use case:

  1. Creating the CAACafViewerFeedbackManager Class Header
  2. Activating the Feedback Mode
  3. Deactivating the Feedback Mode
  4. Decoding the CATVisViewerFeedbackEvent Notification

[Top]
#### Creating the CAACafViewerFeedbackManager Class Header

    // System Framework
    #include "CATBaseUnknown.h"      // Needed to derive from
    #include "CATEventSubscriber.h"  // To set callback

    class CAT2DBagRep ;              // The graphic representation of the feedback
    class CATViewer ;                // The viewer with the visual feedback
    class CATNotification ;          // for callback methods
    class CATUnicodeString ;         //
    class CATPathElement ;           //

    class CAACafViewerFeedbackManager : public CATBaseUnknown

    {
class CATUnicodeString ;         //
class CATPathElement ;           //
class CAACafViewerFeedbackManager : public CATBaseUnknown
```vbscript
      public :

```

       CAACafViewerFeedbackManager ();

       virtual ~CAACafViewerFeedbackManager();

       static void **GetManager**(CAACafViewerFeedbackManager ** opManager);

       void **SetViewerFeedbackOn**();

       void **SetViewerFeedbackOff**();

```vbscript
      private :

```

       void **ViewerFeedbackCB**          (CATCallbackEvent  iEventAlarm,
                               void             *iAlarm,
                               CATNotification  *iNotifAlarm,
                               CATSubscriberData iBurglarData,
                               CATCallback       iCallBack );

       void **WindowActivatedCB**          (CATCallbackEvent  iEventAlarm,
                               void             *iAlarm,
                               CATNotification  *iNotifAlarm,
                               CATSubscriberData iBurglarData,
                               CATCallback       iCallBack );

       void **WindowDeactivatedCB**          (CATCallbackEvent  iEventAlarm,
                               void             *iAlarm,
                               CATNotification  *iNotifAlarm,
                               CATSubscriberData iBurglarData,
                               CATCallback       iCallBack );

       void **PathElementString**(CATPathElement   * ipPath,
                               CATUnicodeString & oPathName) ;

       void **ChangeBagPosition**(float Xpos, float Ypos) ;

       CAACafViewerFeedbackManager(const CAACafViewerFeedbackManager &iObjectToCopy);
       CAACafViewerFeedbackManager & operator = (const CAACafViewerFeedbackManager &iObjectToCopy);

      private :
       CATViewer     * **_pCurrentViewer** ;
       CAT2DBagRep   * **_pInformationsToDisplay** ;

       **CATCallback**     _ViewerFeedbackCB ;
private :
CATViewer     * **_pCurrentViewer** ;
CAT2DBagRep   * **_pInformationsToDisplay** ;
       CATCallback     _WindowActivatedCB ;
       CATCallback     _WindowDeactivatedCB ;
       CATCallback     _WindowDeletedCB ;

    };

---

This class contains the following methods:

  * `GetManager`: it is a static method which manages the singleton.
  * `SetViewerFeedbackOn:` actives the feedback mode - see the Activating the Feedback Mode section
  * `SetViewerFeedbackOff:` deactivates the feedback mode - see the Deactivating the Feedback Mode section
  * `ViewerFeedbackCB`: this method is a callback method to analyze the CATVisViewerFeedback notification
  * `WindowActivatedCB and WindowDeactivatedCB`: these two methods are callback methods to manage window activation, deactivation and deletion. The first one calls the `SetViewerFeedbackOn` method if the feedback mode is active, and the second method calls the `SetViewerFeedbackOff` method.
  * `PathElementString`: It is a service to translate in a string a _CATPathElement_. For each element of the path, the _CATIAlias_ interface is called.
  * `ChangeBagPosition`: this method is also a service to move the text near the mouse position. Click here to see the code.

and contains the following data:

  * _`pCurrentViewer`: it is one viewer of the current window.
  * `_pInformationsToDisplay`: it is the graphic representation which groups together texts
  * `_ViewerFeedbackCB`: it is the identifier of the viewer callback.
  * `_WindowxxxCB`: there are the identifiers of the window callbacks

[Top]
#### Activating the Feedback Mode

The `SetViewerFeedbackOn `method consists in first to retrieve a viewer:

The `SetViewerFeedbackOn `method consists in first to retrieve a viewer:
    void CAACafViewerFeedbackManager::SetViewerFeedbackOn()

    {
The `SetViewerFeedbackOn `method consists in first to retrieve a viewer:
void CAACafViewerFeedbackManager::SetViewerFeedbackOn()
```vbscript
        if ( NULL == _pCurrentViewer )

```

        {
           **CATFrmLayout** * pCurrentLayout= CATFrmLayout::**GetCurrentLayout**();
void CAACafViewerFeedbackManager::SetViewerFeedbackOn()
if ( NULL == _pCurrentViewer )
```vbscript
```vbscript
           if ( NULL != pCurrentLayout )

```

```

           {
              **CATFrmWindow** * pCurrentWindow = pCurrentLayout->**GetCurrentWindow**();

```vbscript
if ( NULL != pCurrentLayout )
```vbscript
              if ( NULL != pCurrentWindow )
```

```

              {
                  _pCurrentViewer = pCurrentWindow->**GetViewer**();
    ...

---

_pCurrentViewer = pCurrentWindow->**GetViewer**();
This viewer is one of the current window (it is the choice of this command). The _CATFrmLayout_ [4] is the class which manages all the windows all the session.

Then, once you have a viewer, you can activate the feedback mode:

     ...
Then, once you have a viewer, you can activate the feedback mode:
```vbscript
           if ( NULL != _pCurrentViewer )

```

           {
```vbscript
if ( NULL != _pCurrentViewer )
              _pCurrentViewer->**SetFeedbackMode**(TRUE);
              if (0 == _ViewerFeedbackCB)
```

              {
```vbscript
if ( NULL != _pCurrentViewer )
_pCurrentViewer->**SetFeedbackMode**(TRUE);
if (0 == _ViewerFeedbackCB)
```vbscript
                 _ViewerFeedbackCB = ::**AddCallback**(this,
```

                                _pCurrentViewer,
```

                                **CATViewer** ::**VIEWER_FEEDBACK_UPDATE**(),
```vbscript
if (0 == _ViewerFeedbackCB)
```vbscript
_ViewerFeedbackCB = ::**AddCallback**(this,
```

_pCurrentViewer,
                                (CATSubscriberMethod) & CAACafViewerFeedbackManager::**ViewerFeedbackCB** , NULL);
```

              }
           }

---

The `SetFeedbackMode` method with `TRUE` actives the feedback mode. It means that now the viewer sends notifications when an interaction occurs. To receive these notifications, the command sets a callback.

  * `this` : the event subscriber
  * `_pCurrentViewer` : the publisher
  * `CATViewer::VIEWER_FEEDBACK_UPDATE`(): the dispatched CATCallbackEvent [5]
  * `ViewerFeedbackCB`: the callback method - See the Decoding the CATVisViewerFeedbackEvent Notification section
  * `NULL`: no argument

`_ViewerFeedbackCB` is an identifier of the callback, it is important to keep it for the callback deletion. See the  `SetViewerFeedbackOn ` method

[Top]
#### Deactivating the Feedback Mode

The `SetViewerFeedbackOn `method consists in to cancel the feedback mode on the current viewer.

The `SetViewerFeedbackOn `method consists in to cancel the feedback mode on the current viewer.
    void CAACafViewerFeedbackManager::SetViewerFeedbackOff()

    {
The `SetViewerFeedbackOn `method consists in to cancel the feedback mode on the current viewer.
void CAACafViewerFeedbackManager::SetViewerFeedbackOff()
```vbscript
        if ( NULL != _pCurrentViewer)

```

        {
void CAACafViewerFeedbackManager::SetViewerFeedbackOff()
if ( NULL != _pCurrentViewer)
           _pCurrentViewer->**SetFeedbackMode**(FALSE);

```vbscript
           if (NULL != **_pInformationsToDisplay**)

```

           {
_pCurrentViewer->**SetFeedbackMode**(FALSE);
if (NULL != **_pInformationsToDisplay**)
              _pCurrentViewer->**RemoveRep**(_pInformationsToDisplay);

              _pInformationsToDisplay->**Destroy**();
              _pInformationsToDisplay = NULL;

           }
_pCurrentViewer->**RemoveRep**(_pInformationsToDisplay);
_pInformationsToDisplay->**Destroy**();
_pInformationsToDisplay = NULL;
           _pCurrentViewer->**Draw**();

```vbscript
           if (0 != _ViewerFeedbackCB)

```

           {
              ::**RemoveCallback**(this,_pCurrentViewer,**_ViewerFeedbackCB**) ;
_pCurrentViewer->**Draw**();
if (0 != _ViewerFeedbackCB)
              _ViewerFeedbackCB = 0 ;

           }
```vbscript
if (0 != _ViewerFeedbackCB)
_ViewerFeedbackCB = 0 ;
           _pCurrentViewer = NULL ;
```

        }
    }

---

There are four steps:

There are four steps:
  1. Deactivate the feedback mode: It is done with the `SetFeedbackMode` method with ` FALSE` as argument. It means that now the viewer will do not send notifications when an interaction will occurs.
  2. Remove the graphic representation created in the `ViewerFeedbackCB` method. `_pInformationsToDisplay` is first removed from the viewer and then deleted. The `Destroy` method deletes the graphic representation and its contents, if it is a bag.
  3. Refresh the viewer: It is the role of the `Draw` method
  4. Removes the callback coming from the viewer: `_ViewerFeedbackCB` is the identifier returns by the `AddCallback` method. See the  `SetViewerFeedbackOn ` method.
  5. `_pCurrentViewer`, returned by the `GetViewer` method of _CATFrmWindow,_ is not "AddReffed" by this method, so you have just to reset the pointer.

[Top]
#### Decoding the CATVisViewerFeedbackEvent Notification

The `ViewerFeedbackCB` method consists in to decode the notification contained in the callback event, and to display in the main 2D viewpoint of the viewer, the information of the notification.

The `ViewerFeedbackCB` method consists in to decode the notification contained in the callback event, and to display in the main 2D viewpoint of the viewer, the information of the notification.
    void CAACafViewerFeedbackManager::ViewerFeedbackCB( CATCallbackEvent   event,
                                                  void             * client,
                                                  CATNotification  * iNotification,
                                                  CATSubscriberData  data,
                                                  CATCallback        callback)

    {
void             * client,
CATNotification  * iNotification,
CATSubscriberData  data,
CATCallback        callback)
```vbscript
      if ( NULL != _pCurrentViewer )

```

      {
CATSubscriberData  data,
CATCallback        callback)
if ( NULL != _pCurrentViewer )
```vbscript
```vbscript
         if (NULL != _pInformationsToDisplay)

```

```

         {
```vbscript
if ( NULL != _pCurrentViewer )
```vbscript
if (NULL != _pInformationsToDisplay)
```

            _pCurrentViewer->**RemoveRep**(_pInformationsToDisplay);

            _pInformationsToDisplay->**Destroy**();
            _pInformationsToDisplay = NULL;
```

         }
    ...

---

The `ViewerFeedbackCB` method is called each time the viewer sends an event. So the graphic representation, `_pInformationsToDisplay`, previously created, should be first removed from the viewer and deleted.

The `ViewerFeedbackCB` method is called each time the viewer sends an event. So the graphic representation, `_pInformationsToDisplay`, previously created, should be first removed from the viewer and deleted.
         CATVisViewerFeedbackEvent * pFeedbackEvent = NULL ;
```vbscript
         if ( NULL != iNotification )

```

         {
CATVisViewerFeedbackEvent * pFeedbackEvent = NULL ;
if ( NULL != iNotification )
```vbscript
```vbscript
            pFeedbackEvent = (**CATVisViewerFeedbackEvent** *) iNotification;

```

```

         }

```vbscript
if ( NULL != iNotification )
```vbscript
```vbscript
pFeedbackEvent = (**CATVisViewerFeedbackEvent** *) iNotification;
         if (NULL != pFeedbackEvent)
```

```

```

         {
pFeedbackEvent = (**CATVisViewerFeedbackEvent** *) iNotification;
```vbscript
if (NULL != pFeedbackEvent)
```

             CATViewer * pViewerPublisher = pFeedbackEvent->**GetViewer**();
```vbscript
             if ( (NULL != pViewerPublisher) && ( pViewerPublisher **==** _pCurrentViewer) )

```

             {
```vbscript
if (NULL != pFeedbackEvent)
CATViewer * pViewerPublisher = pFeedbackEvent->**GetViewer**();
if ( (NULL != pViewerPublisher) && ( pViewerPublisher **==** _pCurrentViewer) )
```vbscript
                _pInformationsToDisplay = new **CAT2DBagRep**();
```

                _pCurrentViewer->**AddRep**(_pInformationsToDisplay);
```

                ...

---

The third argument of the `ViewerFeedbackCB` method is the notification containing the information. This notification, `iNotification`, is a _CATVisViewerFeedbackEvent_**** class. This class instance contains the viewer which has published the event. `GetViewer` retrieves it, it is `pViewerPublisher`. This viewer should be released at this end of the method. This value enables you to check that the current viewer, `_pCurrentViewer,` kept by the manager, is the same as the notification's sender. Once the check is validated, a new graphic representation can be built.

`_pInformationsToDisplay` is a 2D bag added to the viewer thanks to the `AddRep` method. This method adds the 2D representation to the main 2D viewpoint. `_pInformationsToDisplay` will have several children depending on the notification's contents. The `ViewerFeedbackCB` method analyses and displays a text for :

The third argument of the `ViewerFeedbackCB` method is the notification containing the information. This notification, `iNotification`, is a _CATVisViewerFeedbackEvent_**** class. This class instance contains the viewer which has published the event. `GetViewer` retrieves it, it is `pViewerPublisher`. This viewer should be released at this end of the method. This value enables you to check that the current viewer, `_pCurrentViewer,` kept by the manager, is the same as the notification's sender. Once the check is validated, a new graphic representation can be built.
  1. The mouse position in screen coordinates
  2. The intersection point with the selected geometry
  3. The elements under the mouse

These three steps are described below.

  1. The mouse position in screen coordinates

Before to detail the code, a picture to explain the screen coordinates:

```vbscript
```vbscript
 If (Xpos,Ypos) are the screen coordinates of the mouse,

```

```

     * Xpos ranges from 0 to width-1
     * Ypos ranges from 0 to height-1
Before to detail the code, a picture to explain the screen coordinates:
```vbscript
If (Xpos,Ypos) are the screen coordinates of the mouse,
```

where width and height are the support (_CATSupport_) dimensions.

where width and height are the support (_CATSupport_) dimensions.
    int XPos, YPos;
               pFeedbackEvent->**GetMousePosition**(&XPos, &YPos);

               **ChangeBagPosition**(XPos,YPos);

int XPos, YPos;
pFeedbackEvent->**GetMousePosition**(&XPos, &YPos);
               float **points**[2];
               points[0] = 8.0f;
               points[1] = 8.0f;

    ...

---

`GetMousePosition` returns the mouse position in screen coordinates. This position serves to locate the 2D bag. The `ChangeBagPosition` method locates `_pInformationsToDisplay` near the mouse. `points` is an array of two floats which is used to locate the child representations in the 2D bag.

The position of a child is a position in the bag axis system as shown in the picture below:

 (u,v) is the bag axis system (Xpos,Ypos) is the mouse position in screen coordinates The `ChangeBagPosition` method transforms (Xpos,Ypos) is model coordinates.
---|---

The position of a child is a position in the bag axis system as shown in the picture below:
(u,v) is the bag axis system (Xpos,Ypos) is the mouse position in screen coordinates The `ChangeBagPosition` method transforms (Xpos,Ypos) is model coordinates.
Here is the code of the `ChangeBagPosition` method:

    ...
Here is the code of the `ChangeBagPosition` method:
    void CAACafViewerFeedbackManager::ChangeBagPosition(float Xpos, float Ypos)

    {
Here is the code of the `ChangeBagPosition` method:
void CAACafViewerFeedbackManager::ChangeBagPosition(float Xpos, float Ypos)
            CATSupport & Support = _pCurrentViewer->**GetSupport**();

            float width, height, MMInSupportUnit, RatioWH ;

            Support.**GetWidthAndHeight**(width,height);

            MMInSupportUnit = Support.**GetMMInSupportUnit**();
```vbscript
```vbscript
            RatioWH = Support.**GetRatioWH**();

```

```

            CAT2DViewpoint & VP2D = _pCurrentViewer->**GetMain2DViewpoint**() ;

            CATMathPoint2Df ModelPos;
            VP2D.**ComputeModelFromPixel**( Xpos,Ypos,
                                        ModelPos.x, ModelPos.y,
                                        width, height,
                                        MMInSupportUnit,
                                        RatioWH);

            CATMathVector2Df U,V ;

            **CAT3x3Matrix** Matrix(U,V,ModelPos);
MMInSupportUnit,
RatioWH);
CATMathVector2Df U,V ;
           _pInformationsToDisplay->**SetMatrix**(Matrix);

        }
    }
    ...

---

`(ModelPos.x, ModelPos.y)` is the mouse position in model coordinates. The `ComputeModelFromPixel` method transforms a 2D point from screen coordinates to model coordinates.

Come back to the `ViewerFeedbackCB` method:

    ...
Come back to the `ViewerFeedbackCB` method:
               char MousePositionBuffer[200];
               sprintf(MousePositionBuffer, "Mouse Coordinates : X=%d Y=%d", **XPos** , **YPos**);

               CAT2DAnnotationTextRep * pMousePositionTextRep = NULL ;
               pMousePositionTextRep = new **CAT2DAnnotationTextRep**( points,
                                                                 MousePositionBuffer,
                                                                 BASE_LEFT);

```vbscript
               if (NULL != pMousePositionTextRep)

```

               {
MousePositionBuffer,
BASE_LEFT);
if (NULL != pMousePositionTextRep)
                  _pInformationsToDisplay->**AddChild**(*pMousePositionTextRep);

               }
    ...

---

`pMousePositionTextRep` is a _CAT2DAnnotationTextRep_ class instance to display the mouse position screen coordinates.

  2. The intersection point with the selected geometry

2. The intersection point with the selected geometry
Before to detail the code, a picture to explain the intersection point.

 The point symbolized by a bold circle is the intersection point of the line and the nearest selected geometry. This point is in model coordinates.

`GetIntersection`**** returns a _CATGraphicElementIntersection_ class instance pointer. This class contains as public data a _CATMathPoint_ . `point` is the intersection point. If there is nothing under the mouse, `GetIntersection`**** returns NULL.

    ...
               **CATGraphicElementIntersection** * pIntersection = pFeedbackEvent->**GetIntersection**();

               if (NULL != pIntersection)
               {
                  **points**[1] += 8.0f;

```vbscript
if (NULL != pIntersection)
                  char IntersectionBuffer[200];

                  sprintf(IntersectionBuffer,
```

                     "Intersection Coordinates : X=%.2f Y=%.2f Z=%.2f",
                      **pIntersection- >point.GetX**(),
                      **pIntersection- >point.GetY**(),
                      **pIntersection- >point.GetZ**());

                  CAT2DAnnotationTextRep * pIntersectionTextRep = NULL ;
                  pIntersectionTextRep = new **CAT2DAnnotationTextRep**( points,
                                                      IntersectionBuffer, BASE_LEFT);

```vbscript
                  if (NULL != pIntersectionTextRep)

```

                  {
pIntersectionTextRep = new **CAT2DAnnotationTextRep**( points,
IntersectionBuffer, BASE_LEFT);
if (NULL != pIntersectionTextRep)
                     _pInformationsToDisplay->**AddChild**(*pIntersectionTextRep);

                  }

```vbscript
if (NULL != pIntersectionTextRep)
_pInformationsToDisplay->**AddChild**(*pIntersectionTextRep);
                  pIntersection->**Release**();
                  pIntersection = NULL;
```

               }
    ...

---

`pMousePositionTextRep` is a _CAT2DAnnotationTextRep_ class instance which contains the intersection point coordinates.

  3. The elements under the mouse

`GetElementsUnder`**** returns the list of elements under the mouse. This list can be empty. The elements in this list are sorted, the first (0 index) being the nearest, and the last ( n-1) the further. Each element is a _CATPathElement_ from the geometry to the root.

    ...
3. The elements under the mouse
               CATSO* SO = pFeedbackEvent->**GetElementsUnder**();

```vbscript
               if (NULL != SO)

```

               {
CATSO* SO = pFeedbackEvent->**GetElementsUnder**();
if (NULL != SO)
                  int SOSize = SO->**GetSize**() ;
```vbscript
                  for ( int i= 0 ; i < SOSize ; i++)

```

                  {
```vbscript
if (NULL != SO)
int SOSize = SO->**GetSize**() ;
for ( int i= 0 ; i < SOSize ; i++)
                     CATPathElement * pPathElement = (CATPathElement*) ((*SO)[i]) ;

                     CATUnicodeString PathElementName = "";
```

                     **PathElementString**(pPathElement,PathElementName);

CATPathElement * pPathElement = (CATPathElement*) ((*SO)[i]) ;
CATUnicodeString PathElementName = "";
                     char Buffer[200];
                     sprintf(Buffer, "   : %d / %d", i+1,SO->GetSize());

                     CATUnicodeString Count(Buffer);
                     PathElementName.Append(Buffer) ;

                     points[1] += 8.0f;

                     CAT2DAnnotationTextRep* pElementTextRep = NULL ;
                     pElementTextRep = new **CAT2DAnnotationTextRep**( points,
                                                              PathElementName.CastToCharPtr(),
                                                              BASE_LEFT);

```vbscript
                     if (NULL != pElementTextRep)

```

                     {
PathElementName.CastToCharPtr(),
BASE_LEFT);
if (NULL != pElementTextRep)
                        _pInformationsToDisplay->**AddChild**(*pElementTextRep);

                     }
                  }
```vbscript
if (NULL != pElementTextRep)
_pInformationsToDisplay->**AddChild**(*pElementTextRep);
                  SO->**Release**();
                  SO = NULL;
```

    ...

---

This piece of code is a loop from the first element to the last. For each path, `PathElementString` converts a path in a string. This string is the input of a new `CAT2DAnnotationTextRep` class instance.

[Top]

* * *
### In Short

This use case explains how to receive information from a viewer when interactions occur. These information are inside a _CATVisViewerFeebackEvent_ notification class.

[Top]

* * *
### References

[1] | [Making Your Document Independent Command Available in All Workbenches](../CAAAfrUseCases/CAAAfrSampleGeneralWksAddin.md)
---|---
[2] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
[3] | [Creating a Command with Options in the "Tools Palette" Toolbar](../CAAAfrUseCases/CAAAfrCmdPalette.md)
[4] | [Understanding the Application Frame Layout](../CAAAfrTechArticles/CAAAfrLayoutV5.md)
[5] | [The Callback Mechanism](../CAASysTechArticles/CAASysCallbacks.md)
[Top]

* * *
### History

Version: **1** [Aug 2003] | Document created
---|---
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
