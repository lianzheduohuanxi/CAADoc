// COPYRIGHT DASSAULT SYSTEMES 2000
//===================================================================
//
// CAAAniCfgTemplate.h
// Provide implementation to interface
//
#ifndef CAAAniCfgTemplate_H
#define CAAAniCfgTemplate_H

#include "CATBaseUnknown.h"
#include "CATListOfCATString.h"

//-----------------------------------------------------------------------

/**
 * Class Class extending the object "CAAAniCfg_TempList".
 * <br>
 * It implements the interface:
 *  <ol>
 *  <li>@see CATAnalysisInterfaces.CATISamWorkbenchTemplate
 *  </ol>
 */
class CAAAniCfgTemplate: public CATBaseUnknown
{
	CATDeclareClass;

	public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
		CAAAniCfgTemplate();
		virtual ~CAAAniCfgTemplate();

    /**
     * Implements a function from an interface.
     * @see CATISamWorkbenchTemplate.GetTemplates
     */
    HRESULT GetTemplates(CATListOfCATString& oList);

	private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
		CAAAniCfgTemplate (CAAAniCfgTemplate &);
		CAAAniCfgTemplate& operator=(CAAAniCfgTemplate&);
};

//-----------------------------------------------------------------------

#endif
