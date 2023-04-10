#include "Queue.h"

//=========================================================================================================

int queue_ctor(struct queue* que)
{
    if(que == nullptr)
    {
        que->error_code = ERROR_QUEUE_NULLPTR;

        printf("Error code: %d. Check file \"Queue.h\" to decipher the error code.\n", que->error_code);

        return que->error_code;
    }

    que->queue_log = fopen("queue_log.dot", "w");

    if(que->queue_log == nullptr)
    {
        que->error_code = ERROR_LOG_FILE_OPEN;

        printf("Error code: %d. Check file \"Queue.h\" to decipher the error code.\n", que->error_code);

        return que->error_code;
    }

    printf("Hello, this is the terminal menu. The queue can be of size as a power of two. "
           "Select the queue size you need: enter a power of two from 1 to 9.\n");

    int power = 0;

    int scanf_check = scanf("%d", &power);

    if(scanf_check != 1 || (power < 1) || (power > 9))
    {
        que->error_code = ERROR_CAPACITY_USER_INPUT;

        printf("Error code: %d. Check file \"Queue.h\" to decipher the error code.\n", que->error_code);

        return que->error_code;
    }

    que->capacity = 1 << power; 

    que->mask = que->capacity - 1;

    que->data = (elem_t*)calloc(que->capacity, sizeof(elem_t));

    if(que->data == nullptr)
    {
        que->error_code = ERROR_DATA_CALLOC_NULLPTR;

        printf("Error code: %d. Check file \"Queue.h\" to decipher the error code.\n", que->error_code);

        return que->error_code;
    }

    fill_with_POISON(que);

    return 0;
}

//=========================================================================================================

void fill_with_POISON(struct queue* que)
{
    for(int i = 0; i < que->capacity; i++)
    {
        que->data[i] = POISON;
    }
}

//=========================================================================================================

void queue_push(struct queue* que, elem_t value)
{
    if(check_que_tail(que) == EMPTY_QUEUE)
    {
        que->data[que->tail] = value;
        que->size++;
        que->tail++;

        que->tail = que->tail & que->mask;
    }
    
    else
    {
        printf("Queue is full! If you want to continue remove the value from the queue.\n");
    }
}

//=========================================================================================================

elem_t queue_pop(struct queue* que)
{
    elem_t pop_value = 0;

    if(que->size != 0)
    {
        pop_value = que->data[que->head];

        que->data[que->head] = POISON;

        que->head++;

        que->size--;

        que->head = que->head & que->mask;

        return pop_value;
    }

    else
    {
        printf("Queue is empty! If you want to continue push the value in the queue.\n");

        return pop_value;
    }

    return pop_value;
}

//=========================================================================================================

void que_dot_print(struct queue* que)
{
    fprintf(que->queue_log, "digraph G\n{\n");

    fprintf(que->queue_log, "    {\n    rankdir = BT;\n");

    fprintf(que->queue_log, "    size = \"6.7, 15\";\n");

    fprintf(que->queue_log, "    first [color = \"red\", shape = record, label = \"{ {size} | {%d} } | { {head_pos} | {%d} } | { {tail_pos} | {%d} }\"];\n    }\n\n\n", que->size, que->head, que->tail);

    fprintf(que->queue_log, "    {\n    rankdir = BT;\n");

    fprintf(que->queue_log, "    second [shape = record, label = \"");

    for(int i = 0; i < que->capacity - 1; i++)
    {
        fprintf(que->queue_log, "{ {data[%d]} | ", i);

        if(que->data[i] == POISON)
        {
            fprintf(que->queue_log, "{POISON} } | ");
        }

        else
        {
            fprintf(que->queue_log, "{%d} } | ", que->data[i]);
        }
    }

    fprintf(que->queue_log, "{ {data[%d]} | ", que->capacity - 1);

    if(que->data[que->capacity - 1] == POISON)
    {
        fprintf(que->queue_log, "{POISON} } \"];\n");
    }

    else
    {
        fprintf(que->queue_log, "{%d} } \"];\n", que->data[que->capacity - 1]);
    }

    fprintf(que->queue_log, "    }\n");

    fprintf(que->queue_log, "}");
}

//=========================================================================================================

void terminal_menu(struct queue* que)
{
    printf("\nWrite the number of the command you want to use.\n");

    int command = 0;

    while(command != 4)
    {
        printf("\n| 1 - push | 2 - pop | 3 - print queue | 4 - exit |\nCommand: ");

        scanf("%d", &command);

        switch(command)
        {
            case(1):
            {
                printf("Write push value: ");
                
                elem_t push_val = 0;

                scanf("%d", &push_val);

                queue_push(que, push_val);

                break;
            }

            case(2):
            {
                queue_pop(que);

                break;
            }

            case(3):
            {
                que_dot_print(que);

                break;
            }

            case(4):
            {
                return;
            }

            default:
            {
                printf("Unknown command!\n");

                break;
            }
        }
    }
}

//=========================================================================================================

int check_que_tail(struct queue* que)
{
    if((que->tail == que->head) && (que->size != 0))
    {
        return FULL_QUEUE;
    }

    else
    {
        return EMPTY_QUEUE;
    }
}

//=========================================================================================================

void queue_dtor(struct queue* que)
{
    fill_with_POISON(que);

    que->error_code = 0;
    que->capacity   = 0;
    que->size       = 0;

    fclose(que->queue_log);
    que->queue_log = nullptr;
    
    free(que->data);
    que->data = nullptr;
}
