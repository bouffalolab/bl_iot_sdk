from __future__ import print_function
from __future__ import unicode_literals
from bluepy import btle
import time
import re
import os
import subprocess
from tiny_test_fw import DUT, App, TinyFW
from ttfw_bl import BL602App, BL602DUT


@TinyFW.test_method(app=BL602App.BL602App, dut=BL602DUT.BL602TyMbDUT, test_suite_name='bl602_demo_event_RPI_ble_wifi_tc')
def bl602_demo_event_RPI_ble_wifi_tc(env, extra_data):
    # first, flash dut
    # then, test
    dut = env.get_dut("port0", "fake app path")
    print('Flashing app')
    dut.flash_app(env.log_path, env.get_variable('flash'))
    print('Starting app')
    dut.start_app()

    try:
        dut.expect("Booting BL602 Chip...", timeout=0.5)
        print('BL602 booted')
        dut.expect('Init CLI with event Driven', timeout=0.5)
        print('BL602 CLI init done')
        time.sleep(0.1)

        dut.write('stack_ble')
        time.sleep(0.5)
        bd_addr = dut.expect(re.compile(r"BD_ADDR:(.*)"), timeout=2)
        print(f'bd_addr is {bd_addr[0]}')
        dut.write('ble_init')
        dut.expect("Init successfully", timeout=1)
        dut.write('ble_auth')
        dut.expect("Register auth callback successfully", timeout=1)
        dut.write('ble_start_adv 0 0 0x80 0x80')
        dut.expect("Advertising started", timeout=1)
        
        dut.write('ble_read_local_address')
        local_addr = dut.expect(re.compile(r"Local public addr : (.*) "), timeout=2)
        print(f'Local public addr {local_addr[0]}')
        # scan bluetooth
        
        rst = scan_device(local_addr[0])
        if rst != True:
            raise Exception
        else:
            print("scan success!")
            connect_device(local_addr[0])
            time.sleep(1)
            dut.expect("Connected", timeout=1)
            print("connect success!")
        dut.write('stack_wifi')
        time.sleep(0.5)
        bssid = os.getenv('TEST_ROUTER_SSID')
        pwd = os.getenv('TEST_ROUTER_PASSWORD')
        cmd = ("wifi_sta_connect", bssid, pwd)
        cmd_wifi_connect = ' '.join(cmd)
        dut.write(cmd_wifi_connect)
        #dut.write('wifi_sta_connect bl_test_027 12345678')
        dut.expect("Entering wifiConnected_IPOK state", timeout=10)

        print('To reboot BL602')
        dut.write('reboot')
        dut.expect("Booting BL602 Chip...", timeout=0.5)
        print('BL602 rebooted')
        time.sleep(0.2)

        dut.write('stack_wifi')
        time.sleep(0.5)
        bssid = os.getenv('TEST_ROUTER_SSID')
        pwd = os.getenv('TEST_ROUTER_PASSWORD')
        cmd = ("wifi_sta_connect", bssid, pwd)
        cmd_wifi_connect = ' '.join(cmd)
        dut.write(cmd_wifi_connect)
        #dut.write('wifi_sta_connect bl_test_027 12345678')
        dut.expect("Entering wifiConnected_IPOK state", timeout=10)

        dut.write('stack_ble')
        time.sleep(0.5)
        dut.write('ble_init')
        dut.expect("Init successfully", timeout=1)
        dut.write('ble_auth')
        dut.expect("Register auth callback successfully", timeout=1)
        dut.write('ble_start_adv 0 0 0x80 0x80')
        dut.expect("Advertising started", timeout=1)
        
        dut.write('ble_read_local_address')
        local_addr = dut.expect(re.compile(r"Local public addr : (.*) "), timeout=2)
        print(f'Local public addr is {local_addr[0]}')
        rst = scan_device(local_addr[0])
        if rst != True:
            raise Exception
        else:
            print("scan success!")
            connect_device(local_addr[0])
            time.sleep(1)
            dut.expect("Connected", timeout=1)
            print("connect success!")
        dut.halt()
    except Exception:
        print('ENV_TEST_FAILURE: BL602 ble_wifi test failed')
        raise

def scan_device(mac):
    rst = []
    result_list = []
    p = subprocess.Popen('timeout -s INT 10s hcitool lescan', shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    line_list = p.stdout.readlines()
    print(line_list)
    for line in line_list:
        if line != b'':
            try:
                result_list = line.decode('utf-8').split('\n')
            except:
                result_list = line.decode('gbk').split('\n')
            
            finally:
                rst = rst + result_list

    device_dict = {}
    for device in rst:
        if device.find(':') != -1:
            key = device[0:17].strip()
            value = device[18:].strip()
            device_dict[key] = value
    try:
        device_name = device_dict[mac]
        print("mac:{}, name:{}".format(mac, device_name))
        return True
    except KeyError:
        return False

def connect_device(mac):
    
    conn = btle.Peripheral(mac, "public")
    print("BLE is connected")
    #conn.disconnect()
    #print("BLE is disconnected")

if __name__ == '__main__':
    bl602_demo_event_RPI_ble_wifi_tc()
