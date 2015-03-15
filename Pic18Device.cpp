/* 
 * File:   Pic18Prg.cpp
 * Author: deema
 * 
 * Created on March 15, 2015, 6:26 PM
 */

#include <unistd.h>
#include <list>
#include "Pic18Device.h"

#define CMD_DELAY 40

Pic18Device::Pic18Device(const Pic18Phy &pic18Phy) : phy(pic18Phy) {
}

Pic18Device::~Pic18Device() {
}

void Pic18Device::load_tblptr(uint32_t addr) {
    Pic18Cmd load_tblptr_addr_seq[] = {
        { CORE_INSTR, (0x0E << 8) | ((addr) >> 16 & 0x3F) },
        { CORE_INSTR, 0x6EF8 },
        { CORE_INSTR, (0x0E << 8) | ((addr) >> 8 & 0xFF) },
        { CORE_INSTR, 0x6EF7 },
        { CORE_INSTR, (0x0E << 8) | ((addr) & 0xFF) },
        { CORE_INSTR, 0x6EF6 },
    };
    
    exec(load_tblptr_addr_seq, sizeof (load_tblptr_addr_seq) / sizeof (Pic18Cmd));
}

uint16_t Pic18Device::read_device_id() {
    load_tblptr(0x3FFFFE);

    Pic18Cmd read_device_id_seq[] = {
        { TABLE_READ_POST_INCREMENT, 0 },
        { TABLE_READ, 0 },
    };

    exec(read_device_id_seq, sizeof (read_device_id_seq) / sizeof (Pic18Cmd));

    uint16_t dev_id = read_device_id_seq[1].data1;
    dev_id <<= 8;
    dev_id |= read_device_id_seq[0].data1 & 0xE0;

    return dev_id;
}

void Pic18Device::read(uint32_t startAddr, uint8_t *dstBuf, size_t nBytes) {
    load_tblptr(startAddr);
    
    Pic18Cmd read_inc_cmd = { TABLE_READ_POST_INCREMENT, 0 };
    
    for(size_t i = 0; i < nBytes; i++) {
        exec(read_inc_cmd);
        dstBuf[i] = read_inc_cmd.data1;
    }
}

void Pic18Device::exec(Pic18Cmd *cmds, size_t num) {
    for (size_t i = 0; i < num; i++) {
        Pic18Cmd *cmd = cmds + i;
        exec(*cmd);
    }
}

void Pic18Device::exec(Pic18CmdList &cmdList) {
    for (Pic18CmdList::iterator it = cmdList.begin(); it != cmdList.end(); it++) {
        Pic18Cmd &cmd = *it;
        exec(cmd);
    }
}

void Pic18Device::exec(Pic18Cmd &cmd) {
    phy.sendBits(cmd.cmd, 4);
    phy.sendBits(cmd.data0, 8);

    if ((cmd.cmd & 0xC) == 8)
        cmd.data1 = phy.recvBits(8);
    else
        phy.sendBits(cmd.data1, 8);

    usleep(CMD_DELAY);
}
