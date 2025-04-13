#include "btree.h"

int main()
{
    // Создание пустого дерева 
    btree_item* root = NULL;
    
    // Включение в дерево новых узлов, хранящих указатели на экземпляры структур c данными пользователя.
    int toinsert_amount = input_int("Enter amount of routers to insert into the tree: ");
    if (toinsert_amount <= 0)
    {
        puts("Uncorrect data entered. Minimal amount is 1.");
        return 1;
    }

    for (int i = 0; i < toinsert_amount; i++)
    {
        WIFI* router = (WIFI*)malloc(sizeof(WIFI)); 
        if (!router)
        {
            puts("Struct allocation failed");
            delete_btree(&root); // Удаление всего дерева
            return 1;
        }

        printf("\nRouter %d:\n", i+1);
        if (init_userdata(router) != 0)
        {
            free(router);
            router = NULL;
            delete_btree(&root); // Удаление всего дерева
            return 1;
        }
        if (!insert_btree(router, &root)) // Попытка включить в дерево новый узел
        {
            free(router); 
            delete_btree(&root); // Удаление всего дерева
            puts("Failed to insert");
        }
    }

    // Подсчет количества узлов в дереве
    int vert_count = vertex_count(root);
    printf("\n%d - entered count, %d result vertex count\n\n", toinsert_amount, vert_count);

    puts("Printing tree elements by increasing values:");
    print_btree_incr(root); // Вывод данных из узлов дерева по возрастанию
    
    puts("\nPrinting tree elements by decreasing values:");
    print_btree_decr(root); // Вывод данных из узлов дерева по убыванию

    WIFI router_to_delete;
    puts("\nEnter data for router to delete:");
    if (init_userdata(&router_to_delete) != 0)
    {
        puts("Error initializing router data.");
        delete_btree(&root); // Удаление всего дерева
        return 1;
    }

    WIFI* extracted = extract_value(&router_to_delete, &root); // Извелечние из дерева
    no_use_extracted(extracted); // Удаляем extracted т.к. не используется в дальнейшем

    puts("\nTree after deleting element:");
    print_btree_incr(root); // Вывод данных дерева по возрастанию
    
    delete_btree(&root); // Удаление всего дерева

    puts("\nTree fully deleted successfully");
    return 0;
}
