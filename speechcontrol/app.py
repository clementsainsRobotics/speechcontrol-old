from PyQt4.QtGui import QApplication

class App(QApplication):
    def __init__(self, args):
        super().__init__(args)

        self.asr_backend = "pocketsphinx"

    def set_asr_backend(self, backend):
        seld.asr_backend = backend
