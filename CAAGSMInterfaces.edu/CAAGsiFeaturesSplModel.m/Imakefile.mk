#@ autoformat 06:09:14
# COPYRIGHT DASSAULT SYSTEMES 2000
#======================================================================
# Imakefile for module CAAGSMFeaturesSplModel
#======================================================================
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 

LINK_WITH_V5_ONLY=
LINK_WITH_V6_ONLY=
 
LINK_WITH= \
    $(LINK_WITH_V5_ONLY)           \
    $(LINK_WITH_V6_ONLY)           \
    CATAdvancedTopologicalOpe      \ # AdvancedTopologicalOpe         CATAdvancedTopologicalOpe
    CATGitInterfaces               \ # GSMInterfaces                  CATGitInterfaces
    CATCGMGeoMath                  \ # GeometricObjects               CATCGMGeoMath
    CATGeometricObjects            \ # GeometricObjects               CATGeometricObjects
    CATGeometricOperators          \ # GeometricOperators             CATGeometricOperators
    CATInteractiveInterfaces       \ # InteractiveInterfaces          CATInteractiveInterfaces
    KnowledgeItf                   \ # KnowledgeInterfaces            KnowledgeItf
    CATMathStream                  \ # Mathematics                    CATMathStream
    CATMathematics                 \ # Mathematics                    CATMathematics
    CATMecModInterfaces            \ # MecModInterfaces               CATMecModInterfaces
    CATMechanicalModeler           \ # MechanicalModeler              CATMechanicalModeler
    CATNewTopologicalObjects       \ # NewTopologicalObjects          CATTopologicalObjects
    CATObjectModelerBase           \ # ObjectModelerBase              CATObjectModelerBase
    CATObjectSpecsModeler          \ # ObjectSpecsModeler             CATObjectSpecsModeler
    JS0GROUP                       \ # System                         JS0GROUP
    CATTopologicalOperators        \ # TopologicalOperators           CATTopologicalOperators
    CATVisualization               \ # Visualization                  CATVisualization
    CATViz                         \ # VisualizationBase              CATViz
#

# Debug Journal 
#   CAATopDumpJournal \  

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
