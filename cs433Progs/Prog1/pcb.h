#pragma once
#include <iostream>

using namespace std;

/**
 * @enum ProcState
 * @brief Represents the different states of a process.
 * 
 * This enumeration defines the possible states a process can be in:
 * - `NEW`: Process has been created but not yet ready.
 * - `READY`: Process is ready to run but waiting for CPU time.
 * - `RUNNING`: Process is currently executing.
 * - `WAITING`: Process is waiting for an event or resource.
 * - `TERMINATED`: Process has completed execution.
 */
enum class ProcState { NEW, READY, RUNNING, WAITING, TERMINATED };

/**
 * @class PCB
 * @brief Represents a Process Control Block (PCB).
 * 
 * The PCB contains essential information about a process, such as its
 * unique identifier (`id`), priority (`priority`), and current state (`state`).
 */
class PCB {
public:
    unsigned int id;       ///< Unique process ID.
    unsigned int priority; ///< Priority of the process (1-50, higher is better).
    ProcState state;       ///< Current state of the process.

    /**
     * @brief Constructs a PCB with the specified attributes.
     * 
     * @param id The process ID. Default is `0`.
     * @param priority The priority level (higher values indicate higher priority). Default is `1`.
     * @param state The initial state of the process. Default is `ProcState::NEW`.
     */
    PCB(unsigned int id = 0, unsigned int priority = 1, ProcState state = ProcState::NEW) {
        this->id = id;
        this->priority = priority;
        this->state = state;
    }

    /**
     * @brief Destructor for PCB.
     * 
     * Since no dynamic memory allocation is used, the destructor is trivial.
     */
    ~PCB() {}

    /**
     * @brief Retrieves the process ID.
     * @return The unique ID of the process.
     */
    unsigned int getID() { return id; }

    /**
     * @brief Retrieves the priority of the process.
     * @return The priority value of the process.
     */
    unsigned int getPriority() { return priority; }

    /**
     * @brief Retrieves the current state of the process.
     * @return The process state as an enum value (`ProcState`).
     */
    ProcState getState() { return state; }

    /**
     * @brief Sets the state of the process.
     * @param state The new state to be assigned to the process.
     */
    void setState(ProcState state) { this->state = state; }

    /**
     * @brief Sets the priority of the process.
     * @param priority The new priority value to be assigned.
     */
    void setPriority(unsigned int priority) { this->priority = priority; }

    /**
     * @brief Displays the PCB details.
     * 
     * Prints the process ID, priority, and current state to the console.
     */
    void display() const {
        cout << "\tID: " << id << ", Priority: " << priority << ", State: ";
        switch (state) {
            case ProcState::NEW: cout << "NEW"; break;
            case ProcState::READY: cout << "READY"; break;
            case ProcState::RUNNING: cout << "RUNNING"; break;
            case ProcState::WAITING: cout << "WAITING"; break;
            case ProcState::TERMINATED: cout << "TERMINATED"; break;
        }
        cout << endl;
    }
};

