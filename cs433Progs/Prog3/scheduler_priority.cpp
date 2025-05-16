/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority.cpp
 * @author Oscar Lopez
 * @brief This Scheduler class implements the Priority scheduling algorithm.
 * @version 0.1
 */
// Remember to add sufficient and clear comments to your code

#include "scheduler_priority.h"
#include <iostream>

SchedulerPriority::SchedulerPriority() {
    current_time = 0;
    total_waiting_time = 0;
    completed_processes = 0;
}

SchedulerPriority::~SchedulerPriority() {
    // Clear all queues and process list
    priority_queues.clear();
    processes.clear();
}

void SchedulerPriority::init(std::vector<PCB>& process_list) {
    // Store the process list for statistics
    processes = process_list;
    
    // Initialize priority queues with processes
    for (const PCB& pcb : process_list) {
        priority_queues[pcb.priority].push(pcb);
    }
}

void SchedulerPriority::print_results() {
    std::cout << "Priority Scheduler Results:" << std::endl;
    std::cout << "Total time: " << current_time << std::endl;
    if (completed_processes > 0) {
        std::cout << "Average waiting time: " << total_waiting_time / completed_processes << std::endl;
    }
    std::cout << "Number of completed processes: " << completed_processes << std::endl;
}

void SchedulerPriority::simulate() {
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

        // Calculate waiting time for this process
        int waiting_time = current_time - current_process.arrival_time;
        total_waiting_time += waiting_time;

        // Execute the entire process (non-preemptive)
        current_time += current_process.burst_time;
        completed_processes++;

        std::cout << "Time " << current_time << ": Process " << current_process.id 
                  << " (" << current_process.name << ") with priority " 
                  << current_process.priority << " completed. "
                  << "Burst time: " << current_process.burst_time 
                  << ", Waiting time: " << waiting_time << std::endl;
    }
}