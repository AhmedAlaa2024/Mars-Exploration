//-------Doaa
#pragma once

template <typename T, typename F>
class Pair
{
	T item;
	F Priority;
public:
	Pair() {};
	Pair(const T& i, const F& p);
	T getItem();
	F getPriority();
	void setItem(const T& i);
	void setPriority(const F& p);
	~Pair() {}

};



template <typename T, typename F>
Pair<T,F>::Pair(const T& i, const F& p)
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
void Pair<T, F>::setItem(const T& i)
{
	item = i;
}

template <typename T, typename F>
void Pair<T, F>::setPriority(const F& p)
{
	Priority = p;
}
