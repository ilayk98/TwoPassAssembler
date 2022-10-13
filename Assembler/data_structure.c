#include "constant.h"
#include "data_structure.h"
#include "manage_line.h"
#include "pre_assembler_phase.h"
#include "errors.h"



head_of_macro_list *create_macro_list(head_of_macro_list *list)
{
	list = (head_of_macro_list*)malloc(sizeof(head_of_macro_list));
	if(list == NULL)
     {
        MEMORY_ALLOCATION_FAIL
     }
	list->head = NULL;
    return list;
}






head_of_symbol_list *create_symbol_list()
 {
     head_of_symbol_list *list = (head_of_symbol_list*)malloc(sizeof(head_of_symbol_list));
     if(list == NULL)
     {
        MEMORY_ALLOCATION_FAIL
     }
     list->head = NULL;
     return list;
 }






 head_of_data_lines *create_data_list()
{
        head_of_data_lines *list = (head_of_data_lines*)malloc(sizeof(head_of_data_lines));
        if(list == NULL)
        {
            MEMORY_ALLOCATION_FAIL
        }
        list->head = NULL;
        return list;
}






line *add_data_parameter(int x)
{
	line *p = (line*)malloc(sizeof(line));
    if(p==NULL)
    {
        MEMORY_ALLOCATION_FAIL
    }
	p->classify = A;
	p->signal = x;

	return p;
}






line *create_single_line()
{
    line *p = (line*)malloc(sizeof(line));
    if(p==NULL)
    {
            MEMORY_ALLOCATION_FAIL
    }
    p->classify =0;
    p->signal =0;

    return p;
}






line *add_opcode_line(int x)
{
	line *p = (line*)malloc(sizeof(line));

    if(p == NULL)
    {
        MEMORY_ALLOCATION_FAIL
    }
	p->classify = A;
	insert_opcode(x, p);

	return p;
}






void add_macro(head_of_macro_list *list,char* name, char temp_macro_table[LENGTH_MACRO][LENGTH_LINE], int num_of_macro_lines)
{
	int j;
  	macro_table* p = (macro_table*)malloc(sizeof(macro_table));
	macro_table* temp=NULL;
	if(p == NULL)
	{
		MEMORY_ALLOCATION_FAIL
	}
	
	/*copying the information to the macro node */
    strcpy (p->macro_name , name);
    for(j = 0; j < num_of_macro_lines; j++)
    {
    	strcpy(p->macro_lines[j] , temp_macro_table[j]);
    }
		
	p->line_max_indx = num_of_macro_lines;
    p->next = NULL;
	
	/*adding the node to the linked list */
    if(list->head == NULL)
    {
    	list->head = p;
    	return;
    }
	else
    {
    	temp = list->head;
     	while(temp->next != NULL)
           	temp = temp->next;
    	temp->next = p;
	}	
}






void add_label(head_of_symbol_list* symbol_list ,char *label_name, int symbol_type, int TIC)
{
    symbol_table *p = (symbol_table*)malloc(sizeof(symbol_table));
	symbol_table* temp=NULL;

    if(p==NULL)
    {
        MEMORY_ALLOCATION_FAIL
    }

	/*copying the information to the symbol node */
    strcpy (p->symbol , label_name);
    p->printed = 0;

    switch(symbol_type)
    {
        case DATA:
            strcpy(p->attributes, "data");
			p->value = TIC;
    		p->offset = TIC % 16;
			p->base_address = TIC - p->offset;
   			p->next = NULL;
            break;

        case CODE:
            strcpy(p->attributes, "code");
			p->value = TIC;
    		p->offset = TIC % 16;
			p->base_address = TIC - p->offset;
   			p->next = NULL;
            break;

        case ENTRY:
            strcpy(p->attributes, ", entry");
            break;

        case EXTERNAL:
            strcpy(p->attributes, "external");
			p->value = 0;
			p->offset = 0;
			p->base_address = 0;
			p->next = NULL;
            break;

        default: 
            break;
    }

	/*adding the node to the linked symbol list */
    	if(symbol_list->head == NULL)
    	{
        	symbol_list->head = p;
        	return;
    	}
    	else
    	{
        	temp = symbol_list->head;
        	while(temp->next != NULL)
            	temp = temp->next;
        	temp->next = p;
    	}
}






void add_data_line(head_of_data_lines* data_lines_list , line *data_line)
{
    data_lines *p = (data_lines*)malloc(sizeof(data_lines));
	data_lines* temp=NULL;

    if(p==NULL)
    {
        MEMORY_ALLOCATION_FAIL
    }

    p->data = data_line;
    p->next = NULL;

    if(data_lines_list->head == NULL)
    {
        data_lines_list->head = p;
        return;
    }
    else
    {
        temp = data_lines_list->head;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = p;
    }
}









void free_macro_table_memory(head_of_macro_list* list)
{
	macro_table* temp=NULL;
	while(list->head != NULL)
	{
		temp = list->head ;
		list->head  = list->head -> next;
		free(temp);	
	}
	free(list);
}





void free_symbol_table_memory(head_of_symbol_list* list)
{
    symbol_table* p=NULL;
    symbol_table* temp=NULL;

    if(list == NULL)
        return;
    p = list->head;
    while(p != NULL)
    {
        temp = p;
        p = p->next;
        free(temp);
    }
    free(list);
}






void free_data_line_memory(head_of_data_lines* list)
{
    data_lines* p=NULL;
    data_lines* temp=NULL;

    if(list == NULL)
        return;
    p = list->head;
    while(p != NULL)
    {
        temp = p;
        p = p->next;
        free(temp);
    }
    free(list);
}






void free_files_names(char *ob_file_name, char *ent_file_name, char *ext_file_name)
{
    free(ob_file_name);
    free(ent_file_name);
    free(ext_file_name);
}




essentials *create_essentials()
{
    essentials *menu = (essentials*)malloc(sizeof(essentials));
    if(menu == NULL)
    {
        MEMORY_ALLOCATION_FAIL
    }

    /* initialize data counter(DC), and instrcution counter(TIC/IC) */
    menu->IC=100;
    menu->TIC=100;
    menu->DC=0;
    
    return menu;
}
