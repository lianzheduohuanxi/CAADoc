#ifndef CAATopStiffener_h_
#define CAATopStiffener_h_

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "CAATopOperator.h"          // for windows nt

class CATGeoFactory;
class CATBody;
class CATTopData;


/**
 * Class for the CAA stiffener operator.
 * <br>The CAA operator follows the general scheme of the topological operators:
 *<ul><li>Creates 
 * <li>Tunes some parameters if needed
 * <li>Runs
 * <li>Reads the results
 * <li>Deletes ith the usual C++ delete operator.
 *</ul>
 */
class ExportedByCAAGMOperatorsOperatorCreation CAATopStiffener 
{
public:

   virtual ~CAATopStiffener();
  
/**
 * Constructs a CAATopStiffener operator.
 * @param iFactory
 * The pointer to the geometry factory.
 * @param iData
 * The pointer to the data defining the configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iFirstSurface
 * The pointer to the first limiting surface.
 * @param iSecondSurface
 * The pointer to the second limiting surface.
 * @param iSkinBody
 * The pointer to the body containing a shell: the profile to extrude.
 * @param iDirection
 * The direction of the stiffener.
 */
  CAATopStiffener (CATGeoFactory     * iFactory,
                   CATTopData        * iData,
                   CATBody           * iFirstSurface,
                   CATBody           * iSecondSurface,
                   CATBody           * iSkinProfile,
                   CATMathVector       iDirection);


/**
 * Runs the operator.
 * @return
 * The error code.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>0</tt></dt><dd>OK
 *     <dt><tt>1</tt></dt><dd>Null Pointer
 * </dl>
 */
  int Run();

 
/**
 * Returns the pointer to the resulting body.
 * @return
 * The pointer to the resulting body. If you do not want to keep it, 
 * use the @href CATICGMContainer#Remove method to remove it from the 
 * geometric factory.
 */
  CATBody * GetResult() ;


private :
	 
  CATGeoFactory     * _piGeomFactory;        // the factory
  CATBody           * _piFirstLimitBody;     // the first relimiting surface
  CATBody           * _piSecondLimitBody;    // the second relimiting surface
  CATBody           * _piSkinBody ;          // the profile (containing an open shell)
  CATMathVector       _direction;            // the stiffener direction
  CATTopData        * _pData;                // the journal and configuration
  CATBody           * _piResultingBody ;     // the resulting body
  
};


#endif
