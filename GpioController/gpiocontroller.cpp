#include "gpiocontroller.h"
#include <jni.h>
#include <QJniObject>
#include <QJniEnvironment>

GpioController::GpioController(QObject *parent) : QObject(parent) {}

void GpioController::gpioWrite(int pin, int value) {
    QJniObject::callStaticMethod<void>(
        "org/myapp/gpio/GpioJNI",
        "gpioWrite",
        "(II)V",
        pin, value
        );
}

void GpioController::gpioPWM(int pin, int dutyCycle) {
    QJniObject::callStaticMethod<void>(
        "org/myapp/gpio/GpioJNI",
        "gpioPWM",
        "(II)V",
        pin, dutyCycle
        );
}

void GpioController::setGpioPermission() {
    QJniObject::callStaticMethod<void>(
        "org/myapp/gpio/GpioJNI",
        "setGpioPermission",
        "()V"
        );
}
