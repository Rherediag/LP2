#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;
//--------------------------------------------------------------------

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

//--------------------------------------------------------------------------
class Person {
public:
	std::string name;
	int phoneNumber;
	int id;

	Person() {};
	Person(std::string n, int i) : name(n), phoneNumber(i) {}
	void set_name(std::string n) { name = n; }
	void set_phoneNumber(int n) { phoneNumber = n; }
	std::string get_name() { return name; }
	int get_phoneNumber() { return phoneNumber; }
	friend std::ostream& operator<<(std::ostream& os, const Person& s)
	{
		// write out individual members of s with an end of line between each one
		os << s.name << '\n';
		os << s.phoneNumber;
		return os;
	}
	friend std::istream& operator>>(std::istream& is, Person& s)
	{
		// read in individual members of s
		//is >> s.name >> s.phoneNumber;
		is >> s.name;
		return is;
	}

};
class BST
{
	struct node
	{
		Person data;
		node* left;
		node* right;
		int height;
	};

	node* root;



	void makeEmpty(node* t)
	{
		if (t == nullptr)
			return;
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}

	node* insert(Person x, node* t)
	{
		if (t == nullptr)
		{
			t = new node;
			t->data = x;
			t->height = 0;
			t->left = t->right = nullptr;
			
		}
		else if (x.name < t->data.name)
		{
			t->left = insert(x, t->left);
			if (height(t->left) - height(t->right) == 2)
			{
				if (x.name < t->left->data.name)
					t = singleRightRotate(t);
				else
					t = doubleRightRotate(t);
			}
		}
		else if (x.name > t->data.name)
		{
			t->right = insert(x, t->right);
			if (height(t->right) - height(t->left) == 2)
			{
				if (x.name > t->right->data.name)
					t = singleLeftRotate(t);
				else
					t = doubleLeftRotate(t);
			}
		}

		t->height = max(height(t->left), height(t->right)) + 1;
		return t;
	}

	node* singleRightRotate(node* &t)
	{
		node* u = t->left;
		t->left = u->right;
		u->right = t;
		t->height = max(height(t->left), height(t->right)) + 1;
		u->height = max(height(u->left), t->height) + 1;
		return u;
	}

	node* singleLeftRotate(node* &t)
	{
		node* u = t->right;
		t->right = u->left;
		u->left = t;
		t->height = max(height(t->left), height(t->right)) + 1;
		u->height = max(height(t->right), t->height) + 1;
		return u;
	}

	node* doubleLeftRotate(node* &t)
	{
		t->right = singleRightRotate(t->right);
		return singleLeftRotate(t);
	}

	node* doubleRightRotate(node* &t)
	{
		t->left = singleLeftRotate(t->left);
		return singleRightRotate(t);
	}

	node* findMin(node* t)
	{
		if (t == nullptr)
			return nullptr;
		else if (t->left == nullptr)
			return t;
		else
			return findMin(t->left);
	}

	node* findMax(node* t)
	{
		if (t == nullptr)
			return nullptr;
		else if (t->right == nullptr)
			return t;
		else
			return findMax(t->right);
	}

	node* remove(Person x, node* t)
	{
		node* temp;

	
		if (t == nullptr)
			return nullptr;

		// Busca elemento
		else if (x.name < t->data.name)
			t->left = remove(x, t->left);
		else if (x.name > t->data.name)
			t->right = remove(x, t->right);

		// Encontro elemento con dos hijos
	
		else if (t->left && t->right)
		{
			temp = findMin(t->right);
			t->data = temp->data;
			t->right = remove(t->data, t->right);
		}
		// uno o menos hijos
		else
		{
			temp = t;
			if (t->left == nullptr)
				t = t->right;
			else if (t->right == nullptr)
				t = t->left;
			delete temp;
		}
		if (t == nullptr)
			return t;

		t->height = max(height(t->left), height(t->right)) + 1;

		// Si esta desbalanceado
		// If left node is deleted, right case
		if (height(t->left) - height(t->right) == 2)
		{
			// right right case
			if (t->left != nullptr  && height(t->left->left) - height(t->left->right) == 1)
				return singleLeftRotate(t);
			// right left case
			else
				return doubleLeftRotate(t);
		}
		// If right node is deleted, left case
		else if (height(t->right) - height(t->left) == 2)
		{
			// left left case
			if (t->right != nullptr  && height(t->right->right) - height(t->right->left) == 1)
				return singleRightRotate(t);
			// left right case
			else
				return doubleRightRotate(t);
		}
		return t;
	}

	int height(node* t)
	{
		return (t == nullptr ? -1 : t->height);
	}

