#include <stdio.h>
#include "bst_file.h"

// Function for initializing tree and setting initial root and free_head values
FILE *init_tree(tree_t *ptr_tree, const char *name)
{
	FILE *fp = fopen(name, "r+");
	if (fp == NULL)
	{
		printf("empty file\n");
		// Creates a new empty file
		fp = fopen(name, "w");
		ptr_tree->root = -1;
		ptr_tree->free_head = -1;
		// Writes the structure into the .dat file
		fwrite(ptr_tree, sizeof(tree_t), 1, fp);
		fclose(fp);
		fp = fopen(name, "r+");
	}
	// Reads the structure from the file
	fread(ptr_tree, sizeof(tree_t), 1, fp);
	return fp;
}

// Function to close the file
void close_tree(tree_t *ptr_tree, FILE *fp)
{
	fclose(fp);
}

// Function display_inorder function calls this function to parse through the nodes recursively in inorder form
void display_nodes_inorder(node_t *root, int off, FILE *fp){
	// Setting the values for right and left nodes of each root node in the call
	int right_offset, left_offset;
	node_t left_node, right_node;
	// If the offset value isn't -1, then perform the traversal
	if(off!=-1){
		// Sets the values for the left node and then calls the same function again on the left node
		left_offset = root->left_offset;
		fseek(fp, root->left_offset, SEEK_SET);
		fread(&left_node, sizeof(node_t), 1, fp);
		display_nodes_inorder(&left_node, left_offset, fp);
		
		// Prints the key of the current node
		printf("%d ", root->key);
		
		// Sets the values for the right node and then calls the same function again on the right node
		right_offset = root->right_offset;
		fseek(fp, root->right_offset, SEEK_SET);
		fread(&right_node, sizeof(node_t), 1, fp);
		display_nodes_inorder(&right_node, right_offset, fp);
	}
}

// Function for display the nodes of the tree in inorder form, calls another function inside it
void display_inorder(const tree_t *ptr_tree, FILE *fp)
{
	node_t temp;
	int off = ptr_tree->root;
	// If the tree root offset isn't -1, then call display_nodes_inorder function with the root node
	if(off != -1)
	{
		fseek(fp, off, SEEK_SET);
		fread(&temp, sizeof(node_t), 1, fp);
		display_nodes_inorder(&temp, off, fp);
	}
	printf("\n");
}

// Function display_inorder function calls this function to parse through the nodes recursively in preorder form
void display_nodes_preorder(node_t *root, int off, FILE *fp){
	// Setting the values for right and left nodes of each root node in the call
	int right_offset, left_offset;
	node_t left_node, right_node;
	// If the offset value isn't -1, then perform the traversals
	if(off!=-1){
		// Prints the key of the current node
		printf("%d ", root->key);

		// Sets the values for the left node and then calls the same function again on the left node
		left_offset = root->left_offset;
		fseek(fp, root->left_offset, SEEK_SET);
		fread(&left_node, sizeof(node_t), 1, fp);
		display_nodes_preorder(&left_node, left_offset, fp);
		
		// Sets the values for the right node and then calls the same function again on the right node
		right_offset = root->right_offset;
		fseek(fp, root->right_offset, SEEK_SET);
		fread(&right_node, sizeof(node_t), 1, fp);
		display_nodes_preorder(&right_node, right_offset, fp);
	}
}

// Function for display the nodes of the tree in preorder form, calls another function inside it
void display_preorder(const tree_t *ptr_tree, FILE *fp)
{
	node_t temp;
	int off = ptr_tree->root;
	// If the tree root offset isn't -1, then call display_nodes_preorder function with the root node
	if(off != -1)
	{
		fseek(fp, off, SEEK_SET);		
		fread(&temp, sizeof(node_t), 1, fp);
		display_nodes_preorder(&temp, off, fp);
	}
	printf("\n");
}

