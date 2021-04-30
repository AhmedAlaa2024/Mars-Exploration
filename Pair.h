//-------Doaa
#pragma once

template <typename T, typename F>
class Pair
{
	T item;
	F Priority;
public:
	Pair() {};
	Pair(T i, F p);
	T getItem();
	F getPriority();
	void setItem(T i);
	void setPriority(F p);
	~Pair() {}

};



template <typename T, typename F>
Pair<T,F>::Pair(T i, F p)
{
	setItem(i);
	setPriority(p);
}

template <typename T, typename F>
T Pair<T, F>::getItem()
{
	return item;
}

template <typename T, typename F>
F Pair<T, F>::getPriority()
{
	return Priority;
}


template <typename T, typename F>
void Pair<T, F>::setItem(T i)
{
	item = i;
}

template <typename T, typename F>
void Pair<T, F>::setPriority(F p)
{
	Priority = p;
}
