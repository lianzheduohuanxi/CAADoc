# COPYRIGHT DASSAULT SYSTEMES 1999
#======================================================================

# SHARED LIBRARY 
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 

#if defined (CATIAR214)
LINK_WITH= JS0GROUP \
           CATObjectModelerNavigator \
           CATGeometricObjects \
           CATVisItf \
           CATMecModExtendItf \
           CATMecModLiveUseItf \
	       CATMecModUseItf \
           CATProviderItf \
           FeatureModelerExt \
           CATGSMUseItf \ 
           DataCommonProtocolUse \
#elif defined (CATIAV5R23)
LINK_WITH= JS0GROUP \
           CATObjectModelerNavigator \
           CATGeometricObjects \
           CATViz \
		   CATVisualization \
           CATMecModExtendItf \
           CATMecModLiveUseItf \
	       CATMecModUseItf \
           FeatureModelerExt \
           CATGSMUseItf \ 
		   CATObjectSpecsModeler  \
           CATMecModInterfaces \
		   CATInteractiveInterfaces \
#endif
