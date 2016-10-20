#include "../../include/list.h"

void add_node(struct s_node* node, struct s_node** head)
{
	if (node == NULL)
		return;

	if (node->elem == NULL)
		return;

	if (head == NULL)
		return;

	else
	{
		node->next = *head;
		if (node->next != NULL) node->next->prev = node;
		*head = node;
		node->prev = NULL;
	}
}

