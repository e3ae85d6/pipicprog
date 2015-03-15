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

int main(int argc, const char * argv[]) {

    //std::string fileName(argv[1]);
    /*std::string fileName("b452-1.hex");
    
    ifstream inputData(fileName.c_str());

    if (!inputData.is_open()) {
        perror("open");
        return (EXIT_FAILURE);
    }

     
    HexFile hexFile;
    hexFile.load(inputData);
    hexFile.save(std::cout);*/

    PiPic18Phy phy = PiPic18Phy::getInstance();
    if(!phy.isInitSucceeded()) {
        clog << "Error: can't init phy" << endl;
        return (EXIT_FAILURE);
    }
    
    Pic18Device device(phy);
    
    uint32_t device_id = device.read_device_id();
    printf("device id: 0x%.4x\n", device_id);

    // insert code here...
    //std::cout << "Hello, World!\n";
    return (EXIT_SUCCESS);
}

