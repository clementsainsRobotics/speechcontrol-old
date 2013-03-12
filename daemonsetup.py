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
        Extension("pocketsphinx", ["daemon/asr/pocketsphinx/pocketsphinx.pyx"],
            include_dirs=include_dirs,
            libraries=libraries
            )
        ]


package_dirs = {"" : "daemon"}
setup(
        name="SpeechControl (daemon)",
        version="0.1",
        description="control your computer with voice",
        author="SpeechControl Developers",
        author_email="dev@thesii.org",
        url="http://www.thesii.org/projects/speechcontrol.html",
        license="GPLv3+",
        package_dir=package_dirs,
        packages=["asr"],
        scripts=["daemon/speechdaemon.py"],
        cmdclass = {'build_ext': build_ext},
        ext_modules = ext_modules
        )
