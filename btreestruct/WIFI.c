#define _CRT_SECURE_NO_WARNINGS
#include "WIFI.h"
#ifndef WIFI_C
#define WIFI_C

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
		exit(EXIT_FAILURE);
	}
}

enum _5G_MARK input_5G_mark(const char* message) 
{
	char buffer[MAX_MARK_LENGTH];

	printf("%s", message);
	input_string(buffer, MAX_MARK_LENGTH);
	if (strcmp(buffer, "yes") == 0) return Is5G;
	if (strcmp(buffer, "no") == 0) return Not5G;
	return Undefined;
}

enum ERROR_CODE router_DataCheck(const WIFI* router)
{
	if (router->port_count > 32) 
	{
		printf("Entered port count information is incorrect. Port count cant be more than 32.\n");
		return Invalid_Port_Count;
	}

	if(router->has_5G == Undefined)
	{
		printf("Entered 5G mark is incorrect.");
		return Invalid_5G_Mark;
	}
	printf("Entered data is correct!\n");
	return Success; 
}

int init_struct(WIFI* router, const char* vendor, unsigned short port_count, enum _5G_MARK has_5G ) 
{ 
    strncpy(router->vendor, vendor, MAX_VENDOR_LENGTH);
    router->vendor[MAX_VENDOR_LENGTH - 1] = '\0';
    router->port_count = port_count;
    router->has_5G = has_5G;   
    return router_DataCheck(router);
}

int struct_init_result(const enum ERROR_CODE result_code)
{
	switch (result_code)
	{
		case Success:
			printf("Structure initialized successfully.\n");
			return 0;
		default:
			printf("Structure initialization failed.\n");
			return 1;
	}
}

int init_userdata(WIFI* router)
{
	char vendor[MAX_VENDOR_LENGTH];

        printf("Enter brand name: ");
	input_string(vendor, MAX_VENDOR_LENGTH);

	unsigned short port_count = input_int("\nEnter port count: ");
	enum _5G_MARK has_5G = input_5G_mark("\nHas 5G? (yes/no): ");
	
	if (struct_init_result(init_struct(router, vendor, port_count, has_5G)) != 0) return 1;
	return 0;
}

void copy_struct(const WIFI* src, WIFI* dest)
{
    if (!src || !dest) return;
    
    strncpy(dest->vendor, src->vendor, MAX_VENDOR_LENGTH);
    dest->vendor[MAX_VENDOR_LENGTH - 1] = '\0';
    dest->port_count = src->port_count;
    dest->has_5G = src->has_5G;
}

void print_struct(const WIFI* router)
{
    printf("Brand name: %s \nport_count: %d\nhas 5g: %s\n\n ",
    router->vendor,
    router->port_count,
    router->has_5G == Is5G ? "yes" : "no");
}

int field_changing(WIFI* router)
{
    int field_tochange = input_int("\nWhich field you want to change?\n1 - brand name\n2 - port count\n3 - Wifi 5G Mark\nEnter any other symbol if you won't change anything\n\nEnter only digit: ");

    short init_checkmark;

    switch (field_tochange)
    {
        case 1:
        	char vendor_name_tochange[MAX_VENDOR_LENGTH];
		printf("\nEnter new vendor value: ");
		input_string(vendor_name_tochange, MAX_VENDOR_LENGTH);
		init_checkmark = struct_init_result(update_vendor_name(router, vendor_name_tochange));
		break;
        case 2:
		unsigned short port_count_tochange = input_int("\nEnter new port count value: ");
		init_checkmark = struct_init_result(update_port_count(router, port_count_tochange));
		break;
        case 3:
                enum _5G_MARK _5G_mark_tochange = input_5G_mark("\nEnter new 5G mark value: ");
		init_checkmark = struct_init_result(update_5G_mark(router, _5G_mark_tochange));
		break;
        default:
                printf("\nUndefined value received. Nothing will be changed.\n");
		break;
    }
    if (init_checkmark == 0) return 0;

    return 1;
}

int update_port_count(WIFI* router, const unsigned short value)
{
	router->port_count = value;
	return router_DataCheck(router);
}

int update_vendor_name(WIFI* router, const char* value)
{
	strncpy(router->vendor, value, MAX_VENDOR_LENGTH);
	return router_DataCheck(router);
}

int update_5G_mark(WIFI* router, const enum _5G_MARK value)
{
	router->has_5G = value;
	return router_DataCheck(router);
}

void dynamic_struct_free(WIFI* dym_struct_ptr)
{ 
	free(dym_struct_ptr);
}

int is_equal(const WIFI* router1, const WIFI* router2)
{
	return ((strcmp(router1->vendor, router2->vendor) == 0) && router1->port_count == router2->port_count && router1->has_5G == router2->has_5G);
}

int compare(const WIFI* router1, const WIFI* router2)
{
	int vend_cmp_result = strcmp(router2->vendor, router1->vendor);
	if (vend_cmp_result != 0) return (vend_cmp_result < 0 ? 1 : 0);
	return compare_int(router1, router2); 
}

// Port_count - Second priority of comparsion. 5G mark - third.
// Returns 1 if p2 is bigger. Else 0. 
int compare_int(const WIFI* router1, const WIFI* router2)
{
	if (router2->port_count != router1->port_count) return (router2->port_count > router1->port_count ? 0 : 1);
	return (router2->has_5G > router1->has_5G ? 1 : 0);
}

#endif 
 
