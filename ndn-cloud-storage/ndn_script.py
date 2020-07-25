#!/usr/bin/python
# Copyright (c) 2019-2020, Regents of the University of Arizona.
# Author: Wenkai Zheng <zmkzmj@gmail.com>
#
# You should have received a copy of the GNU General Public License along with
# this script e.g., in COPYING.md file. If not, see <http://www.gnu.org/licenses/>.
#
from __future__ import print_function
import pickle
import os.path
import io
import shutil
import subprocess
import datetime
import dateutil.parser
from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request
#from googleapiclient.http import MediaIoBaseDownload
from MY_FILE import myFile
# If modifying these scopes, delete the file token.pickle.
SCOPES = ['https://www.googleapis.com/auth/drive']

def download(id,creds):
    id = id.encode("utf-8")
    update_token(creds)
    g = u'gdrive --access-token ' + creds.token + u' download --force ' +id 
    process = subprocess.Popen(g, shell=True, stdout=subprocess.PIPE)
    output, err = process.communicate()
    print(output)
    if not err:
        return 0
    else: return 1 
def write_record(file_instance):
    '''
    todo write record to txt file when first time load storage 
    '''
    with open('file_record.txt','a') as f:
                f.write(str(file_instance))

def dump_data(file_coll):
    with open('data-s', 'wb') as token:
               pickle.dump(file_coll, token)
def load_data():
     rc = None
     with open('data-s', 'wr') as token:
              rc = pickle.load(token)
     return rc
def driver_script(file_name,file_instance,file_coll):
    
    pwd = os.path.dirname(os.path.realpath("driver.sh"))
    #pwd1 = os.path.dirname(os.path.realpath("packager.sh")) +'/packager.sh'
    file_name_prefix = file_name[:file_name.find('.')]
    base = '/ndn/web/video'
    encode(file_name,file_instance,file_coll)

    packaged(file_name,file_instance,file_coll)
    version = '1'
    segmentSize = '8000'
    chunker = ('chunker '+ base + '/' + file_name_prefix + ' -i ' 
        +pwd + '/' + file_name_prefix + ' -s '
            +segmentSize + ' -e ' + version + ' && wait')
    if driver_script_helper(chunker) == 0:
        print('chunked alreay in here')
        file_instance.set_status('chunked')
        dump_data(file_coll)
        write_record(file_instance)
    
    html(file_name,file_instance,file_coll,True)
def encode(file_name,file_instance,file_coll):
    encode = './transcoder.sh ' + file_name + ' && wait'
    if driver_script_helper(encode) == 0:
        file_instance.set_status('encoded')
        dump_data(file_coll)   
def packaged(file_name,file_instance,file_coll):
    pwd = os.path.dirname(os.path.realpath("driver.sh"))
    pwd1 = os.path.dirname(os.path.realpath("packager.sh")) +'/packager.sh'
    file_name_prefix = file_name[:file_name.find('.')]
    protocol = 'hls'
    playlist = 'playlist.m3u8'
    package = (pwd1+' ' +pwd+' ' + file_name_prefix + ' '
        + pwd +'/'+file_name_prefix + '/' + protocol + ' ' 
            + protocol + ' && wait')
    if driver_script_helper(package) == 0:
        file_instance.set_status('packaged')
        dump_data(file_coll)
        write_record(file_instance)   
def html(file_name,file_instance,file_coll,judge):
    file_name_prefix = file_name[:file_name.find('.')]
    base = '/ndn/web/video'
    protocol = 'hls'
    playlist = 'playlist.m3u8'
    manifestUrl = base + '/' + file_name_prefix + '/' + protocol + '/' +playlist
    inputs = ('https://gist.githubusercontent.com/chavoosh/f7db8dc41c3e8bb8e6a058b1ea342b5a/raw' 
      + '/cb9ea05b57f769f845398721f68c3f6f4b3b88ac/base.html')
    line = ('      <!-- manifest uri -->\n')
    line +='      '+ "'<span id= 'manifestUri' hidden>'"+manifestUrl +"'</span>\n\n'"
    line = '"' + line + '"'
    curl_one = ('curl '+ inputs + ' | ' + 'sed -n ' + "'0, /begin url section/p'"
        +' > ' + file_name_prefix + '.html ' +'&& ' +'printf '
        + line + ' >> ' + file_name_prefix + '.html')
    curl_two = ('curl '+ inputs + ' | ' + 'sed -n ' + "'/end url section/, $p'"
        + ' >> ' + file_name_prefix + '.html')
    if judge:
       if driver_script_helper(curl_one) == 0:
            file_instance.set_status('html and js first')
            dump_data(file_coll)
            write_record(file_instance)     
    if driver_script_helper(curl_two) == 0:
        file_instance.set_status('html and js second')
        dump_data(file_coll)
        write_record(file_instance)

def driver_script_helper(command):
    process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)
    output, err = process.communicate()
    print(output)
    print (process.returncode)
    return process.returncode
def update_token(creds):
    if creds.expired and creds.refresh_token:
            creds.refresh(Request())
