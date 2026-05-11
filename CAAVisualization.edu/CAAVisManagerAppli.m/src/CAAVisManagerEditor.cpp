// COPYRIGHT DASSAULT SYSTEMES 2000
#include "CAAVisManagerEditor.h" 

// Visualization Framework
#include "CATPSO.h" 
#include "CATHSO.h" 

// LocalFramework
#include "CAAVisManagerCmdSelector.h"
#include "CAAVisManagerDocument.h"

//-------------------------------------------------------------------------------

CAAVisManagerEditor::CAAVisManagerEditor(CAAVisManagerDocument * iDocument):
                     _pHSO(NULL),
                     _pPSO(NULL),
                     _pDocument(NULL),
                     _pSelector(NULL)
{
   if ( NULL != iDocument )
   {
      _pDocument = iDocument ;

      _pPSO = new CATPSO();
      _pHSO = new CATHSO();

      _pSelector = new CAAVisManagerCmdSelector(*_pHSO,*_pPSO);
   }   
}

//-------------------------------------------------------------------------------

CAAVisManagerEditor::~CAAVisManagerEditor()
{
   if ( NULL != _pDocument )
   {
      _pDocument = NULL ;

      _pPSO ->Empty() ;
      _pPSO ->Release() ;
      _pPSO = NULL ;

      _pHSO ->Empty() ;
      _pHSO ->Release() ;
      _pHSO = NULL ;

      _pSelector ->RequestDelayedDestruction() ;
      _pSelector = NULL ;
      
   }

}

//-------------------------------------------------------------------------------
CATPSO * CAAVisManagerEditor::GetPSO()
{
   return _pPSO ;
}

//-------------------------------------------------------------------------------
CATHSO * CAAVisManagerEditor::GetHSO()
{
   return _pHSO ;
}

//-------------------------------------------------------------------------------
CAAVisManagerCmdSelector * CAAVisManagerEditor::GetSelector()
{
   return _pSelector ;
}


//------------------------------------------------------------------------------
CAAVisManagerDocument * CAAVisManagerEditor::GetDocument()
{
   return _pDocument ;
}
