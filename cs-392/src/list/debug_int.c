#include "../../include/list.h"

void debug_int(struct s_node* head)
{
	struct s_node* node = head;

	if (head == NULL)
		return;

	my_str("(NULL <- ");
	my_int(*((int*) node->elem));
	my_str(" -> ");

	if (node->next != NULL)
	{
		my_int(*((int*) node->elem));
		my_str("), (");
	}

	else
	{
		my_str("NULL)");
		return;
	}

	while (node->next != NULL)
	{
		my_int(*((int*) node->prev->elem));
		my_str(" <- ");
		my_int(*((int*) node->elem));
		my_str(" -> ");
		my_int(*((int*) node->next->elem));
		my_str("), (");
		node = node->next;
	}

	my_int(*((int*) node->prev->elem));
	my_str(" <- ");
	my_int(*((int*) node->elem));
	my_str(" -> NULL)");
}
