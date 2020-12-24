# Bluetooh mesh node demo user guide

This demo code button pin is IO12. Please add the following setting to corresponding dts file ：this node feature is " button" and mode is " multipress".  this node will trigger three event , customer can set "press time" setting.

 This mesh node default provision mode is PB-GATT.   This demo has two button event:

1. short press: enable unprovisioned advertising (PB-GATT).

2. long press : reset node.

```c
gpio2 {
    status = "okay";
    pin = <12>;
    feature = "button";
    active = "Hi";
    mode = "multipress";
    button {
        debounce = <10>;
        short_press_ms {
            start = <100>;
            end = <2000>;
            kevent = <2>;
        };
        long_press_ms {
            start = <3000>;
            end = <5000>;
            kevent = <3>;
        };
        longlong_press_ms {
            start = <10000>;
            kevent = <4>;
        };
        trig_level = "Lo";
    };
    hbn_use = "disable";
};
```





   