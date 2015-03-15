/* 
 * File:   Pic18Prg.h
 * Author: deema
 *
 * Created on March 15, 2015, 6:26 PM
 */

#ifndef PIC18PRG_H
#define	PIC18PRG_H

#include "Pic18Phy.h"
#include <list>
#include <vector>

using namespace std;

#define CORE_INSTR 0
#define TABLE_READ 8
#define TABLE_READ_POST_INCREMENT 9

struct Pic18Cmd {
    uint16_t cmd;

    union {
        uint16_t data;

        struct {
            uint8_t data0;
            uint8_t data1;
        };
    };
};

typedef list<Pic18Cmd> Pic18CmdList;

class Pic18Device {
public:
    Pic18Device(const Pic18Phy &pic18Phy);
    virtual ~Pic18Device();

public:
    void exec(Pic18Cmd &cmd);
    void exec(Pic18CmdList &cmdList);
    void exec(Pic18Cmd *cmds, size_t num = 1);
    
    void read(uint32_t startAddr, uint8_t *dstBuf, size_t nBytes);
    

public:
    void load_tblptr(uint32_t addr);
    uint16_t read_device_id();

private:
    const Pic18Phy &phy;
};

#endif	/* PIC18PRG_H */

