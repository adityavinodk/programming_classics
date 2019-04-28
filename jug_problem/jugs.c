// Implementation file

#include <stdio.h>
#include <stdlib.h>
#include "jugs.h"

// Initializing the list
void init_list(list_t *ptr_list)
{
	ptr_list->head = NULL;
	ptr_list->tail = NULL;
}

// Function to add node at the end of the list
void add_at_end(list_t *ptr_list, const state_t* ptr_state)

{
	node_t* temp = (node_t*) malloc(sizeof(node_t));
	temp->st = *ptr_state; 
	temp->next = temp->prev = NULL;

	if(ptr_list->tail == NULL)
	{
		temp->prev = temp->next = NULL;
		ptr_list->head = ptr_list->tail = temp;
	}
	else
	{
		temp->prev = ptr_list->tail;
		temp->next = NULL;
		ptr_list->tail = ptr_list->tail->next = temp;
	}
}

// Function to remove the node from the end of the list
void remove_at_end(list_t *ptr_list)
{
	if(ptr_list->tail == NULL)
	{
		printf("empty list\n");
	}
	else  
	{
		node_t* temp = ptr_list->tail;
		ptr_list->tail = ptr_list->tail->prev;	
		if(ptr_list->tail == NULL)
		{
			ptr_list->head = NULL;
		}
		else
		{
			ptr_list->tail->next = NULL;
		}
		free(temp);		
	}
}

// Function to display the list 
void disp_list(const list_t *ptr_list)
{
	node_t* temp = ptr_list->head;
	while(temp)
	{
		//printf("%d ", temp->key);
		disp_state(&temp->st);
		temp = temp->next;
	}
}

// Function to check if any of the states in the node are repeated
int is_repeated(const list_t* ptr_list, const state_t* ptr_state)
{
	node_t* temp = ptr_list->head;
	int found = 0;
	while(temp && ! found)
	{
		found  = are_same(&temp->st, ptr_state);
		temp = temp->next;
	}
	return found;
}

// Function to initialize the state as the start state
void init_state(state_t *ptr_state)
{
	ptr_state->jug8 = 8;
	ptr_state->jug5 = 0;
	ptr_state->jug3 = 0;
	ptr_state->fn_index = 0;
}

// Function to display the value of the jugs in the state
void disp_state(const state_t *ptr_state)
{
	printf("%d %d %d\n", ptr_state->jug8, ptr_state->jug5, ptr_state->jug3);
}

// Function to move the water from jug 8 in the source state to jug 5 in the destination state
void move_85(const state_t *src, state_t *dst)
{
	int rem_amount = 5 - src->jug5;
    if(src->jug8 >= rem_amount){
        dst->jug8 = src->jug8 - rem_amount;
        dst->jug5 = src->jug5 + rem_amount; 
    }
    else{
        dst->jug5 = src->jug5 + src->jug8;
        dst->jug8 = 0;
    }
	dst->fn_index = 0;
    dst->jug3 = src->jug3;
    dst->fn_index = 0;
}

// Function to move the water from jug 5 in the source state to jug 8 in the destination state
void move_58(const state_t *src, state_t *dst)
{
    int rem_amount = 8 - src->jug8;
    if(src->jug5 >= rem_amount){
        dst->jug5 = src->jug5 - rem_amount;
        dst->jug8 = src->jug8 + rem_amount; 
    }
    else{
        dst->jug8 = src->jug5 + src->jug8;
        dst->jug5 = 0;
    }
	dst->fn_index = 0;
    dst->jug3 = src->jug3;
    dst->fn_index = 0;
}

// Function to move the water from jug 5 in the source state to jug 3 in the destination state
void move_53(const state_t *src, state_t *dst)
{
    int rem_amount = 3 - src->jug3;
    if(src->jug5 >= rem_amount){
        dst->jug5 = src->jug5 - rem_amount;
        dst->jug3 = src->jug3 + rem_amount; 
    }
    else{
        dst->jug3 = src->jug5 + src->jug3;
        dst->jug5 = 0;
    }
	dst->fn_index = 0;
    dst->jug8 = src->jug8;
    dst->fn_index = 0;
}

// Function to move the water from jug 3 in the source state to jug 5 in the destination state
void move_35(const state_t *src, state_t *dst)
{
    int rem_amount = 5 - src->jug5;
    if(src->jug3 >= rem_amount){
        dst->jug3 = src->jug3 - rem_amount;
        dst->jug5 = src->jug5 + rem_amount; 
    }
    else{
        dst->jug5 = src->jug5 + src->jug3;
        dst->jug3 = 0;
    }
	dst->fn_index = 0;
    dst->jug8 = src->jug8;
    dst->fn_index = 0;
}

// Function to move the water from jug 3 in the source state to jug 8 in the destination state
void move_38(const state_t *src, state_t *dst)
{
    int rem_amount = 8 - src->jug8;
    if(src->jug3 >= rem_amount){
        dst->jug3 = src->jug3 - rem_amount;
        dst->jug8 = src->jug8 + rem_amount; 
    }
    else{
        dst->jug8 = src->jug3 + src->jug8;
        dst->jug3 = 0;
    }
	dst->fn_index = 0;
    dst->jug5 = src->jug5;
    dst->fn_index = 0;
}

// Function to move the water from jug 8 in the source state to jug 3 in the destination state
void move_83(const state_t *src, state_t *dst)
{
    int rem_amount = 3 - src->jug3;
    if(src->jug8 >= rem_amount){
        dst->jug8 = src->jug8 - rem_amount;
        dst->jug3 = src->jug3 + rem_amount; 
    }
    else{
        dst->jug3 = src->jug3 + src->jug8;
        dst->jug8 = 0;
    }
	dst->fn_index = 0;
    dst->jug5 = src->jug5;
    dst->fn_index = 0;
}

// Function to set the values of the jugs in the state as per the paramater values
void set_state(state_t *ptr_state, int jug8, int jug5, int jug3)
{
	ptr_state->jug8 = jug8;
	ptr_state->jug5 = jug5;
	ptr_state->jug3 = jug3;
    ptr_state->fn_index = 0;
}

// Function to check if the volums of water in the jugs do not exceed their limit and the value of water totally is 8
int is_safe(const state_t* ptr_state)
{
	return ((ptr_state->jug8<=8 && ptr_state->jug5<=5 && ptr_state->jug3<=3) && (ptr_state->jug8>=0 && ptr_state->jug5>=0 
    && ptr_state->jug3>=0) &&(ptr_state->jug5+ptr_state->jug3+ptr_state->jug8==8));
}

// Checks if the values of the water volumes in the 2 jugs are the same
int are_same(const state_t *lhs, const state_t *rhs)
{
	return lhs->jug8 == rhs->jug8 && lhs->jug5 == rhs->jug5 && lhs->jug3 == rhs->jug3;
}