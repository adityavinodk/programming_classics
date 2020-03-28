# Implementation of Persistant Binary Search Tree on Harddisk

## Introduction - 
The first structure in the file is the header. In case of file, it has offset to the first filled node and offset to the first free node. If there are no freenodes, we add the new node at the end of the file. New freenodes are created only on deletion of a node.

Tree implementation can have a key and offset to both right and left nodes in file.
The first structure may have the offset to the root and offset to the first free node.
Every other node may have key, offset to the leftsub tree and offset to the right subtree.

Support the following operations:
1. insert
2. delete based on the key
3. traversal - inorder
4. traversal - pre-order

Please Check `sample_input.txt` and `sample_output.txt` for example. 


## About the Program - 
1. Run the file using $CMD: 
```shell
gcc bst_file.h client.c bst_file.c
./a.out
```
2. This program implements a Binary Search Tree on a Harddisk using a `.dat` file
3. It uses 2 structures, a tree structure and a node structure.
4. The tree structure is first written into the file and it contains two offsets, one for the root 
   and one for the free_head.
5. When an key is inserted, first we check if the free_head exists, then we write the node into the 
   location of the free_head else we write it into the end of the file and set the respective 
   offsets of the previous and current node.
6. When a key is deleted we find the node and then we reset the respective offsets of the previous
   and current node.
7. Thus the file contains the nodes in binary search format and is entirely space eficient storing
   the new nodes in the free blocks.