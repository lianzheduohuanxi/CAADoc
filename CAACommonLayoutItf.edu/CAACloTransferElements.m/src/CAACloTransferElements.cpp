// COPYRIGHT DASSAULT SYSTEMES 2015
//=============================================================================
//
// CAACloTransferElements
//
//  This sample illustrates how to use the CAA CommonLayout interface to transfer plant layout parts.
//
//
//  Prerequisite: 
//  -------------------
//  This sample uses the input drawing CAACloTransferElements.CATProduct.
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//  
//        CAACloTransferElements InstallationRootDirectory\CAACommonLayoutItf.edu\CNext\resources\graphic\CAACloTransferElements.CATProduct
//  
//  where InstallationRootDirectory is the pathname of the root directory where you copied and built the use case.
//
//=============================================================================
//
#include "CATDocumentServices.h"
#include "CATUnicodeString.h"
#include "CATDocument.h"
#include "CATBaseUnknown.h"
#include "CATIArrSegmentsString.h"
#include "CATIProduct.h"
#include "CATICloTransferElements.h"
#include "CATLISTV_CATBaseUnknown.h"
#include <iostream.h>

#include "CATICloTransferElements.h"
#include "CAACloTransferElements.h"
#include "IUnknown.h"
#include "CATErrors.h"


//-----------------------------------------------------------------------------
// CAACloTransferElements : constructor    
//-----------------------------------------------------------------------------
CAACloTransferElements::CAACloTransferElements():CAAPspBaseEnvProtected()
{
	cout<<"--> CAACloTransferElements::CAACloTransferElements"<<endl;

	cout<<"<-- CAACloTransferElements::CAACloTransferElements"<<endl;
}

//-----------------------------------------------------------------------------
// CAACloTransferElements : destructor
//-----------------------------------------------------------------------------
CAACloTransferElements::~CAACloTransferElements()
{
	cout<<"<-> CAACloTransferElements::~CAACloTransferElements"<<endl;
}


int CAACloTransferElements::DoSample(const CATUnicodeString &iuFileToBeLoaded)
{
	cout <<"============================================================"<< endl;
	cout <<"===       CAACloTransferElements::DoSample Start         ==="<< endl;
	cout <<"============================================================"<< endl;

	CATIProduct *piFromProduct = NULL;
	CATIProduct *piToProduct ;
	CATICloTransferElements *piTransferElements = NULL;
	CATListValCATBaseUnknown_var ListOfParts ;
	HRESULT rc = E_FAIL;

	CATTry 
	{
		//  Load input document
		CreateCATProductEnv(iuFileToBeLoaded);
		cout << "Product environment created." << endl;

		//  Initialize application
		ApplicationInit("CATSpatial");
		cout << "Application initialized." << endl;

		piFromProduct = (CATIProduct*)GetChildObject(IID_CATIProduct, "Product2.1");
		piToProduct = (CATIProduct*)GetChildObject(IID_CATIProduct, "Product3.1");

		CATBaseUnknown_var spTemp((CATBaseUnknown *)GetChildObject(IID_CATIArrSegmentsString, "Run-0006", piFromProduct));
		ListOfParts.Append(spTemp);

		CATBaseUnknown_var spTemp1((CATIProduct *)GetChildObject(IID_CATIProduct, "T-001", piFromProduct));
		ListOfParts.Append(spTemp1);

		CATIProduct_var hRun(spTemp);
		CATIProduct_var hTee(spTemp1);
		CATIProduct_var hRunFather = hRun->GetFatherProduct();
		CATIProduct_var hTeeFather = hTee->GetFatherProduct();
		CATUnicodeString  RunFatherInstName ;
		CATUnicodeString  TeeFatherInstName ;
		hRunFather->GetPrdInstanceName( RunFatherInstName );
		hTeeFather->GetPrdInstanceName( TeeFatherInstName );
		cout << "Run father before transfer:" << RunFatherInstName <<endl;
		cout << "Tube father before transfer:" << TeeFatherInstName <<endl;

		if (piToProduct && 
			SUCCEEDED(piToProduct->QueryInterface(IID_CATICloTransferElements,(void**)&piTransferElements)))
		{
			cout << "Transferring Run and Tube from Product2.1 to Product3.1" <<endl;
			rc = piTransferElements->TransferElements(ListOfParts);
			piTransferElements->Release();
			piTransferElements = NULL;
			if(SUCCEEDED(rc))
			{
				piToProduct = (CATIProduct*)GetChildObject(IID_CATIProduct, "Product3.1");
				spTemp=(CATBaseUnknown *)GetChildObject(IID_CATIArrSegmentsString, "Run-0006", piToProduct);
				spTemp1=(CATIProduct *)GetChildObject(IID_CATIProduct, "T-001", piToProduct);
				hRun = spTemp;
				hTee = spTemp1;
				hRunFather = hRun->GetFatherProduct();
				hTeeFather = hTee->GetFatherProduct();
				hRunFather->GetPrdInstanceName( RunFatherInstName );
				hTeeFather->GetPrdInstanceName( TeeFatherInstName );
				cout << "Run father after transfer:" << RunFatherInstName <<endl;
				cout << "Tube father after transfer:" << TeeFatherInstName <<endl;
			}
		}
	} // end CATTry

	CATCatch (CATError, pError)
	{
		cout << "CAACloTransferElements::DoSample *** Error Caught ***" << endl;
		cout << pError;

		rc = CATReturnError(pError);
	} // end CATCatch

	CATEndTry;

	cout << "CAACloTransferElements::DoSample rc = " << rc << endl;
	return rc;
}

