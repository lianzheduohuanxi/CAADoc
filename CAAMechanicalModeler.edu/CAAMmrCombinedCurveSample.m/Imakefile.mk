#
# COPYRIGHT DASSAULT SYSTEMES 2000
#
BUILT_OBJECT_TYPE= LOAD MODULE

LINK_WITH= CATLiteralFeatures  JS0GROUP \
           CATObjectModelerBase \
           CATObjectSpecsModeler \
           CATMechanicalModeler \
           CATMecModInterfaces \
           CATGeometricObjects \
           CATCGMGeoMath \
           CATConstraintModelerItf \
           CAAMmrCombinedCurve \
           KnowledgeItf \
           CATGitInterfaces $(LINK_WITH_DEBUG)


#ifdef CATIAV5R9
#if os SunOS

# By pass forte 6.1 

LINK_WITH_DEBUG= CATProductStructure1
#else
LINK_WITH_DEBUG=

#endif

#else
LINK_WITH_DEBUG=

#endif
