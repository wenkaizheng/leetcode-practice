import os
import time
import sys
import pickle
import subprocess
import threading
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request
SCOPES = ['https://www.googleapis.com/auth/drive']
def insertion():
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
    g = u'gdrive --access-token ' + creds.token + u' upload --parent 1hQaB1EKaeiaqOVCQ_PGCR9teksRsGjaH game1.flv'
    process = subprocess.Popen(g, shell=True, stdout=subprocess.PIPE)
    output, err = process.communicate()
    #print(output)
    print("30th")
    os.remove('game1.flv')
    

def test(name):
    assert True == os.path.exists(name)
    prefix =name[:name.find('.')]
    encoded_arr = [prefix+'_h264_1080p.mp4',prefix+'_h264_240p.mp4',prefix+'_h264_360p.mp4'
                  ,prefix+'_h264_480p.mp4',prefix+'_h264_720p.mp4']
    count = 5 
    real_count = 0
    for i in range(0,count):
        if os.path.exists(encoded_arr[i]):
           real_count +=1
    assert real_count == count
    assert True == os.path.exists(prefix)
    html_file = prefix+'.html'
    assert True == os.path.exists(html_file)
def wait(): 
    print("49th")   
    time.sleep(200)
    test('game1.flv')
    print("no resume from here")
    process.kill()
    sys.exit(0)

pwd = os.path.abspath('../') + '/'+'ndn_script.py'
print(pwd)
insertion()
#t1 = threading.Thread(target=wait, args=())
#t1.start() 
cmd = 'python '+pwd
process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
wait()


