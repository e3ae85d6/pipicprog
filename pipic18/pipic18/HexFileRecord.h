//
//  HexFileRecord.h
//  pipic18
//
//  Created by deema on 05.03.15.
//  Copyright (c) 2015 xxx. All rights reserved.
//

#ifndef __pipic18__HexFileRecord__
#define __pipic18__HexFileRecord__

#include <string>
#include <vector>

enum HexFileRecordType : uint8_t {
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
	std::vector<uint8_t> data;

public:
	void fromString(const std::string &hexLine);
	const std::string toString();
};

#endif /* defined(__pipic18__HexFileRecord__) */
