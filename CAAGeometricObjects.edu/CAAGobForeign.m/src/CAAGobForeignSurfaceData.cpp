/**
* @quickReview CRE 03:10:17
*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
// The code corresponding to the foreign surface (egg box) attribute
//=============================================================================
#include "CAAGobForeignSurfaceData.h"                          


// Mathematics                         
#include "CATMath.h"                    // mathematical function
#include "CATMathConstant.h"            // CAT2PI constant
#include "CATMathPoint.h"               // 3D mathematical point
#include "CATMathVector.h"              // 3D mathematical vector
#include "CATMathVector2D.h"            // 2D mathematical vector
#include "CATMathTransformation.h"      // 3D affine tranformation
#include "CATMathTransformation2D.h"    // 2D affine transformation 

// CAAAdvancedMathematics
#include "CAAAmtForeignFctXY.h"         // the created foreign function class

//GeometricObjects
#include "CATSurLimits.h"               // the surface limits
#include "CATTransfoManager.h"          // the tranformation operator
#include "CATCGMStream.h"               // to stream and unstream the persistent attribute
#include "CATIForeignSurface.h"         // foreign surface


//
// The macro to take into account the derivation between your CAAGobForeignSurfaceData class
// and the CATForeignSurfaceData base class.
// CAAGobFS is the application name that you will find in the dictionary.
// This application name is declared in the CAAGobApplicationName.cpp file.
// 1 must not be changed. 
CATCGMImplAttribute(CAAGobForeignSurfaceData, CATForeignSurfaceData, CAAGobFS, 1);


//-------------------------------------------------------------------------------------------------
CAAGobForeignSurfaceData::CAAGobForeignSurfaceData() : CATForeignSurfaceData()
//-------------------------------------------------------------------------------------------------
{
}
//-------------------------------------------------------------------------------------------------
CAAGobForeignSurfaceData::CAAGobForeignSurfaceData( const CATMathPoint  & iOrigin,
                                                    const CATMathVector & iUDirection,
                                                    const CATMathVector & iVDirection,
                                                    const double          iHeight,
                                                    const double          iUMin,
                                                    const double          iUMax,
                                                    const double          iVMin,
                                                    const double          iVMax ) 
//-------------------------------------------------------------------------------------------------
{ // just valuates the data
  iOrigin.GetCoord(_Origin) ;
  iUDirection.GetCoord(_dU) ;
  iVDirection.GetCoord(_dV) ;
  _Height = iHeight ;
  _uMin   = iUMin ;
  _uMax   = iUMax ;
  _vMin   = iVMin ;
  _vMax   = iVMax ;
}
//-------------------------------------------------------------------------------------------------
void CAAGobForeignSurfaceData::Stream(CATCGMStream & iStr) const 
//-------------------------------------------------------------------------------------------------
{
  iStr.WriteDouble( _Origin, 3 ) ;   // streams the origin (array of 3 doubles)
  iStr.WriteDouble( _dU    , 3 ) ;   // streams the first vector (array of 3 doubles)
  iStr.WriteDouble( _dV    , 3 ) ;   // streams the second vector (array of 3 doubles)
  iStr.WriteDouble( _Height    ) ;   // streams the other values
  iStr.WriteDouble( _uMin      ) ;
  iStr.WriteDouble( _uMax      ) ;
  iStr.WriteDouble( _vMin      ) ;
  iStr.WriteDouble( _vMax      ) ;
}
//-------------------------------------------------------------------------------------------------
void CAAGobForeignSurfaceData::UnStream(CATCGMStream & iStr) 
//-------------------------------------------------------------------------------------------------
{
  iStr.ReadDouble( _Origin, 3 ) ;   // unstreams the origin (array of 3 doubles)
  iStr.ReadDouble( _dU    , 3 ) ;   // unstreams the first vector (array of 3 doubles)
  iStr.ReadDouble( _dV    , 3 ) ;   // unstreams the second vector (array of 3 doubles)
  iStr.ReadDouble( _Height   ) ;    // unstreams the other values
  iStr.ReadDouble( _uMin      ) ;
  iStr.ReadDouble( _uMax      ) ;
  iStr.ReadDouble( _vMin      ) ;
  iStr.ReadDouble( _vMax      ) ;
}
//-------------------------------------------------------------------------------------------------
CATForeignGeometryData* CAAGobForeignSurfaceData::Clone(CATCloneManager & iCloning) const 
//-------------------------------------------------------------------------------------------------
{ // only duplicates the attribute. 
  // The duplication of the CATIForeignSurface is made by the clone manager
  return new CAAGobForeignSurfaceData(CATMathPoint(_Origin), 
                                      CATMathVector(_dU),
                                      CATMathVector(_dV),
                                      _Height,
                                      _uMin,
                                      _uMax,
                                      _vMin,
                                      _vMax) ;
}
//-------------------------------------------------------------------------------------------------
void CAAGobForeignSurfaceData::Move3D(CATTransfoManager & iTransfo) 
//-------------------------------------------------------------------------------------------------
{ // manages the attribute values. 
  // The duplication of the CATIForeignSurface is made by the clone manager

  if ( FALSE == iTransfo.IsIdentity() )    // in case of a non-identity tranformation
  { 
      CATMathTransformation* pMathTransfo = NULL;
      iTransfo.GetMathTransformation( pMathTransfo ) ;

      if ( NULL != pMathTransfo )
      {
		     
        double determinant = pMathTransfo->GetMatrix().Determinant() ;
        if (  determinant > 0. )           // only direct tranformations
        {
                  
          CATMathVector Vector ;

          Vector.SetCoord(_dU) ;              // Gets the value before the transformation  
          Vector = (*pMathTransfo) * Vector ; // Uses the operator for the mathematical transformation
          Vector.GetCoord(_dU) ;              // Sets the value after the transformation  

          Vector.SetCoord(_dV) ;              // Gets the value before the transformation
          Vector = (*pMathTransfo) * Vector ;
          Vector.GetCoord(_dV) ;              // Sets the value after the transformation

          CATMathPoint Point ;

          Point.SetCoord(_Origin) ;           // Gets the value before the transformation
          Point = (*pMathTransfo) * Point ;
          Point.GetCoord(_Origin) ;           // Sets the value after the transformation

          _Height /= determinant ;            // Sets the height after the transformation
        }
      }
  }
}
//-------------------------------------------------------------------------------------------------
void CAAGobForeignSurfaceData::SetLimits(const CATSurLimits & iNewLimits)   
//-------------------------------------------------------------------------------------------------
{
  iNewLimits.GetExtremities(_uMin, _vMin, _uMax, _vMax) ;
}
//-------------------------------------------------------------------------------------------------
void CAAGobForeignSurfaceData::GetLimits(CATSurLimits & oLimits) const  
//-------------------------------------------------------------------------------------------------
{
  // the only authorized case of use of this method with this signature
  oLimits.SetExtremities(_uMin, _vMin, _uMax, _vMax, GetParamReference()) ;
}
//-------------------------------------------------------------------------------------------------
void CAAGobForeignSurfaceData::GetMaxLimits(CATSurLimits & oLimits) const 
//-------------------------------------------------------------------------------------------------
{
  CATPositiveLength infinite = GetInfinite() ;
  CATPositiveLength dUNorm = sqrt(_dU[0]*_dU[0]+_dU[1]*_dU[1]+_dU[2]*_dU[2]) ;
  CATPositiveLength dVNorm = sqrt(_dV[0]*_dV[0]+_dV[1]*_dV[1]+_dV[2]*_dV[2]) ;
  CATPositiveLength absUMax = 0.;
  CATPositiveLength absVMax = 0.;
  if ( dUNorm>0. && dVNorm>0. ) // if dUNorm==0. or dVNorm==0., the surface is degenerated
  { 
    absUMax = infinite / dUNorm ;
    absVMax = infinite / dVNorm ;
  }
  oLimits.SetExtremities(-absUMax, -absVMax, absUMax, absVMax, GetParamReference()) ;
}
//-------------------------------------------------------------------------------------------------
void CAAGobForeignSurfaceData::GetInternalMaxLimits(const CATLONG32 iPu, // useless in this case (only one patch)
                                                    const CATLONG32 iPv, // useless in this case (only one patch)
                                                    CATSurLimits & oLimits) const 
//-------------------------------------------------------------------------------------------------
{ 
  GetMaxLimits(oLimits) ; 
}
//-------------------------------------------------------------------------------------------------
CATBoolean CAAGobForeignSurfaceData::Extrapolate(const CATMathVector2D & iRequiredParamExtension, 
                                                CATMathVector2D * oActualExtension        )  
//-------------------------------------------------------------------------------------------------
{
  // Already maximum extension, cannot extrapolate
  if ( oActualExtension ) oActualExtension->SetCoord(0., 0.) ;
  return FALSE ;
}
//-------------------------------------------------------------------------------------------------
const CATKnotVector* CAAGobForeignSurfaceData::GetKnotVectorU() const
//-------------------------------------------------------------------------------------------------
{
  return NULL ; // Implicit KnotVector because canonic
}
//-------------------------------------------------------------------------------------------------
const CATKnotVector* CAAGobForeignSurfaceData::GetKnotVectorV() const
//-------------------------------------------------------------------------------------------------
{
  return NULL ; // Implicit KnotVector because canonic
}
//-------------------------------------------------------------------------------------------------
void CAAGobForeignSurfaceData::CreateLocalEquation(const CATLONG32 iPu,  // useless, only one patch 
                                                   const CATLONG32 iPv,  // useless, only one patch
                                                   const CATMathFunctionXY* & oFx, 
                                                   const CATMathFunctionXY* & oFy, 
                                                   const CATMathFunctionXY* & oFz)  
//-------------------------------------------------------------------------------------------------
{ // Creates the mathematical equations relative to the egg box
  // S(u,v) = Origin + u*dU + v*dV + Height*cos(u)*cos(v)*dU^dV.
  oFx = new CAAAmtForeignFctXY(_dU[0],_dV[0],_Height*(_dU[1]*_dV[2]-_dU[2]*_dV[1]),_Origin[0]) ;
  oFy = new CAAAmtForeignFctXY(_dU[1],_dV[1],_Height*(_dU[2]*_dV[0]-_dU[0]*_dV[2]),_Origin[1]) ;
  oFz = new CAAAmtForeignFctXY(_dU[2],_dV[2],_Height*(_dU[0]*_dV[1]-_dU[1]*_dV[0]),_Origin[2]) ;
}
//-------------------------------------------------------------------------------------------------
CATBoolean CAAGobForeignSurfaceData::IsConfused( const CATMathTransformation  & iTransfo,
			                                     const CATSurface*              iTSurface,
			                                     CATMathTransformation2D* oTransfo2D) const 
//-------------------------------------------------------------------------------------------------
{
  // TSurface must be a CATIForeignSurface
  if (NULL == iTSurface) return FALSE;
  if ( FALSE == (iTSurface->IsATypeOf(CATIForeignSurfaceType) ) ) return FALSE ;
  CATForeignSurfaceData* pTForeignSurfaceData = ((CATIForeignSurface*)iTSurface)->GetData() ;
  if (NULL==pTForeignSurfaceData) return FALSE;

  // TSurface Data must have the CAAGobForeignSurfaceData type
  if ( FALSE == (pTForeignSurfaceData->IsATypeOf( GetCGMAttrId()) ) ) return FALSE ;

  // Gets the data of the eggs box, to test its invariance by iTransfo
  CAAGobForeignSurfaceData* pTSample = (CAAGobForeignSurfaceData*)pTForeignSurfaceData ;
  if (NULL == pTSample) return FALSE;

  // Geometry of iTransfo (this )  and iTSurface must be identical
  CATMathVector u(_dU), v(_dV); 
  u = iTransfo * u ;
  v = iTransfo * v ;   
  
  CATMathVector tu(pTSample->_dU), tv(pTSample->_dV) ;
  CATMathVector w(u^v),       tw(tu^tv) ;

  // First geometric test: iTransfo(_dU,_dV) and (tu,tv) defines the same plane
  if ( FALSE == w.IsParallel(tw) ) return FALSE ;

  // second geometric test: iTransfo(_heigth) and 
  double determinant = iTransfo.GetMatrix().Determinant() ;
  if (  determinant == 0. ) return FALSE ;
  double tHeight = _Height / determinant ;

  // Compares the heights
  double eps = 1.e-12;
  if ( (tHeight*w - pTSample->_Height*tw).Norm() > eps*fabs(_Height)*w.Norm() ) return FALSE ;

  // Compares u & v ,  computes Transformation2D
  double aT[6] = { 0., 0., 0., 0., 0., 0.} ;

  if (u.IsParallel(tu) ) 
    {
      if ( fabs ( u.Norm() - tu.Norm() ) < eps*u.Norm() ) 
        {
          aT[0] = CATSign(u*tu) ;
          if ( v.IsParallel( tv ) )
            {
              if ( fabs ( v.Norm() - tv.Norm() ) < eps*v.Norm() ) 
                {
                  aT[3] = CATSign(v*tv) ;
                }
              else return FALSE ;
            }
          else return FALSE ;
        }
      else return FALSE ;
    }
  else if (u.IsParallel(tv) ) 
    {
      if ( fabs ( u.Norm() - tv.Norm() ) < eps*u.Norm() ) 
        {
          aT[2] = CATSign(u*tv) ;
          if ( v.IsParallel( tu ) )
            {
              if ( fabs ( v.Norm() - tu.Norm() ) < eps*v.Norm() ) 
                {
                  aT[1] = CATSign(v*tu) ;
                }
              else return FALSE ;
            }
          else return FALSE ;
        }
      else return FALSE ;
    }

  // Compares the Origins
  CATMathPoint point(_Origin), tpoint(pTSample->_Origin) ;
  point = iTransfo * point ;
  CATMathVector deltaPoint = tpoint - point ;
  if ( fabs(deltaPoint*w) > w.Norm()*eps ) return FALSE ;
  aT[4] = deltaPoint * tu / ( tu.SquareNorm() * CAT2PI ) ;
  if ( fabs ( aT[4] - int ( aT[4] ) ) > eps ) return FALSE ;
  aT[5] = deltaPoint * tv / ( tv.SquareNorm() * CAT2PI ) ;
  if ( fabs ( aT[5] - int ( aT[5] ) ) > eps ) return FALSE ;

  if ( oTransfo2D ) oTransfo2D->SetCoef(aT) ;
  return TRUE ;
}
//-------------------------------------------------------------------------------------------------
CATBoolean CAAGobForeignSurfaceData::IsPeriodicU() const 
//-------------------------------------------------------------------------------------------------
{
  return FALSE ; // because it is not periodic
}
//-------------------------------------------------------------------------------------------------
CATBoolean CAAGobForeignSurfaceData::IsPeriodicV() const 
//-------------------------------------------------------------------------------------------------
{
  return FALSE ; // because it is not periodic
}
//-------------------------------------------------------------------------------------------------
  
