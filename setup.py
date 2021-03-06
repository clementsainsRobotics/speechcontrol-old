from distutils.core import setup

package_dirs = {"speechcontrol" : "package",
				"asr" : "daemon",
				"gui" : "trainer"}
setup(
        name="SpeechControl",
        version="0.1",
        description="control your computer with voice",
        author="SpeechControl Developers",
        author_email="dev@thesii.org",
        url="http://www.thesii.org/projects/speechcontrol.html",
        license="GPLv3+",
        package_dir=package_dirs,
        packages=["speechcontrol", "asr", "gui"],
        scripts=["trainer/speechtrainer.py", "daemon/speechdaemon.py"]
        )
