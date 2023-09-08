#pragma once
#include <vector>
#include "makeString.h"

template<typename Value>
struct Vertex {
	Vertex<Value>* nodes[256];
	bool isTerminal;
	Value value;

	~Vertex() {};
};

template<typename Key, typename Value>
class Trie
{
private:
	Vertex<Value>* root;
	Value& findKey(Key);
	void display(struct Vertex<Value>*, unsigned char, int);
public:
	Value& operator[](Key);
	int erase(Key);
	bool isKey(Key);
	void print();
	Trie();
	~Trie() {};
};

template<typename Key, typename Value>
Trie<Key, Value>::Trie()
{
	root = new Vertex<Value>();
}

template<typename Key, typename Value>
Value& Trie<Key, Value>::operator[](Key index)
{
	return this->findKey(index);
}

template<typename Key, typename Value>
inline Value& Trie<Key, Value>::findKey(Key key)
{
	std::string newKey = makeString(key);

	auto curNode = this->root;

	for (int i = 0; i < newKey.size(); ++i)
	{
		unsigned char index = static_cast<unsigned char>(newKey[i]);
		if (!curNode->nodes[index])
		{
			curNode->nodes[index] = new Vertex<Value>();
		}
		
		curNode = curNode->nodes[index];
	}

	curNode->isTerminal = true;
	//std::cout << newKey << " inserted\n";
	return curNode->value;
}

template<typename Key, typename Value>
inline void Trie<Key, Value>::display(struct Vertex<Value>* node,unsigned char symbol, int level)
{
	for (int i = 0; i < level; ++i)
		std::cout << "\t";
	if (node->isTerminal)
		std::cout << symbol << "(" << node->value << ")" << std::endl;
	else
		std::cout << symbol<<std::endl;
	for (int i = 0; i < 256; ++i)
	{
		unsigned char index = static_cast<unsigned char>(i);
		if (node->nodes[index])
			this->display(node->nodes[index], i, level + 1);
	}
}

/*
* 0 - key not found
* 1 - element erased successfully
*/
template<typename Key, typename Value>
inline int Trie<Key, Value>::erase(Key key)
{
	std::string newKey = makeString(key);

	auto curNode = this->root;

	for (int i = 0; i < newKey.size(); ++i)
	{
		unsigned char index = static_cast<unsigned char>(newKey[i]);
		if (!curNode->nodes[index])
		{
			return 0;
		}

		curNode = curNode->nodes[index];
	}

	if (curNode->isTerminal) {
		curNode->isTerminal = false;
		curNode->value = NULL;
		return 1;
	}
	else {
		return 0;
	}
}

template<typename Key, typename Value>
inline bool Trie<Key, Value>::isKey(Key key)
{
	std::string newKey = makeString(key);

	auto curNode = this->root;

	for (int i = 0; i < newKey.size(); ++i)
	{
		unsigned char index = static_cast<unsigned char>(newKey[i]);
		if (!curNode->nodes[index])
			return false;

		curNode = curNode->nodes[index];
	}

	return curNode->isTerminal;
}

template<typename Key, typename Value>
inline void Trie<Key, Value>::print()
{
	this->display(this->root, '\n', 0);
}
