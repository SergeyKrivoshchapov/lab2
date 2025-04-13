#include "btree.h"

// 0 = err
int insert_btree (const int val, btree_item** vert) 
{
	if (!vert) return 0;

	if ((*vert) == NULL) 
	{
		*vert = (btree_item*)malloc(sizeof(btree_item));
		if (!(vert)) return 0;

		(*vert)->left = (*vert)->right = NULL;
		(*vert)->value = val;
		return 1;
	}
	
	if ((*vert)->value > val) return insert_btree(val, &((*vert)->left));
	else return insert_btree(val, &((*vert)->right));
}

void print_btree_incr(const btree_item* vert)
{
	if (vert == NULL) return;
	print_btree_incr(vert->left);
	printf("%d\n", vert->value);
	print_btree_incr(vert->right);
}

void print_btree_decr(const btree_item* vert)
{
	if (vert == NULL) return;
	print_btree_decr(vert->right);    
	printf("%d\n", vert->value);
	print_btree_decr(vert->left);
}

int vertex_count(const btree_item* vert) 
{
	if (!vert) return 0;
	return vertex_count(vert->left) + vertex_count(vert->right) + 1;
}

int extract_value(const int key, btree_item** vert)
{
	btree_item* t, *up;
	if (vert == NULL) return 0; 
	if ((*vert)->value == key) 
	{
		// вершина является листом
		if (((*vert)->left == NULL) && ((*vert)->right == NULL))
		{
			int val = (*vert)->value;
			free(*vert);
			*vert = NULL;
			return val;
		}
		// есть только правое поддерево
		if((*vert)->left == NULL)
		{
			t = *vert;
			*vert = (*vert)->right;
			int val = t->value;
			free(t);
			return val;
		}
		// есть только левое поддерево
		if((*vert)->right == NULL)
		{
			t = *vert;
			*vert = (*vert)->left;
			int val = t->value;
			free(t);
			return val;
		}
		up = *vert; // есть оба потомка
		t = (*vert)->left; // ищем в левом поддереве крайнюю правую вершину
		while (t->right != NULL)
		{
			up = t;
			t = t->right;
		}
		(*vert)->value = t->value; // копируем значение из найденной вершины

		if (up != (*vert)) // удаляемая и найденная вершины не совпадают
		{
			 if(t->left != NULL) up->right = t->left;
			 else up->right = NULL;
		}
		else (*vert)->left = t->left;
		int val = t->value;
		free(t);
		return val;
	}

	if((*vert)->value < key) return extract_value(key, &((*vert)->right));
	return extract_value(key, &((*vert)->left));
}

void delete_btree(btree_item** vert)
{
	if ((!*vert) || (!vert)) return;

	delete_btree(&((*vert)->left));
	delete_btree(&((*vert)->right));
	
	free(*vert);
}

int input_int(const char* message) 
{
	char buffer[MAX_INT_LENGTH];
	char temp[MAX_INT_LENGTH];
	printf("%s", message);
	input_string(buffer, MAX_INT_LENGTH);
	snprintf(temp, MAX_INT_LENGTH, "%d", atoi(buffer)); 
	if ((atoi(buffer) == 0 && buffer[0] != '0') || (atoi(buffer) >= USHRT_MAX) || (atoi(buffer) < 0) || (strcmp(buffer, temp) != 0))
	{
		printf("Entered value is incorrect.");
		exit(EXIT_FAILURE);
	}
	return atoi(buffer);
}

void input_string(char* buffer, int buffer_size) 
{
	fgets(buffer, buffer_size, stdin);
	size_t len = strlen(buffer);
	if (len > 1 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';
	else
	{
		printf("Entered value is too long or empty.\n");
		int temp; 
		while ((temp = getchar()) != '\n' && temp != EOF);
		exit(EXIT_FAILURE);
	}
}

