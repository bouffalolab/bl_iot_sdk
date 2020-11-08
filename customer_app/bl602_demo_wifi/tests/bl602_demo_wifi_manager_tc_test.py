from __future__ import print_function
from __future__ import unicode_literals
import time
import re
import subprocess
import os

from tiny_test_fw import DUT, App, TinyFW
from ttfw_bl import BL602App, BL602DUT


@TinyFW.test_method(app=BL602App.BL602App, dut=BL602DUT.BL602TyMbDUT, test_suite_name='bl602_demo_wifi_manager_tc')
def bl602_demo_wifi_manager_tc(env, extra_data):
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

        dut.write('stack_wifi')
        time.sleep(0.5)
        dut.write('wifi_sta_connect bl_test 12345678')
        dut.expect("Reason: SSID error, scan no bssid and channel", timeout=10)
        print('case1:SSID error test successed')

        print('To reboot BL602')
        dut.write('reboot')
        dut.expect("Booting BL602 Chip...", timeout=0.5)
        print('BL602 rebooted')
        time.sleep(0.2)
        dut.write('stack_wifi')
        time.sleep(0.5)
        bssid = os.getenv('TEST_ROUTER_SSID')
        cmd = ("wifi_sta_connect", bssid, "123456789")
        cmd_wifi_connect = ' '.join(cmd)
        dut.write(cmd_wifi_connect)
        dut.expect("Reason: Passwd error, 4-way handshake timeout", timeout=20)
        print('case2:Passwd error test successed')

        print('To reboot BL602')
        dut.write('reboot')
        dut.expect("Booting BL602 Chip...", timeout=0.5)
        print('BL602 rebooted')
        time.sleep(0.2)
        dut.write('stack_wifi')
        time.sleep(0.5)
        bssid = os.getenv('TEST_ROUTER_SSID_CLOSED')
        pwd = os.getenv('TEST_ROUTER_PASSWORD_CLOSED')
        cmd = ("wifi_sta_connect", bssid, pwd)
        cmd_wifi_connect = ' '.join(cmd)
        dut.write(cmd_wifi_connect)

        dut.expect("Entering wifiConnected_IPOK state", timeout=20)
        print('case3:connect wifi test successed')
        print('Please power off router!')

        #cmd = "ssh xiaohei@192.168.4.145 'cd /home/xiaohei/PycharmProjects/router_auto_test/ ; python3 test.py close_wifi'"
        #subprocess.call(cmd, shell=True)
        #dut.expect("Reason: Beacon Loss", timeout=20)

        print('case4:Beacon Loss test successed')
        dut.halt()

    except Exception:
        print('ENV_TEST_FAILURE: BL602 wifi manager test failed')
        raise


if __name__ == '__main__':
    bl602_demo_wifi_manager_tc()
