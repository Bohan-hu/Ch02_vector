//
// Created by 胡博涵 on 2018/1/23.
//

#ifndef CH02_VECTOR_MYVECTOR_H
#define CH02_VECTOR_MYVECTOR_H
#define DEFAULT_CAPACITY 3
typedef int Rank;

template <typename T>
class Vector {
protected:
    Rank _size;//规模
    int _capacity;//容量
    T *_elem;//数据区域指针

    void copyFrom(T const *A, Rank lo, Rank hi);//复制区间函数[lo,hi)
    void expand();//自动扩容函数
    void shrink();//空间利用率（装填因子）过低时自动收缩
    bool bubble(Rank lo, Rank hi);//?????为什么时bool？？？？冒泡排序（对某区间）
    void bubblesort(Rank lo, Rank hi);//冒泡排序
    Rank max(Rank lo, Rank hi);//找到最大值，返回其下标
    void selectionsort(Rank lo, Rank hi);//选择排序算法
    void merge(Rank lo, Rank hi);//归并算法
    void mergesort(Rank lo, Rank hi);//归并排序算法
    Rank partition(Rank lo, Rank hi);//轴点构造算法
    void quickSort(Rank lo, Rank hi);//快速排序算法
    void heapSort(Rank lo, Rank hi);//归并排序算法

public:
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

    T remove(Rank r);//删除下标为r的元素
    int remove(Rank lo, Rank hi);//删除区间内的元素
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

template <typename T>
void _swap(T &a,T &b){ T c; c=a; a=b; b=c;}

#endif //CH02_VECTOR_MYVECTOR_H
