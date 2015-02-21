/* 
 * File:   pi_gpio.h
 * Author: deema
 *
 * Created on January 25, 2015, 9:53 PM
 */

#ifndef PI_GPIO_H
#define	PI_GPIO_H

#include <stdint.h>

#define PIN_INPUT  0 // 000
#define PIN_OUTPUT 1 // 001
#define PIN_ALT0   4 // 100
#define PIN_ALT1   5 // 101
#define PIN_ALT2   6 // 110
#define PIN_ALT3   7 // 111
#define PIN_ALT4   3 // 011
#define PIN_ALT5   2 // 010

typedef struct _gpio_registers_t {

    union {

       struct {
            uint32_t gpfsel0;
            uint32_t gpfsel1;
            uint32_t gpfsel2;
            uint32_t gpfsel3;
            uint32_t gpfsel4;
            uint32_t gpfsel5;
        };

        uint32_t gpfsel[6];
    };

    // offset: 18; Reserved
    uint32_t reserved0;

    // GPSET
    union {

        struct {
            // offset: 1C; GPSET0
            uint32_t gpset0;
            // offset: 20; GPSET1
            uint32_t gpset1;
        };

        uint32_t gpset[2];
    };

    // offset: 24; Reserved
    uint32_t reserved1;

    // GPCLR
    union {

        struct {
            // offset: 28; GPCLR0
            uint32_t gpclr0;
            // offset: 2C; GPCLR1
            uint32_t gpclr1;
        };

        uint32_t gpclr[2];
    };

    // offset: 30; Reserved
    uint32_t reserved2;

    // GPLEV
    union {

        struct {
            // offset: 34; GPLEV0
            uint32_t gplev0;
            // offset: 38; GPLEV1
            uint32_t gplev1;
        };

        uint32_t gplev[2];
    };

    // offset: 3C; Reserved
    uint32_t reserved3;

    // offset: 40; GPEDS0
    // offset: 44; GPEDS1
    //GPIO_BIT_REG(eds);
    // offset: 48; Reserved
    uint32_t reserved4;

    // offset: 4C; GPREN0
    // offset: 50; GPREN1
    // offset: 54; Reserved
    uint32_t reserved5;

    // offset: 58; GPFEN0
    // offset: 5C; GPFEN1
    // offset: 60; Reserved
    uint32_t reserved6;

    // offset: 64; GPHEN0
    // offset: 68; GPHEN1
    // offset: 6C; Reserved
    uint32_t reserved7;

    // offset: 70; GPLEN0
    // offset: 74; GPLEN1
    // offset: 78; Reserved
    uint32_t reserved8;

    // offset: 7C; GPAREN0
    // offset: 80; GPAREN1
    // offset: 84; Reserved
    uint32_t reserved9;

    // offset: 88; GPAFEN0
    // offset: 8C; GPAFEN1
    // offset: 90; Reserved
    uint32_t reservedA;

    // offset: 94; GPPUD
    // offset: 98; GPPUDCLK0
    // offset: 9C; GPPUDCLK1

    // offset: A0; Reserved
    // offset: B0; Test
} gpio_registers_t;

#ifndef PI_GPIO_LIB
extern
#endif
volatile gpio_registers_t *gpio_registers;

#define OFFSET_OF(struct_t, _field) \
    (uint8_t*)(&(((struct_t*)NULL)->_field)) - (uint8_t*)((struct_t*)NULL)

#define _pi_gpio_fsel(pin, func)                                \
    do {                                                        \
        uint32_t gpfselx = gpio_registers->gpfsel[(pin) / 10];  \
        gpfselx &= ~((7) << (((pin) % 10) * 3));                \
        gpfselx |= (func) << (((pin) % 10) * 3);                \
        gpio_registers->gpfsel[(pin) / 10] = gpfselx;           \
    } while(0);

#define _pi_gpio_set(pin) \
    gpio_registers->gpset[(pin) >> 5] = 1 << ((pin) & 0x1F)

#define _pi_gpio_clr(pin) \
    gpio_registers->gpclr[(pin) >> 5] = 1 << ((pin) & 0x1F)

#define _pi_gpio_lev(pin) \
    (gpio_registers->gplev[(pin) >> 5]) & (1 << ((pin) & 0x1F))

#define _pi_gpio_write(pin, val) \
    (val) ? ( _pi_gpio_set(pin) ) : ( _pi_gpio_clr(pin) )

#ifdef	__cplusplus
extern "C" {
#endif

    int pi_gpio_map();
    void pi_gpio_unmap();

#ifdef	__cplusplus
}
#endif

#endif	/* PI_GPIO_H */

