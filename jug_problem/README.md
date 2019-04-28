# Implementation of 8-5-3 litre jug problem
By Aditya Vinod Kumar - PES1201700138

## Introduction - 
Find all solutions to 8-5-3 litre jug problem. You are given 3 jugs of capacity 8 litre, 5 litre and 3 litre. 8 litre jug is full with milk. Measure exactly 4 litres.
You can pour from any jug to any other jug. There are no markings on any of the jugs.

1. Run the file using $CMD: 
```shell
gcc jugs.h client.c jugs.c
./a.out
```
2. This program used function backtracking and a linked list to reach the goal state from the start state.
3. It starts with an setting the start state of 8,0,0 and goal state of 4,4,0. 
4. A linked list is used in which the nodes consist of a state and the pointer to the next and previous nodes.
5. A pointer to array of functions is used and each function is called on the current state of the list, and if the state after the operation is safe(doesn't exceed the amount),
   it is added to the list and the operation is continued. If the current state reached is the goal state, then the list is displayed.
6. When all the operations are exhausted on the current state, it is removed from the linked list.
7. The entire process runs until the tail node of the linked list points to NULL.