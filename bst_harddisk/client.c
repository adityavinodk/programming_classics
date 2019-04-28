#include <stdio.h>
#include "bst_file.h"

int main()
{
	FILE *fp;
	tree_t t;
	fp = init_tree(&t, "mytree.dat");
	int key;
	int opt;
	scanf("%d", &opt);
	while(opt)
	{
		switch(opt)
		{
			case 1 : //printf("enter key to insert : ");
					 scanf("%d", &key);
					 insert_key(&t, key, fp);
					 break;
			case 2 : scanf("%d", &key);
					 delete_key(&t, key, fp);
					 break;
			case 3 : //printf("tree begin\n");
					 display_inorder(&t, fp);
					 //printf("list end\n");
					 break;
			case 4 : //printf("tree begin\n");
					 display_preorder(&t, fp);
					 //printf("list end\n");
					 break;
		}
		//printf("enter option : ");
		scanf("%d", &opt);
	}
	close_tree(&t, fp);
}
