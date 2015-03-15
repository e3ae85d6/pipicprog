//
//  HexFile.cpp
//  pipic18
//
//  Created by deema on 05.03.15.
//  Copyright (c) 2015 xxx. All rights reserved.
//

#include "HexFile.h"

#include <string>
#include <iostream>

void HexFile::load(istream &inputStream) {
    string hexLine;
    while (getline(inputStream, hexLine)) {
        HexFileRecord hexFileRecord;
        if(hexFileRecord.fromString(hexLine)) {
            hexFileRecords.push_back(hexFileRecord);
        }
    }
}

void HexFile::save(ostream &outputStream) {
    for (list<HexFileRecord>::iterator it = hexFileRecords.begin(); it != hexFileRecords.end(); it++) {
        outputStream << (*it).toString() << endl;
    }
}

list<HexFileRecord> HexFile::getHexFileRecords() {
    return hexFileRecords;
}
