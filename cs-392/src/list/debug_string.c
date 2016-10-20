#include "../../include/list.h"

void debug_string(struct s_node* head)
{
	struct s_node* node = head;

	if (head == NULL)
		return;

	my_str("(NULL <- ");
	my_str(((char*) node->elem));
	my_str(" -> ");

	if (node->next != NULL)
	{
		my_str(((char*) node->next->elem));
		my_str("), (");
		node = node->next;
	}

	else
	{
		my_str("NULL)\n");
		return;
	}

	while (node->next != NULL)
	{
		my_str(((char*) node->prev->elem));
		my_str(" <- ");
		my_str(((char*) node->elem));
		my_str(" -> ");
		my_str(((char*) node->next->elem));
		my_str("), (");
		node = node->next;
	}

	my_str(((char*) node->prev->elem));
	my_str(" <- ");
	my_str(((char*) node->elem));
	my_str(" -> NULL)\n");
}
