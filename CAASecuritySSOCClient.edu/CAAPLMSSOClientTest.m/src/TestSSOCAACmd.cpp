/**
 * @fullreview SMQ		05:11:08
 * @quickReview SMQ     05:11:08 R17 
 * @quickReview SMQ     06:12:26 R17
 */

#include "TestSSOCAACmd.h"
#include "CATDlgNotify.h"
#include "CATCreateExternalObject.h"
#include "CATApplicationFrame.h"
#include "CATUnicodeString.h"
#include "CATMsgCatalog.h"

#include "PLMSSOClient.h"
#include "PLMSSOCredential.h"
#include "PLMSSOCredentialSet.h"

CATCreateClass(TestSSOCAACmd);

//-------------------------------------------------------------------------
TestSSOCAACmd::TestSSOCAACmd ():CATStateCommand ("TestSSOCAACmd")
{
	//Loading Msg Catalog for this Command
	m_msgCat =  new CATMsgCatalog();
	if (m_msgCat != NULL)
		m_msgCat->LoadMsgCatalog("TestSSOCAACmd");
}

//-------------------------------------------------------------------------
TestSSOCAACmd::~TestSSOCAACmd()
{
	if (m_msgCat != NULL)
	{
		delete m_msgCat;
		m_msgCat=NULL;
	}

}

//-------------------------------------------------------------------------
void TestSSOCAACmd::BuildGraph()
{
	CATUnicodeString texte; //text to be display in the Pop-up
	HRESULT hr = E_FAIL;

	//create the SSO Client Object
	PLMSSOClient sso;

	CATBoolean activated = FALSE;

	// Test if the SSO Has been activated in the RuntimeView
	hr = sso.IsSSOActivated(activated);

	// if it fails display the error message and exits
	if (FAILED(hr)) 
	{
		texte = HandleError(hr);
		DisplayMessage(texte,TRUE);
		return;
	}

	//IF SSO is not activated no need to go further
	if (!activated)
	{
		if (m_msgCat)
			texte=(m_msgCat->GetCatalogMsg ("NotActivated")).BuildMessage();
		DisplayMessage(texte,TRUE);
		return;
	}

	//prepare the display of the SSO Activated message
	if (m_msgCat)
		texte = texte +(m_msgCat->GetCatalogMsg ("Activated")).BuildMessage()+"\n";
	
	CATBoolean authenticated=FALSE;

	//Test if the End User is Authenticated on the SSO Server
	hr = sso.IsAlreadyAuthenticated(authenticated);

	//if an error occurs display the error Message and exit 
	if (FAILED(hr))
	{
		texte = HandleError(hr);
		DisplayMessage(texte,TRUE);
		return;
	}

	//if the user is not authenticated Display the message and exit
	if (!authenticated)
	{
		if (m_msgCat)
			texte = texte +(m_msgCat->GetCatalogMsg ("NotAuhtenticated")).BuildMessage()+"\n";
		DisplayMessage(texte,TRUE);
		return;
	}

	//prepare the display of the SSO Activated message
	if (m_msgCat)
		texte = texte +(m_msgCat->GetCatalogMsg ("Auhtenticated")).BuildMessage()+"\n";

	//Try to retrieve the Authenticated User
	CATUnicodeString user;
	hr = sso.GetAuthenticatedUsername(user);

	//If fails display the error and exit
	if (FAILED(hr))
	{
		CATUnicodeString temp;
		if (m_msgCat)
			temp=(m_msgCat->GetCatalogMsg ("ErrorSSOUser")).BuildMessage();
		texte =texte + temp+"\n"+HandleError(hr);
		DisplayMessage(texte,TRUE);
		return;
	}

	//prepare the display of the retrieved SSO User
	if (m_msgCat)
		texte = texte +(m_msgCat->GetCatalogMsg ("SSOUser")).BuildMessage()+user+"\n";


	//Retrieving Credentials for the authenticated user
	PLMSSOCredentialSet credentialSet;
	hr = sso.GetCredentialSetForApplication("MySystem","",credentialSet);

	//if an error occurs display the error Message and exit 
	if (FAILED(hr))
	{
		CATUnicodeString tmp;
		if (m_msgCat)
			tmp = (m_msgCat->GetCatalogMsg ("GetCredentialError")).BuildMessage()+"\n";

		texte = tmp+HandleError(hr);
		DisplayMessage(texte,TRUE);
		return;
	}

	//Prepare the dispaly of the credentials well retrieve status
	if (m_msgCat)
		texte = texte +(m_msgCat->GetCatalogMsg ("CredentialsOK")).BuildMessage()+"\n";

	//Do a loop to retrieve and Display all credentials
	int size = credentialSet.Size();
	for (int k=1;k<=size;k++)
	{
		CATUnicodeString credentialValue;
		CATUnicodeString credentialName;

		hr = credentialSet[k].GetCredentialValue(credentialValue);

		// if fails while retrieving credential value
		if (FAILED(hr))
		{
			texte =texte + HandleError(hr)+"\n";
			DisplayMessage(texte,TRUE);
			return;
		}

		//retrieve the name of the credential
		hr = credentialSet[k].GetCredentialName(credentialName);

		//if it fails while retrieving credential value
		if (FAILED(hr))
		{
			texte =texte + HandleError(hr)+"\n";
			DisplayMessage(texte,TRUE);
			return;
		}

		//prepare the Display of the credential name : value
		texte = texte +credentialName+" : "+credentialValue + "\n";
	}
	//display the info Message
	DisplayMessage(texte,FALSE);
}

void TestSSOCAACmd::DisplayMessage(CATUnicodeString& iMsg,int iIsError)
{
	CATApplicationFrame* applicationFrame=CATApplicationFrame::GetFrame();

	//exits if no applicationFrame found
	if (applicationFrame == NULL) return;

	CATDlgStyle style =CATDlgNfyOK|CATDlgWndModal;	
	CATUnicodeString title;

	if (iIsError)
	{
		//retrieve the NLS title of the Display Error Box
		if (m_msgCat != NULL)
			title=(m_msgCat->GetCatalogMsg ("TitleError")).BuildMessage();
		//Set the style of the pop-up to an Error Box
		style = style |CATDlgNfyError;
	}
	else
	{
		//retrieve the NLS title of the Display Info Box
		if (m_msgCat != NULL)
			title=(m_msgCat->GetCatalogMsg ("TitleInfo")).BuildMessage();
	}

	//create the message Box
	CATDlgNotify *notif =  new CATDlgNotify(applicationFrame->GetApplicationDocument(),"Notif",style );
	//disp.lay the Message
	notif->DisplayBlocked(iMsg,title);
	//ask for destruction of the box
	notif->RequestDelayedDestruction();

}

//----------------------------------------------------------------------------
CATUnicodeString TestSSOCAACmd::HandleError(HRESULT iStatus)
{

	CATUnicodeString message="";
	//Retrieving the Last Error
	CATError * pOccurringError = CATError::CATGetLastError(iStatus);
	if (pOccurringError != 0) 
	{
		//retrieve the NLS Message of the CATError
		message = pOccurringError->GetNLSMessage();
		//free the memory of the CATError
		pOccurringError->Release();
		pOccurringError = NULL;
	}
	return message;
}
