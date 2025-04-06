#include "btree.h"
#include "WIFI.h"

void insert_btree(const WIFI* val, btree_item** vert) 
{
    if ((*vert) == NULL) 
    {
        *vert = (btree_item*)malloc(sizeof(btree_item));
        (*vert)->left = (*vert)->right = NULL;
        copy_struct(val, &(*vert)->value);
        return;
    }
    
    if (compare(&(*vert)->value, val))
        insert_btree(val, &((*vert)->left));
    else
        insert_btree(val, &((*vert)->right));
}

void print_btree_incr(const btree_item* vert)
{
    if (vert == NULL) return;
    print_btree_incr(vert->left);
    print_struct(&vert->value);
    print_btree_incr(vert->right);
}

void print_btree_decr(const btree_item* vert)
{
    if (vert == NULL) return;
    print_btree_decr(vert->right);    
    print_struct(&vert->value);
    print_btree_decr(vert->left);
}

int vertex_count(const btree_item* vert) 
{
    if (!vert) return 0;
    return vertex_count(vert->left) + vertex_count(vert->right) + 1;
}

int extract_value(const WIFI* key, btree_item** vert)
{
    btree_item* t, *up;
    if (vert == NULL) return 0; 
    if (is_equal(&(*vert)->value, key)) 
    {
        if (((*vert)->left == NULL) && ((*vert)->right == NULL))
        {
            free(*vert);
            *vert = NULL;
            return 1;
        }
        if((*vert)->left == NULL)
        {
            t = *vert;
            *vert = (*vert)->right;
            free(t);
            return 1;
        }
        if((*vert)->right == NULL)
        {
            t = *vert;
            *vert = (*vert)->left;
            free(t);
            return 1;
        }
        up = *vert;
        t = (*vert)->left;
        while (t->right != NULL)
        {
            up = t;
            t = t->right;
        }
        copy_struct(&t->value, &(*vert)->value);

        if (up != (*vert))
        {
             if(t->left != NULL) up->right = t->left;
             else up->right = NULL;
        }
        else (*vert)->left = t->left;
        free(t);
        return 1;
    }

    if(compare(key, &(*vert)->value)) 
        return extract_value(key, &((*vert)->right));
    return extract_value(key, &((*vert)->left));
}

void delete_btree(btree_item** vert)
{
    if (*vert == NULL) return;

    delete_btree(&((*vert)->left));
    delete_btree(&((*vert)->right));
    
    free(*vert);
}
