//
//  HexFile.h
//  pipic18
//
//  Created by deema on 05.03.15.
//  Copyright (c) 2015 xxx. All rights reserved.
//

#ifndef __pipic18__HexFile__
#define __pipic18__HexFile__

#include <iostream>
#include <list>

#include "HexFileRecord.h"

class HexFile {
private:
    list<HexFileRecord> hexFileRecords;

public:
    void load(istream &inputStream);
    void save(ostream &outputStream);

    list<HexFileRecord> getHexFileRecords();
};

#endif /* defined(__pipic18__HexFile__) */
