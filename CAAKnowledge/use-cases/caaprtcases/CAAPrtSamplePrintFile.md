---
title: "Printing Files"
category: "use-case case"
module: "CAAPrtUseCases"
tags: "["CAAPrtPrintFile", "CAAPrint"]"
source_file: "Doc/online/CAAPrtUseCases/CAAPrtSamplePrintFile.htm"
converted: "2026-05-11T17:17:56.141802"
---
# 3D PLM Enterprise Architecture

|
## 3D Visualization - Print

|
### Printing Files

_Creating a paper output from your files_
---|---|---
Use Case

* * *
### Abstract

This article shows how to print a given object on a printer.

  * **What You Will Learn With This Use Case**
  * **The CAAPrtPrintFile Use Case**
    * What Does CAAPrtPrintFile Do
    * How to Launch CAAPrtPrintFile
    * Where to Find the CAAPrtPrintFile Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What You Will Learn With This Use Case

This use case is intended to show how to print a given object on a printer.

[Top]
### The CAAPrtPrintFile Use Case

CAAPrtPrintFile is a use case of the CAAPrint.edu framework that illustrates the Print framework capabilities.

[Top]
#### What Does CAAPrtPrintFile Do

CAAPrtPrintFile is a batch program that reads a JPEG file from the command line and prints it on the chosen printer.

[Top]
#### How to Launch CAAPrtPrintFile Use

CAAPrtPrintFile is a batch program that reads a JPEG file from the command line and prints it on the chosen printer.
To launch CAAPrtPrintFile Use, you will need to set up the build time environment, then compile CAAPrtPrintFile Use along with its prerequisites, set up the run time environment, and then execute the use case [1].

You can launch CAAPrtPrintFile using a JPEG file as argument. The use case lists the available printers and then type the number associated to the chosen printer,  the input JPEG file is printed on the chosen printer.

  * With Windows

        E:>**CAAPrtPrintFile**  InstallRootDirectory/CAAPrint.edu/CNext/resources/graphic/images/CAAPrtPrintFile.jpg

---
  * With UNIX

        $ **CAAPrtPrintFile** InstallRootDirectory/CAAPrint.edu/CNext/resources/graphic/images/CAAPrtPrintFile.jpg

---

where:

  * `InstallRootDirectory` is the directory into which the CAA CD-ROM were unloaded
  * `CAAPrtPrintFile.jpg `is the sample JPEG file supplied. You can use other JPEG files you may have at hand.

_The CAAPrtPrintFile.jpg File_ ![](images/CAASamplePrtPrintFile.jpg)
---

[Top]
#### Where to Find the CAAPrtPrintFile Use Code

The CAAPrtPrintFile use case is made of a several classes located in the CAAPrtPrintFile.m module of the CAAPrint.edu framework:

Windows | `InstallRootDirectory/CAAPrint.edu/CAAPrtPrintFile.m/`

