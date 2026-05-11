// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract:
//  ---------
//
//  Batch showing the use of CATString, CATMsgCatalog and 
//  CATUnicodeString in CATIA.
//
//  Illustrates:
//
//     1- Use of CATString
//
//     2- Use of CATUnicodeString to create NLS message
//        2-1 Build a NLS Message without parameter from a NLS file  
//        2-2 Build a NLS Message with 2 parameters from a NLS file
//     3- Use of CATRscCatalog to create a hard-coded string which must not be translated into other languages, 
//        without parameters
//     4- Conversion between the CATUnicodeString and other formats:
//        3-1 2-bytes unicode
//        3-2 UTF-8 (persistent data format)
//        3-3 STEP (famous CAD-CAM interface format)
//        3-4 integer and real 
//
//
//=============================================================================
//  How to launch:
//  -------------
//
//  Type:
//    CAASysCharStrings  
//  
//  The different traces of the sample appear on the standard output.
//
//  Return Code:
//     0 : OK
//
//=============================================================================

// System Framework
#include "CATString.h"
#include "CATMsgCatalog.h"
#include "CATRscCatalog.h"
#include "CATUnicodeString.h"
#include "CATLib.h"

// C++ Standard library      
#include <iostream.h>     
#include <wchar.h>        // for wide chars


