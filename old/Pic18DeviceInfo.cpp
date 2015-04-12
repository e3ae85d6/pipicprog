/* 
 * File:   Pic18DeviceConfig.cpp
 * Author: deema
 * 
 * Created on March 15, 2015, 11:05 PM
 */

#include <stdint.h>

#include "Pic18DeviceInfo.h"

Pic18DeviceInfo::Pic18DeviceInfo(
        uint16_t deviceId,
        size_t memorySize,
        string deviceName) :
        
        deviceId(deviceId),
        memorySize(memorySize),
        deviceName(deviceName)
{ }

Pic18DeviceInfo Pic18DeviceInfo::findDeviceInfo(uint16_t deviceId) {
    vector<Pic18DeviceInfo> KnownPic18DeviceInfos = {{
        Pic18DeviceInfo(0x0420, 32 * 1024, string("PIC18F452")),
        Pic18DeviceInfo(0x0421, 32 * 1024, string("PIC18F452"))
    }};
      
    for(Pic18DeviceInfo pic18DeviceInfo : KnownPic18DeviceInfos) {
        if(pic18DeviceInfo.deviceId == deviceId) {
            return pic18DeviceInfo;
        }
    }
    
    /*Pic18DeviceInfo devices[] = {
        Pic18DeviceInfo(0x0420, 32 * 1024, string("PIC18F452")),
    };
            
    for (int i = 0; i < sizeof(devices) / sizeof(Pic18DeviceInfo); i++) {
        if(devices[i].deviceId == deviceId) {
            return devices[i];
        }
    }*/
    
    return Pic18DeviceInfo(0, 0, string("Unknown"));
}