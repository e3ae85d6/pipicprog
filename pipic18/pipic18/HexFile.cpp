//
//  HexFile.cpp
//  pipic18
//
//  Created by deema on 05.03.15.
//  Copyright (c) 2015 xxx. All rights reserved.
//

#include "HexFile.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <memory>

void HexFile::load(const std::string &fileName) {
	std::ifstream inputData(fileName);
	
	if (!inputData.is_open()) {
		perror("open");
		return;
	}
	
	std::string hexLine;
	while (getline(inputData, hexLine)) {
		HexFileRecord hexFileRecord;
		hexFileRecord.fromString(hexLine);
		hexFileRecords.push_back(hexFileRecord);
	}
	
	inputData.close();
}

void HexFile::save(const std::string &fileName) {
	for(HexFileRecord &rec : hexFileRecords) {
		std::cout << rec.toString() << std::endl;
	}
}
	
std::list<HexFileRecord> HexFile::getHexFileRecords() {
	return hexFileRecords;
}
