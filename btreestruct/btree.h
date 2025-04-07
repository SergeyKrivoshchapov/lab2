#ifndef BTREE_H
#define BTREE_H

#define _CRT_SECURE_NO_WARNINGS
#include "WIFI.h"

typedef struct btree_item
{
    WIFI* data;
    struct btree_item* left;
    struct btree_item* right;
}btree_item;

int insert_btree(WIFI* router, btree_item** vert);

void print_btree_incr(const btree_item* vert); 

void print_btree_decr(const btree_item* vert); 

WIFI* extract_value(const WIFI* router, btree_item** vert);

void no_use_extracted(WIFI* router);

int vertex_count(const btree_item* vert);

void delete_btree(btree_item** vert);

#endif
