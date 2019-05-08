#include <iostream>
#include <string>
#include <sstream>
#include <cassert>


using namespace std;


template<typename KeyType, typename ValueType>
struct Node
{

	//struktura pelniaca role hasla w slowniku, majaca na celu przechowanie klucza i wartosci
	//oraz wskazania na prawe i lewe dziecko
	struct Node<KeyType, ValueType>* right = NULL;
	struct Node<KeyType, ValueType>* left = NULL;
	KeyType key;
	ValueType value;

};

template<typename KeyType, typename ValueType>
class MultiSlownik
{
public:

	using key_type = KeyType;
	using value_type = ValueType;
	MultiSlownik()
	{
		//kontruktor trywialny
		root = nullptr;
		elements = 0;
	}
	~MultiSlownik()
	{
		//destruktor trywialny
		destroy(root);

	}

	void insert(key_type key, value_type value)
	{

		if (!root)
		{
			root = new Node<key_type, value_type>;
			root->left = nullptr;
			root->right = nullptr;
			root->key = key;
			root->value = value;
		}
		else
		{
			splay(root, key);
			if (root->key > key)
			{
				Node<key_type, value_type>* node = new Node<key_type, value_type>;
				node->right = root;
				node->left = root->left;
				root->left = nullptr;
				node->key = key;
				node->value = value;
				root = node;
			}
			else if (root->key < key)
			{
				Node<key_type, value_type>* node = new  Node<key_type, value_type>;
				node->left = root;
				node->right = root->right;
				root->right = nullptr;
				node->key = key;
				node->value = value;
				root = node;
			}
			else
			{
				root->value = value;
				elements--;
			}

		}
		elements++;

	}

	/*
	*usuniecie wezla o zadanym kluczu i wartosci
	*/
	void delete_node(key_type& key, value_type& value)
	{
		if (!(root->key == key))
		{
			splay(root, key);
			if (root->key == key)
			{
				if (root->value != value)
					cout << "Nie istnieje element o zadanym kluczu i wartosci" << endl;
				Node<key_type, value_type>* tempL = nullptr;
				Node<key_type, value_type>* tempR = nullptr;

				tempL = root->left;
				tempR = root->right;
				delete root;
				root = nullptr;
				if (tempL)//sprawdzenie istnienia lewego poddrzewa
				{
					splay(tempL, key); //do korzenia lewe dziecko
					while (tempL->right)
						rotL(tempL); //rotacja prawej czesci lewego poddrzewa
					tempL->right = tempR;
					root = tempL;

				}
				else if (tempR) //sprawdzenie istnienia prawego poddrzewa, jezeli nie ma lewego
				{
					splay(tempR, key);
					while (tempR->left)
						rotR(tempR);//rotacja lewej czesci prawego poddrzewa
					tempR->left = tempL;
					root = tempR;
				}

			}
		}
	}

	/*
	*metoda wyswietlajaca elementy slownika
	*/
	void display(Node<key_type, value_type>*& root)
	{
		if (!root) //sprawdzenie czy slownik ma zawartosc
			cout << "Slownik pusty" << endl;

		cout << "Klucz: " << root->key << " Wartosc: " << root->value << endl;

		if (root->left)
		{
			display(root->left);
		}
		if (root->right)
			display(root->right);
	}

	void show()
	{
		display(root);
	}

    bool compare_nodes(Node<key_type,value_type>* root1, Node<key_type,value_type>* root2)
    {
        if(root1->key == root2->key)
            {
                if(root1->left)
                    compare_nodes(root1->left,root2->left);
                else if(root1->right)
                    compare_nodes(root1->right,root2->right);
                return true;
            }

        else return false;
    }

	bool compare_dict(MultiSlownik<KeyType, ValueType>& slownik1,MultiSlownik<KeyType, ValueType>& slownik2)
	{

	    if((slownik1.size()==0)&&(slownik2.size()==0)) return true;

	    if(slownik1.size() == slownik2.size())
            return compare_nodes(slownik1.root,slownik2.root);
        else return false;
	}

	/*!
	 * zwraca wartosc dla podanego klucza
	 */
	value_type& value(key_type key) const
	{
		//szukamy wezla w drzewie splay z kluczem key, ktory zostanie przemieszczony do korzenia
		splay(root, key);
		if (root->key == key)
			return root->value;
		else
			cout << "nie odnaleziono klucza" << endl;
	}

	/*
		zmienia wartosc dla podanego klucza
	*/

