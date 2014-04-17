
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* This program Implements the Finite state Machine which contains
 * 3 states as STATE_1, STATE_2, STATE_3 and 3 EVENTS
 * EVENT_1, EVENT_2, EVENT_3 as depicted below

 STATES/EVENTS  | EVENT_1 | EVENT_2 | EVENT_3 | EVENT_4   
 ======================================================
 STATE_1        | 
 ---------------- 
 STATE_2        |
 ----------------
 STATE_3        |
 ----------------
*/

/* 
 * Declare states
 */ 
typedef enum states 
{
   INVALID_STATE = 0,
   STATE_1,
   STATE_2,
   STATE_3,
   MAX_STATES
}FSMStates;

/* 
 * Declare Events
 */ 
typedef enum events 
{
   INVALID_EVENT = 0,
   EVENT_1,
   EVENT_2,
   EVENT_3,
   MAX_EVENTS
}FSMEvents; 

/* Call back Function */
typedef void (*FSMActionFunc)(void *data1);

/* ========================= 
 * Declaration of FSMStruct
 * ========================= 
 * FSM Struct should contain
 * ACTION function and Next State
 */
typedef struct FSM
{
   /* Action Function */
   FSMActionFunc  actionFunc;
   /* Next State */
   FSMStates      nextState;
}FSMStruct;


/* Declare FSMStruct Variable */
FSMStruct FSMArray[MAX_STATES][MAX_EVENTS];

/* The Handle Functions are declared Here */
unsigned char currentState;

void processFSMEvent(unsigned int event);
void handle_FSM_EVENT_1(void *data1);
void handle_FSM_EVENT_2(void *data1);
void handle_FSM_EVENT_3(void *data1);

void  initialiseFSM(void)
{
   /* Memset to FSMArray to Zero */
   memset(FSMArray, 0x00,  sizeof(FSMStruct));

   /* Intial State */
   currentState = STATE_1;

   /* STATE_1 Intialisation */
   FSMArray[STATE_1][EVENT_1].actionFunc = handle_FSM_EVENT_1;
   FSMArray[STATE_1][EVENT_1].nextState  = STATE_1;

   FSMArray[STATE_1][EVENT_2].actionFunc = handle_FSM_EVENT_2;
   FSMArray[STATE_1][EVENT_2].nextState  = STATE_2;
  
   FSMArray[STATE_1][EVENT_3].actionFunc = handle_FSM_EVENT_3;
   FSMArray[STATE_1][EVENT_3].nextState  = STATE_3;

   /* STATE 2 */
   FSMArray[STATE_2][EVENT_1].actionFunc = handle_FSM_EVENT_1;
   FSMArray[STATE_2][EVENT_1].nextState  = STATE_1;
   
   FSMArray[STATE_2][EVENT_2].actionFunc = handle_FSM_EVENT_2;
   FSMArray[STATE_2][EVENT_2].nextState  = STATE_2;

   FSMArray[STATE_2][EVENT_3].actionFunc = handle_FSM_EVENT_3;
   FSMArray[STATE_2][EVENT_3].nextState  = STATE_3;
   
   /* STATE 3 */
   FSMArray[STATE_3][EVENT_1].actionFunc = handle_FSM_EVENT_1;
   FSMArray[STATE_3][EVENT_1].nextState  = STATE_1;

   FSMArray[STATE_3][EVENT_2].actionFunc = handle_FSM_EVENT_2;
   FSMArray[STATE_3][EVENT_2].nextState  = STATE_2;
   
   FSMArray[STATE_3][EVENT_3].actionFunc = handle_FSM_EVENT_3;
   FSMArray[STATE_3][EVENT_3].nextState  = STATE_3;
}

/* 
 * Handle Event-1  Fn 
 */
void handle_FSM_EVENT_1(void *data1)
{
   char *buffer = (char *)data1;
   printf("--------------------------------------------------------------\n");
   printf("OUTPUT OF FSM :In function handle_FSM_EVENT_1 : %s\n", buffer);
   printf("--------------------------------------------------------------\n");
}
/* 
 * Handle Event-2  Fn 
 */
void handle_FSM_EVENT_2(void *data1)
{
   char *buffer = (char *)data1;
   printf("--------------------------------------------------------------\n");
   printf("OUTPUT OF FSM : In function handle_FSM_EVENT_2 : %s\n", buffer);
   printf("--------------------------------------------------------------\n");
}
/* 
 * Handle Event-3  Fn 
 */
void handle_FSM_EVENT_3(void *data1)
{
   char *buffer = (char *)data1;

   printf("--------------------------------------------------------------\n");
   printf("OUTPUT OF FSM : In function handle_FSM_EVENT_3 : %s\n", buffer);
   printf("--------------------------------------------------------------\n");
}
/*
 * processFSMEvent()
 */
void processFSMEvent(unsigned int event)
{
  char data1[20];

  if ((event > INVALID_EVENT) && (event < MAX_EVENTS))  
   {
     if(event == EVENT_1)
     {
       strcpy(data1, "EVENT_1 Data\n");
     }
     else if(event == EVENT_2)
     {
       strcpy(data1, "EVENT_2 Data\n");
     }
     else
     {
       strcpy(data1, "EVENT_3 Data\n");
     }
     
     /* Call the Respective Action Function */ 
     FSMArray[currentState][event].actionFunc(data1);

     /* Set the Current State */ 
     currentState =  FSMArray[currentState][event].nextState; 
   }
  else
   {
      printf(" Event is Invalid \n");
   }
}
/*
 * Main fn 
 */
int main()
{
   unsigned int event; char ch;

   /* Initialise FSM */
   initialiseFSM();

  do
   {      
      printf("Enter the Event(1-3) To be Trigger in FSM STATE Machine \n");
      scanf("%d", &event);

      /* Process FSM Events */
      processFSMEvent(event);

      printf("Do You Want To Run STATE MACHINE Further ....\n");
      printf("For exit enter 100-> Other wise to Continue Enter any  Number\n");
      scanf("%d", &ch);

   }while(ch!= 100);
}
