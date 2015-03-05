//
//  HexFileRecord.cpp
//  pipic18
//
//  Created by deema on 05.03.15.
//  Copyright (c) 2015 xxx. All rights reserved.
//

#include <iostream>

#include "HexFileRecord.h"

#define MAX_NIBBLE 0xF
#define MIN_HEX_CHARS 11 // :<nn><addr><tt>...<cs>
#define MAX_HEX_BYTES 260 // 255 + 5

char digits[] = {
	'0', '1', '2', '3',
	'4', '5', '6', '7',
	'8', '9', 'A', 'B',
	'C', 'D', 'E', 'F',
};

char nibbleToHex(uint8_t nibble) {
	return nibble > MAX_NIBBLE ? 'X' : digits[nibble];
}

void appendHexByte(std::string &str, uint8_t byte) {
	uint8_t highNibble = (byte & 0xF0) >> 4,
			lowNibble  = (byte & 0xF);
	
	str += nibbleToHex(highNibble);
	str += nibbleToHex(lowNibble);
}

uint8_t hexToNibble(char digit) {
	uint8_t nibble = 0xFF;
	
	if(digit >= 'A' && digit <= 'F')
		nibble = digit - 'A' + 10;
	else if(digit >= 'a' && digit <= 'f')
		nibble = digit - 'a' + 10;
	else if(digit >= '0' && digit <= '9')
		nibble = digit - '0';
	
	return nibble;
}

void HexFileRecord::fromString(const std::string &hexLine) {
	std::vector<uint8_t> hexBytes;
	hexBytes.reserve(MAX_HEX_BYTES);

	if(hexLine[0] != ':' || hexLine.length() < MIN_HEX_CHARS) {
		std::cerr << "Invalid line start code: " << hexLine << std::endl;
		return;
	}

	for(std::string::size_type i = 1; i < hexLine.length() - 2; ) {
		uint8_t highNibble = hexToNibble(hexLine[i++]),
				lowNibble  = hexToNibble(hexLine[i++]);
			
		if(highNibble > MAX_NIBBLE || lowNibble > MAX_NIBBLE) {
			std::cerr << "Invalid line format: " << hexLine << std::endl;
			continue;
		}
			
		uint8_t byte = (highNibble << 4) | lowNibble;
		hexBytes.push_back(byte);
	}
		
	uint8_t checksum = 0;
	for(uint8_t byte : hexBytes)
		checksum += byte;
		
	if(checksum) {
		std::cerr << "Invalid line checksum: " << hexLine << std::endl;
		return;
	}
		
	uint8_t dataLen = hexBytes[0];
	if(hexBytes.size() - dataLen != 5) { // 1(dataLen) + 2(addr) + 1(type) + 1(checksum)
		std::cerr << "Invalid line format: " << hexLine << std::endl;
		return;
	}
		
	addr = ((uint16_t)hexBytes[1] << 8) | hexBytes[2];
	type = static_cast<HexFileRecordType>(hexBytes[3]);

	data.reserve(dataLen);
	for(size_t i = 0; i < dataLen; i++)
		data.push_back(hexBytes[i + 4]);
}

const std::string HexFileRecord::toString() {
	uint8_t checksum = 0;
	std::string str(":");
	
	// byteCount
	uint8_t byteCount = data.size();
	appendHexByte(str, byteCount);
	checksum += byteCount;
	
	// address
	uint8_t addrHigh = (uint8_t)(addr >> 8);
	appendHexByte(str, addrHigh);
	checksum += addrHigh;

	uint8_t addrLow = (uint8_t)addr;
	appendHexByte(str, addrLow);
	checksum += addrLow;
	
	// recordType
	uint8_t recordType = type;
	appendHexByte(str, recordType);
	checksum += recordType;
	
	// data bytes
	for (uint8_t dataByte : data) {
		appendHexByte(str, dataByte);
		checksum += dataByte;
	}
	
	// checksum
	checksum = ~checksum + 1;
	appendHexByte(str, checksum);
	
	return str;
}
