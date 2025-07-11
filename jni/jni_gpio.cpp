#include <jni.h>
#include <unistd.h>
#include <thread>
#include <atomic>
#include <android/log.h>
#include "gpio_mmio.h"

static std::atomic<bool> pwm_running(false);
static std::thread pwm_thread;
static int current_duty = 50;
static int current_pin = -1;

extern "C" {

JNIEXPORT void JNICALL Java_org_myapp_gpio_GpioJNI_setGpioPermission(JNIEnv*, jclass) {
    __android_log_print(ANDROID_LOG_INFO, "GPIOJNI", "Requesting root chmod...");
    int result = system("su -c \"chmod 666 /dev/gpiomem\"");
    if (result == 0) {
        __android_log_print(ANDROID_LOG_INFO, "GPIOJNI", "chmod successful.");
    } else {
        __android_log_print(ANDROID_LOG_ERROR, "GPIOJNI", "chmod failed or su not available.");
    }
}

JNIEXPORT void JNICALL Java_org_myapp_gpio_GpioJNI_gpioPWM(JNIEnv*, jclass, jint pin, jint dutyCycle) {
    current_pin = pin;
    current_duty = dutyCycle;
    set_gpio_output(pin);
    __android_log_print(ANDROID_LOG_INFO, "GPIOJNI", "PWM Set: pin=%d, duty=%d", pin, dutyCycle);
}

JNIEXPORT void JNICALL Java_org_myapp_gpio_GpioJNI_gpioWrite(JNIEnv*, jclass, jint pin, jint value) {
    set_gpio_output(pin);

    if (value == 1 && current_duty > 0) {
        __android_log_print(ANDROID_LOG_INFO, "GPIOJNI", "Starting PWM Thread: pin=%d, duty=%d", pin, current_duty);
        pwm_running = true;
        if (pwm_thread.joinable()) pwm_thread.join(); // Ensure any old thread is done

        pwm_thread = std::thread([=]() {
            while (pwm_running) {
                write_gpio(pin, 1);
                usleep(current_duty * 100);  // High time
                write_gpio(pin, 0);
                usleep((100 - current_duty) * 100);  // Low time
            }
            write_gpio(pin, 0); // Make sure LED is off when exiting
        });
    } else {
        __android_log_print(ANDROID_LOG_INFO, "GPIOJNI", "Stopping PWM Thread: pin=%d", pin);
        pwm_running = false;
        if (pwm_thread.joinable())
            pwm_thread.join();
        write_gpio(pin, 0);  // Ensure LED is OFF
    }
}
}
