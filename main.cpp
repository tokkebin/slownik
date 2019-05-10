#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <cstddef>


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

template<typename KeyType, typename ValueType>class MultiSlownik
{
public:

	//using key_type = KeyType;
	//using value_type = ValueType;
	MultiSlownik()
	{
		//kontruktor trywialny
		root = NULL;
		elements = 0;
	}
	~MultiSlownik()
	{
		//destruktor trywialny
		destroy(root);

	}

	void insert(KeyType key, ValueType value)
	{

		if (!root)
		{
			root = new Node<KeyType, ValueType>;
			root->left = NULL;
			root->right = NULL;
			root->key = key;
			root->value = value;
		}
		else
		{
			splay(root, key);
			if (root->key > key)
			{
				Node<KeyType, ValueType>* node = new Node<KeyType, ValueType>;
				node->right = root;
				node->left = root->left;
				root->left = NULL;
				node->key = key;
				node->value = value;
				root = node;
			}
			else if (root->key < key)
			{
				Node<KeyType, ValueType>* node = new  Node<KeyType, ValueType>;
				node->left = root;
				node->right = root->right;
				root->right = NULL;
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
	void delete_node(KeyType key, ValueType value)
	{
		if (!(root->key == key))
		{
			splay(root, key);
			if (root->key == key)
			{
				if (root->value != value)
					cout << "Nie istnieje element o zadanym kluczu i wartosci" << endl;
				Node<KeyType, ValueType>* tempL;
				Node<KeyType, ValueType>* tempR;

				tempL = root->left;
				tempR = root->right;
				delete root;
				elements--;
				root = NULL;
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
	void display(Node<KeyType, ValueType>*& root)
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

	Node<KeyType,ValueType> showroot(Node<KeyType,ValueType>* root)
	{
	    return this->root;
	}

    bool compare_nodes(Node<KeyType,ValueType>* root1, Node<KeyType,ValueType>* root2)
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
	ValueType& value(KeyType key) const
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

	void change_value(const KeyType& key, const ValueType& new_value)
	{
		//value_type& temp = value(key);

	}

	/*!
	 * zwraca informacje, czy istnieje w slowniku podany klucz
	 */
	bool contains(KeyType key)
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
        os<<"Wielkosc slownika: "<<slownik.size()<<endl;
        slownik.show();
        return os;
	}
	//operator porownania dwoch slownikow
	friend bool operator ==(MultiSlownik<KeyType, ValueType>& slownik1, MultiSlownik<KeyType, ValueType>& slownik2)
	{
		return slownik1.compare_dict(slownik1,slownik2);
	}

	/*!
	 * zwraca referencje na wartosc dla podanego klucza
	 * jezeli elementu nie ma w slowniku, dodaje go
	 */
	ValueType& operator[](const KeyType& key)
	{
		splay(root, key);
		if (root->key != key)
		{
			ValueType value;
			insert(key, value);
		}
		return root->value;
	}

private:
	mutable Node<KeyType,ValueType>* root;
	int elements;


	void splay(Node<KeyType, ValueType>*& root, KeyType key) const
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
