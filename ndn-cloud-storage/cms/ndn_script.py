#!/usr/bin/python
# Copyright (c) 2019-2020, Regents of the University of Arizona.
# Author: Wenkai Zheng <zmkzmj@gmail.com>
#
# You should have received a copy of the GNU General Public License along with
# this script e.g., in COPYING.md file. If not, see <http://www.gnu.org/licenses/>.
#
from __future__ import print_function
import argparse
import pickle
import os.path
import io
import shutil
import subprocess
import datetime
import dateutil.parser
import sys
#from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request
#from googleapiclient.http import MediaIoBaseDownload
from MY_FILE import myFile
# If modifying these scopes, delete the file token.pickle.
SCOPES = ['https://www.googleapis.com/auth/drive']


def download(id, creds):
    id = id.encode("utf-8")
    directorys = directory.encode("utf-8")
    update_token(creds)
    g = directorys + u'gdrive --access-token ' + \
        creds.token + u' download --force ' + id
    print(g)
    process = subprocess.Popen(g, shell=True, stdout=subprocess.PIPE)
    output, err = process.communicate()
    if version == 'debug':
        write_rdebug_record(output)
    # print(output)
    return process.returncode


def write_record(file_instance):
    with open(env_path + 'file_record.txt', 'a') as f:
        f.write(str(file_instance))


def write_rdebug_record(output):
    with open(env_path + 'file_record.txt', 'a') as f:
        f.write(output)


def dump_data(file_coll):
    with open(env_path + 'data-s', 'wb') as token:
        pickle.dump(file_coll, token)


def load_data():
    rc = None
    with open(env_path + 'data-s', 'rb') as token:
        rc = pickle.load(token)
    return rc


def driver_script(file_name, file_instance, file_coll):

    #pwd = os.path.abspath(env_path + "../video/driver.sh")
    #pwd1 = os.path.dirname(os.path.realpath("packager.sh")) +'/packager.sh'
    #file_name_prefix = file_name[:file_name.find('.')]
    base = '/ndn/web/video'
    encode(file_name, file_instance, file_coll)
    packaged(file_name, file_instance, file_coll)
    chunker(file_name, file_instance, file_coll)
    html(file_name, file_instance, file_coll, True)


def chunker(file_name, file_instance, file_coll):
    pwd = os.path.abspath(env_path + owner)
    file_name_prefix = file_name[:file_name.find('.')]
    base = '/ndn/web/video'
    version = '1'
    segmentSize = '8000'
    chunker = (directory + 'chunker ' + base + '/' + file_name_prefix + ' -i '
               + pwd + '/' + file_name_prefix + ' -s '
               + segmentSize + ' -e ' + version + ' && wait')
    if driver_script_helper(chunker) == 0:
        print('chunked alreay in here')
        file_instance.set_status('chunked')
        dump_data(file_coll)
        write_record(file_instance)


def encode(file_name, file_instance, file_coll):
    encode = directory + env_path + '../../video/transcoder.sh ' + file_name + ' && wait'
    if driver_script_helper(encode) == 0:
        file_instance.set_status('encoded')
        dump_data(file_coll)
        write_record(file_instance)


def packaged(file_name, file_instance, file_coll):
    pwd = './'
    pwd1 = directory + env_path + "../../video/packager.sh"
    file_name_prefix = file_name[:file_name.find('.')]
    protocol = 'hls'
    playlist = 'playlist.m3u8'
    package = (pwd1+' ' + '.'+' ' + file_name_prefix + ' '
               + pwd + file_name_prefix + '/' + protocol + ' '
               + protocol + ' && wait')
    if driver_script_helper(package) == 0:
        file_instance.set_status('packaged')
        dump_data(file_coll)
        write_record(file_instance)


