from distutils.core import setup

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
        scripts=["daemon/speechdaemon.py"]
        )
