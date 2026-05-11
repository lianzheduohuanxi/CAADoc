---
```vbscript
title: "Using Cameras"
category: "use case"
module: "CAAAfrUseCases"
tags: ["CATI3DCamera", "CAAAfrChangeViewNormalCmd", "CAAAfrGeometryWshop", "CAAAfrGeoCommands", "CAAGeometry", "CAAAfrGeoCommand", "CAAApplicationFrame"]
source_file: "Doc/online/CAAAfrUseCases/CAAAfrSampleCamera.htm"
converted: "2026-05-11T17:17:55.631615"
```

---
# 3D PLM Enterprise Architecture

| 
## User Interface - Frame

| 
### Using Cameras

_Creating a single command seen as several end user commands_  
---|---|---  
Use Case  

* * *
### Abstract

This article shows how to create a command that can be passed a parameter. It uses a camera to modify the current window viewpoint, the parameter being the selected viewpoint. 

  * **What You Will Learn With This Use Case**
  * **The CAAAfrGeoCommands Use Case**
    * What Does CAAAfrGeoCommands Do
    * How to Launch CAAAfrGeoCommands
    * Where to Find the CAAAfrGeoCommands Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---  

* * *
### What You Will Learn With This Use Case

This use case is intended to show how to pass a parameter to a command, and how to use a camera to modify the current window viewpoint.

[Top]
### The CAAAfrGeoCommands Use Case

CAAAfrGeoCommands is a use case of the CAAApplicationFrame.edu framework that illustrates the ApplicationFrame framework capabilities.

[Top]
#### What Does the CAAAfrGeoCommands Use Case Do

CAAAfrGeoCommands is a use case of the CAAApplicationFrame.edu framework that illustrates the ApplicationFrame framework capabilities.
The CAAAfrGeoCommands use case includes several commands. The CAAAfrChangeViewNormalCmd command that changes the current window viewpoint is the only command described here. This command that belongs to the CAAAfrGeometryWshop changes the current window viewpoint to one of the following.

 See the yz plane from left. Select View->Normal View->NormalX  

The CAAAfrGeoCommands use case includes several commands. The CAAAfrChangeViewNormalCmd command that changes the current window viewpoint is the only command described here. This command that belongs to the CAAAfrGeometryWshop changes the current window viewpoint to one of the following.
See the yz plane from left. Select View->Normal View->NormalX
 See the zx plane from right. Select View->Normal View->NormalY  
 See the xy plane from top. Select View->Normal View->NormalZ  

This command is instantiated from the workshop using as many command headers as there are end user commands, that is, as there are push items in menus or push buttons in toolbars that trigger this command,

#### How to Launch CAAAfrGeoCommands

See the xy plane from top. Select View->Normal View->NormalZ
This command is instantiated from the workshop using as many command headers as there are end user commands, that is, as there are push items in menus or push buttons in toolbars that trigger this command,
See the section entitled "How to Launch the CAAGeometry Use Case" in the "[The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.md)" use case for a detailed description of how this use case should be launched. For the specific scenario :

Do not type the module name on the command line, but type CNEXT instead. When the application is ready, do the following: 

  * Select File->New
  * In the New box, select CAAGeometry and click OK
  * Select View->Normal View. Three commands are proposed: NormalX, NormalY, and NormalZ, setting the viewpoint to see the YZ plane, the ZX plane, and the XY plane respectively.

[Top]
#### Where to Find the CAAAfrGeoCommands Code

The CAAAfrGeoCommand use case is made of a single class named _CAAAfrChangeViewNormalCmd_ located in the CAAAfrGeoCommands.m module of the CAAApplicationFrame.edu framework:

