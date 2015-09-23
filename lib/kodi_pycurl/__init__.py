"""
## Multiple platform selector for pycurl binary distributions
# Original from: https://pypi.python.org/pypi/pycurl/7.19.5.1

## To Use:
# in addon.xml
<import addon="script.module.pycurl" version="7.19.5"/>
# in your project
import kodi_pycurl
import pycurl

## To add new platform:
# Ensure python compatible toolchain is installed
# Ensure you run the same version of python used in kodi on your platform.

# To build binary module for your platform:
cd script.module.pycurl/lib
python -c "import kodi_pycurl; kodi_pycurl.build_binary_dist()"

# Please do contribute added distributions back to project!
"""

import re
import os
import sys
import string

package = "pycurl"
version = "7.19.5.1"

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
        from distutils.sysconfig import get_config_vars
        cfgvars = get_config_vars()

        macver = os.environ.get('MACOSX_DEPLOYMENT_TARGET')
        if not macver:
            macver = cfgvars.get('MACOSX_DEPLOYMENT_TARGET')

        if 1:
            # Always calculate the release of the running machine,
            # needed to determine if we can build fat binaries or not.

            macrelease = macver
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
            from distutils.sysconfig import get_config_vars
            release = macver
            osname = "macosx"

            if map(int, macrelease.split('.')) >= map(int, '10.4'.split('.')) and \
                    '-arch' in get_config_vars().get('CFLAGS', '').strip():
                # The universal build will build fat binaries, but not on
                # systems before 10.4
                #
                # Try to detect 4-way universal builds, those have machine-type
                # 'universal' instead of 'fat'.

                machine = 'fat'
                cflags = get_config_vars().get('CFLAGS')

                archs = re.findall('-arch\s+(\S+)', cflags)
                archs = tuple(sorted(set(archs)))

                if len(archs) == 1:
                    machine = archs[0]
                elif archs == ('i386', 'ppc'):
                    machine = 'fat'
                elif archs == ('i386', 'x86_64'):
                    machine = 'intel'
                elif archs == ('i386', 'ppc', 'x86_64'):
                    machine = 'fat3'
                elif archs == ('ppc64', 'x86_64'):
                    machine = 'fat64'
                elif archs == ('i386', 'ppc', 'ppc64', 'x86_64'):
                    machine = 'universal'
                else:
                    raise ValueError(
                       "Don't know machine value for archs=%r"%(archs,))

            elif machine == 'i386':
                # On OSX the machine type returned by uname is always the
                # 32-bit variant, even if the executable architecture is
                # the 64-bit variant
                if sys.maxint >= 2**32:
                    machine = 'x86_64'

            elif machine in ('PowerPC', 'Power_Macintosh'):
                # Pick a sane name for the PPC architecture.
                machine = 'ppc'

                # See 'i386' case
                if sys.maxint >= 2**32:
                    machine = 'ppc64'

    return "%s-%s-%s" % (osname, release, machine)

plat_name = get_platform()
target_version = sys.version[0:3]
binary_package_name = "%s-%s-py%s-%s" % (package, version, target_version, plat_name)
binary_package_path = os.path.abspath(os.path.join(os.path.dirname(__file__), binary_package_name))

if not binary_package_path or not os.path.exists(binary_package_path):
    print "%s distribution not available for your platform.\n%s \nPlease add one if possible by following instructions in top of file: %s" %(package,binary_package_name, str(__file__))

else:
    # Load real module
    import imp
    imp.load_source(package, os.path.join(binary_package_path, 'pycurl.py'))

def build_binary_dist():
    # Try to build the binary module
    import os
    import sys
    import zipfile
    import subprocess
    from fnmatch import fnmatch
    from distutils.dir_util import remove_tree

    rootdir = os.path.abspath(os.path.dirname(__file__))
    curdir = os.curdir
    try:
        os.chdir(os.path.join(rootdir, '%s-%s'%(package, version)))
        if os.path.exists('dist'):
            remove_tree('dist')
        if os.path.exists('build'):
            remove_tree('build')

        # python -c "import setuptools; execfile('setup.py')" bdist_egg
        clean = subprocess.call([sys.executable, "-c", "import setuptools; execfile('setup.py')", "clean"])
        build = subprocess.call([sys.executable, "-c", "import setuptools; execfile('setup.py')", "bdist_egg"])
        if build != 0:
            print "Error building %s" %package
        else:
            # cp dist/human_curl-0.1.9-*.egg ../
            egg = None
            for f in os.listdir('dist'):
                if fnmatch(f, '%s-*.egg'%package):
                    egg = f
                    print egg
                    break
            if egg:
                if not os.path.exists(binary_package_path):
                    os.makedirs(binary_package_path)
                zip = zipfile.ZipFile(os.path.join('dist', egg), 'r')
                zip.extractall(binary_package_path)
    finally:
        os.chdir(curdir)

if __name__ == "__main__":
    print "binary_package_path = %s" % binary_package_path

