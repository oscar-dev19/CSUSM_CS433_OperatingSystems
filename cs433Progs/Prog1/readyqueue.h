#pragma once
#include "pcb.h"

/**
 * @class ReadyQueue
 * @brief Implements a priority queue using a max heap to manage process scheduling.
 * 
 * The ReadyQueue stores Process Control Blocks (PCBs) and organizes them based on priority.
 * It ensures that the highest-priority process is always dequeued first.
 */
class ReadyQueue {
private:
    PCB** heap;   ///< Dynamic array storing PCB pointers.
    int capacity; ///< Maximum number of PCBs the queue can hold.
    int count;    ///< Current number of PCBs in the queue.

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    /**
     * @brief Constructs a ReadyQueue with a specified capacity.
     * 
     * @param capacity The maximum number of PCBs the queue can hold. Default is 500.
     */
    ReadyQueue(int capacity = 500);

    /**
     * @brief Destructor for ReadyQueue.
     */
    ~ReadyQueue();

    /**
     * @brief Copy constructor for ReadyQueue.
     * 
     * Performs a deep copy to ensure that each instance maintains its own heap memory.
     * 
     * @param other The ReadyQueue instance to copy.
     */
    ReadyQueue(const ReadyQueue& other);

    /**
     * @brief Copy assignment operator for ReadyQueue.
     * 
     * Ensures that dynamically allocated memory is properly handled.
     * 
     * @param other The ReadyQueue instance to assign from.
     * @return Reference to the updated ReadyQueue instance.
     */
    ReadyQueue& operator=(const ReadyQueue& other);

    void addPCB(PCB* pcbPtr);
    PCB* removePCB();
    int size();
    void displayAll();
};

