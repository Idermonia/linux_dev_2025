AC_PREREQ([2.69])
AC_INIT([Guessing a number with binary search], [1.0], [my_mail@gmail.ru], [guess])

AC_CONFIG_SRCDIR([src/guess.c])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([foreign subdir-objects])


AC_PROG_CC
AC_PROG_LIBTOOL
AC_PROG_INSTALL
AC_PROG_MKDIR_P


DX_INIT_DOXYGEN([guess])

LT_INIT([disable-static])

PKG_CHECK_MODULES([CHECK], [check >= 0.9.4])

AC_CONFIG_FILES([
    Makefile
    src/Makefile
    po/Makefile
    tests/Makefile
    Doxyfile
])

AC_OUTPUT
