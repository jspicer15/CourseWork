#include "../../include/list.h"

void* remove_last(struct s_node** head)
{
	struct s_node* curr = *head;
	void* element;

	if (head == NULL)
		return NULL;

	else
	{
		while (curr->next != NULL)
		{
			curr = curr->next;
		}

		curr->prev->next = NULL;
		element = curr->elem;
		free(curr);

		return element;
	}
}
