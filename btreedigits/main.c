#include "btree.h"

int main()
{
	// создание пустого дерева
	btree_item* root = NULL;
	
	int toinsert_amount = input_int("Enter amount of numbers to insert into the tree\n");
	if (toinsert_amount <= 0)
	{
		puts("Uncorrect data enteded. Minimal amount of brances is 1.\n");
		return 1;
	}
	srand(time(NULL));
	puts("Generated random numbers: \n");
	for (int i = 0; i < toinsert_amount; i++)
	{
		int rval = rand() % 1000;
		printf("%d ", rval);
		insert_btree(rval, &root);
	}

	int vert_count = vertex_count(root);

	printf("\n%d - entered count, %d result vertex count\n\n", toinsert_amount, vert_count);

	puts("Printing tree elements by increasing values\n");
	print_btree_incr(root);
	
	puts("Printing tree elements by decreasing values\n");
	print_btree_decr(root);

	int key_todelete = input_int("Which value needs to be deleted?\n");
	
	extract_value(key_todelete, &root);

	puts("Value deleted from tree succesfully\n");
	print_btree_incr(root);
	
	delete_btree(&root);
	root = NULL;
	puts("Tree fully deleted succesfully");
}
