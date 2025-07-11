cmake_minimum_required(VERSION 3.16)
project(New_Control VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appNew_Control
    main.cpp
)

qt_add_qml_module(appNew_Control
    URI New_Control
    VERSION 1.0
    QML_FILES
        Main.qml
    SOURCES
        GpioController/gpiocontroller.cpp
        GpioController/gpiocontroller.h
)

target_link_libraries(appNew_Control PRIVATE Qt6::Quick)

# JNI native library
add_library(gpiojni SHARED
    jni/jni_gpio.cpp
    jni/gpio_mmio.cpp
    jni/gpio_mmio.h
)

set_target_properties(gpiojni PROPERTIES
    OUTPUT_NAME "gpiojni"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/android/libs/${ANDROID_ABI}"
)

target_include_directories(gpiojni PRIVATE
    ${CMAKE_SYSROOT}/usr/include
)

target_link_libraries(gpiojni PRIVATE
    android
    log
)

set_property(TARGET appNew_Control APPEND PROPERTY
    QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android
)
