#ifndef CAAEMmrCCDataExtensionParmPublisher_H_ 
#define CAAEMmrCCDataExtensionParmPublisher_H_ 
//========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2007
//=================================================================================================
//
// CAAEMmrCCDataExtensionParmPublisher .cpp
// Provide implementation to interface
//    CATIParmPublisher for MmrCCDataExtension
//
//=================================================================================================

#include "CATParmPublisherAdapter.h" 

class CATListValCATISpecObject_var;
class CATIVisitor;
 
//-----------------------------------------------------------------------
class CAAEMmrCCDataExtensionParmPublisher : public CATParmPublisherAdapter
{
	CATDeclareClass;

	public:
		//---------------------------------------------------------------
		// constructeur et destructeur
		//---------------------------------------------------------------
		CAAEMmrCCDataExtensionParmPublisher();
		virtual ~CAAEMmrCCDataExtensionParmPublisher();

		// Methode GetDirectChildren : To list all Direct Children
		void GetDirectChildren (CATClassId intfName,CATListValCATISpecObject_var &lst);

		// Methode GetAllChildren : To list all Children
		void GetAllChildren (CATClassId intfName,CATListValCATISpecObject_var &lst);

	  void VisitChildren( CATIVisitor*, const int recursively = 0 );
  
	private:
	  
		void AddChildren(CATClassId intfName,CATListValCATISpecObject_var& lst);
  
		CAAEMmrCCDataExtensionParmPublisher (CAAEMmrCCDataExtensionParmPublisher &);
		CAAEMmrCCDataExtensionParmPublisher& operator=(CAAEMmrCCDataExtensionParmPublisher&);

};
#endif