The CAAPrtPrintFile use case is made of a several classes located in the CAAPrtPrintFile.m module of the CAAPrint.edu framework:
Windows | `InstallRootDirectory/CAAPrint.edu/CAAPrtPrintFile.m/`
Unix | `InstallRootDirectory/CAAPrint.edu/CAAPrtPrintFile.m/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

To print a JPEG file on aprinter, there are seven main steps:
# | Step | Where
---|---|---
To print a JPEG file on aprinter, there are seven main steps:
1 | Displays the List of Printers | main
2 | Asks the End User for a Printer Choice | main
3 | Creates a Print File Image from the Input File | main
4 | Creates a Printer Device | main
5 | Defines Print Parameters | main
6 | Prints the Image | main
7 | Cleans the application | main

The preliminary task that consist in retrieving the input file name from the command line is not described. The input file name is retrieved from the command line in the `InputName` variable, such as TestFile.jpg.

[Top]
#### Displaying the List of Printers

As soon as the input file is retrieved, the list of available printers is displayed.

    #include "CATPrintFileImage.h"   _// To create an image from the input file_
    #include "CATPrintParameters.h"  _// To define print parameters_
    #include "CATPrinterDevice.h"    _// To define a print device_
    #include "CATPrinterManager.h"   _// To retrieve the printer list_
    #include "CATPrinter.h"          _// To print_
    ...

    int main(int argc, char* argv[])
    {
      int ReturnCode = 0;
      ... _// Retrieving the input file name is not described here_

      **CATPrinterManager::Begin(#);**

      // Retrieves and displays the list of printers
      cout << "Available printers: " << endl << endl;

```cpp
      for (int i=0; i<**CATPrinterManager::GetPrinterCount(#)** ; i++)

```

      {
cout << "Available printers: " << endl << endl;
for (int i=0; i<**CATPrinterManager::GetPrinterCount(#)** ; i++)
        CATPrinter printer = **CATPrinterManager::GetPrinterFromIndex(i)** ;
        int old_width = cout.width(3);
        cout.setf( ios::right );
        cout << i+1;
        cout.setf( ios::left );

        //cout.width(old_width);
int old_width = cout.width(3);
cout.setf( ios::right );
cout << i+1;
cout.setf( ios::left );
        cout << " : " << (const char*) **printer.GetDescription(#)** << endl;

      }
      ...

---

This printer manager is initialized using the static `Begin` method. Then for each available printer, the printer description is retrieved using the `GetDescription` method of the CATPrinter class, and displayed, associated with its number. The static `GetPrinterCount` method returns the number of available printers.

[Top]
#### Asking the End User for a Printer Choice

The end user should now select a printer.

    ...
      CATPrinter printer = **CATPrinterManager::GetPrinterFromIndex**(printerIndex);
      **CATPrinterManager::End(#);**
    ...

---

The printer is selected using its index. This index is used to retrieve the printer. As soon as this is done, the printer manager becomes useless and can freed using the static `End` method.

[Top]
#### Creating a Print File Image from the Input File

The printer is selected using its index. This index is used to retrieve the printer. As soon as this is done, the printer manager becomes useless and can freed using the static `End` method.
The print file image can now be built from the input file.

A print parameter object should be defined to be associated with the print file image to convert.

    ...
      CATPrintFileImage* image = new **CATPrintFileImage**(InputName, "JPEG");
    ...

---

This print file image is an instance of the CATPrintFileImage class instantiated from the input file. The input file format is passed as the second argument, here JPEG. The print file image created holds the input file in memory and the JPEG interpreter to enable the file interpretation as soon as this will be asked.

[Top]
#### Creating a Printer Device

The printer device should be next instantiated.

    ...
      CATPrinterDevice device( &printer );
    ...

---

The printer device is created using the selected printer as input. It is made of a generator for the printer format, and of of a stream into which the created file will be written.

[Top]
#### Defining Print Parameters

A print parameter object should be defined to be associated with the print file image to print.

    ...
A print parameter object should be defined to be associated with the print file image to print.
      CATPrintParameters parameters;

      parameters.SetRotation( CATPRINTCCW_90 );     _// Rotate the image_
      parameters.SetMapToPaper(1);                   _// Resize image to match paper forma_ t
```vbscript
      parameters.SetMargins(20.0, 20.0, 10.0, 10.0); _// Set margins_

    ...
```

---

The print parameters are taken into account to create the printed output. The following parameters are set:

  * The image is rotated by 90 degrees
  * The image is resized to match the paper size
  * The margins are set to 20 mm for left and right margins, and to 10 mm for top and bototom margins.

Other print parameters take their default values.

[Top]
#### Printing the Image

The file conversoin can now take place.

    ...
      image->**Print**( &device, parameters );
    ...

---

The `Print` method converts the print file image from JPEG to the printer format, usually PostScript, and prints the file using the parameters set.

[Top]
#### Cleaning the Application

    ...
      delete image;

      return ReturnCode;
    ...

---

Simply don't forget to delete allocated objects, and return the appropriate return code..

[Top]

* * *
### In Short

This use case shows the objects involved when printing a file, here encoded using JPEG, on a printer. These objects are the pinter manager, the printer, print file image, the printer device, and the set of parameters that are needed to print.

[Top]

* * *
### References

[1] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[Top]

* * *
### History

Version: **1** [Jan 2000] | Document created
---|---
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
