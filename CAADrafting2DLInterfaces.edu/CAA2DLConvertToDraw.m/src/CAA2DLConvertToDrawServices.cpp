// COPYRIGHT DASSAULT SYSTEMES 2007
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
// DESCRIPTION :
//                  
//-----------------------------------------------------------------------------
// COMMENTS :
//     This class contains services used by the batch "batchConvertToDraw"
//-----------------------------------------------------------------------------


#include "CAA2DLConvertToDrawServices.h"

//System
#include "IUnknown.h"
#include "CATBaseUnknown.h"
#include "CATIUnknownList.h"
#include "CATBoolean.h"
#include "CATUnicodeString.h"
#include "CATSettingRepository.h"

// ObjectModelerBase
#include "CATDocument.h"
#include "CATDocumentServices.h"
#include "CATInit.h"
#include "CATIContainer.h"

// ObjectSpecsModeler
#include "CATISpecObject.h"
#include "CATLISTV_CATISpecObject.h"

//DraftingInterfaces
#include "CATIDftDocumentServices.h"
#include "CATIDftDrawing.h"
#include "CATIDftDrawingFormats.h"
#include "CATIDftSheet.h"
#include "CATIDftSheetFormat.h"
#include "CATIDftStandardManager.h"
#include "CATIDftStandard.h"
#include "CATIDftFormat.h"
#include "CATSheetOrientation.h"

// Drafting2DLInterfaces
#include "CATI2DLayoutLayout.h"
#include "CATI2DLayoutSheet.h"
#include "CAT2DLDrawingServices.h"

// PrintBase
#include "CATPrintParameters.h"
#include "CATPrintVisuParameters.h"
#include "CATPrintFileDevice.h"

// BatchInfrastructure
#include "CATBatchLogCAA.h"

// Mathematics
#include "CATMath.h"

