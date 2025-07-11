#include "gpio_mmio.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <android/log.h>

#define TAG "GPIOJNI"
#define GPIO_BASE 0xFE200000  // Pi 4
#define BLOCK_SIZE 4096

static volatile uint32_t* gpio_map = nullptr;

void setup_gpio_mmap() {
    if (gpio_map != nullptr)
        return;

    int mem_fd = open("/dev/gpiomem", O_RDWR | O_SYNC);
    if (mem_fd < 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "Failed to open /dev/gpiomem");
        return;
    }

    void* map = mmap(nullptr, BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, 0);
    if (map == MAP_FAILED) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "mmap failed");
        close(mem_fd);
        return;
    }

    gpio_map = reinterpret_cast<volatile uint32_t*>(map);
    close(mem_fd);
}

void set_gpio_output(int gpio) {
    setup_gpio_mmap();
    if (!gpio_map) return;

    int reg = gpio / 10;
    int shift = (gpio % 10) * 3;
    gpio_map[reg] = (gpio_map[reg] & ~(7 << shift)) | (1 << shift);
}

void write_gpio(int gpio, int value) {
    setup_gpio_mmap();
    if (!gpio_map) return;

    if (value)
        gpio_map[7] = 1 << gpio;  // GPSET0
    else
        gpio_map[10] = 1 << gpio; // GPCLR0
}
