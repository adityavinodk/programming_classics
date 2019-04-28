// Client File

#include <stdio.h>
#include <stdlib.h>
#include "jugs.h"
int main()
{
	// Set initial start state
	state_t start_state;
	set_state(&start_state, 8, 0, 0);
	// Set final goal state
	state_t goal_state;
	set_state(&goal_state, 4, 4, 0);
	// Initialize list
	list_t l;
	init_list(&l);
	// Temporary state variable
	state_t temp;
	int solutions = 0;
	// Add node with start_state to the end of list initially
	add_at_end(&l, &start_state);
	int index;

	// Store the different functions under a pointer to array of functions
	void (*move[])(const state_t *src, state_t *dst) = {
		move_85,
		move_83,
		move_58,
		move_53,
		move_38,
		move_35,
	};

	while(l.tail != NULL)
	{
		// the index value stores the next function to call in the move pointer
		index = l.tail->st.fn_index;
		move[index](&l.tail->st, &temp);
		// If the current state is safe and isn't repeated add it at the end and check if it is the goal state
		if(is_safe(&temp) && !is_repeated(&l, &temp)){
			add_at_end(&l, &temp);
			// If the current state is the goal state, then increment the solutions and display the list
			if(are_same(&temp, &goal_state)){
				solutions+=1;
				disp_list(&l);
				printf("\n");	
			}
		}
		// If end state of list isn't equal to the goal state, update the fn_index and remove the node from the end
		else{
			while(l.tail!=NULL && ++l.tail->st.fn_index==6){
				remove_at_end(&l);
			}
		}
	}
	printf("%d", solutions);
}