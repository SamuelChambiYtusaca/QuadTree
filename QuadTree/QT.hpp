#pragma once
#include "Nodo.hpp"
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <fstream>
template <typename T = int>
class QT
{
private:
    Nodo<T> *root = nullptr;

public:
    QT();
    void insert(int _x, int _y, T value);
    bool coord_eq(int x_1, int y_1, int x_2, int y_2);
    void search(int a_x, int a_y, int b_x, int b_y)
    {
        search(root, a_x, a_y, b_x, b_y);
    }
    void search(Nodo<T> *S, int a_x, int a_y, int b_x, int b_y);
    std::string QT_Compare(Nodo<T> *p, Nodo<T> *r);
    void graph_node(std::ofstream &f, Nodo<T> *r, int &n);
    void graph(std::string arch);
    ~QT();
};

template <typename T>
QT<T>::QT()
{
}

template <typename T>
void QT<T>::insert(int _x, int _y, T value)
{
    Nodo<T> *nuevo = new Nodo<T>(_x, _y, value);
    Nodo<T> *padre;
    if (!root)
        root = nuevo;
    else
    {
        Nodo<T> *tmp = root;
        std::string Q;
        while (tmp && (tmp->x != nuevo->x && tmp->y != nuevo->y))
        {
            padre = tmp;
            Q = QT_Compare(nuevo, tmp);
            if (Q == "NE")
                tmp = tmp->NE;
            else if (Q == "NW")
                tmp = tmp->NW;
            else if (Q == "SE")
                tmp = tmp->SE;
            else
                tmp = tmp->SW;
        }
        if (!tmp)
        {
            if (Q == "NE")
                padre->NE = nuevo;
            else if (Q == "NW")
                padre->NW = nuevo;
            else if (Q == "SE")
                padre->SE = nuevo;
            else
                padre->SW = nuevo;
        }
        else    
            tmp->value = value;
    }
    //std::cerr << "Elmento insertado\n";
}

template <typename T>
void QT<T>::search(Nodo<T> *S, int a_x, int a_y, int b_x, int b_y)
{
    if (!S)
        return;
    if (a_x <= S->x && S->x <= b_x && b_y <= S->y && S->y <= a_y)
    {
        std::cout << "Punto encontrado: " << S->get_val() << '\n';
        printf("x: %d, y: %d\n", S->x, S->y);
    }
    /*Limites*/
    if (a_x <= S->x && S->y <= a_y)
    {
        search(S->NW, a_x, a_y, b_x, b_y);
        if (b_y <= S->y)
            search(S->SW, a_x, a_y, b_x, b_y);
    }
    else if (a_x <= S->x && a_y <= S->y)
    {
        search(S->SW, a_x, a_y, b_x, b_y);
    }
    if (S->x <= b_x && b_y <= S->y)
    {
        search(S->SE, a_x, a_y, b_x, b_y);
        if (S->y <= a_y)
            search(S->NE, a_x, a_y, b_x, b_y);
    }
    else if (S->x <= b_x && S->y <= b_y)
    {
        search(S->NE, a_x, a_y, b_x, b_y);
    }
}

template <typename T>
bool QT<T>::coord_eq(int x_1, int y_1, int x_2, int y_2)
{
    return (x_1 == x_2 && y_1 == y_2);
}

template <typename T>
std::string QT<T>::QT_Compare(Nodo<T> *P, Nodo<T> *R)
{
    if (P->x < R->x)
    {
        return P->y < R->y ? "SW" : "NW";
    }
    else if (P->y < R->y)
    {
        return "SE";
    }
    else
        return "NW";
}

template <typename T>
void QT<T>::graph(std::string arch)
{
    int null_n = 1;
    std::ofstream f(arch);
    f << "graph T{\n";
    graph_node(f, root, null_n);
    f << "}";
    f.close();

    std::stringstream dir1(arch);
    std::string name, ext, aux;
    std::getline(dir1, aux, '.');
    name = aux;
    std::getline(dir1, aux, '.');
    ext = aux;
    system(&(("dot " + arch + " -o " + name + ".png -Tpng")[0]));
    system(&((name + ".png")[0]));
}

template <typename T>
void QT<T>::graph_node(std::ofstream &f, Nodo<T> *N, int &null_n)
{
    if (!N)
        return;
    f << N->value << ";\n";
    if (N->NW)
    {
        f << N->value << " -- " << N->NW->value << ";\n";
        graph_node(f, N->NW, null_n);
    }
    else{
        f << N->value << " -- NW_" + std::to_string(null_n++) << ";\n";
    }
    if (N->NE)
    {
        f << N->value << " -- " << N->NE->value << ";\n";
        graph_node(f, N->NE, null_n);
    }
    else
        f << N->value << " -- NE_" + std::to_string(null_n++) << ";\n";
    if (N->SW)
    {
        f << N->value << " -- " << N->SW->value << ";\n";
        graph_node(f, N->SW, null_n);
    }
    else
        f << N->value << " -- SW_" + std::to_string(null_n++) << ";\n";
    if (N->SE)
    {
        f << N->value << " -- " << N->SE->value << ";\n";
        graph_node(f, N->SE, null_n);
    }
    else
        f << N->value << " -- SE_" + std::to_string(null_n++) << ";\n";
}

template <typename T>
QT<T>::~QT()
{
}
