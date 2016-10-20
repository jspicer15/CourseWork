#include "../../include/list.h"

void* remove_node(struct s_node** node)
{
	void* element;
	struct s_node* nd;

	if ((node == NULL) || (*node == NULL))
		return NULL;

	else
	{
		nd = *node;
		*node = (*node)->next;

		element = nd->elem;

		nd->next = NULL;
		nd->elem = NULL;
		nd->prev = NULL;

		free(nd); 
		return element;
	}
}

