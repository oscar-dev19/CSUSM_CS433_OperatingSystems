/**
* Assignment 5: Page replacement algorithms
 * @file replacement.cpp
 * @author Oscar Lopez
 * @brief A base class for different page replacement algorithms.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include <iostream>
#include "replacement.h"

// Constructor: Initialize member variables
Replacement::Replacement(int num_pages, int num_frames)
: page_table(num_pages)
{
	this->num_pages = num_pages;
	this->num_frames = num_frames;
	this->page_faults = 0;
	this->page_replacements = 0;
	this->total_references = 0;
	
	// Initialize free frames tracking
	free_frames = new bool[num_frames];
	for (int i = 0; i < num_frames; i++) {
		free_frames[i] = true;  // All frames are initially free
	}
	next_frame = 0;
}

// Destructor: Clean up any allocated memory
Replacement::~Replacement()
{
	delete[] free_frames;
}

// Helper function to find the next free frame
int Replacement::find_free_frame() {
	for (int i = 0; i < num_frames; i++) {
		if (free_frames[i]) {
			free_frames[i] = false;  // Mark as used
			return i;
		}
	}
	return -1;  // No free frames available
}

// Simulate a single page access 
// @return true if it's a page fault
bool Replacement::access_page(int page_num, bool is_write)
{
	total_references++;
	
	// Check if the page is valid (in memory)
	if (page_table[page_num].valid) {
		// Page is in memory, just update access info
		touch_page(page_num);
		if (is_write) {
			page_table[page_num].dirty = true;
		}
		return false;  // No page fault
	}
	
	// Page fault occurred
	page_faults++;
	
	// Try to find a free frame
	int frame = find_free_frame();
	if (frame != -1) {
		// We have a free frame available
		page_table[page_num].frame_num = frame;
		page_table[page_num].valid = true;
		page_table[page_num].dirty = is_write;
		load_page(page_num);
	} else {
		// No free frames, need to replace a page
		replace_page(page_num);
	}
	
	return true;  // Page fault occurred
}

// Print out statistics of simulation
void Replacement::print_statistics() const {
	std::cout << "Number of references: \t\t" << total_references << std::endl;
	std::cout << "Number of page faults: \t\t" << page_faults << std::endl;
	std::cout << "Number of page replacements: \t" << page_replacements << std::endl;
}