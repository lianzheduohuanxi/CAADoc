// COPYRIGHT Dassault Systemes 2000
//===================================================================
//
// CAAAniADCharacCollector.h
// Provide implementation to interface CATICharacCollector
//
//===================================================================
#ifndef CAAAniADCharacCollector_H
#define CAAAniADCharacCollector_H

#include "CATECharacCollector.h"
#include "CATAnalysisExplicitModel.h"
#include "CATAnalysisExplicitTypes.h"
#include "CATAnalysisCharacCollector.h"
#include "CATSamCharacVersion.h"
#include "CATAnalysisExplicitSet.h"
#include "CATSamDimension.h"
//----------------------------------------------------------------------
/**
 * Class Class extending the object "AeroDynamicsSet".
 * <br>
 * It implements the interfaces :
 *  <ol>
 *  <li>@see CATAnalysisBase.CATICharacCollector
 *  </ol>
 */
class CAAAniADCharacCollector: public CATECharacCollector
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     CAAAniADCharacCollector ();
     virtual ~CAAAniADCharacCollector ();

    /**
     * Implements a function from an interface.
     * @see CATAnalysisBase.CATICharacCollector#GetAvailablePhysicalTypes
     */
     HRESULT GetAvailablePhysicalTypes (int &  oNumber , 
		 const CATSamPhysicalType* &  oPhysicalTypes , 
		 const CATString* &  oUnits) ;

    /**
     * Implements a function from an interface.
     * @see CATAnalysisBase.CATICharacCollector#GetAvailableVersions
     */
     HRESULT GetAvailableVersions (const CATSamPhysicalType  iPhysicalType , 
		 int &  oNumber , 
		 const CATSamCharacVersion* &  oVersions) ;

    /**
     * Implements a function from an interface.
     * @see CATAnalysisBase.CATICharacCollector#GetAvailablePositions
     */
     HRESULT GetAvailablePositions (const CATSamPhysicalType  iPhysicalType , const CATSamCharacVersion &  iVersion , int &  oNumber , const CATString* &  oPositions) ;

    /**
     * Implements a function from an interface.
     * @see CATAnalysisBase.CATICharacCollector#GetNumberOfOccurrences
     */
     HRESULT GetNumberOfOccurrences (int &  oNumberOfOccurrences) ;

    /**
     * Implements a function from an interface.
     * @see CATAnalysisBase.CATICharacCollector#GetCurrentOccurrence
     */
     HRESULT GetCurrentOccurrence (int &  oOccurrenceNumber) ;

    /**
     * Implements a function from an interface.
     * @see CATAnalysisBase.CATICharacCollector#SetCurrentOccurrence
     */
     HRESULT SetCurrentOccurrence (const int  iOccurrenceNumber) ;

    /**
     * Implements a function from an interface.
     * @see CATAnalysisBase.CATICharacCollector#GetCharacCollector
     */
     HRESULT GetCharacCollector (const CATSamPhysicalType  iPhysicalType , 
                                 const CATSamCharacVersion &  iVersion , 
                                 const CATString &  iPosition , 
                                 const char*  const iEntityFlags  , 
                                 const CATAnalysisCharacCollector* &  oCharacCollector , 
                                 const CATBoolean  iCollectValues = TRUE,
                                 const CATSamPhysicalType iEntiyPhysicalTypeToCollect = CATSamPhysicalTypeNone) ;

    /**
     * Implements a function from an interface.
     * @see CATAnalysisBase.CATICharacCollector#Update
     */
     HRESULT Update (CATBoolean iFullUpdate = TRUE) ;

  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAAAniADCharacCollector (CAAAniADCharacCollector &);
  CAAAniADCharacCollector& operator=(CAAAniADCharacCollector&);

  HRESULT Init();
  void ReadFile(char* iName,int iNb	,float *iFvalues);

  CATAnalysisExplicitModel * _Model ;
  CATAnalysisExplicitSet    _Context ;
  CATSamPhysicalType       * _PhysicalTypes ;
  CATString                * _Units, *_Positions ;
  CATSamCharacVersion      * _VersionsT ;
  CATSamCharacVersion      * _VersionsG ;
  int                       _NumberOfOccurences, _CurrentOccurence ;
  int                       _NbPhysicalType;
  int                       _NbVersionsT;
  int                       _NbVersionsG;
  int                       _NbPositions;
};
//-----------------------------------------------------------------------

#endif
