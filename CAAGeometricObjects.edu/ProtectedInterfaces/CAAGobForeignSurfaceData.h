#ifndef CAAGobForeignSurfaceData_H
#define CAAGobForeignSurfaceData_H
//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
#include "CAAGobForeign.h"                // For Windows - ExportedBy 
#include "CATForeignSurfaceData.h"        // Base class declaration                          

                       
/**
 * Class for the definition of the data for the foreign surface CAA sample (the eggs box).
 * A foreign surface is introduced into CGM by filling the CATIForeignSurface object data
 * with a CATForeignSurfaceData. Then, it is automatically integrated into CGM, and
 * can be used as any CATSurface by the operators and the topology.
 * <br>To create the CAA sample surface , the CATForeignSurfaceData
 * class is derived into CAAGobForeignSurfaceData, 
 * and the mandatory methods that are associated with are overloaded.
 * @see CATIForeignSurface, CATSurface
 */
class ExportedByCAAGobForeign CAAGobForeignSurfaceData : public CATForeignSurfaceData
{
  public :

/**
 * Mandatory macro for inheriting from CATCGMAttribute .
 * @param CAAGobForeignSurfaceData
 * The name of you new class.
 * @param CATForeignSurfaceData
 * The base class.
 */
  CATCGMDeclareAttribute (CAAGobForeignSurfaceData,CATForeignSurfaceData);


/**
 * Constructs the surface data.
 * <br> The geometric surface is defined as follows:
 * <pre>
 * S(u,v) = iOrigin + u*iUDirection + v*iVDirection + iHeight*cos(u)*cos(v)*iUDirection^iVDirection, 
 * uMin<=u<=uMax, vMin<=v<=vMax. </pre>
 */
  CAAGobForeignSurfaceData(const CATMathPoint  & iOrigin,
                           const CATMathVector & iUDirection,
                           const CATMathVector & iVDirection,
                           const double          iHeight,
                           const double          iUMin,
                           const double          iUMax,
                           const double          iVMin,
                           const double          iVMax       ) ;
 //----------------------------------------------------------------------------------------------
 // Mandatory methods for CATCGMAttribute
 //----------------------------------------------------------------------------------------------
/**
 * Default constructor.
 */
  CAAGobForeignSurfaceData();

/**
 * Streams the data.
 */
  void   Stream(CATCGMStream & iStr) const ;

/**
 * Unstreams the data.
 */
  void UnStream(CATCGMStream & iStr) ;

 //----------------------------------------------------------------------------------------------
 // Mandatory methods for CATForeignGeometryData
 //----------------------------------------------------------------------------------------------
/**
 * Clones <tt>this</tt> CAAAForeignSurfaceSample.
 */
  CATForeignGeometryData* Clone(CATCloneManager & iCloning) const ;

/**
 * Moves <tt>this</tt> CAAAForeignSurfaceSample.
 */
  void Move3D(CATTransfoManager & iTransfo) ;
             
