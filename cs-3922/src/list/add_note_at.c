#include "../../include/list.h"

void add_node_at(struct s_node* node, struct s_node** head, int n)
{
	struct s_node* curr = *head;

	if (n <= 0)
		n = 0;

	if (node == NULL)
		return;

	if (head == NULL)
		add_node(node, head);

	else
	{
		while ((curr->next != NULL) && (n > 1))
		{
			curr = curr->next;
			n--;
		}

		if (curr->next == NULL)
		{
			curr->next = node;
			node->prev = curr;
			node->next = NULL;
		}

		else
		{
			curr->next->prev = node;
			node->next = curr->next->next;
			curr->next = node;
			node->prev = curr;
		}
	}
}

