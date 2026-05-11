// COPYRIGHT DASSAULT SYSTEMES 1994-2000
// Copyright © 1994-2000 Dassault Systèmes.
// All right reserved

BUILT_OBJECT_TYPE=LOAD MODULE

LINK_WITH_V5_ONLY=
#
LINK_WITH_V6_ONLY=
#

LINK_WITH = \
            $(LINK_WITH_V5_ONLY) \
            $(LINK_WITH_V6_ONLY) \
            JS0GROUP \
            CATMathematics \
            CATMathStream \
            CATObjectModelerBase \
            CATObjectSpecsModeler \
            CATGeometricObjects \
            CATCGMGeoMath \
            CATMecModInterfaces \
            CATMechanicalModeler \
            CATConstraintModelerItf \
            CATConstraintModeler \
            CATSketcherInterfaces \
            CATPartInterfaces \
			      KnowledgeItf \
#

#if defined(CATIAR201)
LINK_WITH_V6_ONLY = \
            CATPartUseItf \
            MecModLiveItf \
            CATGMModelInterfaces \
#
#else
#if defined(CATIAV5R21)
LINK_WITH_V5_ONLY = \
#
#endif
#endif
