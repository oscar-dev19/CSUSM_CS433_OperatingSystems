/**
 * Assignment 1: priority queue of processes
 * @file pcb.h
 * @author Oscar Lopez
 * @brief This is the header file for the PCB class, a process control block.
 * @version 0.1
 */
// This header file defines the Process Control Block (PCB) class which represents
// a process in the operating system simulation

#pragma once
#include <iostream>
#include <string>
using namespace std;

/**
 * @brief A process control block (PCB) Process control block(PCB) is a data structure representing a process in the system.
 *       It contains the following fields:
 *       - process ID (PID)
 *       - process name
 *       - burst time
 *       - priority
 *       - arrival time
 */
class PCB {
public:
    // Name of the process - stores the identifier string for the process
    string name;
    
    // The unique process ID - holds a unique numeric identifier for the process
    unsigned int id;
    
    // The priority of a process - larger number represents higher priority (range: 1-50)
    unsigned int priority;
    
    // The CPU burst time of the process - represents the total execution time needed
    unsigned int burst_time;
    
    // The arrival time of the process - represents when the process entered the system
    unsigned int arrival_time;

    /**
     * @brief Construct a new PCB object
     * @param name: the name of the process
     * @param id: each process has a unique ID (default: 0)
     * @param priority: the priority of the process in the range 1-50. Larger number represents higher priority (default: 1)
     * @param burst_time: the execution time required by the process (default: 0)
     */
    PCB(string name, unsigned int id = 0, unsigned int priority = 1, unsigned int burst_time = 0) {
        this->id = id;                   // Initialize process ID
        this->name = name;               // Initialize process name
        this->priority = priority;       // Initialize process priority
        this->burst_time = burst_time;   // Initialize process burst time
        this->arrival_time = 0;          // Initialize arrival time to 0 by default
    }

    /**
     * @brief Destroy the PCB object - cleans up any resources used by the process
     */
    ~PCB() {}

    /**
     * @brief Print the PCB object - displays all information about the process
     */
    void print() {
        cout << "Process " << id << ": " << name << " has priority " << priority << " and burst time "
             << burst_time << endl;
    }
};