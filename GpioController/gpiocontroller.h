#ifndef GPIOCONTROLLER_H
#define GPIOCONTROLLER_H

#include <QObject>

class GpioController : public QObject
{
    Q_OBJECT
public:
    explicit GpioController(QObject *parent = nullptr);
    Q_INVOKABLE void gpioWrite(int pin, int value);
    Q_INVOKABLE void gpioPWM(int pin, int dutyCycle);
};

#endif // GPIOCONTROLLER_H
