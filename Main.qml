import QtQuick 2.15
import QtQuick.Controls 2.15
import My.Gpio 1.0

ApplicationWindow {
    visible: true
    width: 400
    height: 300
    title: qsTr("LED Controller")

    GpioController {
        id: gpio
    }

    Column {
        spacing: 20
        anchors.centerIn: parent

        Slider {
            id: pwmSlider
            from: 0
            to: 100
            value: 50
        }

        Button {
            text: "Set PWM"
            onClicked: gpio.gpioPWM(12, pwmSlider.value)
        }

        Button {
            text: "LED ON"
            onClicked: gpio.gpioWrite(12, 1)
        }

        Button {
            text: "LED OFF"
            onClicked: gpio.gpioWrite(12, 0)
        }

    }
}
