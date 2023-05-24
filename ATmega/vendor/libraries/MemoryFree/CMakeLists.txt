# Default module cmake file
# SOURCE_FILES: Handcoded C++ source files
# MOD_DEPS: Modules needed by this module

set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/MemoryFree.cpp"
)

register_fprime_module()
