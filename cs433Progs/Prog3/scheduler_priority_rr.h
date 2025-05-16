/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority_rr.h
 * @author Oscar Lopez
 * @brief This Scheduler class implements the Priority RR scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#ifndef ASSIGN3_SCHEDULER_PRIORITY_RR_H
#define ASSIGN3_SCHEDULER_PRIORITY_RR_H

#include "scheduler.h"
#include <queue>
#include <map>

class SchedulerPriorityRR : public Scheduler {
private:
    // Time quantum for RR scheduling
    int quantum;
    // Map of priority levels to queues of processes
    std::map<unsigned int, std::queue<PCB>, std::greater<unsigned int>> priority_queues;
    // List of all processes for statistics
    std::vector<PCB> processes;
    // Current time in the simulation
    int current_time;
    // Statistics for average waiting time
    double total_waiting_time;
    // Number of completed processes
    int completed_processes;

public:
    /**
     * @brief Construct a new SchedulerPriority object
     */
    SchedulerPriorityRR(int time_quantum = 10);

    /**
     * @brief Destroy the SchedulerPriority object
     */
    ~SchedulerPriorityRR() override;

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

#endif //ASSIGN3_SCHEDULER_PRIORITY_RR_H