 //----------------------------------------------------------------------------------------------
 //  Mandatory methods for CATForeignSurfaceData
 //----------------------------------------------------------------------------------------------
/**
 * Defines the current limits.
 * @param iNewLimits
 * The new current limitations.
 */
  void SetLimits(const CATSurLimits & iNewLimits) ;
  
/**
 * Returns the current limits on <tt>this</tt> CAAAForeignSurfaceSample.
 * @param ioLimits
 * The limitations of <tt>this</tt> CATSurface.
 */
  void GetLimits(CATSurLimits & ioLimits) const  ;

/**
 * Returns the maximum limitations.
 *<br>This does not take into account the current limitations .
 * @param ioLimits
 * The maximum limitations of <tt>this</tt> CATSurface.
 */
  void GetMaxLimits(CATSurLimits & ioLimits) const ;

/**
 * Returns the maximum limitations of an internal patch.
 *<br>This does not take into account the current limitations . These maximum
 * limits can be the creation limits or the limits that are obtained by 
 * extrapolation, depending on the types of geometric objects.
 * @param iPatchU
 * The patch number in the first direction.
 * @param iPatchV
 * The patch number in the second direction.
 * @param ioLimits
 * The limitations of a patch.
 */
  void GetInternalMaxLimits(const CATLONG32 iPatchU, const CATLONG32 iPatchV, CATSurLimits & ioLimits) const ;
  
/**
 * Changes the maximum limitations.
 * @param iRequiredParamExtension
 * The value of extension.
 *<ul>
 * <li>if iRequiredParamExtension.GetX()>0, Umax is expected to increase by this value.
 * <li>if iRequiredParamExtension.GetY()<0, Vmin is expected to decrease,
 * <li>if null, no change is required in the related direction.
 * </ul>
 * @param ioActualExtension
 * If NULL, no information on actual extrapolation is required.
 */
	CATBoolean Extrapolate(const CATMathVector2D & iRequiredParamExtension, 
		                   CATMathVector2D * ioActualExtension = NULL  )  ;

/**
 * Returns a pointer to the first nodal vector.
 * <br>This is used when the surface has several patches. If it always
 * has only one patch, you must return a null pointer.
 * @return
 * The pointer to the knot vector.
 */
	const CATKnotVector* GetKnotVectorU() const;

/**
 * Returns a pointer to the second nodal vector.
 * <br>This is used when the surface has several patches. If it always
 * has only one patch, you must return a null pointer.
 * @return
 * The pointer to the knot vector.
 */
  const CATKnotVector* GetKnotVectorV() const;

/**
 * Retrieves the mathematical equation associated with a patch.
 * <br>(oFx(U,V), oFy(U,V), oFz(U,V)) is then a point of the surface patch.
 * The method creates the equations, that must not be deleted as part of the object.
 * @param iPatchU
 * The patch number in the first direction.
 * @param iPatchVm
 * The patch number in the second direction.
 * @param oFx
 * A pointer to the parametric equation of the first coordinate. 
 * @param oFy
 * A pointer to the parametric equation of the second coordinate. 
 * @param oFz
 * A pointer to the parametric equation of the third coordinate. 
 */
  void CreateLocalEquation(const CATLONG32 iPatchU, const CATLONG32 iPatchV, 
                           const CATMathFunctionXY* & oFx, 
                           const CATMathFunctionXY* & oFy, 
                           const CATMathFunctionXY* & oFz) ; 
  
/**
 * Tests whether the transformation of <tt>this</tt> CAA foreign surface is coiencident with another curve.
 *<br>This method does not take into account the current limitations of 
 * the curves.
 * @param iTransfo
 * The tested transformation.
 * @param iTSurface
 * The other surface.
 * @param ioTransfo2D
 * The 2D-transformation defining the change of parametrization between the transformation of 
 * <tt>this</tt> and <tt>iTSurface</tt>.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl> <dt><tt>1</tt> <dd>If the transformation of <tt>this</tt> is geometrically the same as <tt>iTSurface</tt>.
 *     <dt><tt>0</tt> <dd>Otherwise.</dl>
 */	
	CATBoolean IsConfused(const CATMathTransformation   & iTransfo,
                          const CATSurface              * iTSurface,
                          CATMathTransformation2D * ioTransfo2D = NULL) const ;

/**
 * Tests whether <tt>this</tt> CAA foreign surface is periodic along the first direction.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl><dt> 0 <dd> if it is not periodic along the U direction
 *    <dt> 1 <dd> if it is periodic along the U direction</dl>
 */
  CATBoolean IsPeriodicU() const ;

/**
 * Tests whether <tt>this</tt> CAA foreign surface is periodic along the second direction.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl><dt> 0 <dd> if it is not periodic along the V direction
 *    <dt> 1 <dd> if it is periodic along the V direction</dl>
 */
  CATBoolean IsPeriodicV() const ;
  
  private :
  
  // Data
  // S(u,v) = Origin + u*dU + v*dV + Height*cos(u)*cos(v)*dU^dV, uMin<=u<=uMax, vMin<=v<=vMax.
  double _uMin      ;
  double _uMax      ;
  double _vMin      ;
  double _vMax      ;
  double _Origin[3] ;
  double _Height    ;
  double _dU[3]     ;
  double _dV[3]     ;
};

#endif
