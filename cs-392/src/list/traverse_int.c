#include "../../include/list.h"

void traverse_int(struct s_node* head)
{
	struct s_node* curr;

	if (head == NULL)
		return;

	else
	{
		curr = head;

		while (curr != NULL)
		{
			my_int(*((int*) head->elem));
			my_char(' ');
			curr = curr->next;
		}
		my_char('\n');
	}
}

