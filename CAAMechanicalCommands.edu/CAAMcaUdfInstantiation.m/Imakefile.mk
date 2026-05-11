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
            CATGeometricObjects \
            CATCGMGeoMath \
            CATConstraintModeler \
            CATConstraintModelerItf \
            CATMechanicalCommands \
            CATVisualization CATViz\
    	    CATInteractiveInterfaces \
    	    CAAMcaUtilities \
            KnowledgeItf CATLiteralFeatures 