def html(file_name, file_instance, file_coll, judge):
    file_name_prefix = file_name[:file_name.find('.')]
    base = '/ndn/web/video'
    protocol = 'hls'
    playlist = 'playlist.m3u8'
    manifestUrl = base + '/' + file_name_prefix + '/' + protocol + '/' + playlist
    inputs = ('https://gist.githubusercontent.com/chavoosh/f7db8dc41c3e8bb8e6a058b1ea342b5a/raw'
              + '/cb9ea05b57f769f845398721f68c3f6f4b3b88ac/base.html')
    line = ('      <!-- manifest uri -->\n')
    line += '      ' + "'<span id= 'manifestUri' hidden>'"+manifestUrl + "'</span>\n\n'"
    line = '"' + line + '"'
    curl_one = (directory + 'curl ' + inputs + ' | ' + 'sed -n ' + "'0, /begin url section/p'"
                + ' > ' + file_name_prefix + '.html ' + '&& ' + 'printf '
                + line + ' >> ' + file_name_prefix + '.html')
    curl_two = (directory + 'curl ' + inputs + ' | ' + 'sed -n ' + "'/end url section/, $p'"
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
    if version == 'debug':
        write_rdebug_record(output)
   # print(output)
    print (process.returncode)
    return process.returncode


def update_token(creds):
    if creds.expired and creds.refresh_token:
        creds.refresh(Request())


def check_all_encode(prefix):
    count = 5
    real_count = check_encoded_number(prefix)
    if real_count != count:
        return False
    else:
        return True


def check_encoded_number(prefix):
    encoded_arr = [owner + '/' + prefix+'_h264_1080p.mp4', owner + '/' + prefix+'_h264_240p.mp4', owner +
                   '/'+prefix+'_h264_360p.mp4', owner + '/' + prefix+'_h264_480p.mp4', owner + '/' + prefix+'_h264_720p.mp4']
    num = 0
    for i in encoded_arr:
        if os.path.exists(i):
            num += 1
    return num


def check_status(file_coll, creds, items):
    global directory
    global owner
    for key in file_coll:
        for file_instance in file_coll[key]:
            owner = search_items(file_instance.get_parent(), items)
            directory = 'cd '+owner+' && '
            status = file_instance.get_status()
            name = file_instance.get_name()
            file_id = file_instance.get_id()
            web = name[:name.find('.')]+'.html'
            prefix = name[:name.find('.')]
            if status == 'initial':
                download(file_id, creds)
                file_instance.set_status("download")
                dump_data(file_coll)
                driver_script(name, file_instance, file_coll)

            elif status == 'download':
                # todo check if the file exist and process
                if os.path.exists(owner+'/'+name):
                    pass
                else:
                    download(file_id, creds)
                if check_encoded_number(prefix) > 0:
                    delete_encoder(name)
                driver_script(name, file_instance, file_coll)
            elif status == 'encoded':
                if check_all_encode(prefix):
                    pass
                else:
                    delete_encoder(name)
                    driver_script(name, file_instance, file_coll)
                    continue
                # in the middle of package
                if os.path.exists(owner + '/' + prefix):
                    delete_packager(name)
                packaged(name, file_instance, file_coll)
                chunker(name, file_instance, file_coll)
                html(name, file_instance, file_coll,True)

            elif status == 'packaged':
                if os.path.exists(owner + '/' + prefix):
                    pass
                else:
                    packaged(name, file_instance, file_coll)
                # todo wait for MongoDB stuff
                # in the middle of chunck
                chunker(name, file_instance, file_coll)
                html(name, file_instance, file_coll,True)

            elif status == 'chunked':
                # todo we need to check MongoDB before generate html
                # in the middle of html
                if os.path.exists(owner + '/' + web):
                    delete_html(name)
                html(name, file_instance, file_coll, True)
            # only one left is html but we need to have two
            else:
                if not os.path.exists(owner + '/' + web):
                    html(name, file_instance, file_coll, True)
                else:
                    if file_instance.get_status() == 'html and js first':
                        print("---------------")
                        html(name, file_instance, file_coll, False)


def delete(file_name):
    # delete it self
    file_name = owner + '/' + file_name
    print(file_name)
    if os.path.exists(file_name):
        os.remove(file_name)


def delete_packager(file_name):
    prefix = file_name[:file_name.find('.')]
    prefix = owner + '/' + prefix
    print(prefix)
    if os.path.exists(prefix):
        shutil.rmtree(prefix)


def delete_encoder(file_name):
    # delete the encoder
    prefix = file_name[:file_name.find('.')]
    encoded_arr = encoded_arr = [owner + '/' + prefix+'_h264_1080p.mp4', owner + '/' + prefix+'_h264_240p.mp4',
                                 owner + '/'+prefix+'_h264_360p.mp4', owner + '/' + prefix+'_h264_480p.mp4', owner + '/' + prefix+'_h264_720p.mp4']
    count = 5
    for i in range(0, count):
        print(encoded_arr[i])
        if os.path.exists(encoded_arr[i]):
            os.remove(encoded_arr[i])


def delete_html(file_name):
    prefix = file_name[:file_name.find('.')]
    prefix = owner + '/' + prefix
    html_file = prefix+'.html'
    print(html_file)
    if os.path.exists(html_file):
        os.remove(html_file)


def change_name(old, new):
    old_prefix = old[:old.find('.')]
    new_prefix = new[:new.find('.')]
    old_encoded_arr = [owner + '/' + old_prefix+'_h264_1080p.mp4', owner+'/' + old_prefix+'_h264_240p.mp4', owner +
                       '/'+old_prefix+'_h264_360p.mp4', owner+'/'+old_prefix+'_h264_480p.mp4', owner+'/'+old_prefix+'_h264_720p.mp4']
    new_encoded_arr = [owner + '/'+new_prefix+'_h264_1080p.mp4', owner+'/'+new_prefix+'_h264_240p.mp4', owner +
                       '/'+new_prefix+'_h264_360p.mp4', owner+'/'+new_prefix+'_h264_480p.mp4', owner+'/'+new_prefix+'_h264_720p.mp4']
    # name of file replacement
    os.rename(owner + '/' + old, owner + '/' + new)
    # encoder replacement
    for i in range(0, 5):
        os.rename(old_encoded_arr[i], new_encoded_arr[i])
    # package replacement
    os.rename(owner + '/' + old_prefix, owner + '/' + new_prefix)
    # html replacement
    os.rename(owner + '/' + old_prefix + '.html',
              owner + '/' + new_prefix+'.html')


def search_items(id, items):
    for item in items:
        item = item.split('\n')[:-1]
        file_id = item[0][item[0].find(':')+2:]
        name = item[1][item[1].find(':')+2:]
        if id == file_id:
            return name


def process(creds):
    # gdrive stuff to get meta data from each file
    global owner
    global directory
    update_token(creds)
    g = u'gdrive --access-token ' + creds.token + u' list'
    process = subprocess.Popen(g, shell=True, stdout=subprocess.PIPE)
    output, err = process.communicate()
    output_list = output.split('\n')[1:-1]
    items = []
    for file_info in output_list:
        file_id = file_info.split()[0]
       # file_id = file_id.encode("utf-8")
        update_token(creds)
        g = u'gdrive --access-token '+creds.token + u' info ' + file_id
        process = subprocess.Popen(g, shell=True, stdout=subprocess.PIPE)
        output, err = process.communicate()
        items.append(output)
    file_coll = None
    if os.path.exists(env_path + 'data-s'):
        with open(env_path + 'data-s', 'rb') as token:
            file_coll = pickle.load(token)
            print(file_coll)
        check_status(file_coll, creds, items)
        # print(file_coll)
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
            item = item.split('\n')[:-1]
            file_id = item[0][item[0].find(':')+2:]
            name = item[1][item[1].find(':')+2:]
            mime_type = item[3][item[3].find(':')+2:]
           # print(name,time,parent,file_id,mime_type,file_id)
            if mime_type == 'application/vnd.google-apps.folder':
                if file_id not in file_coll:
                    file_coll[file_id] = []
                    if not os.path.exists(name):
                        os.mkdir(name)
                continue
            if mime_type.find('video') == -1:
                continue
            time = item[6][item[6].find(':')+2:]
            parent = item[9][item[9].find(':')+2:]
           # print('80th   ' + parent)
            file_instance = myFile(
                name, file_id, mime_type, dateutil.parser.parse(time), 'initial', parent)
            compare_coll.append(file_instance)
            # this folder is here
            if parent in file_coll:
                record = file_coll[parent]
                find = False
                for re in record:
                    if re == file_instance:
                        find = True
                        # user modifies the name of file
                        if file_instance.get_time() > re.get_time():
                            old_name = re.get_name()
                            change = True
                            re.set_time(file_instance.get_time())
                            re.set_name(file_instance.get_name())
                            re.set_status('change name from ' + old_name)
                            dump_data(file_coll)
                            write_record(re)
                            print("97th")
                            owner = search_items(parent, items)
                            print(owner)
                            directory = 'cd '+owner+' && '
                            change_name(old_name, file_instance.get_name())
                if not find:
                    # new file insert into this folder
                    owner = search_items(parent, items)
                    directory = 'cd '+owner+' && '
                    file_coll[parent].append(file_instance)
                    dump_data(file_coll)
                    write_record(file_instance)
                    print("101th")
                    rv = download(file_id, creds)
                    if rv == 0:
                        file_instance.set_status("download")
                        dump_data(file_coll)
                        write_record(file_instance)
                        driver_script(name, file_instance, file_coll)
            # create the new folder and insert the file into it
            else:
                file_coll[parent] = []
                file_coll[parent].append(file_instance)
                owner = search_items(parent, items)
                if not os.path.exists(owner):
                    os.mkdir(owner)
                directory = 'cd '+owner+' && '
                # when it is initial
                dump_data(file_coll)
                write_record(file_instance)
                print("106th")
                print(directory)
                rv = download(file_id, creds)
                if rv == 0:
                    file_instance.set_status("download")
                    dump_data(file_coll)
                    write_record(file_instance)
                    driver_script(name, file_instance, file_coll)

    for key in file_coll:
        for fi in file_coll[key][:]:
            if fi in compare_coll:
                continue
                # copy[key].append(fi)
            else:
                delete_name = fi.get_name()
                owner = search_items(fi.get_parent(),items)
                directory = 'cd '+owner+' && '
                delete(delete_name)
                delete_encoder(delete_name)
                delete_packager(delete_name)
                delete_html(delete_name)
                fi.set_status('deleted')
                write_record(fi)
                file_coll[key].remove(fi)
                dump_data(file_coll)

    # write_record(file_coll)


def start():
    creds = None
    count = 0
    #pwd = os.path.abspath('../')
    # print(pwd)
    print(env)
    while True:
        if count == 0:
            """
            Netwrok stuff to get token with google drive server
            """
            if os.path.exists(env_path + 'token.pickle'):
                with open(env_path + 'token.pickle', 'rb') as token:
                    creds = pickle.load(token)
            if not creds or not creds.valid:
                if creds and creds.expired and creds.refresh_token:
                    creds.refresh(Request())
                else:
                    flow = InstalledAppFlow.from_client_secrets_file(
                        env_path + 'credapi.json', SCOPES)
                    creds = flow.run_local_server(port=0)
            with open(env_path + 'token.pickle', 'wb') as token:
                pickle.dump(creds, token)
        process(creds)
        count += 1


env_path = ''
env = os.path.abspath('./')
env = env.split('/')[-1]
if env == 'test':
    env_path = '../'
parser = argparse.ArgumentParser(prog='ndn_script.py')
parser.add_argument('-v', choices=['info', 'debug'], metavar='version',
                    nargs=1, help='valid version should be info or debug')
result = parser.parse_args(sys.argv[1:])
if result.v == None:
    parser.print_help(sys.stderr)
    sys.exit(1)
version = result.v

owner = ''
directory = ''
start()
