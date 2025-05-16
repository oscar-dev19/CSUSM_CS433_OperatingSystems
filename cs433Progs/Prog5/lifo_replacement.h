/**
 * Assignment 5: Page replacement algorithms
 * @file lifo_replacement.h
 * @author Oscar Lopez
 * @brief A class implementing the LIFO page replacement algorithm
 * @version 0.1
 * 
 * This class implements the Last-In-First-Out (LIFO) page replacement algorithm.
 * In LIFO, when a page fault occurs and no free frames are available, the most
 * recently loaded page is selected as the victim for replacement. This is implemented
 * using a stack data structure where new pages are pushed onto the stack and
 * victim pages are popped from the top.
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#pragma once

// Remember to add comments to your code

#include "replacement.h"
#include <stack>

/**
 * @brief A class to simulate LIFO (Last-In-First-Out) page replacement algorithm.
 * 
 * The LIFO algorithm maintains a stack of pages in memory, where the most recently
 * loaded page is at the top of the stack. When a page needs to be replaced, the
 * algorithm chooses the page at the top of the stack (the most recently loaded one)
 * as the victim.
 */
class LIFOReplacement : public Replacement {
private:
    /** Stack to maintain the order of pages loaded into memory (LIFO order) */
    std::stack<int> page_stack;

public:
    /**
     * @brief Constructor
     * @param num_pages Total number of pages in the logical address space
     * @param num_frames Total number of physical frames available in memory
     */
    LIFOReplacement(int num_pages, int num_frames);

    /**
     * @brief Destructor - cleans up any allocated resources
     */
    virtual ~LIFOReplacement();

    /**
     * @brief Load a page into memory when free frames are available
     * @param page_num The logical page number to be loaded
     * @details The page is assigned to an available frame and pushed onto the stack
     */
    virtual void load_page(int page_num);

    /**
     * @brief Replace a page when no free frames are available
     * @param page_num The logical page number to be loaded
     * @return The page number of the victim page that was replaced
     * @details Selects the most recently loaded page (top of stack) as victim,
     *          removes it from memory, and loads the new page in its place
     */
    virtual int replace_page(int page_num);
};
