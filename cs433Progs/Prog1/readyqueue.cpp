#include <iostream>
#include "readyqueue.h"

using namespace std;

/**
 * @brief Constructs a ReadyQueue with a specified capacity.
 * 
 * @param capacity The maximum number of PCBs the queue can hold. Default is 500.
 */
ReadyQueue::ReadyQueue(int capacity) : capacity(capacity), count(0) {
    heap = new PCB*[capacity]; ///< Dynamic array to store PCB pointers.
}

/**
 * @brief Destructor for ReadyQueue.
 * 
 * Frees dynamically allocated memory.
 */
ReadyQueue::~ReadyQueue() {
    delete[] heap;
}

/**
 * @brief Copy constructor for ReadyQueue.
 * 
 * Creates a deep copy to ensure that each ReadyQueue instance maintains its own heap memory.
 * 
 * @param other The ReadyQueue instance to copy.
 */
ReadyQueue::ReadyQueue(const ReadyQueue& other) 
    : capacity(other.capacity), count(other.count) {
    heap = new PCB*[capacity];

    for (int i = 0; i < count; ++i) {
        heap[i] = other.heap[i]; ///< Copying PCB pointers.
    }
}

/**
 * @brief Copy assignment operator for ReadyQueue.
 * 
 * Ensures proper memory handling and prevents memory leaks.
 * 
 * @param other The ReadyQueue instance to assign from.
 * @return Reference to the updated ReadyQueue instance.
 */
ReadyQueue& ReadyQueue::operator=(const ReadyQueue& other) {
    if (this == &other) return *this; // Prevent self-assignment

    // Free existing memory
    delete[] heap;

    // Copy new values
    capacity = other.capacity;
    count = other.count;
    heap = new PCB*[capacity];

    for (int i = 0; i < count; ++i) {
        heap[i] = other.heap[i]; ///< Copying PCB pointers.
    }

    return *this;
}

void ReadyQueue::addPCB(PCB* pcbPtr) {
    if (count >= capacity) {
        cout << "Queue is full, cannot add more PCBs!" << endl;
        return;
    }
    pcbPtr->setState(ProcState::READY);
    heap[count] = pcbPtr;
    heapifyUp(count);
    count++; 
}

PCB* ReadyQueue::removePCB() {
    if (count == 0) return nullptr;

    PCB* top = heap[0];
    top->setState(ProcState::RUNNING);
    count--;

    heap[0] = heap[count];
    heapifyDown(0);

    return top;
}

int ReadyQueue::size() {
    return count;
}

void ReadyQueue::displayAll() {
    for (int i = 0; i < count; ++i) { // Changed i++ to ++i
        heap[i]->display();
    }
}

void ReadyQueue::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[parent]->getPriority() >= heap[index]->getPriority()) break;

        swap(heap[parent], heap[index]);
        index = parent;
    }
}

void ReadyQueue::heapifyDown(int index) {
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < count && heap[left]->getPriority() > heap[largest]->getPriority())
            largest = left;
        if (right < count && heap[right]->getPriority() > heap[largest]->getPriority())
            largest = right;
        if (largest == index) break;

        swap(heap[index], heap[largest]);
        index = largest;
    }
}

