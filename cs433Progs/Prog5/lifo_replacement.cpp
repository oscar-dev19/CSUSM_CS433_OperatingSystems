/**
 * Assignment 5: Page replacement algorithms
 * @file lifo_replacement.cpp
 * @author Oscar Lopez
 * @brief Implementation of the LIFO page replacement algorithm
 * @version 0.1
 * 
 * This file contains the implementation of the Last-In-First-Out (LIFO)
 * page replacement algorithm. The algorithm uses a stack to track page order
 * and selects the most recently loaded page as the victim for replacement.
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "lifo_replacement.h"

/**
 * Constructor initializes the LIFO replacement algorithm
 * Inherits base initialization from Replacement class
 */
LIFOReplacement::LIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    // No additional initialization needed beyond base class
}

/**
 * Destructor ensures proper cleanup of the page stack
 * Although the stack would clean itself automatically, we explicitly
 * clear it for good practice and to prevent any potential memory leaks
 */
LIFOReplacement::~LIFOReplacement() {
    while (!page_stack.empty()) {
        page_stack.pop();
    }
}

/**
 * Loads a new page into memory when free frames are available
 * The page is pushed onto the stack to maintain LIFO order
 */
void LIFOReplacement::load_page(int page_num) {
    page_stack.push(page_num);
}

/**
 * Implements the LIFO page replacement algorithm when no free frames are available
 * 1. Selects the most recently added page as victim (top of stack)
 * 2. Frees the victim's frame
 * 3. Updates page table entries
 * 4. Loads the new page into the freed frame
 * 5. Updates replacement statistics
 */
int LIFOReplacement::replace_page(int page_num) {
    // Get the most recently added page from the stack
    int victim_page = page_stack.top();
    page_stack.pop();
    
    // Get the frame number from the victim page
    int victim_frame = page_table[victim_page].frame_num;
    
    // Mark the victim's frame as available
    free_frames[victim_frame] = true;
    
    // Invalidate the victim page's entry
    page_table[victim_page].valid = false;
    page_table[victim_page].frame_num = -1;
    
    // Load the new page into the victim's frame
    page_table[page_num].frame_num = victim_frame;
    page_table[page_num].valid = true;
    free_frames[victim_frame] = false;  // Mark frame as used
    
    // Add new page to LIFO stack
    page_stack.push(page_num);
    
    // Update replacement statistics
    page_replacements++;
    
    return victim_page;
}