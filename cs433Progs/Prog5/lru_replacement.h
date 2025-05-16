/**
* Assignment 5: Page replacement algorithms
 * @file lru_replacement.h
 * @author Oscar Lopez
 * @brief A class implementing a highly optimized Clock-LRU algorithm
 * @version 0.1
 */

#ifndef LRU_REPLACEMENT_H
#define LRU_REPLACEMENT_H

#include "replacement.h"
#include <unordered_map>

/**
 * @brief A class implementing the LRU page replacement algorithm
 */
class LRUReplacement : public Replacement
{
private:
	// Use a fixed-size array for clock buffer (faster than vector for fixed size)
	int* clock_buffer;
	
	// Current position in the clock buffer
	int clock_hand;
	
	// Number of pages currently in memory
	int pages_in_memory;
	
	// Counter for LRU tracking
	unsigned long long lru_counter;
	
	// Array to store last access time for each page
	unsigned long long* last_access;
	
	// Array to store frame index for each page (for quick lookup)
	int* page_to_frame_index;

public:
	/**
	 * Constructor
	 * @param num_pages Total number of pages in the system
	 * @param num_frames Total number of frames in the system
	 */
	LRUReplacement(int num_pages, int num_frames);
	
	/**
	 * Copy constructor
	 * @param other The LRUReplacement object to copy from
	 */
	LRUReplacement(const LRUReplacement& other);
	
	/**
	 * Assignment operator
	 * @param other The LRUReplacement object to assign from
	 * @return Reference to this object
	 */
	LRUReplacement& operator=(const LRUReplacement& other);
	
	/**
	 * Destructor
	 */
	~LRUReplacement();
	
	/**
	 * Access a page already in the memory
	 * @param page_num The logical page number to be accessed
	 */
	void touch_page(int page_num);
	
	/**
	 * Load a page that is not in the memory
	 * @param page_num The logical page number to be loaded
	 */
	void load_page(int page_num);
	
	/**
	 * Replace an existing page with a new page
	 * @param page_num The logical page number to be loaded
	 * @return The page number of the replaced page
	 */
	int replace_page(int page_num);
	
	/**
	 * Access a page, if it's not in the memory, load it
	 * @param page_num The logical page number to be accessed
	 * @param is_write Whether the access is a write
	 * @return Whether a page fault occurred
	 */
	bool access_page(int page_num, bool is_write);
};

#endif // LRU_REPLACEMENT_H