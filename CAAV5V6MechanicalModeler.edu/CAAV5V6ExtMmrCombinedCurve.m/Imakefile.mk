# COPYRIGHT DASSAULT SYSTEMES 2012
#======================================================================
# Imakefile for module CAAV5V6ExtMmrCombinedCurve.m
#======================================================================
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
#if defined (CATIAR214)
LINK_WITH=JS0GROUP \
          CATGeometricObjects \
          CATMathematics \
          CATMathStream \ 
          CATGMModelInterfaces \
	      CATGMOperatorsInterfaces \
	      CATObjectModelerNavigator \
          KnowledgeItf \
          CATMecModLiveUseItf \
	      CATMecModUseItf \
	      CATMecModExtendItf \
          CATMecModUIExtendItf \
	      FeatureModelerExt \
	      CATVisItf \
#elif defined (CATIAV5R23)
LINK_WITH=JS0GROUP \
          CATGeometricObjects \
          CATMathematics \
          CATMathStream \ 
          CATGMModelInterfaces \
	      CATGMOperatorsInterfaces \
	      CATObjectModelerNavigator \
          KnowledgeItf \
          CATMecModLiveUseItf \
	      CATMecModUseItf \
	      CATMecModExtendItf \
	      FeatureModelerExt \
	      CATVisualization \
		  CATInteractiveInterfaces \
		  CATMecModInterfaces \
		  CATObjectSpecsModeler \
#endif
