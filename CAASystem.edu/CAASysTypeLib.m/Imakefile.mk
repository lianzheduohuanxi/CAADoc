BUILT_OBJECT_TYPE = TYPELIB
#
# Must be built after InfTypeLib which has a priority of 0
#
# no more BUILD_PRIORITY=10

LINK_WITH = InfTypeLib