The CAAAfrGeoCommand use case is made of a single class named _CAAAfrChangeViewNormalCmd_ located in the CAAAfrGeoCommands.m module of the CAAApplicationFrame.edu framework:
Windows | `InstallRootDirectory\CAAApplicationFrame.edu\CAAAfrGeoCommands.m\`  

The CAAAfrGeoCommand use case is made of a single class named _CAAAfrChangeViewNormalCmd_ located in the CAAAfrGeoCommands.m module of the CAAApplicationFrame.edu framework:
Windows | `InstallRootDirectory\CAAApplicationFrame.edu\CAAAfrGeoCommands.m\`
Unix | `InstallRootDirectory/CAAApplicationFrame.edu/CAAAfrGeoCommands.m/`  

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

In addition, the command header that stands for this command in the CAAAfrGeometryWshop and that passes the parameter to the command is described with the workshop. 

[Top]
### Step-by-Step

To create the command that changes the current window viewpoint, there are three steps:
# | Step | Where  
---|---|---  
To create the command that changes the current window viewpoint, there are three steps:
1 | Create the command and storing the argument | constructor  
2 | Set the camera axes | `Activate` method  
3 | Create the camera and assign it to the current window | `Activate` method  

[Top]
#### Creating the Command and Storing the Argument

The command constructor is as follows.

    CAAAfrChangeViewNormalCmd::CAAAfrChangeViewNormalCmd(void *iArgument)
                             : CATCommand("ViewNormalId",**CATCommandModeExclusive**)
    {
       _ArgumentCmd = **CATPtrToINT32**(iArgument) ;
    }  

---  

The command headers call the constructor with an argument that indicates the plane that should be normal to the sight direction. This argument is:

  * 1 to see the YZ plane
  * 2 to see the ZX plane
  * 3 to see the XY plane.

This argument is kept in the data member `_ArgumentCmd`. It is an integer. The `CATPtrToINT32` macro enables you to safely convert in 64 bits a pointer to an INT. See the referenced article [1] to see instantiations of a command header class using the _CAAAfrChangeViewNormalCmd_ class.

The command is set as exclusive thanks to `CATCommandModeExclusive`. Since it doesn't modify the document, it could be also set as shared, but since it is a one-shot command, there is no possibility of selecting another command before it completes.

[Top]
#### Setting the Camera Axes

The `Activate` method first sets the camera axes depending on the argument value.

The `Activate` method first sets the camera axes depending on the argument value.
    CATStatusChangeRC CAAAfrChangeViewNormalCmd::**Activate**(CATCommand * iFromClient,
                                                          CATNotification * iEvtData)

    {
CATStatusChangeRC CAAAfrChangeViewNormalCmd::**Activate**(CATCommand * iFromClient,
CATNotification * iEvtData)
      CATMathDirection direction, zenith;
      CATMathPoint origin(0.f, 0.f, 0.f);

      switch (_ArgumentCmd)

      {
CATMathDirection direction, zenith;
CATMathPoint origin(0.f, 0.f, 0.f);
switch (_ArgumentCmd)
        case 1 : direction.SetCoord(-1.f,0.f,0.f);
                 zenith.SetCoord(0.f,0.f,1.f);
                 break ;
        case 2 : direction.SetCoord(0.f,-1.f,0.f);
                 zenith.SetCoord(0.f,0.f,-1.f);
                 break ;
        case 3 : direction.SetCoord(0.f,0.f,-1.f);
                 zenith.SetCoord(0.f,1.f,0.f);
                 break ;

      }
      ...  

---  

The argument takes the value of 1 for a plane normal to the x axis, 2 for a plane normal to the y axis, and 3 for a plane normal to the z axis. The camera axes are made up of a sight direction axis that joins the eye and the target, and a zenith axis perpendicular to the sight direction. ![CAAAfr3DCamera.gif \(3610 bytes\)](images/CAAAfr3DCamera.gif)

  * The camera that sees the yz plane has a sight direction opposed to the x axis (-1,0,0) and a zenith direction parallel to the z axis.
  * The camera that sees the zx plane has a sight direction opposed to the y axis (0,-1,0) and a zenith direction opposed to the z axis (0,0,-1)
  * The camera that sees the xy plane has a sight direction opposed to the z axis (0,0,-1) and a zenith direction parallel to the y axis.

These direction as set as _CATMathDirection_ instances is the switch.

[Top]
#### Creating the Camera and Assigning it to the Current Window

      ...
      CATFrmLayout *pCurrentLayout = **CATFrmLayout::GetCurrentLayout**();
CATFrmLayout *pCurrentLayout = **CATFrmLayout::GetCurrentLayout**();
      if ( pCurrentLayout )

      {
CATFrmLayout *pCurrentLayout = **CATFrmLayout::GetCurrentLayout**();
if ( pCurrentLayout )
        CATFrmWindow *pCurrentWindow = pCurrentLayout->**GetCurrentWindow**();
        if ( pCurrentWindow )

        {
```vbscript
if ( pCurrentLayout )
CATFrmWindow *pCurrentWindow = pCurrentLayout->**GetCurrentWindow**();
if ( pCurrentWindow )
          CATFrm3DCamera * pCameraImpl = new **CATFrm3DCamera**("cam3d",
                                                            origin,
                                                            direction,
                                                            zenith);
```

          **CATI3DCamera** *pCamera = NULL;                
CATFrm3DCamera * pCameraImpl = new **CATFrm3DCamera**("cam3d",
origin,
direction,
zenith);
          HRESULT rc = pCameraImpl->QueryInterface(IID_CATI3DCamera, (void**)&pCamera);
          if (SUCCEEDED(rc))

          {
zenith);
HRESULT rc = pCameraImpl->QueryInterface(IID_CATI3DCamera, (void**)&pCamera);
if (SUCCEEDED(rc))
            pCurrentWindow->**SetCurrentCamera**(pCamera);
    	pCamera->Release();

          }
```vbscript
if (SUCCEEDED(rc))
pCurrentWindow->**SetCurrentCamera**(pCamera);
pCamera->Release();
          pCameraImpl->Release();
```

        }
      }  
pCamera->Release();
pCameraImpl->Release();
      return CATStatusChangeRCCompleted;

    }  

---  

To set the camera axes as those of the viewpoint of the current window, the layout is first retrieved thanks to the static `CATFrmLayout::GetCurrentLayout` method, and then the current window is retrieved from this layout using `GetCurrentWindow`. Then a 3D camera is instantiated with the eye location, sight and zenith directions determined with respect to the argument passed, that is, with respect to the View->Normal View item selected by the end user, and a pointer to the _CATI3DCamera_ interfaces is retrieved from this camera. This pointer is assigned to the current window whose viewpoint changes to match the camera thanks to the `SetCamera` method.

[Top]

* * *
### In Short

A command can be passed a parameter to enable a single command to act as if several commands were offerred to the end user. These end user commands should nevertheless be close to each other. There is a command header for each end user command that instantiates the command and passes the parameter value appropriate to the end user intent, and the command tests this value to do the corresponding task.

A camera is an object that can be assigned to a window to set or reset the viewpoint characteristics of the window, that is, the eye location, and the sight and zenith directions.

[Top]

* * *
### References

[1] | [Creating Standard Command Headers](CAAAfrSampleStdCommandHeader.md)  
---|---  
[Top]  
---  

* * *
### History

Version: **1** [Jan 2000] | Document created  
---|---  
Version: **2** [Mar 2004] | 64 bits   
[Top]  

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
