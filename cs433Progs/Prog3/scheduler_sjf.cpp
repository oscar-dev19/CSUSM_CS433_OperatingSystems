/**
* Assignment 3: CPU Scheduler
 * @file scheduler_sjf.cpp
 * @author Oscar Lopez
 * @brief This Scheduler class implements the SJF scheduling algorithm.
 * @version 0.1
 */
// Implementation of the Shortest Job First (SJF) scheduling algorithm

#include "scheduler_sjf.h"
#include <iostream>

SchedulerSJF::SchedulerSJF() {
    // Initialize tracking variables for the simulation
    current_time = 0;          // Current simulation time, starts at 0
    total_waiting_time = 0;    // Cumulative waiting time for calculating average
    completed_processes = 0;   // Counter for number of completed processes
}

SchedulerSJF::~SchedulerSJF() {
    // Clean up all data structures when scheduler is destroyed
    while (!ready_queue.empty()) {
        ready_queue.pop();    // Remove all processes from the priority queue
    }
    processes.clear();        // Clear the stored process list
}

void SchedulerSJF::init(std::vector<PCB>& process_list) {
    // Store the process list for statistics and reference
    processes = process_list;
    
    // Initialize ready queue with all processes, which will be automatically
    // sorted by the priority queue based on burst time (using CompareBurstTime)
    for (const PCB& pcb : process_list) {
        ready_queue.push(pcb);  // Add process to the priority queue
    }
}

void SchedulerSJF::print_results() {
    // Output the simulation results
    std::cout << "Shortest Job First Scheduler Results:" << std::endl;
    std::cout << "Total time: " << current_time << std::endl;
    
    // Calculate and display average waiting time if processes were completed
    if (completed_processes > 0) {
        std::cout << "Average waiting time: " << total_waiting_time / completed_processes << std::endl;
    }
    std::cout << "Number of completed processes: " << completed_processes << std::endl;
}

void SchedulerSJF::simulate() {
    // Process all PCBs in the ready queue until empty
    while (!ready_queue.empty()) {
        // Get the process with shortest burst time (top of priority queue)
        PCB current_process = ready_queue.top();
        ready_queue.pop();

        // Calculate waiting time for this process (current time - arrival time)
        int waiting_time = current_time - current_process.arrival_time;
        total_waiting_time += waiting_time;  // Add to total for averaging later

        // Execute the entire process (non-preemptive SJF)
        current_time += current_process.burst_time;  // Advance time by the burst time
        completed_processes++;                       // Increment completed process count

        // Display information about the completed process
        std::cout << "Time " << current_time << ": Process " << current_process.id 
                  << " (" << current_process.name << ") completed. "
                  << "Burst time: " << current_process.burst_time 
                  << ", Waiting time: " << waiting_time << std::endl;
    }
}