def check_status(file_coll,creds):
    for key in file_coll:
        for file_instance in file_coll[key]:
            status = file_instance.get_status()
            name = file_instance.get_name()
            file_id = file_instance.get_id()
            if status == 'initial':
                download(file_id ,creds)
                driver_script(name,file_instance,file_coll)

            elif status == 'download':
                  #todo check if the file exist and process
                  if not os.path.exists(name):
                      download(file_id,creds)
                  driver_script(name,file_instance,file_coll)
            elif status == 'encoded':
                  # ask chavoosh to answer
                  #   VIDEO_FILE_NAME_h264_720p.mp4
                  prefix =name[:name.find('.')]
                  encoded_arr = [prefix+'_h264_1080p.mp4',prefix+'_h264_240p.mp4',prefix+'_h264_360p.mp4'
                  ,prefix+'_h264_480p.mp4',prefix+'_h264_720p.mp4']
                  count = 5 
                  real_count = 0
                  for i in range(0,count):
                      if os.path.exists(encoded_arr[i]):
                          real_count +=1
                  if real_count != count:
                      encoded_arr(name,file_instance,file_coll)

                  print('todo')
            elif status == 'packaged':
                 prefix = name[:name.find('.')]
                 if not os.path.exists(name):
                     packaged(name,file_instance,file_coll)
            elif status == 'chunked':
                 html(name,file_instance,file_coll,True)
            # only one left is html but we need to have two 
            else:
                web = name[:name.find('.')]+'.html'
                if not os.path.exists(web):
                    html(name,file_instance,file_coll,True)
                else:
                    if file_instance.get_status() == 'html and js first':
                        html(name,file_instance,file_coll,False)
            
def delete(file_name):
    prefix = file_name[:file_name.find('.')]
    #delete the packeger
    if os.path.exists(prefix):
        shutil.rmtree(prefix)
    #delete the encoder
    encoded_arr = [prefix+'_h264_1080p.mp4',prefix+'_h264_240p.mp4',prefix+'_h264_360p.mp4'
                  ,prefix+'_h264_480p.mp4',prefix+'_h264_720p.mp4']
    count = 5 
    for i in range(0,count):
        if os.path.exists(encoded_arr[i]):
             os.remove(encoded_arr[i])
    # delete the html
    html_file = prefix+'.html'
    if os.path.exists(html_file):
        os.remove(html_file)


def main(creds):
    #gdrive stuff to get meta data from each file
    update_token(creds)
    g = u'gdrive --access-token ' + creds.token + u' list'
    process = subprocess.Popen(g, shell=True, stdout=subprocess.PIPE)
    output, err = process.communicate()
    output_list = output.split('\n')[1:-1]
    items = []
    for file_info in output_list:
        file_id = file_info.split()[0]
        file_id = file_id.encode("utf-8")
        update_token(creds)
        g = u'gdrive --access-token '+creds.token + u' info ' +file_id 
        process = subprocess.Popen(g, shell=True, stdout=subprocess.PIPE)
        output, err = process.communicate()
        items.append(output)
    file_coll = None
    if os.path.exists('data-s'):
         with open('data-s','rb') as token:
              file_coll = pickle.load(token)
         check_status(file_coll,creds)
        #print(file_coll)
    else:
        file_coll = {}
    change = False
    # checking if we delete anything
    compare_coll = []
    if not items:
        print('No files found.')
    else:
        print('Files:')
        for item in items:
            item =  item.split('\n')[:-1]
            file_id = item[0][item[0].find(':')+2:]
            name = item[1][item[1].find(':')+2:]
            time = item[5][item[5].find(':')+2:]
            parent = item[7][item[7].find(':')+2:]
            mime_type = item[3][item[3].find(':')+2:]
            print(name,time,parent,file_id,mime_type,file_id)
            if mime_type == 'application/vnd.google-apps.folder':
               if file_id not in file_coll:
                    file_coll[file_id] = []
               continue
           # print('80th   ' + parent)
            file_instance = myFile(name,file_id,mime_type,dateutil.parser.parse(time),'initial',parent)
            compare_coll.append(file_instance)
            if parent in file_coll :
               record = file_coll[parent]
               find = False
               for re in record:
                  if re == file_instance:
                    find = True
                    if file_instance > re:
                        change = True
                        re.set_time(time)
                        dump_data(file_coll)
                        write_record(re)
                        print("97th")
                        rv = download(file_id,creds)
                        if rv == 0:
                           re.set_status("download")
                           dump_data(file_coll)
                           write_record(re)
                           driver_script(name,re,file_coll)
               if not find:
                    file_coll[parent].append(file_instance)
                    print("101th")
                    rv = download(file_id,creds)
                    if rv == 0:
                      # when it is initial
                      dump_data(file_coll)
                      write_record(file_instance)
                      file_instance.set_status("download")
                      dump_data(file_coll)
                      write_record(file_instance)
                      driver_script(name,file_instance,file_coll)
               
            else:
                file_coll[parent] = []
                file_coll[parent].append(file_instance)
                print("106th")
                rv = download(file_id,creds)
                if rv == 0:
                     # when it is initial
                    dump_data(file_coll)
                    write_record(file_instance)
                    file_instance.set_status("download")
                    dump_data(file_coll)
                    write_record(file_instance)
                    driver_script(name,file_instance,file_coll)
            
    #print(file_coll)
    #copy = {}
    # detect if there is any file has been delete
    for key in file_coll:
        for fi in file_coll[key][:]:
            if fi in compare_coll:
                continue
                #copy[key].append(fi)
            else:
                fi.set_status('deleted')
                write_record(fi)
                file_coll[key].remove(fi)
                dump_data(file_coll)
                

    #write_record(file_coll)
if __name__== '__main__':
    creds = None
    count = 0
    while True:
       if count == 0:
          """
          Netwrok stuff to get token with google drive server
          """
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
       main(creds)
       count +=1
