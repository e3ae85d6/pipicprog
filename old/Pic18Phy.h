/* 
 * File:   Pic18Phy.h
 * Author: deema
 *
 * Created on March 15, 2015, 6:01 PM
 */

#ifndef PIC18PHY_H
#define	PIC18PHY_H

#include <stdint.h>

class Pic18Phy {
public:
    virtual void sendBits(uint16_t bits, size_t num_bits) const = 0;
    virtual uint8_t recvBits(size_t num_bits) const = 0;
};

#endif	/* PIC18PHY_H */

