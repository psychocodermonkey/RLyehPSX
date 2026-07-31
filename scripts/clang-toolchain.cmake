# Use Fedora's system Clang for the application, matching the Linux dependency
# build. The platform's default linker remains in use.
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
