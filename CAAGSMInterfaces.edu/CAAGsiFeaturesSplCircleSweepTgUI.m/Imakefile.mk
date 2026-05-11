#@ autoformat 06:09:14
# COPYRIGHT DASSAULT SYSTEMES 2006
#======================================================================
# Imakefile for module CAAGsiFeaturesSplCircleSweepTgUI
#======================================================================
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 

LINK_WITH_V5_ONLY=
LINK_WITH_V6_ONLY=
 
LINK_WITH= \
    $(LINK_WITH_V5_ONLY)           \
    $(LINK_WITH_V6_ONLY)           \
    CATApplicationFrame            \ # ApplicationFrame               CATApplicationFrame
    CAAGsiFeaturesSplModel         \ # CAAGSMInterfaces.edu           CAAGsiFeaturesSplModel
    CAAGsiFeaturesSplUI            \ # CAAGSMInterfaces.edu           CAAGsiFeaturesSplUI
    CAAGsiServices                 \ # CAAGSMInterfaces.edu           CAAGsiServices
    DI0PANV2                       \ # Dialog                         DI0PANV2
    CATDialogEngine                \ # DialogEngine                   CATDialogEngine
    CATGitInterfaces               \ # GSMInterfaces                  CATGitInterfaces
    CATInteractiveInterfaces       \ # InteractiveInterfaces          CATInteractiveInterfaces
    CATMecModInterfaces            \ # MecModInterfaces               CATMecModInterfaces
    CATMechanicalModeler           \ # MechanicalModeler              CATMechanicalModeler
    CATMechanicalModelerUI         \ # MechanicalModelerUI            CATMechanicalModelerUI
    CATObjectModelerBase           \ # ObjectModelerBase              CATObjectModelerBase
    CATObjectSpecsModeler          \ # ObjectSpecsModeler             CATObjectSpecsModeler
    JS0FM                          \ # System                         JS0FM
    JS0GROUP                       \ # System                         JS0GROUP
    CATVisualization               \ # Visualization                  CATVisualization
    CATViz                         \ # VisualizationBase              CATViz
#

                    
           
           
                      
         
         
         

        


OS = COMMON
#if defined(R201)
LINK_WITH_V6_ONLY= \
#
#else
#if defined(CATIAV5R21)
LINK_WITH_V5_ONLY= \
#
#endif
#endif
