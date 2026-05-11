#ifndef CAAEV5V6ExtMmrMultiMeasureParmPublisher_H_ 
#define CAAEV5V6ExtMmrMultiMeasureParmPublisher_H_ 
//========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2012
//=================================================================================================
//
// CAAEV5V6ExtMmrMultiMeasureParmPublisher
// Provide implementation to interface
//    CATIParmParmPublisher for CAAV5V6ExtMmrMultiMeasure
//
//=================================================================================================

#include "CATParmPublisherAdapter.h" 

class CATListValCATBaseUnknown_var;
class CATIVisitor;
 
//-----------------------------------------------------------------------
class CAAEV5V6ExtMmrMultiMeasureParmPublisher : public CATParmPublisherAdapter
{
	CATDeclareClass;

	public:
		//---------------------------------------------------------------
		// constructeur et destructeur
		//---------------------------------------------------------------
		CAAEV5V6ExtMmrMultiMeasureParmPublisher();
		virtual ~CAAEV5V6ExtMmrMultiMeasureParmPublisher();

		//---------------------------------------------------------------
		// CATIParmPublisher
		//---------------------------------------------------------------

	  void VisitChildren( CATIVisitor*, const int recursively = 0 );

		//---------------------------------------------------------------
		// CATIParmDirectAccess
		//---------------------------------------------------------------
  
		HRESULT RetrieveDirectChildren (CATClassId iIntfName,CATListValCATBaseUnknown_var &iListToFill) const ;

	private:
	  
		void AddChildren(CATClassId intfName,CATListValCATBaseUnknown_var &lst);
  
		CAAEV5V6ExtMmrMultiMeasureParmPublisher (CAAEV5V6ExtMmrMultiMeasureParmPublisher &);
		CAAEV5V6ExtMmrMultiMeasureParmPublisher& operator=(CAAEV5V6ExtMmrMultiMeasureParmPublisher&);

};
#endif
