#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <utility>
using namespace std;

class LFUCache1 {
	vector<pair<int, int>> min_heap;
	int count;
	int capacity;
	unordered_map<int, pair<int, int>> table;

	int parent(int i) {
		return (i - 1) / 2;
	}

	int left_child(int i) {
		return (2 * i) + 1;
	}
	int right_child(int i) {
		return (2 * i) + 2;
	}

	void swap(int a, int b) {
		table[min_heap[a].first].first = b;
		table[min_heap[b].first].first = a;

		pair<int, int> tmp = min_heap[a];
		min_heap[a] = min_heap[b];
		min_heap[b] = tmp;
	}

	void heapify_down(int idx) {
		int min = idx;
		int left = left_child(idx);
		if (left < count && min_heap[min].second >= min_heap[left].second) {
			min = left;
		}
		int right = right_child(idx);
		if (right < count && min_heap[min].second >= min_heap[right].second) {
			min = right;
		}

		if (min != idx) {
			swap(min, idx);
			heapify_down(min);
		}
	}

	void heapify_up(int idx) {
		int p = parent(idx);
		if (p >= 0 && min_heap[p].second > min_heap[idx].second) {
			swap(p, idx);
			heapify_up(p);
		}
	}
public:
	LFUCache1(int c) : capacity(c), count(0) {
		min_heap.resize(capacity, make_pair(-1, -1));
	}

	int get(int key) {
		if (table.find(key) != table.end()) {
			min_heap[table[key].first].second++;
			heapify_down(table[key].first);
			return table[key].second;
		}

		return -1;
	}

	void put(int key, int value) {
		if (capacity <= 0) {
			return;
		}

		if (table.find(key) != table.end()) {
			min_heap[table[key].first].second++;
			heapify_down(table[key].first);
			table[key].second = value;
			return;
		}
		if (count == capacity) {
			swap(0, count - 1);
			table.erase(min_heap[count - 1].first);
			count--;
			heapify_down(0);
		}

		min_heap[count].first = key;
		min_heap[count].second = 1;

		table[key].first = count;
		table[key].second = value;
		count++;

		heapify_up(count - 1);
	}
};


class LFUCache {
	unordered_map<int, int> key_value_map;
	unordered_map<int, list<int>> freq_key_map;
	unordered_map<int, pair<int, list<int>::iterator>> key_freq_map;
	int capacity;
	int min_freq = 0;
	int count;

	void add_frequency(int key) {
		if (key_freq_map.find(key) == key_freq_map.end()) {
			freq_key_map[1].push_front(key);
			key_freq_map[key] = make_pair(1, freq_key_map[1].begin());
			min_freq = 1;
			return;			
		}
		int curr_freq = key_freq_map[key].first;

		freq_key_map[curr_freq].erase(key_freq_map[key].second);
		freq_key_map[curr_freq + 1].push_front(key);

		key_freq_map[key].first = curr_freq + 1;
		key_freq_map[key].second = freq_key_map[curr_freq + 1].begin();

		if (curr_freq == min_freq && freq_key_map[curr_freq].size() == 0) {
			freq_key_map.erase(curr_freq);
			min_freq = curr_freq + 1;
		}
	}

public:
	LFUCache(int capacity) {
		this->capacity = capacity;
		min_freq = 0;
		count = 0;
	}

	int get(int key) {
		if (key_value_map.find(key) == key_value_map.end()) {
			return -1;
		}

		add_frequency(key);
		return key_value_map[key];
	}

	void put(int key, int value) {
		if (capacity <= 0) {
			return;
		}

		if (key_value_map.size() == capacity) {
			int k = freq_key_map[min_freq].back();
			freq_key_map[min_freq].pop_back();

			key_value_map.erase(k);
			key_freq_map.erase(k);
		}

		add_frequency(key);
		key_value_map[key] = value;
	}

};
/**
* Your LFUCache object will be instantiated and called as such:
* LFUCache* obj = new LFUCache(capacity);
* int param_1 = obj->get(key);
* obj->put(key,value);
*/

int main() {
	freopen("input.txt", "r", stdin);
	int TC;
	cin >> TC;
	LFUCache * cache = nullptr;
	for (int tc = 1; tc <= TC; tc++) {
		int count;
		cin >> count;
		for (int c = 1; c <= count; c++) {
			int opr;
			cin >> opr;
			switch (opr) {
			case 0:
				int capacity;
				cin >> capacity;
				cache = new LFUCache(capacity);
				cout << "Create Cache : Capacity : " << capacity << endl;
				break;

			case 1:
				int k, v;
				cin >> k >> v;
				cache->put(k, v);
				cout << "Put Cache : Key : " << k << " Value : " << v << endl;
				break;

			case 2:
				cin >> k;
				cout << "Get Cache : Key : " << k << " Value : " << cache->get(k) << endl;
				break;

			default:
				break;
			}
		}
		if (cache) {
			delete cache;
			cache = nullptr;
		}
	}
	return 0;
}