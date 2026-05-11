---
```vbscript
title: "Converting Print Files"
category: "use case"
module: "CAAPrtUseCases"
tags: ["CAAPrtOut", "CAAPrint", "CAACPrtChangeFormat", "CAAPrtChangeFormat"]
source_file: "Doc/online/CAAPrtUseCases/CAAPrtSampleChangeFormat.htm"
converted: "2026-05-11T17:17:56.103894"
```

---
# 3D PLM Enterprise Architecture

|
## 3D Visualization - Print

|
### Converting Print Files

_Creating a TIFF file from a CGM file_
---|---|---
Use Case

* * *
### Abstract

This article discusses the CAAPrtChangeFormat use case. This use case explains how to convert an input file encoded using a given format into an output file encoded using another format.

  * **What You Will Learn With This Use Case**
  * **The CAAPrtChangeFormat Use Case**
    * What Does CAAPrtChangeFormat Do
    * How to Launch CAAPrtChangeFormat
    * Where to Find the CAAPrtChangeFormat Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What You Will Learn With This Use Case

This use case is intended to show how to convert an input file encoded using a given format into an output file encoded using another format. To do this, you'll learn how to create a print file image from the input file, a print device, print parameters, and how to generate the output file encoded using the target format.

[Top]
### The CAAPrtChangeFormat Use Case

CAAPrtChangeFormat is a use case of the CAAPrint.edu framework that illustrates Print framework capabilities.

[Top]
#### What Does CAAPrtChangeFormat Do

CAAPrtChangeFormat is a batch program that reads a CGM file from the command line and converts it into a TIFF file.

[Top]
#### How to Launch CAAPrtChangeFormat

CAAPrtChangeFormat is a batch program that reads a CGM file from the command line and converts it into a TIFF file.
To launch CAAPrtChangeFormat, you will need to set up the build time environment, then compile CAAPrtChangeFormat along with its prerequisites, set up the run time environment, and then execute the use case [1].

In addition, the `CAAPrtOut` environment variable should be set to the directory into which you want to create the resulting TIFF file, prior to launching CAAPrtChangeFormat with the path of the input CGM file as argument.

  * With Windows

In addition, the `CAAPrtOut` environment variable should be set to the directory into which you want to create the resulting TIFF file, prior to launching CAAPrtChangeFormat with the path of the input CGM file as argument.
        E:>set CAAPrtOut=DirForOutputTIFFFile
        E:>CAAPrtChangeFormat InstallRootDirectory\CAAPrint.edu\CNext\resources\graphic\images\CAAPrtChangeFormat.cgm

---
  * With UNIX

        $ export CAAPrtOut=DirForOutputTIFFFile
        $ CAAPrtChangeFormat InstallRootDirectory/CAAPrint.edu/CNext/resources/graphic/images/CAAPrtChangeFormat.cgm

---

where:

  * `DirForOutputTIFFFile` is the directory where the TIFF will be created
  * `InstallRootDirectory` is the directory into which the CAA CD-ROM were unloaded
  * `CAAPrtChangeFormat.cgm` is a sample CGM file. You can use other CGM files you may have at hand.

[Top]
#### Where to Find the CAAPrtChangeFormat Code

The CAAPrtChangeFormat use case is made of a single source file located in the CAAPrtChangeFormat.m module of the CAAPrint.edu framework:

The CAAPrtChangeFormat use case is made of a single source file located in the CAAPrtChangeFormat.m module of the CAAPrint.edu framework:
Windows | ` InstallRootDirectory\CAAPrint.edu\CAAPrtChangeFormat.m\src\CAACPrtChangeFormat.cpp`

The CAAPrtChangeFormat use case is made of a single source file located in the CAAPrtChangeFormat.m module of the CAAPrint.edu framework:
Windows | ` InstallRootDirectory\CAAPrint.edu\CAAPrtChangeFormat.m\src\CAACPrtChangeFormat.cpp`
Unix | ` InstallRootDirectory/CAAPrint.edu/CAAPrtChangeFormat.m/src/CAACPrtChangeFormat.cpp`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.
To create the CGM to TIFF CAAPrtChangeFormat format converter, there are six main steps:

  1. Initializing the Printer Manager
  2. Creating a Print File Image from the Input File
  3. Creating a Print Raster File Device
  4. Defining Print Parameters
  5. Writing the Output File
  6. Cleaning the Application and Closing the Printer Manager

Some preliminary tasks are not described. They deal with retrieving the input file name, finding out the output file directory, and building the output file name. The input file name is retrieved from the command line in the ` InputName` variable, such as TestFile.cgm. The file extension is compared with cgm. The output file directory is given by the `CAAPrtOut` environment variable, which you have to export. The output file name uses the input file name and changes its suffix to tif, such as TestFile.tif and is stored in the `TmpFile` variable.

