####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
#
####
set(SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/ATmegaInternalAdcDriverComponentAi.xml"
    "${CMAKE_CURRENT_LIST_DIR}/ATmegaInternalAdcDriverComponentImpl.cpp"
)

register_fprime_module()


