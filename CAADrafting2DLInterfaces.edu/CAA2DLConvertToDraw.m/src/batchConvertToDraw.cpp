//------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2007


//=============================================================================
//  Abstract of Use Case "batchConvertToDraw":
//  ------------------------------------------
//
//  This batch is based on CAA V5 batch infrastructure
//  To make a V5 batch you need 3 things :
//  - An XML descriptor file which describe your batch
//  - An XML parameter file which describe the inputs and outputs of your batch
//  - A library containing the implementation of your batch code through the symbol batchmain
//
// This cpp file is an example of a batch implementation. 
// The descriptor file is located in CNext/resources/batchdesc/batchConvertToDraw.xml
//   of CAADrafting2DLInterfaces.edu
// The parameter file is located in Data.d/ParamSample.xml
//
// Concerning return codes : the value of the RC of your batch is the value you'll use to return from
// batchmain symbol. Several return codes are used by BatchInfrastructure to report specific problems.
// They range from 1 to 19 (except 4 and 8)
// In addition all V5 batch agreed to give special meanings to several return code ranging from 20
// up to 49 (plus 4 and 8)
// 0 means the batch is OK
// 8 means the batch didn't produce results
// 4  means the batch produced partially its results
// You can follow the convention
//
//  TO define your own specific RC you can use the range 50 to 128, avoiding the RC used by the OS 
// (50, 126, 127, 128, ...)
  
//=============================================================================
// System
#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATIUnknownList.h"
#include "IUnknown.h"

// BatchInfrastructure
#include "CATIBatchCAA.h"  
#include "CATIBatchElementCAA.h"  
#include "CATIBatchElementsCAA.h"  
#include "CATUnicodeString.h"
#include "CATListOfCATUnicodeString.h"
#include "CATLib.h"
#include "CATStdIO.h"

#include "CATBatchAccessCAA.h"
#include "CATBatStatePubCAA.h"
#include "CATBatchPublicDefinitions.h"
#include "CATBatchParameters.h"
#include "CATBatchLogCAA.h"

// ObjectModelerBase 
#include "CATSession.h" 
#include "CATSessionServices.h" 
#include "CATInit.h"
#include "CATDocument.h"
#include "CATDocumentServices.h"
#include "CATIContainer.h"
#include "CATISpecObject.h"

// MechModInterfaces
#include "CATIPrtPart.h"
#include "CATIPrtContainer.h"

// DraftingInterfaces 
#include "CATSheetOrientation.h"

// Drafting2DLInterfaces 
#include "CAT2DLayoutServices.h"
#include "CATI2DLayoutLayout.h"
#include "CAT2DLDrawingServices.h"

// Internal
#include "CAA2DLConvertToDrawServices.h"


#ifdef _WINDOWS_SOURCE
extern "C" __declspec(dllexport) int batchmain (int argc, char** argv);
#else
extern "C" int batchmain (int argc, char** argv);
#endif

///////////////////// batchmain symbol implementation /////////////////////
 
