//
//  main.cpp
//  pipic18
//
//  Created by deema on 05.03.15.
//  Copyright (c) 2015 xxx. All rights reserved.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <iostream>
#include <fstream>
#include "HexFile.h"
#include "Pic18Device.h"
#include "Pic18Phy.h"
#include "PiPic18Phy.h"
#include "Pic18DeviceInfo.h"
#include "Pic18Memory.h"

int main(int argc, const char * argv[]) {

    //std::string fileName(argv[1]);
    std::string fileName("b452-1.hex");
    
    ifstream inputData(fileName);

    if (!inputData.is_open()) {
        perror("open");
        return (EXIT_FAILURE);
    }
     
    HexFile hexFile;
    hexFile.load(inputData);

    /*PiPic18Phy phy = PiPic18Phy::getInstance();
    if(!phy.isInitSucceeded()) {
        clog << "Error: can't init phy" << endl;
        return (EXIT_FAILURE);
    }
    
    Pic18Device device(phy);
    
    uint32_t device_id = device.read_device_id();
    printf("device id: 0x%.4x\n", device_id);

    uint8_t config[14] = { 0 };
    device.read(0x300000, config, sizeof(config));
    
    for(int i = 0; i < sizeof(config); i++) {
        for(int j = 7; j >= 0; j--) {
            cout << ((config[i] >> j) & 1);
            
            if(j == 4)
                cout << ' ';
        }
        cout << endl;
    }*/
    
    uint16_t deviceId = 0x0420;
    Pic18DeviceInfo pic18DeviceInfo = Pic18DeviceInfo::findDeviceInfo(deviceId);
    if(pic18DeviceInfo.deviceId == 0) {
        cerr << "Error: unknown device (0x" << hex << deviceId << ")" << endl;
        return (EXIT_FAILURE);
    }
    else {
        cout << "Detected device: " << pic18DeviceInfo.deviceName << endl;
    }

    Pic18Memory pic18Memory(pic18DeviceInfo);
    size_t a = pic18DeviceInfo.IdLocationsAddr;
    
    // insert code here...
    //std::cout << "Hello, World!\n";
    return (EXIT_SUCCESS);
}