void insert_key(tree_t *ptr_tree, int key, FILE *fp)
{
	// Setting the initial value of temp offset as the end of the file
	fseek(fp, 0, SEEK_END);
	int temp = ftell(fp);

	// Creating a temporary node with the given key value and setting both left and righ offsets to -1
	node_t temp_node;
	temp_node.key = key;
	temp_node.right_offset = -1;
	temp_node.left_offset = -1;

	// Enters the block if the root offset of the tree structure is -1, indicating the tree is empty
	if (ptr_tree->root == -1)
	{
		// Set the root offset to temp offset, hence the first node is stored
		ptr_tree->root = temp;

		// Write the tree structure into the file at offset 0
		fseek(fp, 0, SEEK_SET);
		fwrite(ptr_tree, sizeof(tree_t), 1, fp);

		// Sets the file position indicator at the offset specified by temp from the start of the file and writes the node
		fseek(fp, temp, SEEK_SET);
		fwrite(&temp_node, sizeof(node_t), 1, fp);
	}
	else
	{
		// If an empty block exists, set temp to the free_head specified in the tree structure
		if(ptr_tree->free_head != -1){
			temp = ptr_tree->free_head;
			// Set the free_head pointer back to -1
			ptr_tree->free_head = -1;
		}
		// Set the initial offset as the root offset
		int offset = ptr_tree->root;

		// Initialize values for present and previous node 
		node_t pres_node, prev_node;
		int prev_offset = 0;
		fseek(fp, offset, SEEK_SET);
		fread(&pres_node, sizeof(node_t), 1, fp);
		while(offset!=-1){
			// Set the previous offset value as the current offset to be changed
			prev_offset = offset;

			// If the given key is lesser the the present node's key, then set the offset as the present node's left offset, 
			// else the right offset
			if(key<pres_node.key) offset = pres_node.left_offset;
			else offset = pres_node.right_offset;

			// Set the previous node as the current node to be changed
			prev_node = pres_node;

			// Read the current node as the node at the new offset
			fseek(fp, offset, SEEK_SET);
			fread(&pres_node, sizeof(node_t), 1, fp);
		}
		
		// If the key is lesser than the previous node's key, then set the previous node's left offset as the current offset
		// else set the right offset as this offset
		if(prev_node.key>key) prev_node.left_offset = temp;
		else prev_node.right_offset = temp;
		
		// Rewrite the previous node at the previous offset
		fseek(fp, prev_offset, SEEK_SET);
		fwrite(&prev_node, sizeof(node_t),1,fp);

		// Write the new node at the offset given by temp
		fseek(fp, temp, SEEK_SET);
		fwrite(&temp_node, sizeof(node_t), 1, fp);
	}
}

