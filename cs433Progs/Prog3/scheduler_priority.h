/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority.h
 * @author Oscar Lopez
 * @brief This Scheduler class implements the Priority scheduling algorithm.
 * @version 0.1
 */
// Header file for the Priority scheduling algorithm implementation
// Prioritizes processes based on their assigned priority values

#ifndef ASSIGN3_SCHEDULER_PRIORITY_H
#define ASSIGN3_SCHEDULER_PRIORITY_H

#include "scheduler.h"
#include <queue>
#include <map>

/**
 * @brief This Scheduler class implements the Priority scheduling algorithm.
 * The algorithm selects processes with the highest priority first (higher numerical value).
 * Within the same priority level, processes are scheduled in FCFS order.
 */
class SchedulerPriority : public Scheduler {
private:
    // Map of priority levels to queues of processes
    // std::greater<unsigned int> ensures we get highest priority first
    // Each priority level has its own queue of processes ordered by arrival
    std::map<unsigned int, std::queue<PCB>, std::greater<unsigned int>> priority_queues;
    
    // List of all processes preserved for statistics and reference
    std::vector<PCB> processes;
    
    // Current time in the simulation - tracks progression of time
    int current_time;
    
    // Statistics for average waiting time calculation
    double total_waiting_time;
    
    // Number of completed processes - used for statistics
    int completed_processes;

public:
    /**
     * @brief Construct a new SchedulerPriority object
     * Initializes the tracking variables for the simulation
     */
    SchedulerPriority();

    /**
     * @brief Destroy the SchedulerPriority object
     * Cleans up all allocated resources
     */
    ~SchedulerPriority() override;

    /**
     * @brief This function is called once before the simulation starts.
     *        It is used to initialize the scheduler with the provided processes.
     * @param process_list The list of processes to be scheduled in the simulation.
     */
    void init(std::vector<PCB>& process_list) override;

    /**
     * @brief This function is called once after the simulation ends.
     *        It outputs the statistics and results of the simulation.
     */
    void print_results() override;

    /**
     * @brief This function simulates the priority-based scheduling of processes.
     *        It selects processes with the highest priority first.
     *        Within the same priority, processes are handled in FCFS order.
     *        It stops when all processes are finished.
     */
    void simulate() override;
};

#endif //ASSIGN3_SCHEDULER_PRIORITY_H
