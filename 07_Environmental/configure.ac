AC_PREREQ([2.69])
AC_INIT([rhasher], [1.0])
AC_CONFIG_SRCDIR([rhasher.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([foreign subdir-objects])

m4_pattern_allow([AC_MSG_ERROR])
m4_pattern_allow([AC_MSG_NOTICE])

AC_PROG_CC
# AC_PROG_INSTALL

AC_CHECK_LIB([rhash], [rhash_init],[], [AC_MSG_ERROR([Rhash is required])])

AC_ARG_WITH([readline],
    [AS_HELP_STRING([--with-readline],
        [<<no>> if disable readline library even if available])],
    [can_readline=$withval],
    [can_readline=yes])

have_readline=no
AS_IF([test "x$can_readline" != "xno"], [
    AC_CHECK_LIB([readline], [readline],
	[have_readline=yes],
        [AC_MSG_NOTICE([Readline not found, using getline])])
])

AS_IF([test "x$have_readline" = "xyes"], [
    AC_DEFINE([USE_READLINE], [1], [Use readline library])
], [
    AC_DEFINE([USE_READLINE], [0], [Use readline library])
])

AM_CONDITIONAL([USE_READLINE], [test "x$have_readline" = xyes])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
