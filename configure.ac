#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([cb], [0.0.1])
AC_CONFIG_SRCDIR([main.cpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign])
AC_SUBST([AM_CXXFLAGS], ["-Wall -Werror"])

# Checks for programs.
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_17([noext], [mandatory])

# Checks for libraries.
PKG_CHECK_MODULES([SDL2], [sdl2 >= 2.0])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
