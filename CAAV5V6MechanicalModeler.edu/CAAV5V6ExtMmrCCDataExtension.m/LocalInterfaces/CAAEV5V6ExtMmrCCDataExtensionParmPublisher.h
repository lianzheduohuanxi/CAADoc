#ifndef CAAEV5V6ExtMmrCCDataExtensionParmPublisher_H_ 
#define CAAEV5V6ExtMmrCCDataExtensionParmPublisher_H_ 
//========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2010
//=================================================================================================
//
// CAAEV5V6ExtMmrCCDataExtensionParmPublisher 
// Provide implementation to interface
//    CATIParmPublisher for V5V6ExtMmrCCDataExtension
//
//=================================================================================================

#include "CATIAV5Level.h"

// KnowledgeInterfaces Framework
#include "CATParmPublisherAdapter.h" 

class CATListValCATBaseUnknown_var; 
class CATListValCATISpecObject_var; // V5 only
class CATIVisitor;
 
//-----------------------------------------------------------------------
class CAAEV5V6ExtMmrCCDataExtensionParmPublisher : public CATParmPublisherAdapter
{
	CATDeclareClass;

	public:
		//---------------------------------------------------------------
		// constructeur et destructeur
		//---------------------------------------------------------------
		CAAEV5V6ExtMmrCCDataExtensionParmPublisher();
		virtual ~CAAEV5V6ExtMmrCCDataExtensionParmPublisher();

		//---------------------------------------------------------------
		// CATIParmPublisher
		//---------------------------------------------------------------

	  void VisitChildren( CATIVisitor*, const int recursively = 0 );

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
		//---------------------------------------------------------------
		// CATIParmDirectAccess
		//---------------------------------------------------------------
  
		HRESULT RetrieveDirectChildren (CATClassId iIntfName,CATListValCATBaseUnknown_var &iListToFill) const ;
#else
//============================================== 
// V5 only
//==============================================

	  // Methode GetDirectChildren : To list all Direct Children
		void GetDirectChildren (CATClassId intfName,CATListValCATISpecObject_var &lst);


	  // Methode GetAllChildren : To list all Children
		void GetAllChildren (CATClassId intfName,CATListValCATISpecObject_var &lst);
#endif

	private:
	
#ifdef CATIAR214 
		void AddChildren(CATClassId intfName,CATListValCATBaseUnknown_var &lst); //V6 Only
#else 
		void AddChildren(CATClassId intfName,CATListValCATISpecObject_var& lst); //V5 only
#endif  
		CAAEV5V6ExtMmrCCDataExtensionParmPublisher (CAAEV5V6ExtMmrCCDataExtensionParmPublisher &);
		CAAEV5V6ExtMmrCCDataExtensionParmPublisher& operator=(CAAEV5V6ExtMmrCCDataExtensionParmPublisher&);

};
#endif
