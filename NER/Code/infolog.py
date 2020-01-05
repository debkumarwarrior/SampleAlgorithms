from datetime import datetime
class Log:
    def close(self):
        self.file.close()

    def init(self,filename):
        self.close()
        self._format = '%Y-%m-%d %H:%M:%S.%f'
        self.file = open(filename,'a')
        self.file.write('\n-----------------------------------------------------------------\n')
        self.file.write('Starting new training run\n')
        self.file.write('-----------------------------------------------------------------\n')

    def log(self,msg):
        print(msg)
        if self.file is not None:
            self.file.write('[%s]    %s\n' % (datetime.now().strftime(self._format)[:-3], msg))
