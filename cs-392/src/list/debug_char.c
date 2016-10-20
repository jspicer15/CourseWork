#include "../../include/list.h"

void debug_char(struct s_node* head)
{
	struct s_node* node = head;

	if (head == NULL)
		return;

	my_str("(NULL <- ");
	my_char(*((char*) node->elem));
	my_str(" -> ");

	if (node->next != NULL)
	{
		my_char(*((char*) node->elem));
		my_str("), (");
	}

	else
	{
		my_str("NULL)");
		return;
	}

	while (node->next != NULL)
	{
		my_char(*((char*) node->prev->elem));
		my_str(" <- ");
		my_char(*((char*) node->elem));
		my_str(" -> ");
		my_char(*((char*) node->next->elem));
		my_str("), (");
		node = node->next;
	}

	my_char(*((char*) node->elem));
	my_str(" <- ");
	my_char(*((char*) node->elem));
	my_str(" -> NULL)");
}
