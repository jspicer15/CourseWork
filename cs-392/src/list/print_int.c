#include "../../include/list.h"

void print_int(struct s_node* node)
{
	if (node == NULL)
		return;

	my_int(*((int*) node->elem));
	my_char('\n');
}
