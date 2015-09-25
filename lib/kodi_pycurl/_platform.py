"""
Provides details about the current python interpreters' platform
"""

import re
import os
import sys
import string
import platform

""" From distutils.sysconfig """
# These are needed in a couple of spots, so just compute them once.
PREFIX = os.path.normpath(sys.prefix)
EXEC_PREFIX = os.path.normpath(sys.exec_prefix)

""" From distutils.util """
def get_platform ():
    """Return a string that identifies the current platform.  This is used
    mainly to distinguish platform-specific build directories and
    platform-specific built distributions.  Typically includes the OS name
    and version and the architecture (as supplied by 'os.uname()'),
    although the exact information included depends on the OS; eg. for IRIX
    the architecture isn't particularly important (IRIX only runs on SGI
    hardware), but for Linux the kernel version isn't particularly
    important.

    Examples of returned values:
       linux-i586
       linux-alpha (?)
       solaris-2.6-sun4u
       irix-5.3
       irix64-6.2

    Windows will return one of:
       win-amd64 (64bit Windows on AMD64 (aka x86_64, Intel64, EM64T, etc)
       win-ia64 (64bit Windows on Itanium)
       win32 (all others - specifically, sys.platform is returned)

    For other non-POSIX platforms, currently just returns 'sys.platform'.
    """
    if os.name == 'nt':
        # sniff sys.version for architecture.
        prefix = " bit ("
        i = string.find(sys.version, prefix)
        if i == -1:
            return sys.platform
        j = string.find(sys.version, ")", i)
        look = sys.version[i+len(prefix):j].lower()
        if look=='amd64':
            return 'win-amd64'
        if look=='itanium':
            return 'win-ia64'
        return sys.platform

    if os.name != "posix" or not hasattr(os, 'uname'):
        # XXX what about the architecture? NT is Intel or Alpha,
        # Mac OS is M68k or PPC, etc.
        return sys.platform

    # Try to distinguish various flavours of Unix

    (osname, host, release, version, machine) = os.uname()

    # Convert the OS name to lowercase, remove '/' characters
    # (to accommodate BSD/OS), and translate spaces (for "Power Macintosh")
    osname = string.lower(osname)
    osname = string.replace(osname, '/', '')
    machine = string.replace(machine, ' ', '_')
    machine = string.replace(machine, '/', '-')

    if osname[:5] == "linux":
        # At least on Linux/Intel, 'machine' is the processor --
        # i386, etc.
        # XXX what about Alpha, SPARC, etc?
        return  "%s-%s" % (osname, machine)
    elif osname[:5] == "sunos":
        if release[0] >= "5":           # SunOS 5 == Solaris 2
            osname = "solaris"
            release = "%d.%s" % (int(release[0]) - 3, release[2:])
        # fall through to standard osname-release-machine representation
    elif osname[:4] == "irix":              # could be "irix64"!
        return "%s-%s" % (osname, release)
    elif osname[:3] == "aix":
        return "%s-%s.%s" % (osname, version, release)
    elif osname[:6] == "cygwin":
        osname = "cygwin"
        rel_re = re.compile (r'[\d.]+')
        m = rel_re.match(release)
        if m:
            release = m.group()
    elif osname[:6] == "darwin":
        #
        # For our purposes, we'll assume that the system version from
        # distutils' perspective is what MACOSX_DEPLOYMENT_TARGET is set
        # to. This makes the compatibility story a bit more sane because the
        # machine is going to compile and link as if it were
        # MACOSX_DEPLOYMENT_TARGET.
        # from distutils.sysconfig import get_config_vars
        # cfgvars = get_config_vars()

        macver = os.environ.get('MACOSX_DEPLOYMENT_TARGET')
        # if not macver:
        #     macver = cfgvars.get('MACOSX_DEPLOYMENT_TARGET')

        if 1:
            # Always calculate the release of the running machine,
            # needed to determine if we can build fat binaries or not.

            # macrelease = macver
            macrelease = None
            # Get the system version. Reading this plist is a documented
            # way to get the system version (see the documentation for
            # the Gestalt Manager)
            try:
                f = open('/System/Library/CoreServices/SystemVersion.plist')
            except IOError:
                # We're on a plain darwin box, fall back to the default
                # behaviour.
                pass
            else:
                m = re.search(
                        r'<key>ProductUserVisibleVersion</key>\s*' +
                        r'<string>(.*?)</string>', f.read())
                f.close()
                if m is not None:
                    macrelease = '.'.join(m.group(1).split('.')[:2])
                # else: fall back to the default behaviour

        if not macver:
            macver = macrelease

        if macver:
            # from distutils.sysconfig import get_config_vars
            release = macver
            osname = "macosx"

            machine = 'intel' # kodi only has releases for intel

            # if map(int, macrelease.split('.')) >= map(int, '10.4'.split('.')) and \
            #         '-arch' in get_config_vars().get('CFLAGS', '').strip():
            #     # The universal build will build fat binaries, but not on
            #     # systems before 10.4
            #     #
            #     # Try to detect 4-way universal builds, those have machine-type
            #     # 'universal' instead of 'fat'.
            #
            #     machine = 'fat'
            #     cflags = get_config_vars().get('CFLAGS')
            #
            #     archs = re.findall('-arch\s+(\S+)', cflags)
            #     archs = tuple(sorted(set(archs)))
            #
            #     if len(archs) == 1:
            #         machine = archs[0]
            #     elif archs == ('i386', 'ppc'):
            #         machine = 'fat'
            #     elif archs == ('i386', 'x86_64'):
            #         machine = 'intel'
            #     elif archs == ('i386', 'ppc', 'x86_64'):
            #         machine = 'fat3'
            #     elif archs == ('ppc64', 'x86_64'):
            #         machine = 'fat64'
            #     elif archs == ('i386', 'ppc', 'ppc64', 'x86_64'):
            #         machine = 'universal'
            #     else:
            #         raise ValueError(
            #            "Don't know machine value for archs=%r"%(archs,))
            #
            # elif machine == 'i386':
            #     # On OSX the machine type returned by uname is always the
            #     # 32-bit variant, even if the executable architecture is
            #     # the 64-bit variant
            #     if sys.maxint >= 2**32:
            #         machine = 'x86_64'
            #
            # elif machine in ('PowerPC', 'Power_Macintosh'):
            #     # Pick a sane name for the PPC architecture.
            #     machine = 'ppc'
            #
            #     # See 'i386' case
            #     if sys.maxint >= 2**32:
            #         machine = 'ppc64'

    return "%s-%s-%s" % (osname, release, machine)

