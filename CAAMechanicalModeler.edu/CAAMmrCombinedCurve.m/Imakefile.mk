# COPYRIGHT DASSAULT SYSTEMES 2000
#======================================================================
# Imakefile for module CAAMmrCombinedCurve.m
#======================================================================
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
LINK_WITH=CATGeometricObjects          \
          CATCGMGeoMath                   \
          CATMathematics  CATMathStream             \
          CATMecModInterfaces          \
          CATMechanicalModeler         \
          CATConstraintModelerItf         \
          CATNewTopologicalObjects     \
          CATObjectModelerBase         \
          CATObjectSpecsModeler        \
          CATTopologicalOperators      \
          CATInteractiveInterfaces      \
          CATVisualization      \
          JS0GROUP KnowledgeItf
