#include "../../include/list.h"

void* remove_last(struct s_node** head)
{
	struct s_node* curr;
	void* element;

	if ((head == NULL) || (*head == NULL))
		return NULL;

	else
	{
		curr = *head;

		while (curr->next != NULL)
		{
			curr = curr->next;
		}

		curr->prev->next = NULL;
		element = curr->elem;
		curr->elem = NULL;
		curr->prev = NULL;
		curr->next = NULL;
		free(curr);

		return element;
	}
}
