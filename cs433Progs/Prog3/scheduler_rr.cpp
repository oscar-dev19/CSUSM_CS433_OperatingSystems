/**
* Assignment 3: CPU Scheduler
 * @file scheduler_rr.cpp
 * @author Oscar Lopez
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling algorithm.
 * @version 0.1
 */
// Implementation of the Round Robin scheduling algorithm
// Each process gets a fixed time quantum before being preempted

#include "scheduler_rr.h"
#include <iostream>

SchedulerRR::SchedulerRR(int time_quantum) {
    // Initialize the time quantum for this RR scheduler
    quantum = time_quantum;       // The maximum time slice for each process
    
    // Initialize tracking variables
    current_time = 0;             // Start simulation at time 0
    total_waiting_time = 0;       // Initialize accumulated waiting time
    completed_processes = 0;      // No processes completed initially
}

SchedulerRR::~SchedulerRR() {
    // Clean up all allocated data structures
    while (!ready_queue.empty()) {
        ready_queue.pop();       // Remove all processes from the queue
    }
    processes.clear();           // Clear the stored process list
}

void SchedulerRR::init(std::vector<PCB>& process_list) {
    // Store the original process list for statistics and reference
    processes = process_list;
    
    // Initialize ready queue with all processes in the order they arrived
    for (const PCB& pcb : process_list) {
        ready_queue.push(pcb);   // Add process to the back of the queue
    }
}

void SchedulerRR::print_results() {
    // Output the simulation results
    std::cout << "Round Robin Scheduler Results:" << std::endl;
    std::cout << "Total time: " << current_time << std::endl;
    
    // Calculate and display average waiting time if processes completed
    if (completed_processes > 0) {
        std::cout << "Average waiting time: " << total_waiting_time / completed_processes << std::endl;
    }
    std::cout << "Number of completed processes: " << completed_processes << std::endl;
}

void SchedulerRR::simulate() {
    // Continue processing until all processes are complete
    while (!ready_queue.empty()) {
        // Get the next process from the front of the ready queue (FIFO)
        PCB current_process = ready_queue.front();
        ready_queue.pop();

        // Calculate waiting time for this process's current time slice
        // (Current time - when this process was last added to the queue)
        int waiting_time = current_time - current_process.arrival_time;
        total_waiting_time += waiting_time;  // Add to total for statistics

        // Execute process for quantum time or remaining burst time (whichever is smaller)
        int execution_time = std::min(quantum, (int)current_process.burst_time);
        current_time += execution_time;                 // Advance simulation time
        current_process.burst_time -= execution_time;   // Reduce remaining burst time

        // If process still has remaining execution time, put it back in queue
        if (current_process.burst_time > 0) {
            current_process.arrival_time = current_time; // Update arrival time to current time
            ready_queue.push(current_process);           // Add to back of the queue
        } else {
            // Process has completed
            completed_processes++;  // Increment completed process counter
        }

        // Output status of the current process after this time slice
        std::cout << "Time " << current_time << ": Process " << current_process.id 
                  << " (" << current_process.name << ") executed for " 
                  << execution_time << " units. Remaining burst time: "
                  << current_process.burst_time << std::endl;
    }
}