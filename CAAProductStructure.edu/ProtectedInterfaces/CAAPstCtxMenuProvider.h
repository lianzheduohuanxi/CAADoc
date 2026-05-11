// COPYRIGHT DASSAULT SYSTEMES 2004

#ifndef CAAPstCtxMenuProvider_H
#define CAAPstCtxMenuProvider_H

#include "CATBoolean.h"
#include "CATBaseUnknown.h"
#include "CAAPstEduCtxMenuProv.h"
class CATCmdContainer;

class ExportedByCAAPstEduCtxMenuProv CAAPstCtxMenuProvider : public CATBaseUnknown
{
	CATDeclareClass;

public:
	CAAPstCtxMenuProvider();
	virtual ~CAAPstCtxMenuProvider();

	HRESULT GetContextualMenu(CATBaseUnknown *, CATCmdContainer *);

private:

	CAAPstCtxMenuProvider(const CAAPstCtxMenuProvider&);
	CAAPstCtxMenuProvider& operator= (const CAAPstCtxMenuProvider&);
	void CreateCommand();

	CATBoolean _command_created;
};

#endif
