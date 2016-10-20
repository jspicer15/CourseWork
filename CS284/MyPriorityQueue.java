/*
	@author John Spicer
*/
public class MyPriorityQueue extends MyMaxHeap
{
        private MyMaxHeap theQ;

	/*
		default constructor
	*/
        public MyPriorityQueue()
        {
		theQ = new MyMaxHeap();
        }
	
	/*
		@param arr: Array of Comparable to add to the Queue
		@param n: size of the Queue
	*/
        public MyPriorityQueue(Comparable[] arr, int n)
        {
                theQ = new MyMaxHeap(arr, n);
        }

	/*
		@param o: Comparable to enqueue to the queue
		@return MyMaxHeap.add(o)
	*/
        public boolean enqueue(Comparable o)
        {
                return theQ.add(o);
        }

	/*
		@return MyMaxHeap.removeMax()
	*/
        public Object dequeue()
        {
                return theQ.removeMax();
        }

	/*
		@return MyMaxHeap.getMax()
	*/
        public Object peek()
        {
                return theQ.getMax();
        }

	/*
		@return true if queue is empty, false otherwise
	*/
        public boolean empty()
        {
                if(theQ.size() <= 0)
                        return true;
                return false;
        }

	/*
		@return MyMaxHeap.parse()
	*/
	public void parse()
	{
		theQ.parse();
	}

	/*
		testing
	*/
	public static void main(String[] args)
	{
		MyPriorityQueue theQ = new MyPriorityQueue();

		System.out.println("Creating new MyPriorityQueue() theQ \n");
		System.out.println("Enqueueing 5, 6, and 18 to theQ \n");
		theQ.enqueue(5);
		theQ.enqueue(6);
		theQ.enqueue(18);
		
		System.out.println("Expected 18 5 6 \n");
		theQ.parse();

		System.out.println("Dequeueing the first item (18) \n");
		System.out.println(theQ.dequeue() + "\n");

		System.out.println("Getting the peek (6) \n");
		System.out.println(theQ.peek());

		System.out.println("Creating new MyPriorityQueue({1,5,9,15,-65, 106}, 8) newQ \n");
		Comparable[] arr = {1, 5, 9, 15, -65, 106};
		MyPriorityQueue newQ = new MyPriorityQueue(arr, 8);

		System.out.println("Expected 106 15 9 5 -65 1");
                newQ.parse();

                System.out.println("Checking if newQ is empty, Expected false \n");
                System.out.println(newQ.empty());


	}
}
