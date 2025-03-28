#include <stdio.h>
#include <string.h>

#include "stack.h"

int main() {
    
    stack_t stack_1 = {};
    stack_ctor(&stack_1, 5);

    printf("Print a command without spaces and commas\nCommands:\nPush <number>,\nPop,\nVerificator,\nDump,\nExit,\n");

    while(true) {
        
        printf("user:~$ ");

        char cmd[100] = "";
        
        if (scanf("%s", cmd) == 0) {
            printf("error");
            break;
        }

        int action = 0;

        if (strcasecmp(cmd, "push") == 0) {
            action = PUSH;
        }

        else if(strcasecmp(cmd, "pop") == 0) {
            action = POP;
        }

        else if (strcasecmp(cmd, "verificator") == 0) {
            action = VERIFICATOR;
        }

        else if (strcasecmp(cmd, "dump") == 0) {
            action = STACK_DUMP;
        }

        else if (strcasecmp(cmd, "exit") == 0) {
            action = EXIT;
        }

        else {
            printf("No such command, try again\n");
        }
    
        switch (action) {

            case PUSH: {
                double value = 0;
                
                if (scanf("%lg", &value) == 0){
                    printf("Error: you can push only numbers\n");
                }
                
                else {
                    stack_push(&stack_1, value);
                }

                break;
            }

            case POP: {
                double stack_peak = 0;
                
                if(!isEqual((stack_peak = stack_pop(&stack_1)), EMPTY_STACK_ERROR)) {
                    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("    stack_peak = %lg\n", stack_peak);             
                    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");     
                }
                
                break;
            }

            case VERIFICATOR: 
                verificator(&stack_1);
                break;

            case STACK_DUMP: 
                stack_dump(&stack_1);
                break;

            case EXIT: 
                stack_dtor(&stack_1);
                return 0;
                break;

            default:
                break;    
        }
    }

    return 0;
}