int batchmain (int argc, char** argv)
{
  CATBatchLogCAA::PutInLog("Start batch to convert 2DLayout in drawing for Printing");

  int Error_code = 0;

  // 0/ CREATE THE SESSION AND READ THE INFORMATION IN THE XML FILE ASSOCIATED TO THE BATCH
  // ======================================================================================
  CATSession *pSampleSession = NULL;
  HRESULT hr = ::Create_Session("SampleSession",pSampleSession);
  if (FAILED(hr)) return 60;

  //Retrieve the CATBatStatePub object used to publish a completion state for the batch
  CATBatStatePubCAA* pub =  CATBatStatePubCAA::GetCAAStatePub();
  if (!pub)	return 61;

  //Retrieve CATIBatch the main interface to access XML parameter file from the batch  
  CATIBatchCAA* batch = GetCATIBatchCAA();
  if (!batch)	return 62;

  //Retrieves InputParameters section from the XML parameter file
  CATIBatchElementCAA* inputParameters = NULL;
  hr = batch->get_InputParametersCAA(inputParameters);
  if ( FAILED(hr) || !inputParameters )
    return 63;

  CATBatchLogCAA::PutInLog("Next ");

  // Suffix Name
  CATIBatchElementCAA* oSuffixName = NULL;
  CATUnicodeString usufId = "suffixName";
  CATUnicodeString suffixName;
  if (SUCCEEDED(inputParameters->ParameterCAA(usufId, oSuffixName)) && oSuffixName)
  {
    hr = oSuffixName->StringArg(suffixName);
    oSuffixName->Release();oSuffixName = NULL;
    if ( FAILED(hr) )   return 64;
  }

  // Standard Name
  CATIBatchElementCAA* oDrwStd = NULL;
  CATUnicodeString usId = "drwStandard";
  CATUnicodeString stdName;
  if (SUCCEEDED(inputParameters->ParameterCAA(usId, oDrwStd)) && oDrwStd)
  {
    hr = oDrwStd->StringArg(stdName);
    oDrwStd->Release();oDrwStd = NULL;
    if ( FAILED(hr) )   return 64;
  }

  // Printer name
  CATIBatchElementCAA* oPrtName = NULL;
  usId = "PrinterName";
  CATUnicodeString sPrinterName;
  if (SUCCEEDED(inputParameters->ParameterCAA(usId, oPrtName)) && oPrtName)
  {
    hr = oPrtName->StringArg(sPrinterName);
    oPrtName->Release();oPrtName = NULL;
    if ( FAILED(hr) )   return 65;
  }

  // Printer server name
  CATIBatchElementCAA* oPrtSrvName = NULL;
  usId = "PrinterServerName";
  CATUnicodeString sPrinterSrvName;
  if (SUCCEEDED(inputParameters->ParameterCAA(usId, oPrtSrvName)) && oPrtSrvName)
  {
    hr = oPrtSrvName->StringArg(sPrinterSrvName);
    oPrtSrvName->Release();oPrtSrvName = NULL;
    if ( FAILED(hr) )   return 66;
  }

  // Sheet Print Mode
  CATIBatchElementCAA* oSheetPrt = NULL;
  usId = "SheetPrintMode";
  CATUnicodeString sSheetPrintMode;
  if (SUCCEEDED(inputParameters->ParameterCAA(usId, oSheetPrt)) && oSheetPrt)
  {
    hr = oSheetPrt->StringArg(sSheetPrintMode);
    oSheetPrt->Release();oSheetPrt = NULL;
    if ( FAILED(hr) )   return 66;
  }

  //Put this result in the batch log.
  CATBatchLogCAA::PutInLog("Drawing Standard name: ");
  CATBatchLogCAA::PutInLog(stdName);
  CATBatchLogCAA::PutInLog("\n");
  CATBatchLogCAA::PutInLog("Printer location: ");
  CATBatchLogCAA::PutInLog(sPrinterSrvName);
  CATBatchLogCAA::PutInLog(" -- ");
  CATBatchLogCAA::PutInLog(sPrinterSrvName);
  CATBatchLogCAA::PutInLog("\n");

  //Retrieves all the <file> tags included in the inputParameters section
  // If the batch is launched from the command PrintToDraftingCmd, there is only one occurence.
  CATIBatchElementsCAA* inputFiles = NULL;
  hr = inputParameters->get_FileListCAA(inputFiles);
  if ( FAILED(hr) || !inputFiles )
    return 67;

  // Scans the list of <file> 
  long childrenCount = 0;
  hr = inputFiles->get_Count(childrenCount);
  CATIBatchElementCAA * elem  = NULL;

  for ( int i = 0; i<childrenCount; i++ )
  {
    hr = inputFiles->ItemCAA( i, elem  );
    if ( hr != S_OK )
      return 68;
    // for each <file> retrieve the file path corresponding to the attribute "filePath" of the 
    // <file> tag.
    CATUnicodeString usfile_path;
    elem->get_Path(usfile_path); 

    elem->Release();
    elem = NULL;
    // Writes this path in the log of the batch available in $BATCH_HOME/uuid/uuidLog.txt 
    // at the end of the execution. Default for BATCH_HOME is /tmp or C:\temp and uuid is a
    // generated identifier for each batch execution.
    CATBatchLogCAA::PutInLog("filepath : ");
    CATBatchLogCAA::PutInLog(usfile_path.CastToCharPtr() );
    CATBatchLogCAA::PutInLog("\n");

    // Checks the file existence and the right to read it.
    if (CATFileAccess(usfile_path.CastToCharPtr() , 04) != CATLibSuccess)
    {
      CATBatchLogCAA::PutInLog("Cannot access input file:  ");
      CATBatchLogCAA::PutInLog(usfile_path.CastToCharPtr() );
      CATBatchLogCAA::PutInLog("\n");
      return 69;
    }

    // Retrieves the directory name in the usfile_path path
    char in_filename[CATMaxPathSize];
    char in_dirname[CATMaxPathSize];
    memset(in_filename, '\0', CATMaxPathSize);
    memset(in_dirname, '\0', CATMaxPathSize);
    CATSplitPath( usfile_path.CastToCharPtr(), in_dirname, in_filename);
    CATUnicodeString dirToWork = in_dirname;
    CATUnicodeString partName = in_filename;
    CATBatchLogCAA::PutInLog("Part Name = ");
    CATBatchLogCAA::PutInLog(partName);
    CATBatchLogCAA::PutInLog("\n");
    CATBatchLogCAA::PutInLog("directory to work ");
    CATBatchLogCAA::PutInLog(dirToWork);
    CATBatchLogCAA::PutInLog("\n");

    // 1/ Opens the Part document containing the 2DLayout to convert
    // ============================================================
    CATDocument *pDocPart = NULL;
    CATInit_var spInitOnDoc;
    CATBatchLogCAA::PutInLog("\n");
    CATBatchLogCAA::PutInLog("1/ Start Open document : ");
    if( SUCCEEDED(CATDocumentServices::OpenDocument(usfile_path, pDocPart)) && pDocPart)
    {
      // To Prevent the destruction
      CATLockDocument(*pDocPart);
      spInitOnDoc = pDocPart;
      if(NULL_var != spInitOnDoc)
      {
        CATBatchLogCAA::PutInLog("OK");
        CATBatchLogCAA::PutInLog("\n");
      }
    }

    // 2/ Retrieves the Mechanical Part
    // ================================
    CATBatchLogCAA::PutInLog("\n");
    CATBatchLogCAA::PutInLog("2/ Retrieve the Mechanical Part : ");
    CATIPrtPart_var spPart;
    CATIPrtContainer * piPrtCont =  (CATIPrtContainer*) spInitOnDoc->GetRootContainer("CATIPrtContainer");	
    if (piPrtCont)
    {
      // Gets the part feature of the container.
      spPart = piPrtCont->GetPart();
      if (NULL_var != spPart)
        CATBatchLogCAA::PutInLog(" OK ");
      else
      {
        Error_code = 70;
        CATBatchLogCAA::PutInLog(" KO ");
      }
      CATBatchLogCAA::PutInLog("\n");
      piPrtCont->Release();piPrtCont=NULL;
    }

    // 3/ Gets the 2DLayout Root
    // =========================
    CATI2DLayoutLayout *pi2DLayout = NULL;
    if (NULL_var != spPart)
    {
      CATBatchLogCAA::PutInLog("\n");
      CATBatchLogCAA::PutInLog("3/ Get the 2DLayout Root : ");
      CAT2DLayoutServices::GetLayout2DL(spPart,&pi2DLayout);
      if (pi2DLayout)
        CATBatchLogCAA::PutInLog("OK ");
      else
      {
        Error_code = 71;
        CATBatchLogCAA::PutInLog("KO ");
      }
      CATBatchLogCAA::PutInLog("\n");
    }

    // 4/ Retrieves the 2D Layout standard and format of the active sheet
    // ==================================================================
    if (pi2DLayout)
    {
      CATBatchLogCAA::PutInLog("\n");
      CATBatchLogCAA::PutInLog("4/ Retrieve the 2D Layout standard and format of the active sheet : ");
      CATUnicodeString fmtName;
      CATBoolean sheetDisplay = FALSE;
      CATSheetOrientation sheetOrt;
      double fmtWidth=0.0;
      double fmtHeight=0.0;
      int indiceSheet = 0;
      hr = CAA2DLConvertToDrawServices::Get2DLStandardAndFormat(pi2DLayout, stdName,fmtWidth,fmtHeight,sheetOrt,sheetDisplay,indiceSheet);
      if (SUCCEEDED(hr))
        CATBatchLogCAA::PutInLog("OK ");
      else
      {
        Error_code = 72;
        CATBatchLogCAA::PutInLog("KO ");
      }
      CATBatchLogCAA::PutInLog("\n");

      // 5/ Creates the new Drawing Document
      // ===================================
      CATDocument* pDocDraw = NULL;
      CATBatchLogCAA::PutInLog("\n");
      CATBatchLogCAA::PutInLog("5/ Create the new Drawing document : ");
      hr = CATDocumentServices::New("CATDrawing", pDocDraw);
      if (SUCCEEDED(hr))
        CATBatchLogCAA::PutInLog("OK");
      else
      {
        Error_code = 73;
        CATBatchLogCAA::PutInLog("KO");
      }
      CATBatchLogCAA::PutInLog("\n");

      if (pDocDraw)
      {
        // 6/ Drawing document initialisation: Standard, Sheet format and 2DLayout extraction
        // ==================================================================================
        CATBatchLogCAA::PutInLog("\n");
        CATBatchLogCAA::PutInLog("6/ Drawing document initialisation: Standard, Sheet format and 2DLayout extraction : ");
        hr = CAA2DLConvertToDrawServices::InitDrawingDocument(pDocDraw, stdName,fmtWidth,fmtHeight,sheetOrt,sheetDisplay,pi2DLayout);
        if (SUCCEEDED(hr))
          CATBatchLogCAA::PutInLog("OK ");
        else
        {
          Error_code = 74;
          CATBatchLogCAA::PutInLog("KO ");
        }
        CATBatchLogCAA::PutInLog("\n");

        CATUnicodeString printfmt = "EPS";
        CATUnicodeString drwfileName = dirToWork + "\\DrawingToPrint_"+suffixName+".CATDrawing";
        CATUnicodeString printfileName = dirToWork + "\\PrintDrawing_"+suffixName+".ps";

        // 7/ Print the Drawing document (Sheet number = indiceSheet)
        // ==========================================================
        CATBatchLogCAA::PutInLog("\n");
        CATBatchLogCAA::PutInLog("7/ Print the Drawing document as ");
        CATBatchLogCAA::PutInLog(printfmt);
        CATBatchLogCAA::PutInLog(" format : ");
        CATBatchLogCAA::PutInLog("\n");

        // To print the active Sheet
        int startLoop = indiceSheet;
        int endLoop = indiceSheet+1;

        // All the sheets are printed
        CATUnicodeString AllSheets("AllSheets");
        if (sSheetPrintMode == AllSheets)
        {
          startLoop = 0;
          CATIUnknownList * pi2DLSheetList = NULL;
          if (SUCCEEDED(pi2DLayout->GetSheets(&pi2DLSheetList)) && pi2DLSheetList)
          {
            unsigned int piListSize = 0;
            pi2DLSheetList->Count(&piListSize);
            pi2DLSheetList->Release();pi2DLSheetList=NULL;
            endLoop = piListSize;
          }
        }
        for (int numSheet = startLoop; numSheet < endLoop; numSheet++)
        {
          hr = CAA2DLConvertToDrawServices::PrintDrawingDocument(pDocDraw, printfileName, printfmt,numSheet);
          if (SUCCEEDED(hr))
            CATBatchLogCAA::PutInLog("OK ");
          else
          {
            Error_code = 75;
            CATBatchLogCAA::PutInLog("KO ");
          }
          CATBatchLogCAA::PutInLog("\n");

          // 8/ Launches the print to the printer
          // ====================================
          if (SUCCEEDED(hr))
          {
#ifdef _WINDOWS_SOURCE
            CATBatchLogCAA::PutInLog("\n");
            CATBatchLogCAA::PutInLog("8/ Launch the print to the printer : ");

            // Creates the .bat file to execute the print to the printer
            const char* batFileName;
            const char* tempDir = CATGetTempDirectory();
            char* tempBatFileNameChar = _tempnam(tempDir, "printbatch_");
            CATUnicodeString tempBatFileName;
            if (tempBatFileNameChar != NULL)
            {
              tempBatFileName = tempBatFileNameChar;
              free(tempBatFileNameChar);  
            }
            tempBatFileName= tempBatFileName+suffixName;
            tempBatFileName.Append(".bat");

            batFileName = tempBatFileName.CastToCharPtr();
            CATBatchLogCAA::PutInLog("\n");
            CATBatchLogCAA::PutInLog(batFileName);

            unsigned int batFileDesc;
            HRESULT rc = CATFOpen(&tempBatFileName, "wt", &batFileDesc);
            if ( SUCCEEDED(rc) )
            {
              CATBatchLogCAA::PutInLog("\n");
              CATBatchLogCAA::PutInLog("succeeded fopen");

              CATUnicodeString sSlash("\\");
              CATUnicodeString sBlanc(" ");
              CATUnicodeString slineString = "Copy /b ";
              slineString +=  printfileName;
              slineString +=  sBlanc;
              slineString +=  sSlash;
              slineString +=  sSlash;
              slineString +=  sPrinterSrvName;
              slineString +=  sSlash;
              slineString +=  sPrinterName;
              int nCharWritten = 0;
              CATBatchLogCAA::PutInLog("\n");
              CATBatchLogCAA::PutInLog(slineString.ConvertToChar());
              rc = CATFPuts(slineString.ConvertToChar(), batFileDesc, &nCharWritten);
              rc = CATFClose(batFileDesc);
            }
            char* argv[2];
            argv[0] = (char*) batFileName;
            argv[1] = NULL;
            int iPid,exitStatus;
            CATLibStatus status = CATStartProcess(argv[0], argv, 0, &iPid, &exitStatus);
            if (CATLibSuccess == status)
            {
              Error_code = 0;
              CATBatchLogCAA::PutInLog("OK ");
            }
            else
            {
              Error_code = 76;
              CATBatchLogCAA::PutInLog("KO ");
            }
            CATWaitProcess (iPid,  &exitStatus);
            if (CATLibSuccess == status)
            {
              CATDeleteFile(tempBatFileName.CastToCharPtr());
              CATDeleteFile(printfileName.CastToCharPtr());            
            }
#else
            CATBatchLogCAA::PutInLog("\n");
            CATBatchLogCAA::PutInLog("8/ Launch the print to the printer : ");
            CATBatchLogCAA::PutInLog("\n");
            CATBatchLogCAA::PutInLog("This step is not implemented on UNIX operating system ");
#endif
          }
        }
        // 9/ Removes Drawing Document
        // ===========================
        CATDocumentServices::Remove (*pDocDraw);
      }
      pi2DLayout->Release();pi2DLayout=NULL;
    }

    // 10/ Remove Part Document
    // ========================
    hr = CATUnLockDocument(*pDocPart);
    CATDocumentServices::Remove (*pDocPart);

    //11/ Delete files
    // ===============

    //InputParameter file
    const char* cTemporaryDirectory = CATGetTempDirectory ();
    char cFullPathXMLFile[CATMaxPathSize];
    CATUnicodeString sXMLFileName ("ParamTest_");
    sXMLFileName = sXMLFileName+suffixName;
    sXMLFileName.Append(".xml");
    CATMakePath (cTemporaryDirectory,sXMLFileName.ConvertToChar(),cFullPathXMLFile);
    CATDeleteFile(cFullPathXMLFile);

    // Part Document
    CATDeleteFile(usfile_path.CastToCharPtr());
  }

  if (inputFiles) inputFiles->Release(),inputFiles = NULL;
  if (inputParameters) inputParameters->Release(),inputParameters = NULL;

  //11/ ENDS SESSION
  //================
  ::Delete_Session("SampleSession");
  
  return Error_code;
}
