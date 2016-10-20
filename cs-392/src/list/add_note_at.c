#include "../../include/list.h"

void add_node_at(struct s_node* node, struct s_node** head, int n)
{
	struct s_node* curr;

	if (n <= 0)
	{
		add_node(node, head);
		return;
	}

	if (node == NULL)
		return;

	if ((head == NULL) || (*head == NULL))
	{
		add_node(node, head);
		return;
	}

	else
	{
		curr = *head;

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
			node->next = curr->next;
			curr->next = node;
			node->prev = curr;
		}
	}
}

