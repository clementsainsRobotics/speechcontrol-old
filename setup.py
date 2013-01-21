from distutils.core import setup
setup(
        name="SpeechControl",
        version="0.1",
        description="control your computer with voice",
        author="SpeechControl Developers",
        author_email="dev@thesii.org",
        url="http://www.thesii.org/projects/speechcontrol.html",
        packages=["speechcontrol", "speechcontrol.asr", "speechcontrol.gui"],
        scripts=["speechcontrol/speechtrainer.py", "speechcontrol/speechdaemon.py"]
        )
