# COPYRIGHT DASSAULT SYSTEMES 1999
#======================================================================

# SHARED LIBRARY 
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 

LINK_WITH=  JS0GROUP \
            CATObjectModelerBase \
            CATObjectSpecsModeler  \
            CATMecModInterfaces \
            CATMechanicalModeler \
            CATCGMGeoMath CATGeometricObjects \
            CATConstraintModelerItf \
            CATGitInterfaces \
            CATVisualization CATViz \
            CATInteractiveInterfaces
