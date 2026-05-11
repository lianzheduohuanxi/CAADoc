// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAADlgElement.h"

// Standard C++ library
#include <string.h>

// -------------------------------------------------------

CAADlgElement::CAADlgElement(char *iName)
{
  // Keep the name of the model
  if ( NULL != iName )
  {
     _pElementName = new char [strlen(iName)+1];
     strcpy(_pElementName,iName);
  }else
  {
      _pElementName = new char [15];
      strcpy(_pElementName,"DefaultElement");
  }
  printf("The %s element is created.\n", _pElementName );
}

// -------------------------------------------------------

CAADlgElement::~CAADlgElement() 
{
  printf("The %s element is deleted.\n", _pElementName );

  if ( NULL != _pElementName )
  {
     delete [] _pElementName ;
     _pElementName = NULL ;
  }
}


// -------------------------------------------------------
char * CAADlgElement::GetElementName() 
{
  return(_pElementName);
}


