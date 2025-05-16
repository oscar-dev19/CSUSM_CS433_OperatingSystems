/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority_rr.cpp
 * @author Oscar Lopez
 * @brief This Scheduler class implements the Priority RR scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_priority_rr.h"
#include <iostream>

SchedulerPriorityRR::SchedulerPriorityRR(int time_quantum) {
    quantum = time_quantum;
    current_time = 0;
    total_waiting_time = 0;
    completed_processes = 0;
}

SchedulerPriorityRR::~SchedulerPriorityRR() {
    // Clear all queues
    priority_queues.clear();
    processes.clear();
}

void SchedulerPriorityRR::init(std::vector<PCB>& process_list) {
    // Store the original process list for statistics
    processes = process_list;
    
    // Initialize priority queues with processes
    for (const PCB& pcb : process_list) {
        priority_queues[pcb.priority].push(pcb);
    }
}

void SchedulerPriorityRR::print_results() {
    std::cout << "Priority Round Robin Scheduler Results:" << std::endl;
    std::cout << "Total time: " << current_time << std::endl;
    if (completed_processes > 0) {
        std::cout << "Average waiting time: " << total_waiting_time / completed_processes << std::endl;
    }
    std::cout << "Number of completed processes: " << completed_processes << std::endl;
}

void SchedulerPriorityRR::simulate() {
    while (!priority_queues.empty()) {
        // Get highest priority queue that has processes
        auto it = priority_queues.begin();
        while (it != priority_queues.end() && it->second.empty()) {
            it = priority_queues.erase(it);
        }
        
        if (it == priority_queues.end()) {
            break; // No more processes to execute
        }

        // Get the next process from the highest priority queue
        PCB current_process = it->second.front();
        it->second.pop();

        // Calculate waiting time
        int waiting_time = current_time - current_process.arrival_time;
        total_waiting_time += waiting_time;

        // Execute process for quantum time or remaining burst time
        int execution_time = std::min(quantum, (int)current_process.burst_time);
        current_time += execution_time;
        current_process.burst_time -= execution_time;

        // If process is not finished, put it back in its priority queue
        if (current_process.burst_time > 0) {
            current_process.arrival_time = current_time; // Update arrival time
            it->second.push(current_process);
        } else {
            completed_processes++;
        }

        std::cout << "Time " << current_time << ": Process " << current_process.id 
                  << " (" << current_process.name << ") with priority " 
                  << current_process.priority << " executed for " 
                  << execution_time << " units." << std::endl;
    }
}
