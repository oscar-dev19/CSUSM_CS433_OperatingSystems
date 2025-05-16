/**
* Assignment 5: Page replacement algorithms
 * @file lru_replacement.cpp
 * @author Oscar Lopez
 * @brief A class implementing a true LRU algorithm
 * @version 0.1
 */

#include "lru_replacement.h"
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <climits>

LRUReplacement::LRUReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames), clock_hand(0), pages_in_memory(0), lru_counter(0)
{
    // Allocate fixed-size array for clock buffer (faster than vector)
    clock_buffer = new int[num_frames];
    
    // Initialize clock buffer with -1 (empty) using memset for speed
    std::memset(clock_buffer, -1, num_frames * sizeof(int));
    
    // Allocate and initialize last_access array
    last_access = new unsigned long long[num_pages];
    std::memset(last_access, 0, num_pages * sizeof(unsigned long long));
    
    // Allocate and initialize page_to_frame_index array with -1 (not in memory)
    page_to_frame_index = new int[num_pages];
    std::memset(page_to_frame_index, -1, num_pages * sizeof(int));
}

LRUReplacement::LRUReplacement(const LRUReplacement& other)
: Replacement(other), clock_hand(other.clock_hand), 
  pages_in_memory(other.pages_in_memory), lru_counter(other.lru_counter),
  clock_buffer(nullptr), last_access(nullptr), page_to_frame_index(nullptr) // Initialize pointers to nullptr first
{
    // Deep copy of clock_buffer
    clock_buffer = new int[num_frames];
    std::memcpy(clock_buffer, other.clock_buffer, num_frames * sizeof(int));
    
    // Deep copy of last_access
    last_access = new unsigned long long[num_pages];
    std::memcpy(last_access, other.last_access, num_pages * sizeof(unsigned long long));
    
    // Deep copy of page_to_frame_index
    page_to_frame_index = new int[num_pages];
    std::memcpy(page_to_frame_index, other.page_to_frame_index, num_pages * sizeof(int));
}

LRUReplacement& LRUReplacement::operator=(const LRUReplacement& other) {
    if (this != &other) {
        // Clean up existing resources
        delete[] clock_buffer;
        delete[] last_access;
        delete[] page_to_frame_index;
        
        // Set to nullptr after deletion to avoid dangling pointers
        clock_buffer = nullptr;
        last_access = nullptr;
        page_to_frame_index = nullptr;
        
        // Copy base class
        Replacement::operator=(other);
        
        // Copy simple members
        clock_hand = other.clock_hand;
        pages_in_memory = other.pages_in_memory;
        lru_counter = other.lru_counter;
        
        // Deep copy of clock_buffer
        clock_buffer = new int[num_frames];
        std::memcpy(clock_buffer, other.clock_buffer, num_frames * sizeof(int));
        
        // Deep copy of last_access
        last_access = new unsigned long long[num_pages];
        std::memcpy(last_access, other.last_access, num_pages * sizeof(unsigned long long));
        
        // Deep copy of page_to_frame_index
        page_to_frame_index = new int[num_pages];
        std::memcpy(page_to_frame_index, other.page_to_frame_index, num_pages * sizeof(int));
    }
    return *this;
}

LRUReplacement::~LRUReplacement() {
    // Clean up dynamic memory
    delete[] clock_buffer;
    delete[] last_access;
    delete[] page_to_frame_index;
}

void LRUReplacement::touch_page(int page_num) {
    // Update the last access time for this page
    // Note: We don't increment lru_counter here to avoid double-counting
    // since access_page already increments it
    last_access[page_num] = lru_counter;
    
    // Set the reference bit (not actually used in true LRU, but kept for compatibility)
    page_table[page_num].referenced = true;
}

void LRUReplacement::load_page(int page_num) {
    // Find a free frame
    int frame = find_free_frame();
    
    // Update page table
    page_table[page_num].frame_num = frame;
    page_table[page_num].valid = true;
    page_table[page_num].referenced = true;
    
    // Add to clock buffer at current position
    clock_buffer[pages_in_memory] = page_num;
    
    // Update the mapping from page to frame index
    page_to_frame_index[page_num] = pages_in_memory;
    
    // Update the last access time for this page
    // We don't increment the counter here since it was already incremented in access_page
    last_access[page_num] = lru_counter;
    
    // Increment pages in memory
    pages_in_memory++; 
}

int LRUReplacement::replace_page(int page_num) {
    // True LRU implementation - find the least recently used page by checking all frames
    int victim_page = clock_buffer[0];
    int victim_pos = 0;
    unsigned long long oldest_access = ULLONG_MAX; // Start with maximum possible value
    
    // Check all frames to find the true LRU page
    for (int i = 0; i < pages_in_memory; i++) {
        int current_page = clock_buffer[i];
        if (current_page != -1 && last_access[current_page] < oldest_access) {
            oldest_access = last_access[current_page];
            victim_page = current_page;
            victim_pos = i;
        }
    }
    
    // Get the frame number of the victim page
    int victim_frame = page_table[victim_page].frame_num;
    
    // Update page table for victim
    page_table[victim_page].valid = false;
    
    // Mark the victim page as not in any frame
    page_to_frame_index[victim_page] = -1;
    
    // Update page table for new page
    page_table[page_num].frame_num = victim_frame;
    page_table[page_num].valid = true;
    page_table[page_num].referenced = true;
    
    // Update the last access time for the new page
    // Use the current counter value without incrementing to maintain proper LRU ordering
    last_access[page_num] = lru_counter;
    
    // Update clock buffer and page-to-frame mapping
    clock_buffer[victim_pos] = page_num;
    page_to_frame_index[page_num] = victim_pos;
    
    // Update statistics
    page_replacements++;
    
    return victim_page;
}

bool LRUReplacement::access_page(int page_num, bool is_write) {
    // Increment total references
    total_references++;
    
    // Increment the LRU counter once per page access
    ++lru_counter;
    
    // Check if the page is already in memory
    if (page_table[page_num].valid) {
        // Page hit - update the last access time for this page using touch_page
        touch_page(page_num);
        
        // Update dirty bit if this is a write
        if (is_write) {
            page_table[page_num].dirty = true;
        }
        
        return false; // No page fault
    }
    
    // Page fault occurred
    page_faults++;
    
    // Set dirty bit if this is a write
    if (is_write) {
        page_table[page_num].dirty = true;
    }
    
    // Check if we have free frames
    if (pages_in_memory < num_frames) {
        // We have a free frame available
        load_page(page_num);
    } else {
        // No free frames, need to replace a page
        replace_page(page_num);
    }
    
    return true; // Page fault occurred
}