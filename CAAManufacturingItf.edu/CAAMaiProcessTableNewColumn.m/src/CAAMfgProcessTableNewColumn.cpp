/**
 * @quickreview FBF 07:02:09
 * @quickreview PFE 05:02:16 // Blocage multimodif de certaines colonnes
 * @quickreview PFE 05:01:24
 * @quickreview OLC 04:11:22
 * @fullreview ECU XMN 04:10:22
 */
// COPYRIGHT Dassault Systemes 2004
//===================================================================
//
// CAAMfgProcessTableNewColumn.cpp
// Provide implementation to interface
//    CATIMfgTabularViewColumn
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//  Jul 2004  Creation
//===================================================================
#include "CAAMfgProcessTableNewColumn.h"

// KnowledgeInterfaces
#include "CATICkeParm.h"
#include "CATIEnumere.h"

#include "iostream.h"

#include "CATIMfgActivityParameters.h"

CATImplementBOA (CATIMfgTabularViewColumn, CAAMfgProcessTableNewColumn);
 
CATImplementClass( CAAMfgProcessTableNewColumn, Implementation, CATIMfgTabularViewColumn, CATNull );
 
//-----------------------------------------------------------------------------
// CAAMfgProcessTableNewColumn : constructor
//-----------------------------------------------------------------------------
CAAMfgProcessTableNewColumn::CAAMfgProcessTableNewColumn():
    CATIMfgTabularViewColumn()
{
}

//-----------------------------------------------------------------------------
// CAAMfgProcessTableNewColumn : destructor
//-----------------------------------------------------------------------------
CAAMfgProcessTableNewColumn::~CAAMfgProcessTableNewColumn()
{
}
 
//-----------------------------------------------------------------------------
// Implements CATIMfgTabularViewColumn::GetListColumnId
//-----------------------------------------------------------------------------
HRESULT CAAMfgProcessTableNewColumn::GetListColumnId (CATListOfCATString&  oListColumnId)
{
    oListColumnId.RemoveAll();
    
    oListColumnId.Append("FixtureAccuracyID");
    oListColumnId.Append("InfoID");
    
    return S_OK;
}

//-----------------------------------------------------------------------------
// Implements CATIMfgTabularViewColumn::GetListTitleColumn
//-----------------------------------------------------------------------------
HRESULT CAAMfgProcessTableNewColumn::GetListTitleColumn (CATListOfCATUnicodeString&  oListTitle)
{
    oListTitle.RemoveAll();
    
    oListTitle.Append("Fixture accuracy");
    oListTitle.Append("info");
    
    return S_OK;
}

//-----------------------------------------------------------------------------
// Implements CATIMfgTabularViewColumn::GetParamCke
//-----------------------------------------------------------------------------
HRESULT CAAMfgProcessTableNewColumn::GetParamCke (const CATBaseUnknown_var&  ispBUActivity , const CATString&  iColumnId , CATBaseUnknown_var&  ospBUCkeParm, int & MultiModif)
{
    HRESULT RC = E_FAIL;

    if (iColumnId == "FixtureAccuracyID")
    {
        CATIMfgActivityParameters_var spActParameters(ispBUActivity);
        if (NULL_var != spActParameters)
        {
            CATBaseUnknown_var spBUCkeParm;
            HRESULT hr = spActParameters->FindElement("MfgFixtureAccuracy", spBUCkeParm);
            if (NULL_var != spBUCkeParm)
            { 
                CATICkeParm_var spCkeParm(spBUCkeParm);
                if (NULL_var != spCkeParm)
                {
                    ospBUCkeParm = spCkeParm;
                    RC = S_OK;
                }
            }
        }
    }

    return RC;
}

//-----------------------------------------------------------------------------
// Implements CATIMfgTabularViewColumn::GetValue
//-----------------------------------------------------------------------------
HRESULT CAAMfgProcessTableNewColumn::GetValue (const CATBaseUnknown_var&  ispBUActivity , const CATString&  iColumnId , CATUnicodeString&  ostrValue)
{

    ostrValue = "-";

    if (iColumnId == "InfoID")
        ostrValue = "Info User";
    return S_OK;
}

//-----------------------------------------------------------------------------
// Implements CATIMfgTabularViewColumn::GetValue
//-----------------------------------------------------------------------------
HRESULT CAAMfgProcessTableNewColumn::ResetCache (const int  iCacheID)
{
    // no cache to manage here !
    return S_OK;
}