// Function to delete a key from the tree
void delete_key(tree_t *ptr_tree, int key, FILE *fp)
{
	// If the root offset is -1, the tree is empty
	if (ptr_tree->root == -1)
	{
		printf("empty list; cannot delete\n");
	}
	else
	{
		// Set the initial offset as root offset
		int offset = ptr_tree->root;

		// Initialize values for present and previous node 
		node_t pres_node, prev_node;
		int prev_offset = ptr_tree->root;
		fseek(fp, offset, SEEK_SET);
		fread(&pres_node, sizeof(node_t), 1, fp);

		// While the current offset doesn't equal -1 and the node key isn't equal to the key, execute the while loop
		while(offset!=-1 && pres_node.key!=key){
			// Set the previous offset as the current offset
			prev_offset = offset;

			// If the given key is lesser the the present node's key, then set the offset as the present node's left offset, 
			// else the right offset
			if(key<pres_node.key) offset = pres_node.left_offset;
			else offset = pres_node.right_offset;

			// Set the previous node as the current node to be changed
			prev_node = pres_node;

			// Read the current node as the node at the new offset
			fseek(fp, offset, SEEK_SET);
			fread(&pres_node, sizeof(node_t), 1, fp);
		}

		// If the offset after exiting the while loop equals -1, it means the tree doesn't contain the given key
		if(offset==-1){
			printf("key not found\n");
			return;
		}
		
		// If both offsets of the pres_node is -1 and the tree root points to this offset, then it implies
		// that the root node is the only node in the tree
		if(pres_node.left_offset==-1 && pres_node.right_offset==-1 && ptr_tree->root==offset){
			// Set the root offset equal to -1 and the free_head offset to this offset
			ptr_tree->root = -1;
			ptr_tree->free_head = offset;
		}

		// If both the offsets of the pres_node is -1 then it implies it is a leaf node
		// Operation is to just remove the leaf node
		else if(pres_node.left_offset==-1 && pres_node.right_offset==-1){
			// If the key is greater than the previous node's key, set the previous node's right offset as -1
			// else set its left offset as -1
			if(prev_node.key>key) prev_node.left_offset=-1;
			else prev_node.right_offset=-1;

			// Rewrites the previous node at its offset
			fseek(fp, prev_offset, SEEK_SET);
			fwrite(&prev_node, sizeof(node_t),1,fp);

			// Set the free head pointer to the offset of the leaf
			ptr_tree->free_head = offset;
		}

		// If either the offsets of the pres_node is -1 then it implies it is a node with a single subtree
		// Operation is to just replace with the first node of the subtree
		else if((pres_node.left_offset!=-1 && pres_node.right_offset==-1) || (pres_node.right_offset!=-1 && pres_node.left_offset==-1)){
			int new_offset = 0;
			// Set the new offset as right offset if right subtree ecists else set it as left offset if left tree exists
			if(pres_node.right_offset!=-1) new_offset = pres_node.right_offset;
			else new_offset = pres_node.left_offset;
			
			// Set a new node which reads the node at the new offset
			node_t new_node;
			fseek(fp, new_offset, SEEK_SET);
			fread(&new_node, sizeof(node_t), 1, fp);

			// Write the new node back to the initial offset
			fseek(fp, offset, SEEK_SET);
			fwrite(&new_node, sizeof(node_t), 1, fp);

			// Set the free head of the tree as the new offset value (first node of the subtree)
			ptr_tree->free_head = new_offset;
		}

		// If both offsets are not equal to -1, implies that the node has both left and right subtrees
		// Operation is to find the replace the node with its inorder predecessor
		else if(pres_node.left_offset!=-1 && pres_node.right_offset!=-1){
			// Inorder predecessor is calculated as the right most node on the left subtree
			// Set the new_offset initially as pres_node.left_offset and old_offset as the offset of the node
			// We set a count to find how many layers down the inorder predecessor exists
			int new_offset = pres_node.left_offset, old_offset = offset, count=1;

			// Set the initial values of the nodes, one node to have to current node and another to hold the previous node
			node_t prev_node_inorder_predecessor=pres_node, pres_node_inorder_predecessor, new_node;
			fseek(fp, new_offset, SEEK_SET);
			fread(&pres_node_inorder_predecessor, sizeof(node_t), 1, fp);

			// Execute until a right offset value of -1 is found, indicating right_most node
			while(pres_node_inorder_predecessor.right_offset!=-1){
				// Set the old offset as the current offset
				old_offset = new_offset;

				// Set the current offset to the right offset of the present node
				new_offset = pres_node_inorder_predecessor.right_offset;
				
				// Set the previous node as the current node
				prev_node_inorder_predecessor = pres_node_inorder_predecessor;

				// Read the current node as the node at the new offset
				fseek(fp, new_offset, SEEK_SET);
				fread(&pres_node_inorder_predecessor, sizeof(node_t), 1, fp);
				
				// Increment count
				count++;
			}
			// Set the new node to replace the deleted node as the right most node of left subtree
			new_node = pres_node_inorder_predecessor;
			
			// Set the right offset of the right_most node as the right_offset of the deleted node
			new_node.right_offset = pres_node.right_offset;
			
			// If the right most node is present at a layer more than 1
			// We need to update the right offset of the previous node in the left subtree
			if(count!=1){
				// Set the left offset of the new node as the left offset of the deleted node
				new_node.left_offset = pres_node.left_offset;

				// Set the right offset of the previous node in the left subtree as -1
				prev_node_inorder_predecessor.right_offset = -1;

				// Rewrite the previous node at its position
				fseek(fp, old_offset, SEEK_SET);
				fwrite(&prev_node_inorder_predecessor, sizeof(node_t), 1, fp);
			}

			// Write the new node at the offsets
			fseek(fp, offset, SEEK_SET);
			fwrite(&new_node, sizeof(node_t), 1, fp);

			// Set the free_head offset of the tree as the right_most element offset
			ptr_tree->free_head = new_offset;
		}
	}
}