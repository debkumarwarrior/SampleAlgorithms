struct HeapNode
{
	ListNode * node;
	int listId;
	HeapNode(ListNode * n, int id) :node(n), listId(id) {}
	HeapNode() : node(NULL), listId(-1) {}
};

class MinHeap
{
	HeapNode * arr;
	int capacity;
	int size;
	void heapify(int i);
	inline int leftChild(int i) { return (2 * i) + 1; }
	inline int rightChild(int i) { return (2 * i) + 2; }
	inline int parent(int i) { return (i - 1) / 2; }
public:
	MinHeap(int n) :capacity(n), size(0) {
		try {
			arr = new HeapNode[capacity];
		} catch (...) {
			arr = NULL;
		}
	}
	void insert(ListNode * p, int id);
	HeapNode deleteMin();
	int getCount() { return size; }
	~MinHeap() { delete[]arr; size = 0; capacity = 0; }

};
void MinHeap::heapify(int i)
{
	int l = leftChild(i);
	int r = rightChild(i);

	int smallest = i;
	if (l < size && arr[l].node->val < arr[smallest].node->val) {
		smallest = l;
	}
	if (r < size && arr[r].node->val < arr[smallest].node->val) {
		smallest = r;
	}
	if (smallest != i) {
		HeapNode tmp = arr[i];
		arr[i] = arr[smallest];
		arr[smallest] = tmp;
		heapify(smallest);
	}
}
void MinHeap::insert(ListNode * p, int id)
{
	int i = size;
	arr[size].node = p;
	arr[size].listId = id;
	size++;
	while (i >= 0 && arr[parent(i)].node->val > arr[i].node->val)
	{
		HeapNode tmp = arr[parent(i)];
		arr[parent(i)] = arr[i];
		arr[i] = tmp;
        i = parent(i);
	}
}

HeapNode MinHeap::deleteMin()
{
	HeapNode ret(arr[0].node, arr[0].listId);
	arr[0] = arr[size - 1];

	size--;
	heapify(0);
	return ret;
}

void print(ListNode * p)
{
	if (!p) { cout << endl; return; }
	cout << p->val << " ";
	print(p->next);
}

class Solution {
public:
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		MinHeap minHeap(lists.size());

		for (int k = 0; k < lists.size(); k++) {
			ListNode * p = lists[k];
			if (p) {
				lists[k] = lists[k]->next;
				p->next = NULL;
				minHeap.insert(p, k);
			}
		}
		ListNode * head = NULL;
		ListNode * p1 = NULL;
		while (minHeap.getCount() > 0) {
			HeapNode h = minHeap.deleteMin();
			ListNode * p = lists[h.listId];
			if (p) {
				lists[h.listId] = lists[h.listId]->next;
				p->next = NULL;
				minHeap.insert(p, h.listId);
			}
			ListNode * p2 = h.node;
			if (head == NULL) {
				head = p2;
				p1 = p2;
			} else {
				p1->next = p2;
				p1 = p2;
			}
		}
        print(head);
		return head;
	}
};
