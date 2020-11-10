from __future__ import print_function
from __future__ import unicode_literals
import socket,fcntl,struct,psutil
import time
import re
import os
import subprocess,signal
from tiny_test_fw import DUT, App, TinyFW
from ttfw_bl import BL602App, BL602DUT


@TinyFW.test_method(app=BL602App.BL602App, dut=BL602DUT.BL602TyMbDUT, test_suite_name='bl602_demo_wifi_ota_tc')
def bl602_demo_wifi_ota_tc(env, extra_data):
    # first, flash dut
    # then, test
    dut = env.get_dut("port0", "fake app path")
    print('Flashing app')
    dut.flash_app(env.log_path, env.get_variable('flash'))
    print('Starting app')
    dut.start_app()

    try:
        nc = False
        cat = False
        dut.expect("Booting BL602 Chip...", timeout=0.5)
        print('BL602 booted')
        #dut.expect('Init CLI with event Driven', timeout=0.5)
        #print('BL602 CLI init done')
        time.sleep(0.1)
        list_all = dut.expect(re.compile(r'======= PtTable_Config([\s\S]*?)======= FlashCfg magiccode'), timeout=4)
        rst_str = 'FW  (.*)  (.*)  (.*)  (.*)  (.*)'
        dev1 = re.search(rst_str, list_all[0])
        if (dev1 != None) :
            old_age = int(dev1.group(5))
            print(old_age)

        print(dev1)
        dut.write('stack_wifi')
        time.sleep(0.5)
        bssid = os.getenv('TEST_ROUTER_SSID')
        pwd = os.getenv('TEST_ROUTER_PASSWORD')
        cmd = ("wifi_sta_connect", bssid, pwd)
        cmd_wifi_connect = ' '.join(cmd)
        dut.write(cmd_wifi_connect)
        dut.expect("Entering wifiConnected_IPOK state", timeout=30)

        #get host ip

        ip = get_ip_address(bytes('eth0', encoding = "utf8"))
        print(ip)
        path = os.getcwd()
        path = os.path.abspath('../../../../..')
        print(path)
        ota_path = path + '/tools/flash_tool/bl602/ota'
        p = subprocess.Popen('cat FW_OTA.bin.xz.ota | nc -l 3333', shell=True, cwd=ota_path)
        print(p.pid)

        cmd = 'ota_tcp' + ' ' + ip
        dut.write(cmd)
        time.sleep(0.5)
        dut.expect("Update PARTITION", timeout=20)
        time.sleep(10)
        dut.expect("Booting BL602 Chip...", timeout=0.5)
        list_all = dut.expect(re.compile(r'======= PtTable_Config([\s\S]*?)======= FlashCfg magiccode'), timeout=4)
        rst_str = 'FW  (.*)  (.*)  (.*)  (.*)  (.*)'
        dev1 = re.search(rst_str, list_all[0])
        if (dev1 != None) :
            new_age = int(dev1.group(5))
            print(new_age)
        else:
            raise Exception("no match")

        if new_age != old_age + 2:
            raise Exception("ota failed")

        #os.killpg(os.getpgid(p.pid),9)
        nc=processinfo('nc')
        cat=processinfo('cat')

        if (nc) :
            os.kill(int(nc), signal.SIGKILL)
            nc = False
        if (cat) :
            os.kill(int(cat), signal.SIGKILL)
            cat = False
        p.kill()
        dut.halt()
    except Exception:
        #os.killpg(os.getpgid(p.pid),9)
        if (nc) :
            os.kill(int(nc), signal.SIGKILL)
        if (cat) :
            os.kill(int(cat), signal.SIGKILL)
        p.kill()
        print('ENV_TEST_FAILURE: BL602 ota test failed')
        raise

def processinfo(processName):
    pids = psutil.pids()
    for pid in pids:
        #print(pid)
        p = psutil.Process(pid)
        #print(p.name)
        if p.name() == processName:
            #print(pid)
            return pid
    print(processName)
    return False

def get_ip_address(ifname):
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    ip=fcntl.ioctl(s.fileno(),0x8915,struct.pack('256s', ifname[:15]))
    return socket.inet_ntoa(ip[20:24])

if __name__ == '__main__':
    bl602_demo_wifi_ota_tc()
