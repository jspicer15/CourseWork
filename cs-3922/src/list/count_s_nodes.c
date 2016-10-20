#include "../../include/list.h"

int count_s_nodes(struct s_node* head)
{
	int len = 0;
	struct s_node* curr = head;

	if (head == NULL)
		return len;

	else
	{
		while (curr->next != NULL)
		{
			len++;
			curr = curr->next;
		}

		return len;
	}
}
