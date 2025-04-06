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
#include "WIFI.h"

typedef struct btree_item
{
    WIFI value;
    struct btree_item* left;
    struct btree_item* right;
}btree_item;

void insert_btree(const WIFI* val, btree_item** vert);

void print_btree_incr(const btree_item* vert); 

void print_btree_decr(const btree_item* vert); 

int extract_value(const WIFI* key, btree_item** vert);

int vertex_count(const btree_item* vert);

void delete_btree(btree_item** vert);

#endif
