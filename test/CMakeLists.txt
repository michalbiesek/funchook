cmake_minimum_required(VERSION 3.5)
project(libfunchook_test LANGUAGES C CXX ASM)

set(FUNCHOOK_CPU ${CMAKE_SYSTEM_PROCESSOR})

if (FUNCHOOK_CPU STREQUAL AMD64)
  set(FUNCHOOK_CPU "x86_64")
endif ()

if (FUNCHOOK_CPU STREQUAL x86_64)
  if (CMAKE_SIZEOF_VOID_P EQUAL "4")
    set(FUNCHOOK_CPU "x86")
  endif ()
endif ()

if (FUNCHOOK_CPU MATCHES "i.86")
  set(FUNCHOOK_CPU "x86")
endif ()

if (FUNCHOOK_CPU STREQUAL "arm64")
  set(FUNCHOOK_CPU "aarch64")
endif ()

if (FUNCHOOK_CPU STREQUAL "riscv")
  set(FUNCHOOK_CPU "riscv")
endif ()

set(TEST_EXE_SOURCES test_main.c test_prehook.c test_cpp.cpp)
if (FUNCHOOK_CPU STREQUAL x86)
  set(TEST_EXE_SOURCES ${TEST_EXE_SOURCES} ${FUNCHOOK_CPU}_test.S)
endif ()


if (NOT MSVC)
  set(FUNCHOOK_ASM_SUFFIX _gas.S)
elseif (FUNCHOOK_CPU MATCHES "^x86")
  enable_language(ASM_MASM)
  set(FUNCHOOK_ASM_SUFFIX _masm.asm)
else ()
  set(FUNCHOOK_CPU noasm)
  set(FUNCHOOK_ASM_SUFFIX .c)
endif ()

set(CMD "")
if (CMAKE_HOST_UNIX AND MINGW)
  find_program(WINE_EXECUTABLE NAMES wine)
  set(CMD ${WINE_EXECUTABLE})
endif ()
