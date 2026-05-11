#@ autoformat 06:09:14
# COPYRIGHT DASSAULT SYSTEMES 1999
# 
# LOAD MODULE CAAGsiNozzle 
# 
BUILT_OBJECT_TYPE=LOAD MODULE

LINK_WITH_V5_ONLY=
LINK_WITH_V6_ONLY=
#
LINK_WITH= \
    $(LINK_WITH_V5_ONLY)           \
    $(LINK_WITH_V6_ONLY)           \
    CAAGsiToolkit                  \ # CAAGSMInterfaces.edu           CAAGsiToolkit
    CATObjectSpecsModeler          \ # ObjectSpecsModeler             CATObjectSpecsModeler
    JS0GROUP                       \ # System                         JS0GROUP
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
