#pragma once
#include <string>
template <typename T>
class QT;

template <typename T = int>
class Nodo
{
private:
    T value;
    Nodo<T> *NW = nullptr;
    Nodo<T> *NE = nullptr;
    Nodo<T> *SW = nullptr;
    Nodo<T> *SE = nullptr;

public:
    int x;
    int y;

    Nodo(int x, int y, T value);
    T get_val() { return value; }
    ~Nodo();
    friend class QT<T>;
};

template <typename T>
Nodo<T>::Nodo(int _x, int _y, T _value) : x(_x), y(_y), value(_value)
{
}

template <typename T>
Nodo<T>::~Nodo()
{
}
