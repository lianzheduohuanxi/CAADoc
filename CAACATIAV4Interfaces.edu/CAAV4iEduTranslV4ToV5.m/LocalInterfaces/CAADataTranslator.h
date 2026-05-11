#ifndef CAADataTranslator_H
#define CAADataTranslator_H
#include "CATBaseUnknown.h"
#include "CATV4iV4Element.h"
class CAADataTranslator : public CATBaseUnknown
{
  CATDeclareClass;
  public : 
  CAADataTranslator();
  virtual ~CAADataTranslator();
  HRESULT GetUserIntent(CATV4iV4Element * V4Elem, int & oIntent);

};
#endif
