from __future__ import print_function
from __future__ import unicode_literals
import time
import re
import os

from tiny_test_fw import DUT, App, TinyFW
from ttfw_bl import BL602App, BL602DUT


@TinyFW.test_method(app=BL602App.BL602App, dut=BL602DUT.BL602TyMbDUT, test_suite_name='bl602_demo_joylink_tc')
def bl602_demo_joylink_tc(env, extra_data):
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

        dut.write('wifi_ap_stop')
        time.sleep(1)
        dut.write('jltc_memory')
        dut.expect('jl_tc_memory SUCCESS', timeout=1)
        
        dut.write('jltc_stdio')
        dut.expect('jl_tc_stdio SUCCESS', timeout=60)
       
        bssid = os.getenv('TEST_ROUTER_SSID')
        pwd = os.getenv('TEST_ROUTER_PASSWORD')
        cmd = ("wifi_sta_connect", bssid, pwd)
        cmd_wifi_connect = ' '.join(cmd)
        dut.write(cmd_wifi_connect)
        #dut.write('wifi_sta_connect bl_test_026 12345678')
        dut.expect("Entering wifiConnected_IPOK state", timeout=30)

        dut.write('jltc_socket')
        dut.expect('jl_tc_socket SUCCESS', timeout=10)
 
        dut.write('jltc_extern')
        dut.expect('jl_tc_extern_task SUCCESS', timeout=10)
  
        dut.write('jltc_time')
        dut.expect('jl_tc_time SUCCESS', timeout=10)

        dut.write('jl_dump_jlp')
        dut.expect('.isUsed', timeout=10)

        dut.halt()
    except DUT.ExpectTimeout:
        print('ENV_TEST_FAILURE: BL602 wifi test failed')
        raise


if __name__ == '__main__':
    bl602_demo_joylink_tc()
