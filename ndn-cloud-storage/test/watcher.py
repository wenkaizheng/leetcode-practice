from watchdog.observers import Observer
from watchdog.events import *
from threading import Lock


class FileEventHandler(FileSystemEventHandler):
    def __init__(self, num, mutex, test):
        FileSystemEventHandler.__init__(self)
        self.num = num
        self.mutex = mutex
        self.test = test

    def on_created(self, event):
        if self.test == 'insert':
            if event.is_directory:
                self.mutex.acquire()
                print("directory created:{0}".format(event.src_path))
               # assert(event.src_path in self.num)
                if event.src_path in self.num:
                    self.num.remove(event.src_path)
                self.mutex.release()
            else:
                self.mutex.acquire()
                print("file created:{0}".format(event.src_path))
               # assert(event.src_path in self.num)
                if event.src_path in self.num:
                    self.num.remove(event.src_path)
                self.mutex.release()

    def on_modified(self, event):
        if self.test == 'update':
            if event.is_directory:
                self.mutex.acquire()
                print("directory modified:{0}".format(event.src_path))
               # assert(event.src_path in self.num)
                if event.src_path in self.num:
                    self.num.remove(event.src_path)
                self.mutex.release()
            else:
                self.mutex.acquire()
                print("directory modified:{0}".format(event.src_path))
               # assert(event.src_path in self.num)
                if event.src_path in self.num:
                    self.num.remove(event.src_path)
                self.mutex.release()
    def on_deleted(self, event):
        if self.test == 'delete':
            if event.is_directory:
                self.mutex.acquire()
                print("directory deleted:{0}".format(event.src_path))
                if event.src_path in self.num:
                    self.num.remove(event.src_path)
                self.mutex.release()
            else:
                self.mutex.acquire()
                print("file deleted:{0}".format(event.src_path))
                if event.src_path in self.num:
                    self.num.remove(event.src_path)
                self.mutex.release()
