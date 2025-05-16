/**
* Assignment 5: Page replacement algorithms
 * @file fifo_replacement.cpp
 * @author Oscar Lopez
 * @brief A class implementing the FIFO page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "fifo_replacement.h"

FIFOReplacement::FIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    // No additional initialization needed
}

FIFOReplacement::~FIFOReplacement() {
    // Clear the queue (though it would happen automatically)
    while (!page_queue.empty()) {
        page_queue.pop();
    }
}

// Access an invalid page, but free frames are available
void FIFOReplacement::load_page(int page_num) {
    // Add to FIFO queue
    page_queue.push(page_num);
}

// Access an invalid page and no free frames are available
int FIFOReplacement::replace_page(int page_num) {
    // Get the oldest page from the queue
    int victim_page = page_queue.front();
    page_queue.pop();
    
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
    
    // Add new page to FIFO queue
    page_queue.push(page_num);
    
    // Update statistics
    page_replacements++;
    
    return victim_page;
}