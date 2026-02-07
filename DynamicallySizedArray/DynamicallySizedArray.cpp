
#include <iostream>
#include "DynamicallySizedArray.h"


int main() {
	// Read number of operations
	int q;
	if (!(std::cin >> q)) return 0;


	// Pre initialize 1000 array instances
	DynamicallySizedArray<int> arrays[1000];

	for (int i = 0; i < q; ++i) {
		int id;
		char op;
		std::cin >> id;         // instance id 1..1000
		--id;                   // convert to 0-based index
		std::cin >> std::ws;    // consume optional whitespacem just in case
		std::cin >> op;         // operation character input

		if (op == 'a') {
			// copy: arrays[id] becomes a copy of arrays[other]
			int other; std::cin >> other; --other;
			arrays[id] = arrays[other];
		} else if (op == '+') {
			// push back: append value at end
			int value; std::cin >> value;
			arrays[id].push_back(value);
		} else if (op == '-') {
			// pop back: remove last element
			arrays[id].pop_back();
		} else if (op == 'i') {
			// insert: place value at index, shifting other values right
			int index, value; std::cin >> index >> value;
			arrays[id].insert(index, value);
		} else if (op == 'e') {
			// erase: remove element at index, shifting other values left
			int index; std::cin >> index;
			arrays[id].erase(index);
		} else if (op == 'g') {
			// get: output element at index
			int index; std::cin >> index;
			std::cout << arrays[id][index] << '\n';
		} else if (op == 's') {
			// set: write value at index
			int index, value; std::cin >> index >> value;
			arrays[id][index] = value;
		} else if (op == 'r') {
			// resize: change logical size to newSize
			int newSize; std::cin >> newSize;
			arrays[id].resize(newSize);
		} else if (op == 'p') {
			// print: size on first line, then elements space-separated
			int s = arrays[id].size();
			std::cout << s << '\n';
			for (int j = 0; j < s; ++j) {
				if (j) std::cout << ' ';
				std::cout << arrays[id][j];
			}
			std::cout << '\n';
		}
	}

	return 0;
}