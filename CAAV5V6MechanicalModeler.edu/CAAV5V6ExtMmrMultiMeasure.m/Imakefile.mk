# COPYRIGHT DASSAULT SYSTEMES 2012
#======================================================================
# Imakefile for module CAAV5V6ExtMmrMultiMeasure.m
#======================================================================
#
BUILT_OBJECT_TYPE=SHARED LIBRARY
#
#if defined (CATIAR214)
LINK_WITH = JS0GROUP \
            CATMecModLiveUseItf \
            CATMecModUseItf \
            CATMecModExtendItf \
            FeatureModelerExt \
            CATGraphicProperties \
            CATVisItf \
            CATVisFoundation \
            CATVisController \
            CATObjectModelerNavigator \
            CATGMOperatorsInterfaces \
            CATGMModelInterfaces \
            CATMathematics \
            CATMathStream \
            KnowledgeItf \
            CATObjectModelerBase \
            CATProviderItf \
            DataCommonProtocolUse \
            ObjectModelerSystem \
            
#elif defined (CATIAV5R23)
LINK_WITH = JS0GROUP \
            CATMecModLiveUseItf \
            CATMecModUseItf \
            CATMecModExtendItf \
            FeatureModelerExt \
			CATVisualization \
			CATMechanicalModeler \
			KnowledgeItf \ 
			CATGMOperatorsInterfaces \
            CATGMModelInterfaces \
			CATMathematics \
			ObjectModelerSystem \
			SpecsModeler \
			CATObjectModelerNavigator \
			CATObjectModelerBase \
			CATGraphicProperties\
#endif            

