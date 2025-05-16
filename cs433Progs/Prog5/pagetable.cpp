/**
* Assignment 5: Page replacement algorithms
 * @file pagetable.cpp
 * @author Oscar Lopez
 * @brief This class represents a traditional pagetable data structure.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "pagetable.h"

// Constructor: Initializes a page table with the specified number of pages
// Each page entry is initialized with frame_num = -1 (indicating no frame assigned)
// valid bit = false (page not in memory), and dirty bit = false
PageTable::PageTable(int num_pages) {
    // Resize the pages vector to hold num_pages entries
    pages.resize(num_pages);
    // Initialize each page entry
    for (int i = 0; i < num_pages; i++) {
        pages[i].frame_num = -1;  // No frame assigned initially
        pages[i].valid = false;   // Page not in memory
        pages[i].dirty = false;   // Page not modified
    }
}

// Destructor: Cleans up the page table
// The vector will automatically clean up its memory
PageTable::~PageTable() {
    // Vector automatically handles cleanup
    pages.clear();
}