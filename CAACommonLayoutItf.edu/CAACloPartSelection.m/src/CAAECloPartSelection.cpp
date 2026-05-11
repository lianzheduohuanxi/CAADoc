/**
 * @quickreview mhd 05:07:20 IsExternalProgramNeeded -- hardcoded
 * @quickreview mhd 05:07:15 RefinePartSelection --  hardcoded list added for testing
 * @quickreview eml 05:07:13 Conform to interface changes.
 */
/**
 * @fullreview eml sa00102 05:07:13
 */
#include <math.h>
#include <iostream.h>

#include "CAAECloPartSelection.h"
#include "CATECloPartSelectionAdapter.h"
#include "CATUnicodeString.h"
#include "CATICkeParm.h"
#include "CATICatalogDescription.h"
#include "IUnknown.h"
#include "CATIUnknownList.h"
#include "CATPspListServices.h"
 

CATImplementClass( CAAECloPartSelection,
                   DataExtension, 
                   CATBaseUnknown,
                   CATPiping );
 
// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATICloPartSelection.h"
TIE_CATICloPartSelection( CAAECloPartSelection); 

//-----------------------------------------------------------------------------
// CATEPipWeldRule : constructor    
//-----------------------------------------------------------------------------
CAAECloPartSelection::CAAECloPartSelection():CATECloPartSelectionAdapter()
{
}

//-----------------------------------------------------------------------------
// CATEPipWeldRule : destructor
//-----------------------------------------------------------------------------
CAAECloPartSelection::~CAAECloPartSelection()
{
}


HRESULT CAAECloPartSelection::FilterPartSelection ( const CATUnicodeString& iuStandard,
                                                    const CATUnicodeString& iuSpec,
                                                    const CATUnicodeString& iuPartType,
                                                    const CATIUnknownList *iLFilterParameters,
                                                    const CATIUnknownList *iLSortParameters,
                                                    const CATIUnknownList *iListDescription,
                                                    CATIUnknownList*& oListDescription ) 
{
  HRESULT RC = S_OK;
  int selected = 0;

  cout << "Standard=" << iuStandard.ConvertToChar() << endl;
  cout << "Spec=" << iuSpec.ConvertToChar() << endl;
  cout << "Part type=" << iuPartType.ConvertToChar() << endl;
  if ( oListDescription ) 
  {
    oListDescription->Release();
    oListDescription = NULL;
  }

  CATPspListServices::CreateCATIUnknownList(&oListDescription);
  if ( !oListDescription ) return E_FAIL;

  //dump out all the filtering parameters
  unsigned int nFilterParameters = 0;
  if ( iLFilterParameters )
  {
    ((CATIUnknownList*)iLFilterParameters)->Count(&nFilterParameters);
    cout << "list of filter parameters:" << endl;
    for ( unsigned int n = 0; n < nFilterParameters; n++ )
    {
      IUnknown* piUnknown = NULL;
      ((CATIUnknownList*)iLFilterParameters)->Item( n, &piUnknown );
      if ( piUnknown )
      {
        CATUnicodeString parmValue;
        CATICkeParm* piCkeParm = NULL;
        piUnknown->QueryInterface(IID_CATICkeParm,(void**)&piCkeParm);
        if ( piCkeParm )
        {
          cout << (piCkeParm->Name()).ConvertToChar() << "=" << (piCkeParm->Show()).ConvertToChar() << endl;
          piCkeParm->Release();   piCkeParm = NULL;
        }
        piUnknown->Release(); piUnknown = NULL;
      }
    }
  }

  //dump out all the parameters used for sorting the order of the descriptions
  unsigned int nSortParameters = 0;
  if ( iLSortParameters )
  {
    ((CATIUnknownList*)iLSortParameters)->Count(&nSortParameters);
    cout << "list of sort parameters:" << endl;
    for (unsigned int n = 0; n < nSortParameters; n++ )
    {
      IUnknown* piUnknown = NULL;
      ((CATIUnknownList*)iLSortParameters)->Item( n, &piUnknown );
      if ( piUnknown )
      {
        CATUnicodeString parmValue;
        CATICkeParm* piCkeParm = NULL;
        piUnknown->QueryInterface(IID_CATICkeParm,(void**)&piCkeParm);
        if ( piCkeParm )
        {
          cout << (piCkeParm->Name()).ConvertToChar() << "=" << (piCkeParm->Show()).ConvertToChar() << endl;
          piCkeParm->Release();   piCkeParm = NULL;
        }
        piUnknown->Release(); piUnknown = NULL;
      }
    }
  }

  //checking the description selected
  unsigned int nDescriptions = 0;
  if ( iListDescription )
  {
    ((CATIUnknownList*)iListDescription)->Count(&nDescriptions);

    cout << "list of descriptions:" << endl;
    for ( unsigned int n = 0; n < nDescriptions; n++ )
    {
      IUnknown* piUnknown = NULL;
      ((CATIUnknownList*)iListDescription)->Item( n, &piUnknown );
      if ( piUnknown )
      {
        CATUnicodeString parmValue;
        CATICatalogDescription* piDescription = NULL;
        piUnknown->QueryInterface(IID_CATICatalogDescription,(void**)&piDescription);
        if ( piDescription )
        {
          CATUnicodeString descName;
          piDescription->GetName(descName);
          cout << descName.ConvertToChar() << endl;

          if ( iuPartType == "PipingNonReduceElbow" )
          {
            //add code for filtering...use CenterToFace >= 3in only for example
            double oValue = 0.0;
          
            HRESULT rcode = piDescription->GetDouble ("CenterToFace", oValue); 
            if ( SUCCEEDED(rcode)  )
            {
              if ( oValue >= 0.076 ) oListDescription->Add(selected++, piUnknown);  
            }
            else
              //keyword "CenterToFace" not found, skip filtering
              oListDescription->Add(selected++, piUnknown);   
          }
          else
          {
            oListDescription->Add(selected++, piUnknown);
          }
          piDescription->Release(); piDescription=NULL;
        }
        piUnknown->Release(); piUnknown = NULL;
      }
    }
  }
  if ( selected > 0 ) RC = S_OK;
  else RC = E_FAIL;
  return RC;
}

