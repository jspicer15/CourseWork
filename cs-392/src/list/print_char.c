#include "../../include/list.h"

void print_char(struct s_node* node)
{
	if (node == NULL)
		return;

	my_char(*((char*) node->elem));
	my_char('\n');
}
