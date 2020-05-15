#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
/*
Author: David van der Laan, 5131669
Maze Router program for Smart Robot Challenge.
Group A1
*/

void clr_kruising() {
    memcpy(kruising, clear_kruising, sizeof(kruising));
}

int mazeRouter(int start, int finish) {
  int i, j, sco1, sco2, fco1, fco2;
  int count, flag = 87;
  int time_penalty = 0;
  char heading;
  int field[13][13] = {{0}};


  memcpy(field, unchanged_field, sizeof(field));

/* start of program */

      /*Conversion from input to coordinates in field*/
         switch(start) {
          case 1:
            sco1 = 12;
            sco2 = 4;
            field[sco1-1][sco2] = 0;
            heading = 'n';
            break;
          case 2:
            sco1 = 12;
            sco2 = 6;
            heading = 'n';
            field[sco1-1][sco2] = 0;
            break;
          case 3:
            sco1 = 12;
            sco2 = 8;
            heading = 'n';
            field[sco1-1][sco2] = 0;
            break;
          case 4:
            sco1 = 8;
            sco2 = 12;
            heading = 'w';
            field[sco1][sco2-1] = 0;
            break;
          case 5:
            sco1 = 6;
            sco2 = 12;
            heading = 'w';
            field[sco1][sco2-1] = 0;
            break;
          case 6:
            sco1 = 4;
            sco2 = 12;
            heading = 'w';
            field[sco1][sco2-1] = 0;
            break;
          case 7:
            sco1 = 0;
            sco2 = 8;
            heading = 's';
            field[sco1+1][sco2] = 0;
            break;
          case 8:
            sco1 = 0;
            sco2 = 6;
            heading = 's';
            field[sco1+1][sco2] = 0;
            break;
          case 9:
            sco1 = 0;
            sco2 = 4;
            heading = 's';
            field[sco1+1][sco2] = 0;
            break;
          case 10:
            sco1 = 4;
            sco2 = 0;
            heading = 'e';
            field[sco1][sco2+1] = 0;
            break;
          case 11:
            sco1 = 6;
            sco2 = 0;
            heading = 'e';
            field[sco1][sco2+1] = 0;
            break;
          case 12:
            sco1 = 8;
            sco2 = 0;
            heading = 'e';
            field[sco1][sco2+1] = 0;
            break;
         };

         switch(finish) {
          case 1:
            fco1 = 12;
            fco2 = 4;
            field[fco1-1][fco2] = 0;
            break;
          case 2:
            fco1 = 12;
            fco2 = 6;
            field[fco1-1][fco2] = 0;
            break;
          case 3:
            fco1 = 12;
            fco2 = 8;
            field[fco1-1][fco2] = 0;
            break;
          case 4:
            fco1 = 8;
            fco2 = 12;
            field[fco1][fco2-1] = 0;
            break;
          case 5:
            fco1 = 6;
            fco2 = 12;
            field[fco1][fco2-1] = 0;
            break;
          case 6:
            fco1 = 4;
            fco2 = 12;
            field[fco1][fco2-1] = 0;
            break;
          case 7:
            fco1 = 0;
            fco2 = 8;
            field[fco1+1][fco2] = 0;
            break;
          case 8:
            fco1 = 0;
            fco2 = 6;
            field[fco1+1][fco2] = 0;
            break;
          case 9:
            fco1 = 0;
            fco2 = 4;
            field[fco1+1][fco2] = 0;
            break;
          case 10:
            fco1 = 4;
            fco2 = 0;
            field[fco1][fco2+1] = 0;
            break;
          case 11:
            fco1 = 6;
            fco2 = 0;
            field[fco1][fco2+1] = 0;
            break;
          case 12:
            fco1 = 8;
            fco2 = 0;
            field[fco1][fco2+1] = 0;
            break;
         };

      /*Algorithm from manual */
      count = 1;
      field[fco1][fco2] = count;
      while (field[sco1][sco2] == 0) {
           for(i = 0; i < 13; i++) {                //Improvement to be made for for looping through.
             for(j = 0; j < 13; j++) {
                if(field[i][j]==count) {
                  if(field[i+1][j]==0){
                    field[i+1][j] = count + 1;
                  }
                  if(field[i-1][j]==0){
                    field[i-1][j] = count + 1;
                  }
                  if(field[i][j+1]==0){
                    field[i][j+1] = count + 1;
                  }
                  if(field[i][j-1]==0){
                    field[i][j-1] = count + 1;
                  }
                };
             };
           };
           count++;
         };

      /*trace back (here also the preferences for random routes can be adjusted)*/
      i = sco1;
      j = sco2;
    int m = 0;

      while(i!=fco1 || j!=fco2){

      int oldI = i;
      int oldJ = j;
        if(i%2==0 && j%2==0){
          kruising[m][0]= i;
          kruising[m][1]= j;
          m++;
        }
      switch(heading){
        case 'n':
          if(field[i-1][j]<field[i][j] && field[i-1][j]>0){
          field[i][j] = flag;
          heading = 'n';
          i--;
        }
          else if(field[i+1][j]<field[i][j] && field[i+1][j]>0){
            field[i][j] = flag;
            heading = 's';
            i++;
          }
          else if(field[i][j+1]<field[i][j]  && field[i][j+1]>0){
            field[i][j] = flag;
            heading = 'e';
            j++;
        }
          else if(field[i][j-1]<field[i][j]  && field[i][j-1]>0){
            field[i][j] = flag;
            heading = 'w';
            j--;
          }
          if(oldJ != j){
            time_penalty += 5;
          }
          break;
        case 's':
          if(field[i+1][j]<field[i][j] && field[i+1][j]>0){
          field[i][j] = flag;
          heading = 's';
          i++;
        }
          else if(field[i-1][j]<field[i][j] && field[i-1][j]>0){
          field[i][j] = flag;
          heading = 'n';
          i--;
        }
          else if(field[i][j+1]<field[i][j]  && field[i][j+1]>0){
          field[i][j] = flag;
          heading = 'e';
          j++;
      }
          else if(field[i][j-1]<field[i][j]  && field[i][j-1]>0){
          field[i][j] = flag;
          heading = 'w';
          j--;
        }
          if(oldJ != j){
            time_penalty += 5;
          }
          break;
        case 'e':
          if(field[i][j+1]<field[i][j]  && field[i][j+1]>0){
          field[i][j] = flag;
          heading = 'e';
          j++;
      }
          else if(field[i+1][j]<field[i][j] && field[i+1][j]>0){
        field[i][j] = flag;
        heading = 's';
        i++;
      }
          else if(field[i-1][j]<field[i][j] && field[i-1][j]>0){
        field[i][j] = flag;
        heading = 'n';
        i--;
      }
          else if(field[i][j-1]<field[i][j]  && field[i][j-1]>0){
        field[i][j] = flag;
        heading = 'w';
        j--;
      }
          if(oldI != i){
            time_penalty += 5;
          }
          break;
        case 'w':
          if(field[i][j-1]<field[i][j]  && field[i][j-1]>0){
          field[i][j] = flag;
          heading = 'w';
          j--;
        }
          else if(field[i-1][j]<field[i][j] && field[i-1][j]>0){
          field[i][j] = flag;
          heading = 'n';
          i--;
        }
          else if(field[i][j+1]<field[i][j]  && field[i][j+1]>0){
          field[i][j] = flag;
          heading = 'e';
          j++;
      }
          else if(field[i+1][j]<field[i][j] && field[i+1][j]>0){
            field[i][j] = flag;
            heading = 's';
            i++;
          }
          if(oldI != i){
            time_penalty += 5;
          }
          break;
      }
        time_penalty++;
      };
     kruising[m][0] = fco1;
     kruising[m][1] = fco2;
      /*----------------------------------------------------------------------
      Conversion to output:

      for(i=0;i<27;i++){
        if(field[cross[i][0]][cross[i][1]]==flag){
            int crX = ((cross[i][0]-2)/2);
            int crY = ((cross[i][1]-2)/2);
            printf("c%d%d\t", crX, crY);
          }
        };

  */
         return time_penalty;

}

