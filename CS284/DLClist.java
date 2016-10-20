//@author John Spicer
public class DLClist
{
	private DLNode head;
	private int size;
	
	public DLClist()
	{
		size = 0;
	}

	/*
	@param i index at which to add the Object
	@param o Object to add at the index
	@return false if Object o is null, true otherwise
	*/
	public boolean add(int i, Object o)
	{ // check next and previous
		if(o == null)
			return false;
		if(i == 0)
			return add(o);
		DLNode curr = head;
		if(i > 0)
		{
			for(curr = head; i > 1; i--)
				curr = curr.next;
			curr.next = new DLNode(o, curr.next, curr);
			curr.next.next.previous = curr.next;
			size++;
		}
		if(i < 0)
		{
			for(curr = head; i < -1; i++)
				curr = curr.previous;
			curr.previous = new DLNode(o, curr, curr.previous);
			curr.previous.previous.next = curr.previous;
			size++;			
		}	
		return true;	
	}

	/*
	@param o Object to add as the new head
	@return false if Objec o is null, true otherwise
	*/
	public boolean add(Object o)
	{ // check next and previous
		if(o == null)
			return false;
		if(size <= 0)
		{
			head = new DLNode(o);
			size++;
			return true;
		}
		head = new DLNode(o, head.next, head.previous);
		head.next.previous = head;
		head.previous.next = head;
		size++;
		return true;		
	}
	
	/*
	@param o Object to append to the end of the list
	@return false if Object o is null, true otherwise
	*/
	public boolean append(Object o)
	{ // check next and previous
		if(o == null)
			return false;
		if(head == null)
			return add(o);
		DLNode curr = new DLNode(o,head,head.previous);
		head.previous = curr;
		curr.previous.next = curr;
		size++;
		return true;
	}
	
	/*
	@param i index of which Node to get the data from
	@return the Object at index i
	*/
	public Object get(int i)
	{
		DLNode curr;
		Object ret = null;
		if(size <= 0)
			ret = null;
		if(i >= 0)
		{
			for(curr = head; i > 0; i--)
				curr = curr.next;
			ret = curr.data;
		}
		if(i < 0)
		{
			for(curr = head; i < 0; i++)
				curr = curr.previous;
			ret = curr.data;
		}
		return ret;
	}

	// @return Object at the head position
	public Object get()
	{
		if(size <= 0)
			return null;
		return head.data;
	}

	// @return Object in the last index
	public Object getLast()
	{
		if(size <= 0)
			return null;
		return head.previous.data;
	}

	// @return the size of the list
	public int size()
	{
		return size;
	}

	// @return Object at the head which was removed
	public Object remove()
	{
		return remove(0);
	}

	// @return Object removed from the last index of the list
	public Object removeLast()
	{
		return remove(size-1);
	}

	/*
	@param i Index at which to remove an Object
	@return Object which was removed from index i
	*/
	public Object remove(int i)
	{ // fix curr.next and curr.previous for both cases
		Object ret = null;
		if(size > 0)
		{
			DLNode curr = head;
			if(size == 1)
			{
				ret = curr.data;
				head = null;
				return ret;
			}
			if(i == 0)
			{
				ret = curr.data;
				curr.next.previous = curr.previous;
				curr.previous.next = curr.next;
				head = curr.next;
				
			}
			else
			{
				if(i > 0)
				{
					for(curr = head; i >= 1; i--)
						curr = curr.next;
				}
				if(i < 0)
				{
					for(curr = head; i <= -1; i ++)
						curr = curr.previous;
				}
				ret = curr.data;
				curr.previous.next = curr.next;
				curr.next.previous = curr.previous;
			}
			size--;	
		}
		return ret;
	}
	
	/*
	@param o Object to be removed at the first instance it is found in
	@return true if Object is found and removed, false if Object is not found or if list is empty
	*/
	public boolean remove(Object o)
	{
		if(head==null)
			return false;
		DLNode curr;
		int i = 0;
		for(curr = head;i <= size-1;i++)
		{
			if(o.equals(curr.data))
			{
				remove(i);
				return true;
			}
			curr = curr.next;
		}
		return false;
	}

	
	public void showList()
	{
		if(head == null)
			System.out.println("List is Empty");
		DLNode curr;
		int i = 0;
		for(curr = head;i <= size-1;i++)
		{
			System.out.println("Element " + i + ": " + curr.data.toString());
			curr = curr.next;
		}
	}

	private class DLNode
	{
		public Object data;
		public DLNode next;
		public DLNode previous;
		
		// @param o Object to put in the data at the head node	
		public DLNode(Object o)
		{
			data = o;
			next = this;
			previous = this;
		}

		/*
		@param o Object to put in the data of the node
		@param n DLNode to put as the next node reference
		@param p DLNode to put as the previous node reference
		*/
		public DLNode(Object o, DLNode n, DLNode p)
		{
			data = o;
			next = n;
			previous = p;
		}
	}

	public static void main(String[] args)
	{
		DLClist list = new DLClist();
                System.out.println("\n");
		System.out.println("Creating empty DLClist lst");
		System.out.println("\n");
		list.showList();
		list.add(7);
		System.out.println("Creating a new head node with data 7");
		System.out.println("\n");
		System.out.println("Expected Element 0: 7");
		list.showList();
		System.out.println("\n");
		System.out.println("Getting element at the head: list.get(), expected 7");
		System.out.println(list.get());
                System.out.println("\n");				
		System.out.println("appending 5, -1, 0, 8, '10' to the list");
		list.append(5);
                list.append(-1);
                list.append(0);
                list.append(8);
                list.append("10");
                System.out.println("\n");
                System.out.println("New List:");
		list.showList();
                System.out.println("\n");
                System.out.println("Getting element at index 3: list.get(3), expected 0");
                System.out.println(list.get(3));
                System.out.println("\n");
                System.out.println("Adding -50 at the index 4");
		list.add(4, -50);
                list.showList();
                System.out.println("\n");
                System.out.println("Adding 15 at the index -1");
		list.add(-1, 15);
                System.out.println("Getting element -1: expected 15");
                System.out.println(list.get(-1));
                System.out.println("\n");
		list.showList();
                System.out.println("\n");
                System.out.println("Removing the item at the head and returning the new head, expecting 5");
		list.remove();
                System.out.println(list.get());
                System.out.println("\n");
		list.showList();
                System.out.println("\n");
                System.out.println("Removing the item at index 3");
		list.remove(3);
		list.showList();
                System.out.println("\n");
                System.out.println("Removing the item at index -3");
		list.remove(-3);
		list.showList();
                System.out.println("\n");
                System.out.println("Removing the first instance of the item 10");
		list.remove("10");
                list.showList();
                System.out.println("\n");
                System.out.println("Removing the last item in the list");
		list.removeLast();
		list.showList();
                System.out.println("\n");
                System.out.println("Getting the last item in the list, expected 0");
		System.out.println(list.getLast());
                System.out.println("\n");
                System.out.println("Getting the size of the list, expected 3");
                System.out.println(list.size());
                System.out.println("\n");
		System.out.println("Adding 100 to index 9");
		list.add(9, 100);
		list.showList();
	}
}
