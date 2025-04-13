#ifndef BTREE_H
#define BTREE_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>

#define MAX_INT_LENGTH 10

typedef struct btree_item // узел бинарного дерева
{
	int value; // информационная часть
	struct btree_item* left; // структурная часть: указатель левое поддерево
	struct btree_item* right; // указатель правое поддерево
}btree_item;

int insert_btree(int val, btree_item** vert);

void print_btree_incr(const btree_item* vert); 

void print_btree_decr(const btree_item* vert); 

int extract_value(int key, btree_item** vert);

int vertex_count(const btree_item* vert);

void delete_btree(btree_item** vert);

int input_int(const char* message);

void input_string(char* buffer, const int buffer_size);

#endif

