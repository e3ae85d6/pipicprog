//
//  main.cpp
//  pipic18
//
//  Created by deema on 05.03.15.
//  Copyright (c) 2015 xxx. All rights reserved.
//

#include <unistd.h>

#include <string>
#include <iostream>
#include "HexFile.h"

int main(int argc, const char * argv[]) {

	std::string fileName(argv[1]);

	HexFile hexFile;
	hexFile.load(fileName);
	hexFile.save("");

	// insert code here...
	//std::cout << "Hello, World!\n";
    return 0;
}
