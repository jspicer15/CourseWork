#include "../../include/list.h"

void* remove_node_at(struct s_node** head, int n)
{
	struct s_node* curr;
	void* element;

	if ((head == NULL) || (*head == NULL))
		return NULL;

	else
	{
		curr = *head;

		if (n <= 0)
		{
			element = curr->elem;
			free(*head);
		}

		while ((curr->next != NULL) && (n > 0))
		{
			curr = curr->next;
			n--;
		}

		if ((curr->prev != NULL) && (curr->next != NULL))
		{
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			element = curr->elem;
			free(curr);
		}

		else if ((curr->prev != NULL) && (curr->next == NULL))
		{
			curr->prev->next = NULL;
			element = curr->elem;
			free(curr);
		}

		else
		{
			element = curr->elem;
			free(curr);
		}

		return element;
	}
}

