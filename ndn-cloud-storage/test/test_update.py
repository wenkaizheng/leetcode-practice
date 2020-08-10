import os
import time
import sys
import pickle
import subprocess
from threading import Lock
#from watchdog.observers import Observer
#from watchdog.events import *
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request
from watcher import FileEventHandler
from watchdog.observers import Observer
SCOPES = ['https://www.googleapis.com/auth/drive']


def update():
    creds = None
    if os.path.exists('token.pickle'):
        with open('token.pickle', 'rb') as token:
            creds = pickle.load(token)
    if not creds or not creds.valid:
        if creds and creds.expired and creds.refresh_token:
            creds.refresh(Request())
        else:
            flow = InstalledAppFlow.from_client_secrets_file(
                'credapi.json', SCOPES)
            creds = flow.run_local_server(port=0)
        with open('token.pickle', 'wb') as token:
            pickle.dump(creds, token)
    # folder id for testing 1hQaB1EKaeiaqOVCQ_PGCR9teksRsGjaH
    # gdrive upload --parent 0B3X9GlR6EmbnY1RLVTk5VUtOVkk gdrive-osx-x64
    g = u'gdrive --access-token ' + creds.token + \
        u' update 1OA8YUbr-BiTDczna_FgzdrZov7jAgyWD game2.flv'
    print(g)
    process = subprocess.Popen(g, shell=True, stdout=subprocess.PIPE)
    output, err = process.communicate()
    # print(output)
    print("30th")
    # os.remove('game1.flv')


def wait():
    mutex = Lock()
    prefix = 'game2'
    nums = ['./zmj']
    observer = Observer()
    event_handler = FileEventHandler(nums, mutex, 'update')
    observer.schedule(event_handler, '.', True)
    observer.start()
    break_condition = False
    while True:
        time.sleep(3)
        mutex.acquire()
        if len(nums) == 0:
            observer.stop()
            break_condition = True
        print(nums)
        mutex.release()
        if break_condition:
            break
    print('end')
    process.kill()
    nums = ['./zmj/game2', './zmj/game2.html', './zmj/game2.flv', './zmj/' + prefix+'_h264_1080p.mp4', './zmj/' +
            prefix+'_h264_240p.mp4', './zmj/'+prefix+'_h264_360p.mp4', './zmj/'+prefix+'_h264_480p.mp4', './zmj/'+prefix+'_h264_720p.mp4']
    for i in nums:
        assert(os.path.exists(i))
    sys.exit(0)


pwd = os.path.abspath('../') + '/'+'ndn_script.py -v info'
print(pwd)
update()
#t1 = threading.Thread(target=wait, args=())
# t1.start()
cmd = 'python '+pwd
process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
wait()
