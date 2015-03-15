/* 
 * File:   PiPic18Phy.h
 * Author: deema
 *
 * Created on March 15, 2015, 6:04 PM
 */

#ifndef PIPIC18PHY_H
#define	PIPIC18PHY_H

#include "Pic18Phy.h"

class PiPic18Phy : public Pic18Phy {
private:
    bool initSucceeded;
    
private:
    PiPic18Phy();

public:
    bool isInitSucceeded() const;
    static PiPic18Phy getInstance();
    virtual ~PiPic18Phy();

public:
    virtual void sendBits(uint16_t bits, size_t num_bits) const;
    virtual uint8_t recvBits(size_t num_bits) const;

};

#endif	/* PIPIC18PHY_H */

