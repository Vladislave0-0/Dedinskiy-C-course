#ifndef DSL_H
#define DSL_H

#define PUUSH(elem)     stack_push(cpu->stack, elem)
#define POOP(elem)      stack_pop(cpu->stack, elem)
#define CREG            (cpu->REG)
#define RAX             (cpu->REG)[0]
#define RBX             (cpu->REG)[1]
#define RCX             (cpu->REG)[2]
#define RDX             (cpu->REG)[3]
#define CRAM            (cpu->RAM)

#endif //DSL_H
