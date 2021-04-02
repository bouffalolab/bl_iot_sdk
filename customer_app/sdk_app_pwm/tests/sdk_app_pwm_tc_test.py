from __future__ import print_function
from __future__ import unicode_literals
import time
import re
import pigpio
import math
from tiny_test_fw import DUT, App, TinyFW
from ttfw_bl import BL602App, BL602DUT

class reader:
   def __init__(self, pi, gpio, weighting=0.0):
      """
      Instantiate with the Pi and gpio of the PWM signal
      to monitor.

      Optionally a weighting may be specified.  This is a number
      between 0 and 1 and indicates how much the old reading
      affects the new reading.  It defaults to 0 which means
      the old reading has no effect.  This may be used to
      smooth the data.
      """
      self.pi = pi
      self.gpio = gpio

      if weighting < 0.0:
         weighting = 0.0
      elif weighting > 0.99:
         weighting = 0.99

      self._new = 1.0 - weighting # Weighting for new reading.
      self._old = weighting       # Weighting for old reading.

      self._high_tick = None
      self._period = None
      self._high = None

      pi.set_mode(gpio, pigpio.INPUT)

      self._cb = pi.callback(gpio, pigpio.EITHER_EDGE, self._cbf)

   def _cbf(self, gpio, level, tick):

      if level == 1:

         if self._high_tick is not None:
            t = pigpio.tickDiff(self._high_tick, tick)

            if self._period is not None:
               self._period = (self._old * self._period) + (self._new * t)
            else:
               self._period = t

         self._high_tick = tick

      elif level == 0:

         if self._high_tick is not None:
            t = pigpio.tickDiff(self._high_tick, tick)

            if self._high is not None:
               self._high = (self._old * self._high) + (self._new * t)
            else:
               self._high = t

   def frequency(self):
      """
      Returns the PWM frequency.
      """
      if self._period is not None:
         return 1000000.0 / self._period
      else:
         return 0.0

   def pulse_width(self):
      """
      Returns the PWM pulse width in microseconds.
      """
      if self._high is not None:
         return self._high
      else:
         return 0.0

   def duty_cycle(self):
      """
      Returns the PWM duty cycle percentage.
      """
      if self._high is not None:
         return 100.0 * self._high / self._period
      else:
         return 0.0

   def cancel(self):
      """
      Cancels the reader and releases resources.
      """
      self._cb.cancel()

@TinyFW.test_method(app=BL602App.BL602App, dut=BL602DUT.BL602TyMbDUT, test_suite_name='sdk_app_pwm_tc')
def sdk_app_pwm_tc(env, extra_data):
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

        dut.write('hal_pwm_init 2')
        time.sleep(0.5)
        dut.write('hal_pwm_duty_set 2 1000 0')
        time.sleep(0.5)
        dut.write('hal_pwm_duty_get 2')
        dut.expect('pwm duty 1000', timeout=1)
        
        PWM_GPIO = 4
        RUN_TIME = 30.0
        SAMPLE_TIME = 2.0

        pi = pigpio.pi()
        p = reader(pi, PWM_GPIO)
        start = time.time()

        while (time.time() - start) < RUN_TIME:
            time.sleep(SAMPLE_TIME)
            f = p.frequency()
            pw = p.pulse_width()
            dc = p.duty_cycle()
            print("f={:.1f} pw={} dc={:.2f}".format(f, int(pw+0.5), dc))
            if math.fabs(dc - 10.0) > 2.0:
                raise Exception
        p.cancel()
        pi.stop()

        dut.halt()
    except Exception:
        print('ENV_TEST_FAILURE: BL602 example test failed')
        raise


if __name__ == '__main__':
    sdk_app_pwm_tc()