HRESULT CAAECloPartSelection::IsExternalProgramNeeded  ( const CATUnicodeString &iuApplicationContext,
                                                         const CATUnicodeString &iuStandard,
                                                         const CATUnicodeString &iuSpec,
                                                         const CATUnicodeString &iuPartType,
                                                         int &oiActivate )
{
  HRESULT RC = S_OK;
  oiActivate = 0;

  cout << "Application=" << iuApplicationContext.ConvertToChar() << endl;
  cout << "Standard=" << iuStandard.ConvertToChar() << endl;
  cout << "Spec=" << iuSpec.ConvertToChar() << endl;
  cout << "Part type=" << iuPartType.ConvertToChar() << endl;

	if (iuSpec == "Non-Spec")
	{
		// Non-spec
		if (iuPartType == "PipingControlValve") oiActivate = 1;
	}
	else
	{
		// Spec
		if (iuPartType == "PipingGlobeValve") oiActivate = 1;
	}

  cout << "Activate=" << oiActivate << endl;
  return RC;
}

HRESULT CAAECloPartSelection::RefinePartSelection ( const CATUnicodeString &iuApplicationContext,
                                                    const CATUnicodeString &iuStandard,
                                                    const CATUnicodeString &iuSpec,
                                                    const CATUnicodeString &iuPartType,
                                                    const CATIUnknownList *iLEnvironmentParameters,
                                                    const CATIUnknownList *iLFilterParameters,
                                                    const CATIUnknownList *iLSortParameters,
                                                    const IUnknown *ipiCatalogObjectToBeSearched,
                                                    CATListValCATUnicodeString &opListPartNumbersFound ) 
{
  HRESULT RC = S_OK;
  int selected = 0;

  cout << "Application=" << iuApplicationContext.ConvertToChar() << endl;
  cout << "Standard=" << iuStandard.ConvertToChar() << endl;
  cout << "Spec=" << iuSpec.ConvertToChar() << endl;
  cout << "Part type=" << iuPartType.ConvertToChar() << endl;

  //dump out all the environment parameters
  unsigned int nEnvironmentParameters = 0;
  if ( iLEnvironmentParameters )
  {
    ((CATIUnknownList*)iLEnvironmentParameters)->Count(&nEnvironmentParameters);
    cout << "list of environment parameters:" << endl;
    for ( unsigned int n = 0; n < nEnvironmentParameters; n++ )
    {
      IUnknown* piUnknown = NULL;
      ((CATIUnknownList*)iLEnvironmentParameters)->Item( n, &piUnknown );
      if ( piUnknown )
      {
        CATUnicodeString parmValue;
        CATICkeParm* piCkeParm = NULL;
        piUnknown->QueryInterface(IID_CATICkeParm,(void**)&piCkeParm);
        if ( piCkeParm )
        {
          cout << (piCkeParm->Name()).ConvertToChar() << "=" << (piCkeParm->Show()).ConvertToChar() << endl;
          piCkeParm->Release();   piCkeParm = NULL;
        }
        piUnknown->Release(); piUnknown = NULL;
      }
    }
  }

  //dump out all the filtering parameters
  unsigned int nFilterParameters = 0;
  if ( iLFilterParameters )
  {
    ((CATIUnknownList*)iLFilterParameters)->Count(&nFilterParameters);
    cout << "list of filter parameters:" << endl;
    for ( unsigned int n = 0; n < nFilterParameters; n++ )
    {
      IUnknown* piUnknown = NULL;
      ((CATIUnknownList*)iLFilterParameters)->Item( n, &piUnknown );
      if ( piUnknown )
      {
        CATUnicodeString parmValue;
        CATICkeParm* piCkeParm = NULL;
        piUnknown->QueryInterface(IID_CATICkeParm,(void**)&piCkeParm);
        if ( piCkeParm )
        {
          cout << (piCkeParm->Name()).ConvertToChar() << "=" << (piCkeParm->Show()).ConvertToChar() << endl;
          piCkeParm->Release();   piCkeParm = NULL;
        }
        piUnknown->Release(); piUnknown = NULL;
      }
    }
  }

  //dump out all the parameters used for sorting the order of the descriptions
  unsigned int nSortParameters = 0;
  if ( iLSortParameters )
  {
    ((CATIUnknownList*)iLSortParameters)->Count(&nSortParameters);
    cout << "list of sort parameters:" << endl;
    for (unsigned int n = 0; n < nSortParameters; n++ )
    {
      IUnknown* piUnknown = NULL;
      ((CATIUnknownList*)iLSortParameters)->Item( n, &piUnknown );
      if ( piUnknown )
      {
        CATUnicodeString parmValue;
        CATICkeParm* piCkeParm = NULL;
        piUnknown->QueryInterface(IID_CATICkeParm,(void**)&piCkeParm);
        if ( piCkeParm )
        {
          cout << (piCkeParm->Name()).ConvertToChar() << "=" << (piCkeParm->Show()).ConvertToChar() << endl;
          piCkeParm->Release();   piCkeParm = NULL;
        }
        piUnknown->Release(); piUnknown = NULL;
      }
    }
  }


	// --- Just for testing / mhd / 2005-7-14
	selected = 1;
	if (iuSpec == "")
	{
		// --------- Non-spec test
		opListPartNumbersFound.Append ("V-GLOBE-FL-DM-RF-300-2in");
		opListPartNumbersFound.Append ("Non-spec-Makoto-10");
		opListPartNumbersFound.Append ("V-GLOBE-FL-DM-RF-150-2in");
		opListPartNumbersFound.Append ("Non-spec-Makoto-20");
		opListPartNumbersFound.Append ("Non-spec-Makoto-30");
		opListPartNumbersFound.Append ("Non-spec-Makoto-40");
	}
	else
	{
		// --------- Spec test
		opListPartNumbersFound.Append ("Spec-Makoto-10");
		opListPartNumbersFound.Append ("ASV0056_2in_RAISED FACE_V_GLBE_FL_HW-RF");
		opListPartNumbersFound.Append ("Spec-Makoto-20");
		opListPartNumbersFound.Append ("Spec-Makoto-30");
	}
	


  if ( selected > 0 ) RC = S_OK;
  else RC = E_FAIL;
  return RC;
}

