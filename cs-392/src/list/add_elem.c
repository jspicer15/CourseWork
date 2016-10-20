#include "../../include/list.h"

void add_elem(void* elem, struct s_node** head)
{
	add_node(new_node(elem, NULL,NULL), head);
	/*struct s_node* node = NULL;
	struct s_node* hd = NULL;

	if ((head == NULL) || (*head == NULL))
		return;

	if (elem == NULL)
		return;

	else
	{
		hd = *head;
 		node = new_node(elem, *head, NULL);
		hd->prev = node;
	}*/
}
