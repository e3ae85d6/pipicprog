/* 
 * File:   Pic18DeviceConfig.h
 * Author: deema
 *
 * Created on March 15, 2015, 11:05 PM
 */

#ifndef PIC18DEVICEINFO_H
#define	PIC18DEVICEINFO_H

#include <stdint.h>
#include <string>
#include <vector>

using namespace std;

class Pic18DeviceInfo {
private:
    Pic18DeviceInfo(
        uint16_t deviceId,
        size_t memorySize,
        string deviceName);
    
public:
    static Pic18DeviceInfo findDeviceInfo(uint16_t deviceId);
    
public:
    const uint16_t deviceId;
    const size_t memorySize;
    const string deviceName;
    
    static const size_t IdLocationsAddr = 0x300000;
    
};

#endif	/* PIC18DEVICEINFO_H */

