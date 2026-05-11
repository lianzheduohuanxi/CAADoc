# COPYRIGHT DASSAULT SYSTEMES 2007
#======================================================================
# Imakefile for module CAAMmrCCDataExtensionUI.m
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
LINK_WITH = JS0GROUP \
            JS0FM \ 
            ObjectModelerSystem \  
            CAAV5V6ExtMmrCCDataExtension \
            CATMecModUIExtendItf \
            CATDialogEngine \
            CATVisItf \
            CATObjectModelerNavigator \  
#elif defined (CATIAV5R23)
LINK_WITH = JS0GROUP \
            JS0FM \ 
            CAAV5V6ExtMmrCCDataExtension \
            CATDialogEngine \
			CATViz \
			CATObjectSpecsModeler \
            CATMechanicalModelerUI \
            ON0MAIN 
            
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