	int getBalance(node* t)
	{
		if (t == nullptr)
			return 0;
		else
			return height(t->left) - height(t->right);
	}

	void inorder(node* t)
	{
		if (t == nullptr)
			return;
		inorder(t->left);
		cout << t->data.get_name()<<endl;
		cout << t->data.get_phoneNumber()<<endl;
		//li.insert_back(t->data);
		inorder(t->right);
	}

	void inorder2(node* t)
	{
		if (t == nullptr)
			return;
		inorder2(t->left);
		
		li.insert_back(t->data);
		inorder2(t->right);
	}

	void inorderit(node* t)
	{
	/*	if (t == nullptr)
			return;
		inorder(t->left);
		
		inorder(t->right);*/
		ofstream ofile;
		ofile.open("foobar.bin", std::ios::binary);
		//Person obj;
		for (Person obj : li)
			writeVal(ofile, obj.name);
		ofile.close();


	}
	void saveinfo() 
	{
		ofstream ofile;
		ofile.open("foobar.bin", std::ios::binary);
		
		for (Person obj : li) {
		writeVal(ofile, obj.name);
		writeVal(ofile, obj.phoneNumber);
		}
			
		ofile.close();
	}
	void bwrite(node* t)
	{
		if (t == nullptr)
			return;

		
		ofstream ofile;
		ofile.open("foobar.bin", std::ios::binary);
		Person obj;
		inorderit(t->left);
		obj = t->data;
		writeVal(ofile, obj.name);
		writeVal(ofile, obj.phoneNumber);
		//cout << t->data;
//		ofile.write(reinterpret_cast<const char*>(&obj.get_phoneNumber), sizeof(obj.get_phoneNumber));
		
		inorderit(t->right);
		//cout << t->data;
		ofile.close();

	}
	void writeVal(std::ostream &fout, const std::string &str)
	{
		int len = str.size();
		// Write the length of the string to the file so we can read the string.
		//fout.write(reinterpret_cast<char*>(&len), sizeof(len));
		// Write the string to the file.
		fout.write(reinterpret_cast<const char*>(str.c_str()), len)<<'\n';
	}
	void writeVal(std::ostream &fout, int &st)
	{
		string str = std::to_string(st);
		int len = str.size();
		// Write the length of the string to the file so we can read the string.
		//fout.write(reinterpret_cast<char*>(&len), sizeof(len));
		// Write the string to the file.
		fout.write(reinterpret_cast<const char*>(str.c_str()), len) << '\n';
	}
	void bread() 
	{
		ifstream istrm;
		istrm.open("foobar.bin", ios::binary);
		Person a;
		string str,str1;
		
		
		//while (!istrm.eof())
		while (istrm >> str)
		{
			a.name = str;
			istrm >> str1;
			a.phoneNumber = std::stoi(str1);

			li.insert_back(a);
			//a.phoneNumber = 
			//istrm.read(reinterpret_cast<char*>(&d), sizeof d);
			//a.phoneNumber = d;
			
			//insert(a, root);

			
		}
	
	}
public:
	void start() {
		bread();
		for (Person obj : li)
			insert(obj);
	}
	void exit() {
		inorder2(root);
		saveinfo();
	}
	BST()
	{
		root = nullptr;
	}
	linked_list<Person> li;
	void insert(Person x)
	{
		root = insert(x, root);
	}

	void remove(Person x)
	{
		root = remove(x, root);
	}

	void display()
	{
		inorder(root);
		cout << endl;
	}
	void write() {
		bwrite(root);
	}
	void read() { bread(); }
};


//-----------------------------------------------




//-----------------------------------------------




int main()
{
	BST t;
	
	int x;
	cin >> x;
	if(x ==1){
		Person a;
		a.name = "aron";
		a.phoneNumber = 963759102;
		Person b;
		b.name = "bruno";
		b.phoneNumber = 963759102;
		Person c;
		c.name = "carlos";
		c.phoneNumber = 963759102;
		Person d;
		d.name = "daniel";
		d.phoneNumber = 963759102;
		Person e;
		e.name = "ernesto";
		e.phoneNumber = 963759102;
		Person f;
		f.name = "franco";
		f.phoneNumber = 963759102;
		Person j;
		j.name = "juan";
		j.phoneNumber = 963759102;

		t.insert(f);
		t.insert(d);
		t.insert(j);
		t.insert(c);
		t.insert(b);
		t.insert(a);
		t.insert(e);
		t.exit();
	}
	else {
		Person x;
		x.name = "daniel";
		t.start();
		t.remove(x);
		t.display();
		t.exit();
	}


}