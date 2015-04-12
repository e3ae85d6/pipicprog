/* 
 * File:   Pic18Memory.h
 * Author: deema
 *
 * Created on March 15, 2015, 11:29 PM
 */

#ifndef PIC18MEMORY_H
#define	PIC18MEMORY_H

#include "Pic18DeviceInfo.h"

class Pic18Memory {
public:
    Pic18Memory(Pic18DeviceInfo &deviceInfo);
    virtual ~Pic18Memory();
private:
    Pic18Memory(const Pic18Memory& orig);
    Pic18DeviceInfo &deviceInfo;
};

#endif	/* PIC18MEMORY_H */

