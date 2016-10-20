#include "../../include/list.h"

struct s_node* new_node(void* elem, struct s_node* next, struct s_node* previous)
{
	struct s_node* new_node = (struct s_node*) malloc(sizeof(struct s_node));

	new_node->elem = elem;
	new_node->next = next;
	new_node->prev = previous;

	return new_node;
}
