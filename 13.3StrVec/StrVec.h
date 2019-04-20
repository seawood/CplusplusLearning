#ifndef STRVEC_H
#define STRVEC_H


#include <string>
#include <memory>
#include <utility>
#include <iostream>

using namespace std;

class StrVec {
public:
	StrVec():
		elements(nullptr), first_free(nullptr), cap(nullptr) {
		cout << "Default Constructor" << endl;
	}
	StrVec(const StrVec&);
	StrVec(StrVec&&) noexcept;
	StrVec& operator=(const StrVec&);
	StrVec& operator=(StrVec&&) noexcept;
	~StrVec() { free(); cout << "free" << endl; }
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	string* begin() const { return elements; }
	string* end() const { return first_free; }
	void push_back(const string&);
private:
	static allocator<string> alloc;
	void reallocate();
	void chk_n_alloc() { if (first_free == cap) reallocate(); }
	void free();
	pair<string*, string*> alloc_n_copy(const string*, const string*); 
	string *elements;
	string *first_free;
	string *cap;
};
#endif