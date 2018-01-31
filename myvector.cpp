//
// Created by 胡博涵 on 2018/1/23.
//


#include "myvector.h"
#include <cstdlib>
template<typename T>
//基于复制的向量构造方法
void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi) {
    _capacity = 2 * (hi - lo);//容量是2倍
    _elem = new T[_capacity];//为什么是2倍？为了尽量减少扩容打断运算
    _size = 0;//规模清零
    while (lo < hi)
        _elem[_size++] = A[lo++];//拷贝元素(size++把有效规模扩大）
}

//自动扩充
template<typename T>
void Vector<T>::expand() {
    if (_size < _capacity) return;
    T *oldelem = _elem;
    _capacity <<= 1;
    _elem = new T[_capacity];
    for (int i = 0; i < _size; i++)
        _elem[i] = oldelem[i];
    delete[]oldelem;//不释放内存会内存泄漏
}

//自动缩容
template<typename T>
void Vector<T>::shrink() {
    if (_size > (_capacity >> 2) )
        return;
    T *oldelem = _elem;
    _capacity >>= 1;
    _elem = new T[_capacity];
    for (int i = 0; i <= _size; i++)
        _elem[i] = oldelem[i];
    delete[]oldelem;
}

//重载下标访问运算符[]
template <typename T>
T &Vector<T>::operator[](Rank r) const {
    return _elem[r];
}

template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
    for(int i = _size;i>0;i--)
        _swap(_elem[i-1],_elem[rand()%i]);

}

template <typename T>
Rank Vector<T>::insert(Rank r, T const &e) {
    expand();
    for(int i=_size;i>r;i--)
        _elem[i]=_elem[i-1];
    _elem[r]=e;
    _size++;
    return r;
}