int main()
{
  int ReturnCode = 0;

  cout << "The CAASysCharStrings sample begins .... "<< endl << endl ;

  //-----------------------------------------------------------------
  // 1- Use of CATString 
  //-----------------------------------------------------------------

  // Constructs a CATString from a constante
  CATString Surface1("SurfaceOfRevolution");

  // Constructs a CATString from a char
  char SurfaceNurbs[13];
  strcpy(SurfaceNurbs,"SurfaceNurbs");

  CATString Surface2(SurfaceNurbs);

  // When you print a CATString always converting into a char *
  cout << "The first  surface is ="<< Surface1.ConvertToChar() << endl;
  cout << "The second surface is ="<< Surface2.ConvertToChar() << endl;

  //-----------------------------------------------------------------
  // 2- Use of CATUnicodeString to create NLS message
  //-----------------------------------------------------------------

     // ------------------------------------
     // Data used in the 2 following samples 
     // ------------------------------------

  // The message catalog is CAASysCharStrings.CATMsg that you find in 
  // this local CNext/resources/msgcatalog
  //
  CATString MsgCatalogName("CAASysCharStrings");

  // The resource catalog is CAASysNotToTranslateCharStrings.CATRsc that you find in 
  // this local CNext/resources/msgcatalog
  //
  CATString RscCatalogName("CAASysNotToTranslateCharStrings");

     //-----------------------------------------------------------------
     // 2-1 Create a NLS message without parameters 
     //-----------------------------------------------------------------

  // Builds a default message. This message should be used if there is a 
  // problem with the CAASysCharStrings.CATRsc file.
  // In general this default message is the english version, but for the
  // sample we have done an explicit sentence.
  //
  CATUnicodeString DefaultMessage1 =
     "A problem occurred while loading the CAASysCharStrings.CATNls file";

  // Identifies the message key
  CATString MsgCatalogKey1("MessageWithoutParameters");

  // Builds the message without parameters  
  // The following method is a static one.
  //
  CATUnicodeString BuiltMessage1 ;
  BuiltMessage1 = CATMsgCatalog::BuildMessage(
                             MsgCatalogName,
                             MsgCatalogKey1,
                             NULL,
                             0,
                             DefaultMessage1);
  
  // and output it ...
  //
  cout << "The message is: " <<  BuiltMessage1.ConvertToChar() << endl;

  // The Key "ErrorMessageKey" does'nt exist in the file
  //
  CATUnicodeString ErrorMessage ;
  ErrorMessage = CATMsgCatalog::BuildMessage(
                             MsgCatalogName,
                             "ErrorMessageKey",
                             NULL,
                             0,
                             DefaultMessage1);
  
  cout << "The message is: " <<  ErrorMessage.ConvertToChar() << endl;

     //-----------------------------------------------------------------
     // 2-2 Create a NLS message with 2 parameters      
     //-----------------------------------------------------------------
  
  // Set a value to the parameters
  int ParametersCount = 2;
  CATUnicodeString Parameters[2];
  
  Parameters[0] = "First parameter";
  Parameters[1] = "Second parameter";

  // The default message is the english version
  CATUnicodeString DefaultMessage2 = "This message contains 2 parameters" ;

  // Identifies the message key
  CATString MsgCatalogKey2("MessageWithTwoParameters");

  // Builds the message and output it. 
  // The following method is a static one.
  //
  CATUnicodeString BuiltMessage2 ;
  BuiltMessage2 = CATMsgCatalog::BuildMessage(
                             MsgCatalogName,
                             MsgCatalogKey2,
                             Parameters,
                             ParametersCount,
                             DefaultMessage2);
  
  cout << "The message is: " <<  BuiltMessage2.ConvertToChar() << endl;


  //-----------------------------------------------------------------
  // 3- Create a hard-coded string which must not be translated into other languages, without parameters 
  //-----------------------------------------------------------------

  // Builds a default message. This message should be used if there is a 
  // problem with the CAASysNotToTranslateCharStrings.CATRsc file.
  //
  CATString DefaultResourceCatalogValue3 =
     "A problem occurred while loading the CAASysNotToTranslateCharStrings.CATRsc file";

  // Identifies the message key
  CATString RscCatalogKey3("ResourceCatalogValueWithoutParameters");

  // Builds the message without parameters  
  // The following method is a static one.
  //
  CATString BuiltResourceCatalogValue3 ;
  CATRscCatalog::BuildResource(
                         RscCatalogName,
                         RscCatalogKey3,
                         BuiltResourceCatalogValue3,
                         NULL,
                         0,
                         DefaultResourceCatalogValue3);
  
  // and output it ...
  //
  cout << "The Resource Catalog value is: " <<  BuiltResourceCatalogValue3.ConvertToChar() << endl;

  //-----------------------------------------------------------------
  // 4- Conversion between the CATUnicodeString and other formats
  //-----------------------------------------------------------------

     //-----------------------------------------------------------------
     // 4-1 Converts between CATUnicodeString and UCS-2 (2-bytes unicode) 
     //-----------------------------------------------------------------

  // Creates a C Language unicode string (wide char in C language
  // terminology)
  wchar_t* CLanguageUnicodeString = L"Unicode string";

  // Gets the C Language unicode string length
  int CharacterCount = wcslen(CLanguageUnicodeString);

  // Builds a CATUC2Bytes from the C Language unicode string 
  CATUC2Bytes* UnicodeCharacters = new CATUC2Bytes[CharacterCount];
  for (int i=0; i<CharacterCount; i++) 
  {
     UnicodeCharacters[i] = CLanguageUnicodeString[i];
  }

  // Fills a CATUnicodeString with the CATUC2Bytes table
  CATUnicodeString UnicodeString ;
  UnicodeString.BuildFromUCChar(UnicodeCharacters, CharacterCount);
  delete [] UnicodeCharacters;
  UnicodeCharacters = NULL ;

  // Output the CATUnicodeString
  cout << "The string is: " << UnicodeString.ConvertToChar() << endl;

     //-----------------------------------------------------------------
     // 4-2 Converts between CATUnicodeString and UTF8 (persistant data 
     // string encoding) or STEP (famous CAD-CAM interface format)
     //-----------------------------------------------------------------

  // Creates a CATUnicodeString containing the "String" string
  CATUnicodeString StringToConvert = "String";

  // Allocates the UTF8 string that the conversion service will fill
  char * UTF8String = new char[4+6*(StringToConvert.GetLengthInChar())];

  // Converts the CATUnicodeString to UTF8
  size_t UTF8StringByteCount;
  StringToConvert.ConvertToUTF8(UTF8String, &UTF8StringByteCount);

  // Output the UTF8 string
  char * OutputString = new char[UTF8StringByteCount+1];
  strncpy(OutputString,UTF8String,UTF8StringByteCount);
  OutputString[UTF8StringByteCount] = '\0';
  
  cout << "UTF8 String = " << OutputString << endl;
  
  delete [] OutputString;
  OutputString = NULL ;
  delete [] UTF8String;
  UTF8String = NULL ;

  // Allocates the STEP string that the conversion service will fill
  char * STEPString = new char[50];

  // Converts the string to the STEP interface format
  StringToConvert.ConvertToSTEP(STEPString);
  cout << "STEP String = " << STEPString << endl;
  
  delete [] STEPString;
  STEPString = NULL ;

     //-----------------------------------------------------------------
     // 4-3 Converts between CATUnicodeString and numerals
     //-----------------------------------------------------------------

  // Creates a CATUnicodeString containing "1250" (decimal form)
  StringToConvert = "1250";

  // Converts the string to an integer
  int OutputInteger = 0 ;
  int IsConversionOK = StringToConvert.ConvertToNum(&OutputInteger);
  cout << "output integer = " << OutputInteger << endl;

  // Creates a CATUnicodeString containing "1250.12" 
  StringToConvert = "1250.12";

  // Converts the string to a real
  double OutputReal;
  IsConversionOK = StringToConvert.ConvertToNum(&OutputReal);
  cout << "output real = " << OutputReal << endl;

  // Converts an integer into a CATUnicodeString, under the decimal form
  CATUnicodeString StringToFill;
  
  int InputInteger = 253;
  int FillingWasOK = StringToFill.BuildFromNum(InputInteger);
  cout << "output string = " << StringToFill.ConvertToChar() << endl;

  // Converts a real into a CATUnicodeString, under the decimal form
  double InputReal = 253.57;
  FillingWasOK = StringToFill.BuildFromNum(InputReal);
  cout << "output string = " << StringToFill.ConvertToChar() << endl;

  cout << endl << "The CAASysCharStrings sample is finished .... "<< endl << endl ;

  return ReturnCode;
}