	void change_value(const key_type& key, const value_type& new_value)
	{
		value_type& temp = value(key);

	}

	/*!
	 * zwraca informacje, czy istnieje w slowniku podany klucz
	 */
	bool contains(key_type key)
	{
		if (!root)
			return false;
		splay(root, key);
		return (root->key == key) ? true : false;
	}

	/*
	*zwraca inf, czy slownik jest pusty
	*/
	bool isEmpty() const
	{
		if (!elements)
		{
			return 1;
		}
		return 0;
	}

	/*!
	 * zwraca liczbe wpisow w slowniku, rozmiar slownika
	 */
	int size()
	{
		return elements;
	}


	//operatory
	//operator wypisania elementow slownika w konsoli
	friend ostream& operator <<(ostream& os,  MultiSlownik<KeyType, ValueType>& slownik)
	{
		os << slownik.root->key<<" "<<slownik.root->value << endl;
	}
	//operator porownania dwoch slownikow
	/*friend bool operator ==(MultiSlownik<KeyType, ValueType>& slownik1, MultiSlownik<KeyType, ValueType>& slownik2)
	{
		if (slownik1.size == slownik2.size)
		{

		}
	}*/

	/*!
	 * zwraca referencje na wartosc dla podanego klucza
	 * jezeli elementu nie ma w slowniku, dodaje go
	 */
	value_type& operator[](const key_type& key)
	{
		splay(root, key);
		if (root->key != key)
		{
			value_type value;
			insert(key, value);
		}
		return root->value;
	}

private:
	mutable Node<key_type, value_type>* root;
	int elements;


	void splay(Node<KeyType, ValueType>*& root, key_type key) const
	{
		if (root)
		{
			if (key > root->key)
			{
				if (root->right)
				{
					if (key > root->right->key)
					{
						if (root->right->right)
						{
							splay(root->right->right, key);
							rotLL(root);
						}
						else
						{
							rotL(root);
						}
					}
					else if (key < root->right->key)
					{
						if (root->right->left)
						{
							splay(root->right->left, key);
							rotRL(root);
						}
						else
						{
							rotL(root);
						}
					}
					else
					{
						rotL(root);
					}
				}
			}
			else if (key < root->key)
			{
				if (root->left)
				{
					if (key < root->left->key)
					{
						if (root->left->left)
						{
							splay(root->left->left, key);
							rotRR(root);
						}
						else
						{
							rotR(root);
						}
					}
					else if (key > root->left->key)
					{
						if (root->left->right)
						{
							splay(root->left->right, key);
							rotLR(root);
						}
					}
					else
					{
						rotR(root);
					}
				}
			}
		}
	}

	void rightRotate(Node<KeyType, ValueType>*& node) const
	{
		Node<KeyType, ValueType>* p;
		Node<KeyType, ValueType>* q;
		p = node;
		q = p->left;
		p->left = q->right;
		q->right = p;
		node = q;
	}

	void leftRotate(Node<KeyType, ValueType>*& node) const
	{
		Node<KeyType, ValueType>* p;
		Node<KeyType, ValueType>* q;
		p = node;
		q = p->right;
		p->right = q->left;
		q->left = p;
		node = q;
	}
	void rotL(Node<KeyType, ValueType>*& node) const
	{
		leftRotate(node);
	}
	void rotLL(Node<KeyType, ValueType>*& node) const
	{
		leftRotate(node);
		leftRotate(node);
	}
	void rotLR(Node<KeyType, ValueType>*& node) const
	{
		leftRotate(node->left);
		rightRotate(node);
	}
	void rotR(Node<KeyType, ValueType>*& node) const
	{
		rightRotate(node);
	}
	void rotRR(Node<KeyType, ValueType>*& node) const
	{
		rightRotate(node);
		rightRotate(node);
	}
	void rotRL(Node<KeyType, ValueType>*& node) const
	{
		rightRotate(node->right);
		leftRotate(node);
	}

	//funkcja usuwajaca wexel wraz z dziecmi

	void destroy(Node<KeyType,ValueType >*& root)
	{
		if (root)
		{
			if (root->left)
			{
				destroy(root->left); //usuwamy lewe dziecko
			}
			if (root->right)
			{
				destroy(root->right);	//usuwamy prawe dziecko
			}
			delete root;
		}
	}

};

#include "test.h"
#include "histogram.h"

int main()
{


    test_int();
    test_hist();
    return 0;
}
