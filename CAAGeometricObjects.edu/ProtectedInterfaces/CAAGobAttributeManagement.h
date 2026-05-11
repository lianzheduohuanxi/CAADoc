#ifndef CAAGobAttributeManagement_H
#define CAAGobAttributeManagement_H
//
// COPYRIGHT DASSAULT SYSTEMES 2001
//
#include "CAAGobAttribute.h"              // For Windows - ExportedBy 
#include "CATCGMStreamAttribute.h"        // Base class declaration                          
                       
/**
 * Class defining the methods whereby the attribute is to be
 * manipulated. The CAAGobAttributeManagement attribute is
 * defined as a CATCGMStreamAttribute and therefore benefits from all the
 * methods defined in the CATCGMStreamAttribute default implementation.
 * The Stream and Unstream methods are redefined (it is mandatory). 
 * The Set/GetValue are added.
 */
class ExportedByCAAGobAttribute CAAGobAttributeManagement : public CATCGMStreamAttribute
{
  public :

/**
 * Mandatory macro for inheriting from CATCGMStreamAttribute .
 * @param CAAGobAttributeManagement
 * The name of the class which implements the attribute.
 * @param CATCGMStreamAttribute
 * The base class.
 */
  CATCGMDeclareAttribute (CAAGobAttributeManagement,CATCGMStreamAttribute);

  public :
  void Stream(CATCGMStream &) const;   // to stream the attribute
  void UnStream(CATCGMStream &);       // to unstream the attribute
  void SetValue(CATLONG32 val);             // to set its value
  void GetValue (CATLONG32 & val);          // to get its value
  private :
    CATLONG32 streamedvalue;
};

#endif