# wheel/pep425tags.py
def get_abbr_impl():
    """Return abbreviated implementation name."""
    if hasattr(sys, 'pypy_version_info'):
        pyimpl = 'pp'
    elif sys.platform.startswith('java'):
        pyimpl = 'jy'
    elif sys.platform == 'cli':
        pyimpl = 'ip'
    else:
        pyimpl = 'cp'
    return pyimpl

# wheel/pep425tags.py
def get_impl_ver():
    """Return implementation version."""
    # impl_ver = sysconfig.get_config_var("py_version_nodot")
    # if not impl_ver:
    impl_ver = ''.join(map(str, sys.version_info[:2]))
    return impl_ver

def get_tag():
    plat_name = get_platform()

    # distutils (os.uname actually) gives the undesired result for linux x86
    # running in a chroot/docker on an x64 machine.
    if plat_name == 'linux-x86_64':
        if platform.architecture()[0] == '32bit':
            plat_name = 'linux-i686'

    plat_name = plat_name.replace('-', '_').replace('.', '_')

    impl_name = get_abbr_impl()
    impl_ver = get_impl_ver()
    # # PEP 3149 -- no SOABI in Py 2
    # # For PyPy?
    # # "pp%s%s" % (sys.pypy_version_info.major,
    # # sys.pypy_version_info.minor)
    # abi_tag = sysconfig.get_config_vars().get('SOABI', 'none')
    abi_tag = 'none'
    if abi_tag.startswith('cpython-'):
        abi_tag = 'cp' + abi_tag.split('-')[1]

    tag = (impl_name + impl_ver, abi_tag, plat_name)
    # XXX switch to this alternate implementation for non-pure:
    return tag

def get_archive_basename(dist_name):
    """Return archive name without extension"""

    impl_tag, abi_tag, plat_tag = get_tag()

    archive_basename = "%s-%s-%s-%s" % (
        dist_name,
        impl_tag,
        abi_tag,
        plat_tag)
    return archive_basename
