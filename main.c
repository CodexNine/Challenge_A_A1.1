#include "robot_lib.h"
#include "MazeRouter_lib.h"
#include "global.h"
#include <Windows.h>
#include <stdlib.h>

extern int checkpoints[3];
extern char instruct_output[];

int main()
{
    int i;
   int status;
   int stations[3];
   char input,output;
   /*the sees is some random value
   each seed value corresponds to only one set of stations
   use seed NULL for random seed
   */


   //char seed[10];
   status = robot_lib_connect(NULL, stations, 'a', NULL);
   printf("try to complete challenge A\n");

shortest(1, stations[0], stations[1], stations[2]);
direction(checkpoints[0], checkpoints[1], checkpoints[2]);


for(i = 0; i<strlen(instruct_output);i++){
   while(1){
       status = robot_lib_read_byte(&input);
       printf("Received: %c, in decimal: %d\n",input,input);
       if(input==0 || input==10){ /*in a previous version of the protocol we used 10*/
           printf("automatically send 0 back\n");
           output = input;
       }else if(input=='n'){
           printf("FINISHED CHALLENGE\n");
           break;
       }else if(input=='g' || input == 't' || input == 'z'){
           output = instruct_output[i];
           printf("Character sent: %c\n", output);
            robot_lib_write_byte(output);
            break;
           /*little trick to remove '\n' from input buffer*/
       } else {
            continue;
       }

       if(output=='q'){
           break;
       }


   }
}
   robot_lib_disconnect();

   /*
   hint:
   type the messages in this order to finish the challenge:
   rrtffflfftflfs
   */

    return 0;
}
