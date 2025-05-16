/**
* Assignment 3: CPU Scheduler
 * @file scheduler.h
 * @author Oscar Lopez
 * @brief This is the header file for the base Scheduler class. Specific schedulers, e.g. FCFS, SJF and RR, inherit
 *        this base class.
 * @version 0.1
 */
// This is the abstract base class that defines the interface for all scheduler implementations
// It provides a common structure that all specific scheduling algorithms must adhere to

#pragma once

#include <vector>
#include "pcb.h"

using namespace std;

/**
 * @brief This is the base abstract class for CPU schedulers.
 * 
 * This class defines the interface that all CPU schedulers must implement.
 * Different scheduling algorithms (FCFS, SJF, Priority, Round Robin) inherit from this base class
 * and provide their own implementations of the virtual methods.
 */
class Scheduler {
public:
    /**
     * @brief Construct a new Scheduler object
     * 
     * Default constructor for the base Scheduler class.
     */
    Scheduler() {}
    
    /**
     * @brief Destroy the Scheduler object
     * 
     * Virtual destructor to ensure proper cleanup of derived classes.
     */
    virtual ~Scheduler() {}
    
    /**
     * @brief Initialize the scheduler with a list of processes
     * 
     * This function is called once before the simulation starts.
     * It is used to initialize the scheduler's internal data structures
     * with the provided list of processes.
     * 
     * @param process_list The list of processes to be scheduled in the simulation.
     */
    virtual void init(std::vector<PCB>& process_list) = 0;

    /**
     * @brief Output the simulation results
     * 
     * This function is called once after the simulation ends.
     * It is used to print out statistics and performance metrics gathered
     * during the simulation, such as total time, average waiting time, etc.
     */
    virtual void print_results() = 0;

    /**
     * @brief Run the scheduling simulation
     * 
     * This function simulates the scheduling of processes according to
     * the specific scheduling algorithm's rules. It manages the ready queue,
     * tracks time, and determines which process runs when.
     * The simulation continues until all processes are completed.
     */
    virtual void simulate() = 0;
};