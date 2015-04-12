/* 
 * File:   PiPic18Phy.cpp
 * Author: deema
 * 
 * Created on March 15, 2015, 6:04 PM
 */

#include <unistd.h>

#include "PiPic18Phy.h"
#include "pi_gpio.h"

#define VPP 25
#define SCLK 24
#define SDATA_OUT 23
#define SDATA_IN 22

#define TICK 20

void pic18_send_bit(uint8_t bit) {
    _pi_gpio_set(SCLK);
    _pi_gpio_write(SDATA_OUT, bit);
    usleep(TICK);

    _pi_gpio_clr(SCLK);
    usleep(TICK);
    _pi_gpio_clr(SDATA_OUT);
}

uint8_t pic18_recv_bit() {
    _pi_gpio_set(SCLK);
    usleep(TICK);
    
    uint8_t bit = _pi_gpio_lev(SDATA_IN);
    _pi_gpio_clr(SCLK);
    usleep(TICK);    

    return bit;
}


PiPic18Phy::PiPic18Phy() : initSucceeded(false) {
    int status = pi_gpio_map();
    if(status)
	return;
    
    _pi_gpio_fsel(VPP, PIN_OUTPUT);
    _pi_gpio_fsel(SCLK, PIN_OUTPUT);
    _pi_gpio_fsel(SDATA_OUT, PIN_OUTPUT);
    _pi_gpio_fsel(SDATA_IN, PIN_INPUT);

    _pi_gpio_clr(SCLK);
    _pi_gpio_clr(SDATA_OUT);

    _pi_gpio_set(VPP);
    usleep(2 * TICK);
    
    initSucceeded = true;
}

PiPic18Phy PiPic18Phy::getInstance() {
    static PiPic18Phy instance;
    return instance;
}

bool PiPic18Phy::isInitSucceeded() const {
    return initSucceeded;
}

PiPic18Phy::~PiPic18Phy() {
    if(!isInitSucceeded())
        return;
    
    _pi_gpio_clr(VPP);
    _pi_gpio_clr(SCLK);
    _pi_gpio_clr(SDATA_OUT);

    _pi_gpio_fsel(VPP, PIN_INPUT);
    _pi_gpio_fsel(SCLK, PIN_INPUT);
    _pi_gpio_fsel(SDATA_OUT, PIN_INPUT);
    _pi_gpio_fsel(SDATA_IN, PIN_INPUT);

    pi_gpio_unmap();
}

void PiPic18Phy::sendBits(uint16_t bits, size_t num_bits) const {
    for(size_t b = 0; b < num_bits; b++)
	pic18_send_bit((bits >> b) & 1);
}

uint8_t PiPic18Phy::recvBits(size_t num_bits) const {
    uint8_t bits = 0;

    for(size_t b = 0; b < num_bits; b++)
	bits |= (pic18_recv_bit() << b);

    return bits;
}
