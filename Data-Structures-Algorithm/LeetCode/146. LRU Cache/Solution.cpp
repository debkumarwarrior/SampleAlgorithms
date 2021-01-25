#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <unordered_map>
using namespace std;

class LRUCache {
	typedef struct ListNode {
		int val;
		int key;
		struct ListNode * prev;
		struct ListNode * next;
		ListNode() : val(-1), prev(nullptr), next(nullptr) {}
		ListNode(int x) : val(x), prev(nullptr), next(nullptr) {}
	};
	ListNode * head;
	ListNode * tail;
	ListNode * cap;
	unordered_map<int, ListNode * > keymap;
public:
	LRUCache(int capacity) {
		cap = nullptr;
		head = new ListNode();
		ListNode * prev = head;
		for (int i = 1; i < capacity; i++) {
			ListNode * t = new ListNode();
			t->prev = prev;
			prev->next = t;
			prev = t;
		}
		tail = prev;
	}

	int get(int key) {
		if (keymap.find(key) != keymap.end()) {
			ListNode * t = keymap[key];
			if (t == nullptr) {
				return -1;
			}
			if (t == head) {
				return t->val;
			}
			if (t == tail) {
				tail = t->prev;
			}
			if (cap == t) {
				cap = t->prev;
			}
			t->prev->next = t->next;
			if (t->next) {
				t->next->prev = t->prev;
			}
			t->next = head;
			head->prev = t;
			head = t;
			return t->val;
		}
		return -1;
	}

	void put(int key, int value) {
		if (keymap.find(key) != keymap.end()) {
			ListNode * t = keymap[key];
			if (t == nullptr) {
				return;
			}
			if (t == head) {
                t->val = value;
				return;
			}
			if (t == tail) {
				tail = t->prev;
			}
			if (cap == t) {
				cap = t->prev;
			}
			t->prev->next = t->next;
			if (t->next) {
				t->next->prev = t->prev;
			}
			t->next = head;
			t->val = value;

			head->prev = t;
			head = t;
			return;
		}
		if (cap == nullptr) {
			cap = head;
			ListNode * t = head;
			t->val = value;
			t->key = key;
			keymap[key] = t;
			return;
		}
		if (head == tail) {
			keymap.erase(head->key);
			keymap[key] = head;
			head->key = key;
			head->val = value;
			return;
		}

		if (cap == tail) {
			ListNode * t = cap;
			int tk = t->key;
			t->val = value;
			t->key = key;

			cap = t->prev;
			tail = t->prev;
			tail->next = nullptr;
			keymap.erase(tk);
			keymap[key] = t;

			t->next = head;
			t->prev = nullptr;
			head->prev = t;
			head = t;
			return;
		}

		ListNode * t = tail;
		tail = tail->prev;
		tail->next = nullptr;

		t->prev = nullptr;
		t->val = value;
		t->key = key;
		keymap[key] = t;
		t->next = head;
		head->prev = t;
		head = t;
		return;
	}
	~LRUCache() {
		while (head) {
			ListNode * t = head;
			head = head->next;
			delete t;
		}
		head = tail = cap = nullptr;
	}
	void print() {
		cout << "Cache is ";
		ListNode * t = head;
		while (t) {
			cout << t->val << " ";
			t = t->next;
		}
		cout << endl;
	}
};


int main ()
{
	freopen("input.txt" "r", stdin);
	int TC;
	cin >> TC;
	for (int tc = 1; tc <= TC; tc++) {
		int capacity;
		cin >> capacity;
		LRUCache cache(capacity);
		int ops;
		cin >> ops;
		while (ops--) {
			int op;
			cin >> op;
			switch(op) {
				case 1:
					int key, value;
					cin >> key >> value;
					cache.put(key,value);
					break;
				case 2:
					int key;
					cin >> key;
					cache.get(key);
					break;
				default:
					break;
			}
		}
	}
	return 0;
}