// Gets the parent standard name and the format from 2DLayout
HRESULT CAA2DLConvertToDrawServices::Get2DLStandardAndFormat(CATI2DLayoutLayout *pi2DLayout,
                                                             CATUnicodeString &ioStdName, 
                                                             double &oFmtWidth,double &oFmtHeight,
                                                             CATSheetOrientation &oSheetOrient,
                                                             CATBoolean &oSheetDisplayMode,
                                                             int &oNum2DLActiveSheet)
{
  HRESULT hr = E_FAIL;
  if (pi2DLayout)
  {
    // standard used for the Drawing is the parent standard of the 2D Layout standard
    CATUnicodeString parentStandard = "ParentStd";
    if (parentStandard == ioStdName)
    {
      // Gets the 2DL container
      CATISpecObject *piSpecObj=NULL;
      CATIContainer_var sp2DLCont;
      if (SUCCEEDED(pi2DLayout->QueryInterface(IID_CATISpecObject,(void **)&piSpecObj)))
      {
        sp2DLCont = piSpecObj->GetFeatContainer();
        piSpecObj->Release();
        piSpecObj=NULL;
      }


      if (NULL_var != sp2DLCont)
      {
        // Retrieve the parent standard name
        CATIDftStandardManager *piStdmgr = NULL;
        if (SUCCEEDED(sp2DLCont->QueryInterface(IID_CATIDftStandardManager,(void**)&piStdmgr)))
        {
          wchar_t  *wstdStd = NULL;
          piStdmgr->GetDefaultStandard (&wstdStd);
          CATIDftStandard *piDftStd = NULL;
          if (SUCCEEDED(piStdmgr->GetStandard(wstdStd,&piDftStd)) && piDftStd)
          {
            wchar_t  *wstdStdParent = NULL;
            hr = piDftStd->GetParentName(&wstdStdParent);
            if (SUCCEEDED(hr))
              ioStdName.BuildFromWChar(wstdStdParent);

            if (wstdStdParent) {delete[] wstdStdParent; wstdStdParent = NULL;}
            piDftStd->Release();piDftStd=NULL;
          }
          piStdmgr->Release (); piStdmgr=NULL;
        }
      }
    }
    // Check the input Standard
    else
    {
      hr = S_OK;
    }

    // Retrieve the format name of the activeSheet
    if (SUCCEEDED(hr))
    {
      CATI2DLayoutSheet *pi2DLSheet = NULL;
      pi2DLayout->GetActiveSheet(&pi2DLSheet);
      CATIDftSheetFormat *piDftSheetFormat = NULL;
      if (pi2DLSheet && SUCCEEDED(pi2DLSheet->QueryInterface (IID_CATIDftSheetFormat,(void **)&piDftSheetFormat)))
      {
        CATIDftFormat *piDftFormat = NULL;
        if (SUCCEEDED(piDftSheetFormat->GetSheetFormat(IID_CATIDftFormat,(IUnknown **)&piDftFormat)))
        {
          hr = piDftFormat->GetFormatWidth(oFmtWidth);
          hr = piDftFormat->GetFormatHeight(oFmtHeight);
          piDftFormat->Release();piDftFormat=NULL;
        }
        piDftSheetFormat->GetSheetOrientation(oSheetOrient);
        piDftSheetFormat->GetSheetDisplayMode(oSheetDisplayMode);
        piDftSheetFormat->Release();piDftSheetFormat=NULL;

        if (SUCCEEDED(hr))
        {
          hr = E_FAIL;
          hr = CAA2DLConvertToDrawServices::GetTheNumber2DLayoutSheet(pi2DLSheet,oNum2DLActiveSheet);
        }
        pi2DLSheet->Release();pi2DLSheet=NULL;
      }
    }
  }
  return hr;
}
// Init Drawing Standard and attributes and extract the 2DLayout to the Drawing
HRESULT CAA2DLConvertToDrawServices::InitDrawingDocument(CATDocument *pDocDraw, 
                                                         CATUnicodeString &iStdName, 
                                                         double &iFmtWidth,double &iFmtHeight,
                                                         CATSheetOrientation &iSheetOrient,
                                                         CATBoolean &iSheetDisplayMode,
                                                         CATI2DLayoutLayout *ipi2DLayout)
{
  HRESULT hr = E_INVALIDARG;
  if (pDocDraw && ipi2DLayout)
  {
    CATIDftDocumentServices *piDftDocServices = NULL;
    CATIContainer_var spDrwCont;
    CATIDftDrawing *piDftDrawing = NULL;
    if (SUCCEEDED(pDocDraw->QueryInterface(IID_CATIDftDocumentServices, (void **)&piDftDocServices)))
    {
      if (SUCCEEDED(piDftDocServices->GetDrawing(IID_CATIDftDrawing, (void **)&piDftDrawing)) && piDftDrawing)
      {
        // Gets the drawing container
        CATISpecObject *piSpecObj=NULL;
        if (SUCCEEDED(piDftDrawing->QueryInterface(IID_CATISpecObject,(void **)&piSpecObj)))
        {
          spDrwCont = piSpecObj->GetFeatContainer();
          piSpecObj->Release();
          piSpecObj=NULL;
        }
      }
      piDftDocServices->Release();
      piDftDocServices=NULL;
    }
    CATUnicodeString fmtName;
    if (NULL_var != spDrwCont)
    {
      // Standard initialization.
      CATIDftStandardManager *piStdmgr = NULL;

      if (SUCCEEDED(spDrwCont->QueryInterface(IID_CATIDftStandardManager,(void**)&piStdmgr)))
      {
        wchar_t  *wstd = new wchar_t[iStdName.GetLengthInChar() + 1];
        iStdName.ConvertToWChar(wstd);
        hr = piStdmgr->ImportStandard (wstd);
        if (wstd) {delete[] wstd; wstd = NULL;}
        piStdmgr->Release (); piStdmgr=NULL;
      }
    }

    // Retrieve the appropriate format name from height and width
    if (SUCCEEDED(hr) && piDftDrawing)
    {
      hr = CAA2DLConvertToDrawServices::GetAppropriateFormat(piDftDrawing,iFmtWidth,iFmtHeight,fmtName);
    }

    if (SUCCEEDED(hr))
    {
      hr = E_FAIL;
      // Sheet format initialization
      CATIDftSheet *piDftSheet = NULL;
      CATIDftSheetFormat *piDftSheetFormat = NULL;

      // Gets active sheet.
      if (piDftDrawing && SUCCEEDED(piDftDrawing->GetActiveSheet(&piDftSheet)))
      {
        CATIDftSheetFormat *piDftSheetFormat = NULL;
        if (piDftSheet && SUCCEEDED(piDftSheet->QueryInterface (IID_CATIDftSheetFormat,(void **)&piDftSheetFormat)))
        {
          HRESULT hr1 = piDftSheetFormat->SetSheetFormat(fmtName);
          HRESULT hr2 = piDftSheetFormat->SetSheetOrientation(iSheetOrient);
          HRESULT hr3 = piDftSheetFormat->SetSheetDisplayMode(iSheetDisplayMode);
          if (SUCCEEDED(hr1) && SUCCEEDED(hr1) && SUCCEEDED(hr3))
            hr = S_OK;

          piDftSheetFormat->Release();
          piDftSheetFormat=NULL;
        }
        piDftSheet->Release();
        piDftSheet=NULL;
      }


      if (SUCCEEDED(hr) && piDftDrawing)
      {
        CATBaseUnknown *pBUDrw = NULL;
        if (SUCCEEDED(piDftDrawing->QueryInterface(IID_CATBaseUnknown,(void **)&pBUDrw)))
        {
          // Extract the 2DLayout to the Drawing
          int gen2DGeom = 1;
          CATSettingRepository *pSetRep = CATSettingRepository::GetRepository("DraftingOptions");
          pSetRep->ReadSetting("CATDrwGeomOf2DLView", &gen2DGeom);
          CATBoolean boolGenGeom = gen2DGeom ? TRUE : FALSE;

          hr = CAT2DLDrawingServices::Extract2DLayoutToDrawing( ipi2DLayout, pBUDrw, boolGenGeom );
          pBUDrw->Release();pBUDrw=NULL;
        }
      }
      if (piDftDrawing) piDftDrawing->Release();piDftDrawing=NULL;
    }
  }

  return hr; 
}
// Print the Active Sheet of the Drawing Document 
HRESULT CAA2DLConvertToDrawServices::PrintDrawingDocument(CATDocument *ipDocDraw,
                                                          CATUnicodeString ipathOutputName,
                                                          CATUnicodeString iFmtPrt,
                                                          int iNumSheet)
{
  HRESULT hr = E_INVALIDARG;
  CATBatchLogCAA::PutInLog("  PrintDrawingDocument method starting");
  CATBatchLogCAA::PutInLog("\n");
  if (ipDocDraw)
  {
    CATIDftDocumentServices * piDftService = NULL;
    hr = ipDocDraw->QueryInterface(IID_CATIDftDocumentServices,(void**)&piDftService);
    if (SUCCEEDED(hr) && piDftService)
    {
      CATIDftDrawing* piDftDrawing = NULL;
      hr = piDftService->GetDrawing(IID_CATIDftDrawing,(void**)&piDftDrawing);
      if (SUCCEEDED(hr) && piDftDrawing)
      {
        CATIDftSheet *piDftSheet = NULL;
        CATBatchLogCAA::PutInLog("  Call RetrieveDrawingSheetFromNumber ");
        CATBatchLogCAA::PutInLog("\n");
        hr = CAA2DLConvertToDrawServices::RetrieveDrawingSheetFromNumber(piDftDrawing,iNumSheet,&piDftSheet);

        if (SUCCEEDED(hr) && piDftSheet)
        {
          CATIDftSheetFormat *piDftSheetFmt = NULL;
          piDftSheet->QueryInterface(IID_CATIDftSheetFormat,(void **)&piDftSheetFmt);
          if (piDftSheetFmt)
          {
            double WidthSheet,HeightSheet = 0.0;
            piDftSheetFmt->GetSheetSize(WidthSheet,HeightSheet);
            CATUnicodeString WidthSheetUC,HeightSheetUC;
            WidthSheetUC.BuildFromNum(WidthSheet);
            HeightSheetUC.BuildFromNum(HeightSheet);
            CATBatchLogCAA::PutInLog("  Sheet Size  WidthSheet = ");
            CATBatchLogCAA::PutInLog(WidthSheetUC);
            CATBatchLogCAA::PutInLog(" , HeightSheet = ");
            CATBatchLogCAA::PutInLog(HeightSheetUC);
            CATBatchLogCAA::PutInLog("\n");

            CATPrintParameters parameters;
            parameters.SetScale(1.f);
            parameters.SetMargins(0.f, 0.f, 0.f, 0.f);
            parameters.SetPosition(0.f, 0.f);
            parameters.GetCurrentForm().SetSize((float) WidthSheet, (float) HeightSheet);
            CATBatchLogCAA::PutInLog("  Call device.Print  method ");
            CATBatchLogCAA::PutInLog("\n");
            CATPrintFileDevice device(ipathOutputName,iFmtPrt);
            int rc = device.Print(piDftSheetFmt, parameters);
            CATUnicodeString rcUC;
            rcUC.BuildFromNum(rc);
            CATBatchLogCAA::PutInLog("  rc device.Print = ");
            CATBatchLogCAA::PutInLog(rcUC);
            CATBatchLogCAA::PutInLog("\n");
            if (1 == rc)
              hr = S_OK;
            else
              hr = E_FAIL;
            piDftSheetFmt->Release();piDftSheetFmt=NULL;
          }
          else
          {
            CATBatchLogCAA::PutInLog("  Sheet format missing on active Sheet");
            CATBatchLogCAA::PutInLog("\n");
          }
          piDftSheet->Release();piDftSheet=NULL;
        }
        else
        {
          CATBatchLogCAA::PutInLog("  Sheet not found ");
          CATBatchLogCAA::PutInLog("\n");
        }
        piDftDrawing->Release();piDftDrawing = NULL;
      }
      else
      {
        CATBatchLogCAA::PutInLog("  Drawing Root not found");
        CATBatchLogCAA::PutInLog("\n");
      }
      piDftService->Release();piDftService = NULL;
    }
  }
  else
  {
    CATBatchLogCAA::PutInLog("  No available Document");
    CATBatchLogCAA::PutInLog("\n");
  }
  if (SUCCEEDED(hr))
    CATBatchLogCAA::PutInLog("  End of PrintDrawingDocument method: OK");
  else
    CATBatchLogCAA::PutInLog("  End of PrintDrawingDocument method: KO");
  CATBatchLogCAA::PutInLog("\n");
  return hr; 
}


