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

package = "pycurl"
version = "7.19.5.1"

import os
import _platform

binary_package_name = _platform.get_archive_basename('-'.join((package,version)))
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

