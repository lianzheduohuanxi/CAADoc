#ifndef CATPLMSSOCAAToolbar_h
	#define CATPLMSSOCAAToolbar_h

	#include "CATBaseUnknown.h"
	class CATCmdContainer;

	class CATPLMSSOCAAToolbar : public CATBaseUnknown
	{
		CATDeclareClass;

		public:
			CATPLMSSOCAAToolbar();
			~CATPLMSSOCAAToolbar();

			void CreateCommands();
			CATCmdContainer * CreateToolbars();

	};
#endif
