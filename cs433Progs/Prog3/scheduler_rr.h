/**
* Assignment 3: CPU Scheduler
 * @file scheduler_rr.h
 * @author Oscar Lopez
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling algorithm.
 * @version 0.1
 */
// Header file for Round Robin scheduling algorithm
// Gives each process a fixed time slice in a circular queue fashion

#ifndef ASSIGN3_SCHEDULER_RR_H
#define ASSIGN3_SCHEDULER_RR_H

#include "scheduler.h"
#include <queue>

/**
 * @brief This Scheduler class implements the Round Robin (RR) scheduling algorithm.
 * Round Robin gives each process a fixed time quantum to execute before moving to the next process.
 * If a process doesn't complete in its time quantum, it's put back at the end of the queue.
 */
class SchedulerRR : public Scheduler {
private:
    // Time quantum for RR scheduling - the maximum time slice allocated to each process
    // before switching to the next process in the queue
    int quantum;
    
    // Queue to store processes in RR order - processes are added to the back
    // and removed from the front in a circular fashion
    std::queue<PCB> ready_queue;
    
    // List of all processes preserved for statistics and reference
    std::vector<PCB> processes;
    
    // Current time in the simulation - tracks the progression of clock ticks
    int current_time;
    
    // Statistics for average waiting time calculation - accumulated across all processes
    double total_waiting_time;
    
    // Number of completed processes - used for performance statistics
    int completed_processes;

public:
    /**
     * @brief Construct a new SchedulerRR object
     * @param time_quantum The time slice allocated to each process (default: 10 time units)
     */
    SchedulerRR(int time_quantum = 10);

    /**
     * @brief Destroy the SchedulerRR object
     * Cleans up all allocated resources
     */
    ~SchedulerRR() override;

    /**
     * @brief This function is called once before the simulation starts.
     *        It is used to initialize the scheduler with the process list.
     * @param process_list The list of processes to be scheduled in the simulation.
     */
    void init(std::vector<PCB>& process_list) override;

    /**
     * @brief This function is called once after the simulation ends.
     *        It outputs the statistics and results of the Round Robin simulation.
     */
    void print_results() override;

    /**
     * @brief This function simulates the Round Robin scheduling of processes.
     *        Each process gets a fixed time quantum to execute.
     *        If a process doesn't complete, it's moved to the back of the queue.
     *        It stops when all processes are finished.
     */
    void simulate() override;
};

#endif //ASSIGN3_SCHEDULER_RR_H
