from __future__ import print_function
from __future__ import unicode_literals
import time
import re
import serial  
from tiny_test_fw import DUT, App, TinyFW
from ttfw_bl import BL602App, BL602DUT


@TinyFW.test_method(app=BL602App.BL602App, dut=BL602DUT.BL602TyMbDUT, test_suite_name='sdk_app_uart_echo_tc')
def sdk_app_uart_echo_tc(env, extra_data):
    # first, flash dut
    # then, test
    dut = env.get_dut("port0", "fake app path")
    print('Flashing app')
    dut.flash_app(env.log_path, env.get_variable('flash'))
    print('Starting app')
    dut.start_app()

    try:

        ser = serial.Serial('/dev/ttyUSB2', 115200, timeout=0.5)   
        time.sleep(1)
        #dut.write('reboot')
        dut.expect("Booting BL602 Chip...", timeout=1)
        print('BL602 booted')
        dut.expect('Init CLI with event Driven', timeout=1)
        print('BL602 CLI init done')

        data = ser.read(17)
        time.sleep(0.5)
        print(data)
        recv_str = str(data, encoding = 'utf-8')
        if recv_str == '1234567890abcdefg':
            ser.write(data)
        time.sleep(0.5)

        dut.expect('recvbuff:', timeout=1)
        dut.halt()
    except DUT.ExpectTimeout:
        print('ENV_TEST_FAILURE: BL602 uart echo test failed')
        raise


if __name__ == '__main__':
    sdk_app_uart_echo_tc()
