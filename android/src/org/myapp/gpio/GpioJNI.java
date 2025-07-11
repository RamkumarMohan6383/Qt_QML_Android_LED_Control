package org.myapp.gpio;
public class GpioJNI {
    static {
        System.loadLibrary("gpiojni");
    }
    public static native void gpioWrite(int pin, int value);  // ✅ static
    public static native void gpioPWM(int pin, int duty);     // ✅ static
    public static native void setGpioPermission();
}
