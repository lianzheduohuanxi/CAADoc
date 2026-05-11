// COPYRIGHT DASSAULT SYSTEMES 2007
//=============================================================================
//
// CAA2DLPrintToDraftingCmd:
// 
//    This command launches a batch to create a Drawing from 2DLayout 
//    and print the active sheet of the drawing
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Dec. 2007 Creation
//=============================================================================

//-------------------------------------------------- Include File of this class
#include "CAA2DLPrintToDraftingCmd.h"

// Internal
#include "CAA2DLWindowWarning.h"
#include "CATMsgCatalog.h"

//---------------------------------------------------------------------- System
#include "CATLib.h"
#include "CATUnicodeString.h"

//------------------------------------------------------------ ApplicationFrame
#include "CATFrmEditor.h"

//---------------------------------------------------------------------- Dialog
#include "CATDlgNotify.h"

//----------------------------------------------------------- ObjectModelerBase
#include "CATDocumentServices.h"
#include "CATDocument.h"

//---------------------------------------------------------- BatchInfrastructure
#include "CATBatClientMonitorCAA.h"
#include "CAA2DLPrintToDraftingWatcher.h"

#include "CATBatchPublicDefinitions.h"
#include "CATIBatchCAA.h"
#include "CATIBatchElementCAA.h"
#include "CATIBatchElementsCAA.h"

#include "CATBatchAccessCAA.h"
#include "CATBatchParameters.h"
#include "CATBatchLogCAA.h"

//---------------------------------------------------------- DraftingInterfaces
#include "CATCreateExternalObject.h"

CATCreateClassArg (CAA2DLPrintToDraftingCmd, CATString);
//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CAA2DLPrintToDraftingCmd::CAA2DLPrintToDraftingCmd (CATString * iArgument)
: CATCommand (CATString("CAA2DLPrintToDraftingCmd"), CATCommandModeExclusive)
{
}


//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
CAA2DLPrintToDraftingCmd::~CAA2DLPrintToDraftingCmd ()
{
}

