// ============================================================================
// Name: Oscar Lopez
// Date: 04/10/25
// Course: CS433 - Operating Systems Section 1
// Assignment: 4 - Multi-threaded Programing for the Producer-Consumer Problem 
// File type: buffer.cpp - implementation file
// ===========================================================================
#include "buffer.h"

// buffer variables
buffer_item buffer[BUFFER_SIZE];    // the circular buffer.
int front = 0;                      // position of the front item.
int back = 0;                       // position of the back item.
int count = 0;                      // number of items in buffer.

// PURPOSE: displays the current items in the buffer within bounds.
void display()
{
    int start = front;
    int i = 0;
    int j = 0;

    std::cout << "[";

    if (count == 0) {
        std::cout << "empty";
    } else {
        for (i = start; j < count; j++) {
            std::cout << buffer[i];
            i = (i + 1) % BUFFER_SIZE;  // Move to next position
            
            // Add comma if not the last element
            if (j < count - 1) {
                std::cout << ", ";
            }
        }
    }

    std::cout << "]" << std::endl;
}

// PURPOSE: checks if the buffer is full.
// RETURN: True = if count is equal to buffer size. False otherwise.
bool isFull() {
    return (count == BUFFER_SIZE);
}

// PURPOSE: checks if the buffer is empty.
// RETURN: True = if count is equal to 0. False otherwise.
bool isEmpty() {
    return (count == 0);
}

// PURPOSE: inserts an item into the circular buffer by updating back pointer.
// PARAMETER: item = the item to insert into buffer.
// RETURN: 0 = if insert was successful. -1 = if insert was unsuccessful.
int insert_item(buffer_item item) {

    // check if buffer is not full first.
    if (!isFull()) {
        buffer[back] = item;
        back = (back + 1) % BUFFER_SIZE;  // modulus used to wrap around.
        count++;

        return 0;
    }

    return -1;
}

// PURPOSE: removes an item from circular buffer by updating front pointer.
// PARAMETER: *item = the item removed from the buffer.
// RETURN: 0 = if insert was successful. -1 = if insert was unsuccessful.
int remove_item(buffer_item *item) {

    // check if buffer is not empty first.
    if (!isEmpty()) {
        *item = buffer[front];
        front = (front + 1) % BUFFER_SIZE;   // modulus used to wrap around.
        count--;

        return 0;
    }

    return -1;
}