void addMines() {
    int a = 0, num, obst1, obst2;
    char dir;

/* asking where obstacles are located */
    printf("Amount of obstacles:");
    scanf("%d", &num);

/* addition of obstacles to global variable unchanged_field */
    while (a < num) {
     printf("Location of a mine:");
     scanf("%d %d %c", &obst1, &obst2, &dir);
     obst1 = obst1*2+2;
     obst2 = obst2*2+2;
     if(dir == 'e'){obst2++;}
     if(dir == 's'){obst1++;}
     if(dir == 'n'){obst1--;}
     if(dir == 'w'){obst2--;}
     unchanged_field[obst1][obst2] = -1;
     a++;
   };
}

void shortest(int start, int checkpoint1, int checkpoint2, int checkpoint3) {
    int i;
    int time[6]; //Six possible combinations of checkpoint order
    int smallIndicator = 0;

/* all possible route combinations */
  time[0] = mazeRouter(start, checkpoint1) + mazeRouter(checkpoint1, checkpoint2) + mazeRouter(checkpoint2, checkpoint3);
  time[1] = mazeRouter(start, checkpoint1) + mazeRouter(checkpoint1, checkpoint3) + mazeRouter(checkpoint3, checkpoint2);
  time[2] = mazeRouter(start, checkpoint2) + mazeRouter(checkpoint2, checkpoint1) + mazeRouter(checkpoint1, checkpoint3);
  time[3] = mazeRouter(start, checkpoint2) + mazeRouter(checkpoint2, checkpoint3) + mazeRouter(checkpoint3, checkpoint1);
  time[4] = mazeRouter(start, checkpoint3) + mazeRouter(checkpoint3, checkpoint1) + mazeRouter(checkpoint1, checkpoint2);
  time[5] = mazeRouter(start, checkpoint3) + mazeRouter(checkpoint3, checkpoint2) + mazeRouter(checkpoint2, checkpoint1);

/* Determining the shortest time stamp for all the routes */
  int smallest = time[0];

  for(i=1;i<6;i++){
    if(time[i] < smallest) {
      smallest = time[i];
      smallIndicator = i;
    }
  }

/* Output given */
  printf("Shortest path:");
  switch(smallIndicator) {
    case 0:
      checkpoints[0] = checkpoint1;
      checkpoints[1] = checkpoint2;
      checkpoints[2] = checkpoint3;
      break;
    case 1:
      checkpoints[0] = checkpoint1;
      checkpoints[1] = checkpoint3;
      checkpoints[2] = checkpoint2;
      break;
    case 2:
      checkpoints[0] = checkpoint2;
      checkpoints[1] = checkpoint1;
      checkpoints[2] = checkpoint3;
      break;
    case 3:
      checkpoints[0] = checkpoint2;
      checkpoints[1] = checkpoint3;
      checkpoints[2] = checkpoint1;
      break;
    case 4:
      checkpoints[0] = checkpoint3;
      checkpoints[1] = checkpoint1;
      checkpoints[2] = checkpoint2;
      break;
    case 5:
      checkpoints[0] = checkpoint3;
      checkpoints[1] = checkpoint2;
      checkpoints[2] = checkpoint1;
      break;
  }
  printf("%d\t%d\t%d\n", checkpoints[0], checkpoints[1], checkpoints[2]);

}

