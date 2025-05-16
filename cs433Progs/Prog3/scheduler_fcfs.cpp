/**
* Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.cpp
 * @author Oscar Lopez
 * @brief This Scheduler class implements the FCFS scheduling algorithm.
 * @version 0.1
 */
// Implementation of the First-Come-First-Serve (FCFS) scheduling algorithm

#include "scheduler_fcfs.h"
#include <iostream>

SchedulerFCFS::SchedulerFCFS() {
    // Initialize tracking variables to their starting values
    current_time = 0;          // Current simulation time, starts at 0
    total_waiting_time = 0;    // Accumulated waiting time across all processes
    completed_processes = 0;   // Counter for completed processes
}

SchedulerFCFS::~SchedulerFCFS() {
    // Clean up all data structures
    while (!ready_queue.empty()) {
        ready_queue.pop();    // Remove all remaining processes from the queue
    }
    processes.clear();        // Clear the stored process list
}

void SchedulerFCFS::init(std::vector<PCB>& process_list) {
    // Store the process list for statistics and tracking
    processes = process_list;
    
    // Initialize ready queue with all processes in order of arrival (FCFS)
    for (const PCB& pcb : process_list) {
        ready_queue.push(pcb);  // Add each process to the back of the queue
    }
}

void SchedulerFCFS::print_results() {
    // Output the scheduling algorithm results
    std::cout << "First Come First Serve Scheduler Results:" << std::endl;
    std::cout << "Total time: " << current_time << std::endl;
    
    // Calculate and display average waiting time if any processes completed
    if (completed_processes > 0) {
        std::cout << "Average waiting time: " << total_waiting_time / completed_processes << std::endl;
    }
    std::cout << "Number of completed processes: " << completed_processes << std::endl;
}

void SchedulerFCFS::simulate() {
    // Process all PCBs in the ready queue until empty
    while (!ready_queue.empty()) {
        // Get the next process in FCFS order (front of queue)
        PCB current_process = ready_queue.front();
        ready_queue.pop();

        // Calculate waiting time for this process (current time - arrival time)
        int waiting_time = current_time - current_process.arrival_time;
        total_waiting_time += waiting_time;   // Add to total for averaging later

        // Execute the entire process (non-preemptive scheduling)
        current_time += current_process.burst_time;   // Move time forward by burst time
        completed_processes++;                        // Increment completed process count

        // Print information about the completed process
        std::cout << "Time " << current_time << ": Process " << current_process.id 
                  << " (" << current_process.name << ") completed. "
                  << "Burst time: " << current_process.burst_time 
                  << ", Waiting time: " << waiting_time << std::endl;
    }
}
