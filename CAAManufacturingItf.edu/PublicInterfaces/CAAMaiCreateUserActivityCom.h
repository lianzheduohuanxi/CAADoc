// COPYRIGHT DASSAULT SYSTEMES 2002
/* -*-c++-*- */
#ifndef CAAMaiCreateUserActivityCom_H
#define CAAMaiCreateUserActivityCom_H
//
//=============================================================================
//
// Class CAAMaiCreateUserActivityCom:
// Manufacturing Generic Activity Commands
//
//=============================================================================
// Usage Notes:
//

#include "CATStateCommand.h"
#include "CAAMaiEnv.h"

class CATPathElementAgent;
class CATDialogState;

class ExportedByCAAMaiEnv CAAMaiCreateUserActivityCom : public CATStateCommand
{
   public:
   
      DeclareResource (CAAMaiCreateUserActivityCom,CATStateCommand)
    
      CAAMaiCreateUserActivityCom (CATString* argument);
      virtual ~CAAMaiCreateUserActivityCom();
      void BuildGraph();

   private:

	   // Create the activity and make sequencing
      boolean ManageChildActivityAndSequence (void *);

	  // Find the program on which you want to create the activity
	  CATBaseUnknown_var FindActivityFather(CATUnicodeString &iTypeToCreate, CATBaseUnknown_var& iActivity);

	  // to Initialize the activity O(i.e. Tool)
      void SetLinksAndDataOnActivity(CATBaseUnknown_var& iActivity);
      HRESULT   InitTool (const CATBaseUnknown_var& iActivity);
      HRESULT	SetCompatibleToolingFromDocument (const CATListOfCATUnicodeString &iToolTypeList,
		                                        CATBaseUnknown_var& oTool);



      CATBaseUnknown_var       _CreatedActivity;    
      CATIContainer_var        _RootContainer;
      CATIContainer_var        _ResourceContainer;
      CATPathElementAgent*     _ActAcq;
      CATUnicodeString         _TypeToCreate;
      CATDialogState*          _InitState;
};
#endif
