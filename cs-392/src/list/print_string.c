#include "../../include/list.h"

void print_string(struct s_node* node)
{
	if (node == NULL)
		return;

	my_str(((char*) node->elem));
	my_char('\n');
}
