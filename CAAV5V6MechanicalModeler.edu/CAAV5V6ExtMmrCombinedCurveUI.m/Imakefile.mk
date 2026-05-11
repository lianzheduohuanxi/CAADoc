# COPYRIGHT DASSAULT SYSTEMES 2012
#
#======================================================================
# Imakefile for module CAAV5V6MmrExtMmrCombinedCurveUI.m
#======================================================================
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 

#if defined (CATIAR214)
LINK_WITH=CAAV5V6ExtMmrCombinedCurve \
          CATAfrFoundation \
          CATDialogEngine \
          CATObjectModelerBase \
          ObjectModelerSystem \
          DI0PANV2 \
          JS0FM \
          JS0GROUP \
          CATVisItf \
          CATMecModLiveUseItf \
          CATMecModUIUseItf \
	      CATMecModUseItf \
	      CATMecModUIExtendItf \
	      CATMecModExtendItf \
	      CATGSMUseItf \
	      FeatureModelerExt \ 
	      CATAfrItf \
#elif defined (CATIAV5R23)
LINK_WITH=CAAV5V6ExtMmrCombinedCurve \
          CATDialogEngine \
          CATObjectModelerBase \
          ObjectModelerSystem \
          DI0PANV2 \
          JS0FM \
          JS0GROUP \
          CATMecModLiveUseItf \
	      CATMecModUseItf \
	      CATMecModExtendItf \
	      CATGSMUseItf \
	      FeatureModelerExt \
		  CATApplicationFrame \ 
		  CATMecModInterfaces \
		  CATMechanicalModelerUI \
		  CATVisualization \
		  CATObjectSpecsModeler \
		  CATInteractiveInterfaces \
#endif	      
	      
          
         
