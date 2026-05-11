# COPYRIGHT DASSAULT SYSTEMES 2012
#======================================================================
# Imakefile for module CAAV5V6ExtMmrCCDataExtension.m
#======================================================================
#  Jan 2007  Creation:
#======================================================================
#
#ifdef LOCAL_DEFINITION_FOR_IID
#
#else
#
#endif
BUILT_OBJECT_TYPE = SHARED LIBRARY
#
#if defined (CATIAR214)
LINK_WITH= JS0GROUP \
           ObjectModelerSystem \
           CATObjectModelerBase \
           CATObjectModelerNavigator \ 
           CAT3DPhysicalRepItf \
           CATPLMComponentInterfaces \
           CATGeometricObjects \
           CATMathematics \
           CATMathStream \
           CATGMModelInterfaces \
	       CATGMOperatorsInterfaces \
           DataCommonProtocolExt \
           VisCore \
           CATVisFoundation \
           CATVisController \
           CATVisItf \
           KnowledgeItf \
           CATMecModUseItf \
           CATMecModExtendItf \
	       CATMecModLiveUseItf \
	       CATProviderItf \
	       FeatureModelerExt \
           DataCommonProtocolUse \
#elif defined (CATIAV5R23)
LINK_WITH= JS0GROUP \
           ObjectModelerSystem \
           CATObjectModelerBase \
           CATObjectModelerNavigator \ 
           CATGeometricObjects \
           CATMathematics \
           CATMathStream \
           CATGMModelInterfaces \
	       CATGMOperatorsInterfaces \
           CATInteractiveInterfaces \
           KnowledgeItf \
           CATMecModUseItf \
           CATMecModExtendItf \
	       CATMecModLiveUseItf \
	       FeatureModelerExt \
           DataCommonProtocolUse \
		   CATVisualization \
		   CATObjectSpecsModeler \
#endif           
           
#
LOCAL_CCFLAGS= -DSPECDEBUG
#
OS = AIX
#
OS = HP-UX
#
OS = IRIX


#
OS = SunOS
#
OS = Windows_NT


#INSERTION ZONE NOT FOUND, MOVE AND APPEND THIS VARIABLE IN YOUR LINK STATEMENT
#LINK_WITH = ... $(WIZARD_LINK_MODULES) ...
# DO NOT EDIT :: THE CAA2 WIZARDS WILL ADD CODE HERE
WIZARD_LINK_MODULES =  \
JS0GROUP JS0FM JS0GROUP CATMmrApplicativeFeaturesUUID 
# END WIZARD EDITION ZONE
