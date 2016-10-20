#include "../../include/list.h"

void* elem_at(struct s_node* head, int n)
{
	struct s_node* curr;

	if (head == NULL)
		return NULL;

	if (n < 0)
		n = 0;

	else
	{
		curr = head;

		while ((n > 0) && (curr->next != NULL))
		{
			curr = curr->next;
			n--;
		}
	}

	return curr->elem;
}