void convert_kruising(int point1, int point2) {
  clr_kruising();

  int i;
  mazeRouter(point1, point2);

  for(i=0;i<27;i++){
    if(kruising[i][0] != 0 || kruising[i][1] != 0){
        kruising[i][0] = (kruising[i][0]-2)/2;
        kruising[i][1] = (kruising[i][1]-2)/2;
  } else {
    break;
  }
}

  for(i=2;i<27;i++){
    if(kruising[i][0] != 0 || kruising[i][1] != 0){
            // Coming from above
        if(kruising[i-2][0] < kruising[i-1][0]) {

            if(kruising[i][0] > kruising[i-1][0]) {
                strncat(instruct_output, &f, 1);
            }
            else if (kruising[i][1] > kruising[i-1][1]){
                strncat(instruct_output, &l, 1);
            }
            else if (kruising[i][1] < kruising[i-1][1]){
                strncat(instruct_output, &r, 1);
            }
            continue;
           }
           // Coming from below
        else if(kruising[i-2][0] > kruising[i-1][0]) {
            if(kruising[i][0] < kruising[i-1][0]) {
                strncat(instruct_output, &f, 1);
            }
            else if (kruising[i][1] > kruising[i-1][1]){
                strncat(instruct_output, &r, 1);
            }
            else if (kruising[i][1] < kruising[i-1][1]){
                strncat(instruct_output, &l, 1);
            }
            continue;
           }
        else if(kruising[i-2][1] > kruising[i-1][1]) {
            if(kruising[i][1] < kruising[i-1][1]) {
                strncat(instruct_output, &f, 1);
            }
            else if (kruising[i][0] > kruising[i-1][0]){
                strncat(instruct_output, &l, 1);
            }
            else if (kruising[i][0] < kruising[i-1][0]){
                strncat(instruct_output, &r, 1);
            }
            continue;
           }
        else if(kruising[i-2][1] < kruising[i-1][1]) {
            if(kruising[i][1] > kruising[i-1][1]) {
                strncat(instruct_output, &f, 1);
            }
            else if (kruising[i][0] > kruising[i-1][0]){
                strncat(instruct_output, &r, 1);
            }
            else if (kruising[i][0] < kruising[i-1][0]){
                strncat(instruct_output, &l, 1);
            }
            continue;
           }

    } else {
        break;
    }
  }
}

void direction(int checkp1, int checkp2, int checkp3)
{
    convert_kruising(1, checkp1);
    strncat(instruct_output, &t, 1);
    convert_kruising(checkp1, checkp2);
    strncat(instruct_output, &t, 1);
    convert_kruising(checkp2, checkpoints[2]);
    strncat(instruct_output, &s, 1);
    printf("%s\n", instruct_output);

}

