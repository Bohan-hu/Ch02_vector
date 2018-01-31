
//
// Created by 胡博涵 on 2018/1/23.
//
#include <iostream>
#include <cstdlib>
#include <iomanip>

#define DEFAULT_CAPACITY 3
typedef int Rank;

//数据结构声明区
template<typename T>
class Vector {
protected:
    Rank _size;//规模
    int _capacity;//容量
    T *_elem;//数据区域指针

    void copyFrom(T const *A, Rank lo, Rank hi);//复制区间函数[lo,hi)
    void expand();//自动扩容函数
    //void shrink();//空间利用率（装填因子）过低时自动收缩


    void selectionsort(Rank lo, Rank hi);//选择排序算法
    void merge(Rank lo, Rank hi);//归并算法
    void mergesort(Rank lo, Rank hi);//归并排序算法
    Rank partition(Rank lo, Rank hi);//轴点构造算法
    void quickSort(Rank lo, Rank hi);//快速排序算法
    void heapSort(Rank lo, Rank hi);//归并排序算法

public:
    Rank max(Rank lo, Rank hi);//找到最大值，返回其下标
    bool bubble(Rank lo, Rank hi);//?????为什么时bool？？？？冒泡排序（对某区间）
    void bubblesort(Rank lo, Rank hi);//冒泡排序
    //构造函数
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)//构造函数的实现
    {
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _size++)
            _elem[_size] = v;
    }

    Vector(T const *A, Rank n) { copyFrom(A, 0, n); }//区间复制
    Vector(T const *A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }//区间复制
    Vector(Vector<T> const &V) { copyFrom(V._elem, 0, V._size); }//向量整体复制
    Vector(Vector<T> const &V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); }//向量整体复制

    //析构函数
    ~Vector() { delete[]_elem; }

    //只读访问接口
    Rank size() const { return _size; }//
    bool empty() const { return !_size; }//判断是否为空
    int disordered() const;

    Rank find(T const &e) const { return find(e, 0, _size); }//无序向量整体查找
    Rank find(T const &e, Rank lo, Rank hi) const;//无序向量区间查找
    Rank search(T const &e) const //有序向量整体查找
    { return (0 >= _size) ? -1 : search(e, 0, _size); }//有结果返回rank，没有结果返回-1
    Rank search(T const &e, Rank lo, Rank hi) const;//有序向量区间查找

    T &operator[](Rank r) const;//重载下标运算符
    Vector<T> &operator=(Vector<T> const &);//重载赋值运算符

    //重载要引用的意义是可以作为左值

    int remove(Rank lo, Rank hi) {
        for (int i = hi; i < _size; i++)
            _elem[lo++] = _elem[i];
        _size = lo;
        std::cout << "Removing..." << std::endl;
        return hi - lo;
    }

    T remove(Rank r) {
        T tmp = _elem[r];
        remove(r, r + 1);
        return tmp;
    }

//删除下标为r的元素


//删除区间内的元素
    Rank insert(Rank r, T const &e);//插入元素

    void sort(Rank lo, Rank hi);//区间排序
    void sort() { sort(0, _size); }

    void unsort(Rank lo, Rank hi);//对区间置乱
    void unsort() { unsort(0, _size); }

    int deduplicate();//无序去重
    int uniquify();//有序去重

    //遍历
    void traverse(void(*)(T &));//函数指针
    template<typename FUCK>
    void traverse(FUCK &);
};

template<typename T>
void _swap(T &a, T &b) {
    T c;
    c = a;
    a = b;
    b = c;
}


//函数定义区
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
    //std::cout<<"Expanding..."<<std::endl;
    T *oldelem = _elem;
    _capacity <<= 1;
    _elem = new T[_capacity];
    for (int i = 0; i < _size; i++)        //log:之前的操作是非法的，往空向量非0位置插入元素
        _elem[i] = oldelem[i];
    delete[]oldelem;//不释放内存会内存泄漏
}

//自动缩容
/*template<typename T>
void Vector<T>::shrink() {
    if (_size > (_capacity >> 2))
        return;
    T *oldelem = _elem;
    _capacity >>= 1;
    _elem = new T[_capacity];
    for (int i = 0; i <= _size; i++)
        _elem[i] = oldelem[i];
    delete[]oldelem;
}*/

//重载下标访问运算符[]
template<typename T>
T &Vector<T>::operator[](Rank r) const {
    return _elem[r];
}