[Top]
#### Initializing the Printer Manager

    #include "CATPrintFileImage.h"   _// To create an image from the input file_
    #include "CATPrintParameters.h"  _// To define print parameters_
    #include "CATPrintFileDevice.h"  _// To create a file device_
    ...

    int main(int argc, char* argv[])
    {
      int ReturnCode = 0;
      ... _// Retrieving the input file name, setting the output file directory, and
      ... // building the output file name is not described here_

      **CATPrinterManager::Begin()** ;
      ...

---

As soon as the input file is retrieved and the output file directory and name are set, the printer manager is initialized.

[Top]
#### Creating a Print File Image from the Input File

As soon as the input file is retrieved and the output file directory and name are set, the print file image can be built from the input file.

As soon as the input file is retrieved and the output file directory and name are set, the print file image can be built from the input file.
    _..._
      CATPrintFileImage *pImage;
```vbscript
      pImage = new **CATPrintFileImage**(InputName, "CGM");

```

      ...

---

This print file image is an instance of the _CATPrintFileImage_ class instantiated from the input file. The input file format is passed as the second argument, here CGM. The print file image created holds the input file in memory and the CGM interpreter to enable the file interpretation as soon as this will be asked.

[Top]
#### Creating a Print Raster File Device

The print raster file device should be next instantiated.

      ...
The print raster file device should be next instantiated.
      CATPrintFileDevice *pDevice;
```vbscript
      pDevice = new **CATPrintFileDevice**( (const char*) TmpFile, "RASTER" );

```

      ...

---

The print raster file device represents the output logical unit for a real device. It is made of a TIFF generator and of a stream into which the TIFF image writing will be performed. For this reason, the output file name and the RASTER type, that stands for TIFF, are passed as arguments.

[Top]
#### Defining Print Parameters

A print parameter object should be defined to be associated with the print file image to convert.

      ...
      **CATPrintParameters** Parameters;

      Parameters.**SetWhitePixel**(1);                               _// Print white pixels white_
      Parameters.**SetMapToPaper**(1);                               _// Resize image to match paper forma_ t
      Parameters.**SetBanner**("CAAPrtChangeFormat");                _// Add a banner_
      Parameters.**SetBannerPosition**(CATPRINT_TOP);                _// at the top of the image_
      Parameters.**SetLineWidthSpecificationMode**(CATPRINT_SCALED); _// Change line width with scale_
      Parameters.**SetLineTypeSpecificationMode**(CATPRINT_SCALED);  _// Change non continuous lines with scale_

      float imageWidth=0, imageHeight=0;
      int result = pImage->**GetSize**(imageWidth, imageHeight); _// Retrieve input file dimensions_
```vbscript
      if (result)

```

      {
        // Set the output image dimensions: width increases from 50%, height doesn't change
float imageWidth=0, imageHeight=0;
int result = pImage->**GetSize**(imageWidth, imageHeight); _// Retrieve input file dimensions_
if (result)
        CATPrintForm CurrentForm = Parameters.**GetCurrentForm**();
        CurrentForm().**SetSize**(imageWidth*1.5, imageHeight);

      }
      ...

---

The print parameters are taken into account to create the output image. The following parameters are set:

  * White pixels are kept white (for a print on white paper, it can be convenient to print them in black)
  * The image is resized to match the paper size
  * A banner with the text "CAAPrtChangeFormat" is printed at the top of the image
  * The line width are changed with respect to the scale
  * The size of the dashes is changed with respect to the scale
  * The image size is changed in order to keep the same height, but to increase its with 50%. To do this, the input file image size is retrieved using the `GetSize` method, and the new size is set as a print parameter through the _CATPrintForm_ instance retrieved using the ` GetCurrentForm` method from `parameters`.

Other print parameters take their default values.

[Top]
#### Writing the Output File

The file conversion can now take place.

      ...
The file conversion can now take place.
```vbscript
      if ( !pImage->**Print**(pDevice, Parameters) )

```

      {
```vbscript
if ( !pImage->**Print**(pDevice, Parameters) )
        cout << " Error during printing " << endl;
        ReturnCode = 1;
```

      }
      ...

---

The `Print` method converts the print file image from CGM to TIFF using the parameters set, and writes the output to the print raster file device.

[Top]
#### Cleaning the Application and Closing the Printer Manager

      ...
      delete pDevice;
delete pDevice;
      delete pImage;

      **CATPrinterManager::End()** ;
delete pDevice;
delete pImage;
      return ReturnCode;

    }

---

Simply don't forget to delete allocated objects, close the Printer Manager, and return the appropriate return code.

[Top]

* * *
### In Short

This use case shows the objects involved when converting a print file, here encoded using CGM, into another file encoded using another format, here TIFF. These objects are the print file image, the print raster file device, and the set of parameters that are needed to create the TIFF file.

First, the Printer Manager is initialized. Then, a _CATPrintFileImage_ instance is created using the input file, and a _CATPrintFileDevice_ instance is created using the target file format to accommodate the output TIFF file. A _CATPrintParameters_ instance is created and valued using the appropriate setters to hold the intended print parameters. Finally, the ` Print` method of the _CATPrintFileImage_ class is used to generate the TIFF file, and the Printer Manager is closed.

[Top]

* * *
### References

[1] |  [ Building and Lauching CAA V5 Samples](../CAADocUseCases/CAADocRunSample.md)
---|---
[Top]

* * *
### History

Version: **1** [Jan 2000] | Document created
---|---
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