CATStatusChangeRC CAA2DLPrintToDraftingCmd::Activate ( CATCommand* FromClient, CATNotification* EvtDat )
{ 
  RequestDelayedDestruction();
#ifdef _WINDOWS_SOURCE

  CATFrmEditor *pEditor = CATFrmEditor::GetCurrentEditor();
  if (pEditor ) 
  {
    // Get the printer name 
    const char* cPrinterName = CATGetEnv("CAT_CAA2DLPrinterName");

    // Get the printer server name
    const char* cPrinterSrvName = CATGetEnv("CAT_CAA2DLPrinterServerName");

    // Get the licensing file 
    const char* clicfile = CATGetEnv("CAT_CAA2DL_LICENSING");

    CATUnicodeString sPrinterName (cPrinterName);
    CATUnicodeString sPrinterSrvName (cPrinterSrvName);
    if (cPrinterName && cPrinterSrvName )
    {
      // Working directory
      const char* cTemporaryDirectory = CATGetTempDirectory ();
      char cFullPath[CATMaxPathSize];
      CATUnicodeString sPrefixName("2DLPartToPrint_");
      CATUnicodeString sSuffixName;
      sSuffixName.BuildFromNum(rand()*4/200);
      CATUnicodeString sFileName;
      CATUnicodeString sExtensionName(".CATPart");
      sFileName = sPrefixName+sSuffixName+sExtensionName;
      CATMakePath (cTemporaryDirectory,sFileName.ConvertToChar(),cFullPath);
      CATUnicodeString storageNameDocument (cFullPath);

      // Save the current part document in CATTemp directory
      CATDocument *pDocPart = pEditor->GetDocument();
      CATDocumentServices::SaveAsNew(*pDocPart, storageNameDocument);

      //Here we generate the XML parameter file corresponding to the batch: 
      CATBatchParameters input_param;
      CATUnicodeString sXMLFileName="ParamTest_";
      sXMLFileName=sXMLFileName+sSuffixName;
      sXMLFileName.Append(".xml");
      if (clicfile)
        input_param.BeginBuffer("batchConvertToDraw", sXMLFileName,NULL,NULL,NULL,cTemporaryDirectory,clicfile); 
      else
        input_param.BeginBuffer("batchConvertToDraw", sXMLFileName,NULL,NULL,NULL,cTemporaryDirectory,NULL); 
 
      input_param.BeginInput();
      input_param.InsertFile("file1",storageNameDocument, "", COMM_FILE_BINARY);

      // The batch works with the parent standard of standard used by the 2D Layout
      // To work with a specific standard replace ParentStd by the DRAWING standard name.
      // Drawing standard and 2D Layout standard must be compatible:
      //   - Identical parent standards
      //   - Identical dimension formats: (Tolerance and Value)

      // Suffix name
      input_param.InsertSimpleArg("suffixName", sSuffixName);

      // Drawing standard name (Optional)
      const char* cDrawingStdName = CATGetEnv("CAT_CAA2DLDrawingStandardName");
      if (cDrawingStdName)
      {
        CATUnicodeString sPrinterSrvName (cDrawingStdName);
        input_param.InsertSimpleArg("drwStandard", sPrinterSrvName);
      }
      // If the environment variable is not set. The Drawing will be created with the parent standard of the 2DLayout Standard
      else
        input_param.InsertSimpleArg("drwStandard", "ParentStd");

      // Sheet Print Mode (Optional)
      const char* cSheetPrintMode = CATGetEnv("CAT_CAA2DLSheetPrintMode");
      if (cSheetPrintMode)
      {
        CATUnicodeString sSheetPrintMode (cSheetPrintMode);
        input_param.InsertSimpleArg("SheetPrintMode", sSheetPrintMode);
      }
      // If the environment variable is not set. Only ActiveSheet is printed
      else
        input_param.InsertSimpleArg("SheetPrintMode", "ActiveSheet");

      // Printer Name initialization
      input_param.InsertSimpleArg("PrinterName", sPrinterName);

      // Printer Server name initialization
      input_param.InsertSimpleArg("PrinterServerName", sPrinterSrvName);
      input_param.EndInput();

      // Here we describe the output directory for BatchSample.
      const char* batch_home = CATGetEnv("BATCH_HOME");
      const char* out_folder = batch_home; // we choose to write the outputs in $BATCH_HOME. 
      input_param.BeginOutput();
      input_param.EndOutput();
      input_param.EndBuffer();

      //Retrieve the ClientMonitor, main interface to start and monitor batches
      CATBatClientMonitorCAA*  cliMonitor = CATBatClientMonitorCAA::GetTheClientMonitorCAA();
      if (!cliMonitor)	
        return CATStatusChangeRCAborted;

      //Monitor V5 batches initialization
      int batchMode = 0;
      HRESULT hr = cliMonitor->InitializeV5Monitoring(batchMode);

      //Create a specific object to register callbacks on batch events:(CATBatchEndNotif)
      static CAA2DLPrintToDraftingWatcher evt;

      char uuid[SIZE_T_ID];

      //We retrieve the full path of the previously generated XML parameter file
      CATUnicodeString path_param;
      input_param.GetFullPath(path_param);

      //We start the batch, uuid is an output argument retrieved by this call. It is a unique identifier for this batch run
      // It must be used later on as an input to get information on this batch execution.
      hr = cliMonitor->StartV5Batch(path_param, uuid);

      if (FAILED(hr))	
        return CATStatusChangeRCAborted;

      // Set the uuid to the batch to the watcher: CAA2DLPrintToDraftingWatcher.
      else
        evt.SetUUID(uuid);
    }
    else
    {
      CATUnicodeString sMsg = CATMsgCatalog::BuildMessage( "CAA2DLPrintToDrafting","InputVariable");
      CATDlgNotify *pBox = CAA2DLWindowCreateMsgBox( "InputVariable", sMsg, CATDlgNfyInformation );
      CATUnicodeString sMsgTitle = CATMsgCatalog::BuildMessage( "CAA2DLPrintToDrafting","BatchReport");
      if (pBox) pBox->SetTitle(sMsgTitle);
    }
  }
#else
  CATUnicodeString sMsg = CATMsgCatalog::BuildMessage( "CAA2DLPrintToDrafting","OnlyWindowOS");
  CATDlgNotify *pBox = CAA2DLWindowCreateMsgBox( "OnlyWindowOS", sMsg, CATDlgNfyInformation );
  CATUnicodeString sMsgTitle = CATMsgCatalog::BuildMessage( "CAA2DLPrintToDrafting","BatchReport");
  if (pBox) pBox->SetTitle(sMsgTitle);
  
#endif
  return CATStatusChangeRCCompleted;
}