HRESULT CAA2DLConvertToDrawServices::GetAppropriateFormat(CATIDftDrawing *piDftDrawing,
                                                          double &iFmtWidth, 
                                                          double &iFmtHeight,
                                                          CATUnicodeString &fmtName)
{
  HRESULT hr = E_INVALIDARG;
  if (piDftDrawing)
  {
    CATIDftDrawingFormats *piDftFormats = NULL;
    if (SUCCEEDED(piDftDrawing->QueryInterface(IID_CATIDftDrawingFormats,(void **)&piDftFormats)))
    {
      CATLISTV(CATISpecObject_var) spListFormat;
      if (SUCCEEDED(piDftFormats->GetAvailableFormats(spListFormat)))
      {
        int nbformats = spListFormat.Size();
        double currentWidth,currentHeight;
        for (int numfmt = 1;numfmt <= nbformats; numfmt++)
        {
          CATIDftFormat_var spFormat = spListFormat[numfmt];
          spFormat->GetFormatWidth(currentWidth);
          spFormat->GetFormatHeight(currentHeight);
          if (CATFabs(currentWidth-iFmtWidth) < 0.1 && CATFabs(currentHeight-iFmtHeight) < 0.1)
          {
            hr = spFormat->GetFormatName(fmtName);
            break;
          }
        }
      }
      piDftFormats->Release();
      piDftFormats=NULL;
    }
  }
  return hr;
}
HRESULT CAA2DLConvertToDrawServices::RetrieveDrawingSheetFromNumber(CATIDftDrawing *piDftDrawing,int &iSheetNumber,
                                                                    CATIDftSheet **opiDftSheet)
{
  HRESULT hr = E_INVALIDARG;
  CATBatchLogCAA::PutInLog("    RetrieveDrawingSheetFromNumber method starting");
  CATBatchLogCAA::PutInLog("\n");
  CATUnicodeString NumsheetUC;
  NumsheetUC.BuildFromNum(iSheetNumber);
  CATBatchLogCAA::PutInLog("    Sheet number = ");
  CATBatchLogCAA::PutInLog(NumsheetUC);
  CATBatchLogCAA::PutInLog("\n");

  if (piDftDrawing)
  {
    CATIUnknownList * piSheetList = NULL;
    if (SUCCEEDED(piDftDrawing->GetSheets(&piSheetList)) && piSheetList)
    {
      unsigned int piListSize = 0;
      piSheetList->Count(&piListSize);
      IUnknown * item = NULL;

      // Loop on all the Sheets of the Drawing document.
      for(unsigned int numSheet=0 ; numSheet<piListSize ; numSheet++)
      {
        if (iSheetNumber == numSheet)
        {
          if( SUCCEEDED(piSheetList->Item(numSheet, &item)) && item)
          {
            hr = item->QueryInterface(IID_CATIDftSheet,(void **)opiDftSheet);
            item->Release(); item = NULL;
            break;
          }
        }
      }
      piSheetList->Release(); piSheetList = NULL;	    
    }
  }
  if (SUCCEEDED(hr))
    CATBatchLogCAA::PutInLog("    End of RetrieveDrawingSheetFromNumber method: OK ");
  else
    CATBatchLogCAA::PutInLog("    End of RetrieveDrawingSheetFromNumber method: KO ");

  CATBatchLogCAA::PutInLog("\n");
  return hr;
}

