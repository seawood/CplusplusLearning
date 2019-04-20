#include "StrVec.h"

allocator<string> StrVec::alloc;

StrVec::StrVec(const StrVec& s) {
	auto data = alloc_n_copy(s.begin(), s.end());
	elements = data.first;
	first_free = cap = data.second;
	cout << "copy constructor" << endl;
}

StrVec& StrVec::operator=(const StrVec& s) {
	auto data = alloc_n_copy(s.begin(), s.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	cout << "copy operator=" << endl;
	return *this;
}

StrVec& StrVec::operator=(StrVec&& s) noexcept {
	if (this != &s) {
		free();
		elements = s.elements;
		first_free = s.first_free;
		cap = s.cap;
		s.elements = s.first_free = s.cap = nullptr;
	}
	cout << "move operator=" << endl;
	return *this;
}

StrVec::StrVec(StrVec && s) noexcept
	:elements(s.elements), first_free(s.first_free), cap(s.cap) {
	s.elements = s.first_free = s.cap = nullptr;
	cout << "move constructor" << endl;
}

void StrVec::push_back(const string& s) {
	chk_n_alloc();
	alloc.construct(first_free++, s);
}

pair<string*, string*> StrVec::alloc_n_copy(const string* b, const string* e) {
	size_t tmp = e - b;
	auto data = alloc.allocate(e - b);
	return{ data, uninitialized_copy(b,e,data) };
}

void StrVec::free() {
	if (!elements) {
		for (auto p = first_free; p != elements;) {
			alloc.destroy(--p);
		}
		alloc.deallocate(elements, cap - elements);
	}
}

void StrVec::reallocate() {
	auto newcapacity = size() ? 2 * size() : 1;
	auto newdata = alloc.allocate(newcapacity);
	auto dest = newdata;
	auto p = elements;
	for (; p != first_free;++p) {
		alloc.construct(dest++, move(*p));
	}
	elements = newdata;
	first_free = dest;
	cap = elements + newcapacity;
}