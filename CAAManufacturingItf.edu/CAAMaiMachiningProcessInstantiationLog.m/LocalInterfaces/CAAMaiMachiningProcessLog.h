/* -*-c++-*- */
#ifndef CAAMaiMachiningProcessLog_h
#define CAAMaiMachiningProcessLog_h
// ===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2004
// ===================================================================
//
// CAAMaiMachiningProcessLog: implementation of the 
// CATIMfgMachiningProcessLog CAA interface for the machining process
//
// ===================================================================

#include "CATIMfgMachiningProcessLog.h"

class CAAMaiMachiningProcessLog : public CATIMfgMachiningProcessLog
{
  CATDeclareClass;

  public:
 
    CAAMaiMachiningProcessLog();
    virtual ~CAAMaiMachiningProcessLog();

  /**
   * Activates or desactivates the generation of the traces.
   *   @param iActive
   *      The active flag
   *   <br><b>Legal values</b>:
   *   <ul>
   *   <li>=CATTrue  : to generate the traces </li>
   *   <li>=CATFalse : to stop the generation of the traces </li>
   *   </ul>
   */
  HRESULT Activate(CATBoolean iActive);

  /**
   * Tells if the traces are generated during instantiation or not.
   *   @param oActive
   *      The active flag
   *   <br><b>Legal values</b>:
   *   <ul>
   *   <li>=CATTrue  : traces are generated  </li>
   *   <li>=CATFalse : traces are not generated </li>
   *   </ul>
   */
  HRESULT IsActive(CATBoolean& oActive);

  /**
   * Traces the instantiation of a machining process.
   *   @param iContext
   *      The computation step of the machining process instantiation.
   *   <br><b>Legal values</b>:
   *   <ul>
   *   <li>=1 : Check evaluation </li>
   *   <li>=2 : Tooling Query execution </li>
   *   <li>=3 : Formula solving </li>
   *   <li>=otherwise : for future use </li>
   *   </ul>
   *   @param iTraces
   *      Information about Machining Process instantiation.
   *   </ul>
   */
  HRESULT Trace(int iContext, const CATListOfCATUnicodeString& iTraces);

  private:

    CAAMaiMachiningProcessLog(const CAAMaiMachiningProcessLog &);
    CAAMaiMachiningProcessLog&operator =(const CAAMaiMachiningProcessLog &);

    CATBoolean _Active;

};
#endif

