#include <jni.h>
#include <unistd.h>
#include <android/log.h>
#include "gpio_mmio.h"  // Include the GPIO header

extern "C" {

JNIEXPORT void JNICALL Java_org_myapp_gpio_GpioJNI_gpioWrite
    (JNIEnv* env, jclass clazz, jint pin, jint value) {
    __android_log_print(ANDROID_LOG_INFO, "GPIOJNI", "gpioWrite called: pin=%d, value=%d", pin, value);
    set_gpio_output(pin);
    write_gpio(pin, value);
}

JNIEXPORT void JNICALL Java_org_myapp_gpio_GpioJNI_gpioPWM
    (JNIEnv* env, jclass clazz, jint pin, jint dutyCycle) {
    set_gpio_output(pin);
    for (int i = 0; i < 100; ++i) {
        write_gpio(pin, 1);
        usleep(dutyCycle * 100);
        write_gpio(pin, 0);
        usleep((100 - dutyCycle) * 100);
    }
}

}
