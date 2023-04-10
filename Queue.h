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

enum QueueErrors
{
    ERROR_DATA_CALLOC_NULLPTR = 1,
    ERROR_QUEUE_NULLPTR       = 2,
    ERROR_LOG_FILE_OPEN       = 3,
    ERROR_CAPACITY_USER_INPUT = 4,
};

//==========================================================================

int queue_ctor(struct queue* que);

//==========================================================================

void fill_with_POISON(struct queue* que);

//==========================================================================

void queue_push(struct queue* que, elem_t value);

//==========================================================================

elem_t queue_pop(struct queue* que);

//==========================================================================

void que_dot_print(struct queue* que);

//==========================================================================

void terminal_menu(struct queue* que);

//==========================================================================

void queue_dtor(struct queue* que);

//==========================================================================

int check_que_tail(struct queue* que);

//==========================================================================

#endif //QUEUE_H
