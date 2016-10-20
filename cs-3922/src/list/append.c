#include "../../include/list.h"

void append(struct s_node* node, struct s_node** head)
{
	struct s_node* curr = *head;

	if (node == NULL)
		return;

	if (node->elem == NULL)
		return;

	if (head == NULL)
	{
		add_node(node, *head);
	}

	else
	{
		while (curr->next != NULL)
		{
			curr = curr->next;
		}

		curr->next = node;
		node->prev = curr;
		node->next = NULL;
	}
}