HRESULT CAA2DLConvertToDrawServices::GetTheNumber2DLayoutSheet(CATI2DLayoutSheet*pi2DLSheet,int &oNum2DLSheet)
{
  HRESULT hr = E_INVALIDARG;
  if (pi2DLSheet)
  {
    CATI2DLayoutLayout *pi2DLayoutRoot = NULL;
    if (SUCCEEDED(pi2DLSheet->GetLayout(&pi2DLayoutRoot)) && pi2DLayoutRoot)
    {
      CATBaseUnknown *piBU2DLSheet = NULL;
      if (SUCCEEDED(pi2DLSheet->QueryInterface(IID_CATBaseUnknown,(void **)&piBU2DLSheet)))
      {
        CATIUnknownList * pi2DLSheetList = NULL;
        if (SUCCEEDED(pi2DLayoutRoot->GetSheets(&pi2DLSheetList)) && pi2DLSheetList)
        {
          unsigned int piListSize = 0;
          pi2DLSheetList->Count(&piListSize);
          IUnknown * item = NULL;

          // Loop on all the Sheets of the 2D Layout.
          for(unsigned int numSheet=0 ; numSheet<piListSize ; numSheet++)
          {
            if( SUCCEEDED(pi2DLSheetList->Item(numSheet, &item)) && item)
            {
              CATBaseUnknown*piCurrentBU2DLSheet = NULL;
              if (SUCCEEDED(item->QueryInterface(IID_CATI2DLayoutSheet,(void **)&piCurrentBU2DLSheet)))
              {
                if (piBU2DLSheet->IsEqual( piCurrentBU2DLSheet))
                {
                  oNum2DLSheet = numSheet;
                  item->Release(); item = NULL;
                  piCurrentBU2DLSheet->Release();piCurrentBU2DLSheet=NULL;
                  hr = S_OK;
                  break;
                }
                piCurrentBU2DLSheet->Release();piCurrentBU2DLSheet=NULL;
              }
              item->Release(),item = NULL;
            }
          }
          pi2DLSheetList->Release(); pi2DLSheetList = NULL;	    
        }
        piBU2DLSheet->Release();piBU2DLSheet=NULL;
      }
      pi2DLayoutRoot->Release();pi2DLayoutRoot=NULL;
    }
  }
  return hr;
}
