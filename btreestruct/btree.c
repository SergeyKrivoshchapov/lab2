#include "btree.h"
#include "WIFI.h"

// 0 = error
int insert_btree(WIFI* router, btree_item** vert) 
{
    if (!vert) return 0;

    if ((*vert) == NULL)
    {
        *vert = (btree_item*)malloc(sizeof(btree_item));
        if (!(*vert)) return 0;

        (*vert)->left = (*vert)->right = NULL;
        (*vert)->data = (WIFI*)malloc(sizeof(WIFI));
        if (!(*vert)->data) 
        {
            free(*vert);
            *vert = NULL;
            return 0;
        }

        copy_struct(router, (*vert)->data);
        return 1;
    }
    
    if (compare((*vert)->data, router))
        return insert_btree(router, &((*vert)->left));
    else
        return insert_btree(router, &((*vert)->right));
}

void print_btree_incr(const btree_item* vert)
{
    if (vert == NULL) return;
    print_btree_incr(vert->left);
    print_struct(vert->data);
    print_btree_incr(vert->right);
}

void print_btree_decr(const btree_item* vert)
{
    if (vert == NULL) return;
    print_btree_decr(vert->right);    
    print_struct(vert->data);
    print_btree_decr(vert->left);
}

int vertex_count(const btree_item* vert) 
{
    if (!vert) return 0;
    return vertex_count(vert->left) + vertex_count(vert->right) + 1;
}

WIFI* extract_value(const WIFI* router, btree_item** vert)
{
    btree_item* t, *up;
    if (vert == NULL) return 0; 
    if (is_equal((*vert)->data, router)) 
    {
        WIFI* extracted = NULL;

        if (((*vert)->left == NULL) && ((*vert)->right == NULL))
        {
            extracted = (*vert)->data;
            free(*vert);
            *vert = NULL;
            return extracted;
        }

        if((*vert)->left == NULL)
        {
            t = *vert;
            *vert = (*vert)->right;
            extracted = t->data;
            free(t);
            return extracted;
        }

        if((*vert)->right == NULL)
        {
            t = *vert;
            *vert = (*vert)->left;
            extracted = t->data;
            free(t);
            return extracted;
        }

        up = *vert;
        t = (*vert)->left;

        while (t->right != NULL)
        {
            up = t;
            t = t->right;
        }
        
        extracted = (*vert)->data;

        (*vert)->data = t->data;

        if (up != (*vert)) up->right = t->left;

        else up->left = t->left;


        free(t);
        return extracted;
    }

    if(compare(router, (*vert)->data)) 
        return extract_value(router, &((*vert)->right));
    return extract_value(router, &((*vert)->left));
}

void no_use_extracted(WIFI* extracted)
{
    if (extracted)
    {
        puts("\nRouter deleted from tree successfully");
        free(extracted);
    }
    else puts("\nRouted not found in tree");
}

void delete_btree(btree_item** vert)
{
    if (!(*vert) || !vert) return;

    delete_btree(&((*vert)->left));
    delete_btree(&((*vert)->right));

    free((*vert)->data);
    free(*vert);
    *vert = NULL;
}
