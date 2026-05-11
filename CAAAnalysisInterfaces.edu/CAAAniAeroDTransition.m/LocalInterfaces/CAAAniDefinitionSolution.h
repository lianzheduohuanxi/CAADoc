// COPYRIGHT DASSAULT SYSTEMES 2000
//===================================================================
//
// CAAAniDefinitionSolution.h
// Provide implementation to interface
//    CATISamDefineSolution
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
//===================================================================
#ifndef CAAAniDefinitionSolution_H
#define CAAAniDefinitionSolution_H

#include "CATISamDefineSolution.h"

//-----------------------------------------------------------------------
/**
 * Class Class extending the object "AeroDynamicSet".
 * <br>
 * It implements the interfaces :
 *  <ol>
 *  <li>@see CATAnalysisInterfaces.CATISamDefineSolution
 *  </ol>
 * Using this prefered syntax will enable mkdoc to document your class.
 */
class CAAAniDefinitionSolution: public CATISamDefineSolution
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     CAAAniDefinitionSolution ();
     virtual ~CAAAniDefinitionSolution ();

    /**
     * Implements a function from an interface.
     * @see CATAnalysisInterfaces.CATISamDefineSolution#GetSetsForDefinition
     */
     HRESULT GetSetsForDefinition (int & oNbDefineSets , CATSamDefineSet * & oDefineSets) ;

    /**
     * Implements a function from an interface.
     * @see CATAnalysisInterfaces.CATISamDefineSolution#DefineDefaultSensors
     */

     int DefineDefaultSensors(const CATBoolean iCreateSensor, const CATISamAnalysisSet* iNewSolution);

  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAAAniDefinitionSolution (CAAAniDefinitionSolution &);
  CAAAniDefinitionSolution& operator=(CAAAniDefinitionSolution&);

};

//-----------------------------------------------------------------------

#endif
