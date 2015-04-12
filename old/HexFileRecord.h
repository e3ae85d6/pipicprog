//
//  HexFileRecord.h
//  pipic18
//
//  Created by deema on 05.03.15.
//  Copyright (c) 2015 xxx. All rights reserved.
//

#ifndef __pipic18__HexFileRecord__
#define __pipic18__HexFileRecord__

#include <stdint.h>
#include <string>
#include <vector>

using namespace std;

enum HexFileRecordType {
    Data,
    EndOfFile,
    ExtendedSegmentAddress,
    StartSegmentAddress,
    ExtendedLinearAddress,
    StartLinearAddress,
};

class HexFileRecord {
private:
    uint16_t addr;
    HexFileRecordType type;
    vector<uint8_t> data;

public:
    bool fromString(const string &hexLine);
    const string toString();
};

#endif /* defined(__pipic18__HexFileRecord__) */
