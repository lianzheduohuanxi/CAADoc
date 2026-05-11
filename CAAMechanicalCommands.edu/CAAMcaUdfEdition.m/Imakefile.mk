# COPYRIGHT DASSAULT SYSTEMES 1999
#======================================================================

# SHARED LIBRARY 
#
BUILT_OBJECT_TYPE=LOAD MODULE 

LINK_WITH=  JS0GROUP JS0FM \
            CATObjectModelerBase \
            CATUdfInterfaces \
            CATObjectSpecsModeler  \
            CATMecModInterfaces \
            CATMechanicalModeler \
            CATConstraintModeler \
            CATConstraintModelerItf \
            CATCGMGeoMath \
            CATGeometricObjects \
            CATMechanicalCommands \
            CAAMcaUtilities \
            CATVisualization CATViz\ 
            CATInteractiveInterfaces \ 
            CATLiteralFeatures KnowledgeItf
