#include "../../include/list.h"

void append(struct s_node* node, struct s_node** head)
{
	struct s_node* curr;

	if (node == NULL)
		return;

	if (node->elem == NULL)
		return;

	if ((head == NULL) || (*head == NULL))
	{
		add_node(node, head);
	}

	else
	{
		curr = *head;

		while (curr->next != NULL)
		{
			curr = curr->next;
		}

		curr->next = node;
		node->prev = curr;
	}
}

