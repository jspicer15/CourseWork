#include "../../include/list.h"

void traverse_char(struct s_node* head)
{
	struct s_node* curr;

	if (head == NULL)
		return;

	else
	{
		curr = head;

		while (curr->next != NULL)
		{
			my_char(*((char*) head->elem));
			my_char(' ');
			curr = curr->next;
		}
		my_char('\n');
	}
}

