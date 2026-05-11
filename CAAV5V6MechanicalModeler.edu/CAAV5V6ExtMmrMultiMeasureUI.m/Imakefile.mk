# COPYRIGHT DASSAULT SYSTEMES 2012
#======================================================================
# Imakefile for module CAAV5V6ExtMmrMultiMeasureUI.m
#======================================================================

BUILT_OBJECT_TYPE = SHARED LIBRARY
#
#if defined (CATIAR214)
LINK_WITH = JS0GROUP \
            JS0FM \
            CATAfrItf \
            CATAfrFoundation \ 
            CATProviderItf \
            CATVisItf \ 
            CATVisController \
            CATVisCommands \
            CATDialogEngine \
            CAAV5V6ExtMmrMultiMeasure \
            CATMecModUseItf \
            CATMecModLiveUseItf \
            CATMecModUIExtendItf \
            CATMecModUIUseItf \
            CATMecModExtendItf \
            FeatureModelerExt \ 
            CATObjectModelerNavigator \             
            ObjectModelerSystem \ 
#elif defined (CATIAV5R23)  
LINK_WITH = JS0GROUP \ 
            CATMechanicalModelerUI \ 
            CATMecModUseItf \
            CATMecModLiveUseItf \  
			CATMecModExtendItf \  
			FeatureModelerExt \ 
			CATObjectSpecsModeler \
			CAAV5V6ExtMmrMultiMeasure \ 
			CATDialogEngine \ 
			CD0FRAME \
			CATVisualization \
			CD0SHOW \
			JS0FM \
#endif           
