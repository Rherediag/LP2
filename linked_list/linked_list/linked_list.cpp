#include <iostream>
#include <set>

using namespace std;

template <class T>
class linked_list;

template <class T>
class nodee
{
private:
	T dato;
	nodee<T> * p_next;
public:
	nodee(const T & d, nodee<T> * n = nullptr) :
		dato(d), p_next(n) {}

	~nodee() = default;

	friend class linked_list<T>;
};


template <class T>
class linked_list
{
private:
	nodee<T> * p_head;
public:
	class iterator
	{
	private:
		nodee<T> * p_current;

	public:
		void del() { ~linked_list(); }
		iterator(nodee<T> * n = nullptr) : p_current(n) {}
		~iterator() = default;

		iterator & operator ++ ()
		{
			p_current = p_current->p_next;
			return *this;
		}

		T & operator * ()
		{
			return p_current->dato;
		}

		bool operator != (const iterator & it)
		{
			return p_current != it.p_current;
		}
	};

	linked_list() : p_head(nullptr) {}


	~linked_list()
	{
		//node<T> * temp = p_head;
		while (p_head != nullptr)
			pop_front();
		delete p_head;
		//delete temp;
	}

	// pop_back
	// pop_front
	// reverse without create new nodes
	void pop_front()
	{
		if (!p_head) {
			return;
		}
		nodee<T> * temp = p_head;
		p_head = p_head->p_next;
		delete temp;
	}
	void pop_back()
	{
		nodee<T> * temp = p_head;
		nodee<T> * last_ptr = nullptr;
		while (temp->p_next != nullptr)
		{
			last_ptr = temp;
			temp = temp->p_next;
		}

		last_ptr->p_next = nullptr;
		delete temp;

		last_ptr = nullptr;
		delete last_ptr;
	}
	void reverse()
	{
		nodee<T> *prev = nullptr, *current = nullptr, *next = nullptr;
		current = p_head;
		while (current != nullptr)
		{
			next = current->p_next;
			current->p_next = prev;
			prev = current;
			current = next;
		}
		p_head = prev;
		prev = nullptr;
		delete prev;
		delete current;
		delete next;
	}
	void insert_front(const T & d)
	{
		p_head = new nodee<T>(d, p_head);
	}

	void insert_back(const T & d)
	{
		nodee<T> ** p_last = &p_head;
		while (*p_last)
			p_last = &(*p_last)->p_next;

		*p_last = new nodee<T>(d);

	}

	const iterator begin()
	{
		return { p_head };
	}

	const iterator end()
	{
		return { nullptr };
	}
};

int main()
{
	set<int> vi;
	vi.insert(4);
	vi.insert(6);
	vi.insert(71);
	vi.insert(3);
	vi.insert(8);
	vi.insert(9);

	for (set<int>::iterator it = vi.begin(); it != vi.end(); it++)
		cout << *it << " ";
	cout << endl;

	for (int e : vi)
		cout << e << " ";
	cout << endl;

	linked_list<int> lli;
	lli.insert_back(31);
	lli.insert_back(11);
	lli.insert_back(62);

	lli.insert_front(3);
	lli.insert_front(1);
	lli.insert_front(6);
	lli.insert_front(2);
	lli.insert_front(7);

	for (linked_list<int>::iterator it = lli.begin(); it != lli.end(); ++it)
		cout << *it << " ";
	cout << endl;
	lli.reverse();
	for (int e : lli)
		cout << e << " ";
	cout << endl;
	lli.pop_front();
	lli.pop_back();
	for (int e : lli)
		cout << e << " ";
	cout << endl;
	
	for (int e : lli)
		cout << e << " ";
	cout << endl;

	//return 0;
}
