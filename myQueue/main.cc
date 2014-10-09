#include "myQueue.h"

using namespace std;

int main(int argc, const char *argv[])
{
	MyQueue<int> queue;
	queue.enQueue(9);
	queue.enQueue(7);
	queue.enQueue(5);
	queue.enQueue(3);
	queue.enQueue(1);
	
	MyQueue<int> queue1 = queue;
	while(!queue.isEmpty()) {
		cout << queue.frontElem() << endl;
		queue.deQueue();
	}

	while(!queue1.isEmpty()) {
		cout << queue1.frontElem() << endl;
		queue1.deQueue();
	}

	return 0;
}