template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
    for (int i = _size; i > 0; i--)
        _swap(_elem[i - 1], _elem[rand() % i]);

}

template<typename T>
Rank Vector<T>::insert(Rank r, T const &e) {
    expand();
    for (int i = _size; i > r; i--)
        _elem[i] = _elem[i - 1];
    _elem[r] = e;
    _size++;
    return r;
}

template<typename T>
void print(Vector<T> E) {
    for (int i = 0; i < E.size(); i++) {
        std::cout << "[" << i << "]" << E[i] << "\t";
        if ((i + 1) % 5 == 0) std::cout << std::endl;
    }

    std::cout << std::endl;
}

template<typename T>
int Vector<T>::disordered() const {
    int ret = 0;
    for (int i = 1; i < _size; i++)
        if (_elem[i - 1] < _elem[i]) ret++;
    return ret;
}

template<typename T>
bool Vector<T>::bubble(Rank lo, Rank hi) {
    bool sorted = true;//假设这个序列已经被排序过，则就让调用者不再进行外层扫描
    for (int i = lo; i < hi - 1; i++)//hi是开区间，取不到
    {
        if (_elem[i] > _elem[i + 1]) {
            //基本操作
            _swap(_elem[i], _elem[i + 1]);
            //标记变量反转
            sorted = false;
        }
    }
    return sorted;
}

template<typename T>
void Vector<T>::bubblesort(Rank lo, Rank hi) {
    while (!bubble(lo, hi--));//bubble是内层扫描交换函数，传入的参数是扫描交换的范围，返回值是是否该范围是有序的，若是有序的，就终止外层的更新
}

template<typename T>
Rank Vector<T>::max(Rank lo, Rank hi) {
    int max = _elem[lo];
    int ret = lo;
    for (int i = lo; i < hi; i++) {
        if (max < _elem[i]) max = _elem[ret = i];
    }
    return ret;
}

template<typename T>
Rank Vector<T>::find(const T &e, Rank lo, Rank hi) const {
    while (lo < hi-- && e != _elem[hi]);//用while循环括号内的语句实现线性查找，并返回找到元素的最后的那个秩
    //如果没有找到，返回-1；
    return hi;
}

template<typename T>
Rank Vector<T>::search(const T &e, Rank lo, Rank hi) const {
    int mi;
    while (lo < hi - 1) {//一定要-1，要不然相差1的时候会是一个死循环
        mi = (hi + lo) >> 1;
        if (e < _elem[mi]) hi = mi;
        else lo = mi;
    }
    return lo;
}

template<typename T>
int Vector<T>::uniquify() {
    Rank cur = 0, r = 0;
    for (r = 0; r < _size; r++) {
        if (_elem[cur] != _elem[r])
            _elem[++cur] = _elem[r];
    }
    _size = ++cur;
    return r - _size;
}

template<typename T>
int Vector<T>::deduplicate() {
    /*for(Rank r=1;r<_size;r++){
        if(find(_elem[r],0,r)>=0)  remove(r);
    }*///有问题的代码：在remove之后下标继续加，导致元素的指向错误
    Rank r=1;
    while(r<_size)
        (find(_elem[r],0,r)<0)?r++:remove(r);
    return 0;
}

int main() {

    Vector<int> Vec(3, 0, 0);
    //std::cout << a << std::endl;
    //制造0-100随机数向量
    for (int i = 0; i < 100; i++)
        Vec.insert(i, i);
    std::cout << "size: " << Vec.size() << std::endl;
    Vec.unsort();
    print(Vec);
    std::cout << "max: " << Vec.max(0, Vec.size()) << std::endl;
    std::cout << "88: " << Vec.search(88, 0, Vec.size()) << std::endl;
    Vec.remove(20, 30);
    print(Vec);
    Vec.bubblesort(0, Vec.size());
    Vec.remove(89);
    print(Vec);

    std::cout << "max: " << Vec.max(0, Vec.size()) << std::endl;
    std::cout << "50: " << Vec.search(50, 0, Vec.size()) << std::endl;

    Vector<int> Vec2(3, 0, 0);
    for (int i = 0; i < 100; i++)
        Vec2.insert(i, i % 20);
    print(Vec2);
    Vec2.deduplicate();
    Vec2.bubblesort(0, Vec2.size());
    print(Vec2);
    Vec2.uniquify();
    print(Vec2);
    return 0;
}

