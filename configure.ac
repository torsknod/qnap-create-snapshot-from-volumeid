#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AM_INIT_AUTOMAKE([-Wall -Werror gnu])
AC_CONFIG_SRCDIR([src/qnap-create-snapshot-from-volumeid.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB(uLinux_Storage, NAS_Snapshot_Create_By_Vol)

# Checks for header files.
AC_CHECK_HEADERS_ONCE([stdio.h argp.h errno.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS_ONCE([printf NAS_Snapshot_Create_By_Vol Snapshot_Create exit argp_parse strtoul strlen strdup])

AC_CONFIG_FILES([
 Makefile
 src/Makefile
])
AC_OUTPUT
