// HAVE_DECL_CTL_KERN : BUILD2_AUTOCONF_LIBC_VERSION

#ifndef BUILD2_AUTOCONF_LIBC_VERSION
#  error BUILD2_AUTOCONF_LIBC_VERSION appears to be conditionally included
#endif

#undef HAVE_DECL_CTL_KERN

/* Since 4.4BSD (OpenBSD 2.1-6.2, FreeBSD, NetBSD, Mac OS X 10.7),
 * <= glibc 2.31.
 * NOTE: Appears to have been available parallel to sysctl()
 */
#if (BUILD2_AUTOCONF_OPENBSD_PREREQ(199706) && !BUILD2_AUTOCONF_OPENBSD_PREREQ(201804)) || \
    BUILD2_AUTOCONF_FREEBSD_PREREQ(2, 3)   || \
    BUILD2_AUTOCONF_NETBSD_PREREQ(2, 0)    || \
    BUILD2_AUTOCONF_MACOS_PREREQ(10, 7)    || \
    !BUILD2_AUTOCONF_GLIBC_PREREQ(2, 32)
#  define HAVE_DECL_CTL_KERN 1
#endif