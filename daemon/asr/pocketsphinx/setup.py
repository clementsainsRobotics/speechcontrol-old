from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext

include_dirs = [
        "/usr/include/sphinxbase",
        "/usr/include/pocketsphinx"
        ]

libraries = [
        "pocketsphinx",
        "sphinxad"
        ]

ext_modules = [
        Extension("pocketsphinx", ["pocketsphinx.pyx"],
            include_dirs=include_dirs,
            libraries=libraries
            )
        ]

setup(
    cmdclass = {'build_ext': build_ext},
    ext_modules = ext_modules
)
