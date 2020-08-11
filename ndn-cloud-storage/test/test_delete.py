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


def delete():
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
    # find the file game1
    g = u'gdrive --access-token ' + creds.token + u' list'
    process = subprocess.Popen(g, shell=True, stdout=subprocess.PIPE)
    output, err = process.communicate()
    output_list = output.split('\n')[1:-1]
    items = []
    for file_info in output_list:
        file_id = file_info.split()[0]
       # file_id = file_id.encode("utf-8")
        g = u'gdrive --access-token '+creds.token + u' info ' + file_id
        process = subprocess.Popen(g, shell=True, stdout=subprocess.PIPE)
        output, err = process.communicate()
        items.append(output)
    game1_id = None
    for item in items:
            item = item.split('\n')[:-1]
            file_id = item[0][item[0].find(':')+2:]
            name = item[1][item[1].find(':')+2:]
            if name =='game1.flv':
                game1_id = file_id
                break
    
    g = u'gdrive --access-token ' + creds.token + \
        u' delete ' + game1_id
    print(g)
    process = subprocess.Popen(g, shell=True, stdout=subprocess.PIPE)
    output, err = process.communicate()
    # print(output)
    print("30th")
    # os.remove('game1.flv')


def wait():
    mutex = Lock()
    if os.path.exists('zmj/game1'):
         prefix = 'game1'
         nums = ['./zmj/game1', './zmj/game1.html', './zmj/game1.flv', './zmj/' + prefix+'_h264_1080p.mp4', './zmj/'+prefix +
            '_h264_240p.mp4', './zmj/'+prefix+'_h264_360p.mp4', './zmj/'+prefix+'_h264_480p.mp4', './zmj/'+prefix+'_h264_720p.mp4']
    # if you alreay ran the update test
    else:
         prefix = 'game2'
         nums = ['./zmj/game2', './zmj/game2.html', './zmj/game2.flv', './zmj/' + prefix+'_h264_1080p.mp4', './zmj/'+prefix +
            '_h264_240p.mp4', './zmj/'+prefix+'_h264_360p.mp4', './zmj/'+prefix+'_h264_480p.mp4', './zmj/'+prefix+'_h264_720p.mp4']
    observer = Observer()
    event_handler = FileEventHandler(nums, mutex, 'delete')
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
    arr = [f for f in os.listdir('./zmj') if not f.startswith('.')]
    assert(len(arr) == 0)
    sys.exit(0)


pwd = os.path.abspath('../') + '/'+'ndn_script.py -v info'
print(pwd)
delete()
#t1 = threading.Thread(target=wait, args=())
# t1.start()
cmd = 'python '+pwd
process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
wait()
