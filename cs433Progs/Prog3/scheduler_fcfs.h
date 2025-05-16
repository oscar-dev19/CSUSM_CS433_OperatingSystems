/**
* Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.h
 * @author Oscar Lopez
 * @brief This Scheduler class implements the FCFS scheduling algorithm.
 * @version 0.1
 */
//Remember to add sufficient and clear comments to your code

#ifndef ASSIGN3_SCHEDULER_FCFS_H
#define ASSIGN3_SCHEDULER_FCFS_H

#include "scheduler.h"
#include <queue>

/**
 * @brief This Scheduler class implements the FCFS scheduling algorithm.
 */
class SchedulerFCFS : public Scheduler {
private:
    // Queue to store processes in FCFS order
    std::queue<PCB> ready_queue;
    
    // Statistics tracking
    int current_time;
    double total_waiting_time;
    int completed_processes;
    std::vector<PCB> processes;

public:
    /**
     * @brief Construct a new SchedulerFCFS object
     */
    SchedulerFCFS();
    /**
     * @brief Destroy the SchedulerFCFS object
     */
    ~SchedulerFCFS() override;

    /**
     * @brief This function is called once before the simulation starts.
     *        It is used to initialize the scheduler.
     * @param process_list The list of processes in the simulation.
     */
    void init(std::vector<PCB>& process_list) override;

    /**
     * @brief This function is called once after the simulation ends.
     *        It is used to print out the results of the simulation.
     */
    void print_results() override;

    /**
     * @brief This function simulates the scheduling of processes in the ready queue.
     *        It stops when all processes are finished.
     */
    void simulate() override;
};
#endif //ASSIGN3_SCHEDULER_FCFS_H
