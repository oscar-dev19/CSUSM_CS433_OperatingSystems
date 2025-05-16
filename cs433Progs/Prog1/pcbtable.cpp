#include "pcbtable.h"
#include <cstdlib>

PCBTable::PCBTable(unsigned int size) : size(size) {
    table = new PCB*[size];
    for (unsigned int i = 0; i < size; i++) {
        table[i] = nullptr;
    }
}

PCBTable::~PCBTable() {
    for (unsigned int i = 0; i < size; i++) {
        delete table[i];
    }
    delete[] table;
}

PCB* PCBTable::getPCB(unsigned int idx) {
    return (idx < size) ? table[idx] : nullptr;
}

void PCBTable::addPCB(PCB* pcb, unsigned int idx) {
    if (idx < size) {
        if (table[idx] != nullptr) {
            delete table[idx];
        }
        table[idx] = pcb;
    }
}

void PCBTable::addNewPCB(unsigned int pid, unsigned int priority, unsigned int idx) {
    if (idx < size) {
        if (table[idx] != nullptr) {
            delete table[idx];
        }
        table[idx] = new PCB(pid, priority, ProcState::NEW);
    }
}

