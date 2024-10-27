// HAVE_GETAUXVAL : BUILD2_AUTOCONF_LIBC_VERSION

#ifndef BUILD2_AUTOCONF_LIBC_VERSION
#  error BUILD2_AUTOCONF_LIBC_VERSION appears to be conditionally included
#endif

#undef HAVE_GETAUXVAL

/* Since glibc 2.16.
 */
#if BUILD2_AUTOCONF_GLIBC_PREREQ(2, 16)
#  define HAVE_GETAUXVAL 1
#endif