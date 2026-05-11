#@ autoformat 06:09:14
# COPYRIGHT DASSAULT SYSTEMES 1999
#======================================================================
# Shared Library  CAAGsiServices
#======================================================================
#
# 
BUILT_OBJECT_TYPE=SHARED LIBRARY

LINK_WITH_V5_ONLY=
LINK_WITH_V6_ONLY=
#
LINK_WITH= \
    $(LINK_WITH_V5_ONLY)           \
    $(LINK_WITH_V6_ONLY)           \
    CATApplicationFrame            \ # ApplicationFrame               CATApplicationFrame
    CATGitInterfaces               \ # GSMInterfaces                  CATGitInterfaces
    CATGeometricObjects            \ # GeometricObjects               CATGeometricObjects
    KnowledgeItf                   \ # KnowledgeInterfaces            KnowledgeItf
    CATMecModInterfaces            \ # MecModInterfaces               CATMecModInterfaces
    CATMechanicalModeler           \ # MechanicalModeler              CATMechanicalModeler
    CATNewTopologicalObjects       \ # NewTopologicalObjects          CATTopologicalObjects
    CATObjectModelerBase           \ # ObjectModelerBase              CATObjectModelerBase
    CATObjectSpecsModeler          \ # ObjectSpecsModeler             CATObjectSpecsModeler
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
