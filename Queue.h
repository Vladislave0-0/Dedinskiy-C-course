#ifndef QUEUE_H
#define QUEUE_H

//==========================================================================

#include <stdlib.h>
#include <stdio.h>

//==========================================================================

typedef int elem_t;

//==========================================================================

const elem_t POISON   = 0xDEADDED;
const int FULL_QUEUE  = 1;
const int EMPTY_QUEUE = 0;

//==========================================================================
/**
 * @brief Queue structure.
 * 
 */
struct queue
{
    FILE* queue_log = nullptr;

    int capacity = 0;
    int mask     = 0;
    elem_t* data = nullptr;
    int size     = 0;

    int tail = 0;
    int head = 0;

    int error_code = 0;
};

//==========================================================================
/**
 * @brief enum for queue errors.
 * 
 */
enum QueueErrors
{
    ERROR_DATA_CALLOC_NULLPTR = 1,
    ERROR_QUEUE_NULLPTR       = 2,
    ERROR_LOG_FILE_OPEN       = 3,
    ERROR_CAPACITY_USER_INPUT = 4,
};

//==========================================================================
/**
 * @brief Creating and populating the queue structure. Handling user input.
 * 
 * @param que the queue pointer
 * @return int error code
 */
int queue_ctor(struct queue* que);

//==========================================================================
/**
 * @brief Filling all cells of the queue with a poison value during 
 *        initialization.
 * 
 * @param que the queue pointer
 */
void fill_with_POISON(struct queue* que);

//==========================================================================
/**
 * @brief Adding an element to the end of the queue.
 * 
 * @param que the queue pointer
 * @param value element to be queued
 */
void queue_push(struct queue* que, elem_t value);

//==========================================================================
/**
 * @brief Removing the first element in the queue.
 * 
 * @param que the queue pointer
 * @return elem_t Element that was removed
 */
elem_t queue_pop(struct queue* que);

//==========================================================================
/**
 * @brief Function for printing in dot language for graphviz.
 * 
 * @param que the queue pointer
 */
void que_dot_print(struct queue* que);

//==========================================================================
/**
 * @brief Menu for the user with a choice of actions on the queue.
 * 
 * @param que the queue pointer
 */
void terminal_menu(struct queue* que);

//==========================================================================
/**
 * @brief Freeing memory, closing a file, deleting queued values.
 * 
 * @param que the queue pointer
 */
void queue_dtor(struct queue* que);

//==========================================================================
/**
 * @brief Returns 0 if the queue is not full, and 1 if full.
 * 
 * @param que the queue pointer
 * @return int state of fullness
 */
int check_que_tail(struct queue* que);

//==========================================================================

#endif //QUEUE_H
