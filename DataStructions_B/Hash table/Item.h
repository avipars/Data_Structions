
#pragma once
#include<iostream>
using namespace std;


enum state { empty, full, deleted };

template <typename T, typename K>
class Item
{
public:
	T data;
	K key;
	state flag = state::empty;
	Item() {}
	Item(T d, K k, state f = state::empty) { data = d; key = k; flag = f; }
	Item(T d, state f = state::empty) { data = d; flag = f; }
};