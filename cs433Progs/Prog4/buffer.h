// ===========================================================================
// Name: Oscar Lopez
// Date: 04/10/25
// Course: CS433 - Operating Systems Section 1
// Assignment: 4 - Multi-threaded Programing for the Producer-Consumer Problem 
// File type: buffer.h - header file
// ===========================================================================
#pragma once
#include <iostream>

typedef int buffer_item;        // buffer_item defined as an int.
#define BUFFER_SIZE 5           // size of the buffer

// Function declarations
void display();
bool isFull();
bool isEmpty();
int insert_item(buffer_item item);
int remove_item(buffer_item *item);
