#ifndef HEAPSORT
#define HEAPSORT
typedef unsigned int Size; 
#include <vector>
#include <algorithm>  
#include <iostream>
template <typename T>
inline void Swap(T& m, T& n) { 
    T temp = m;
    m = n;
    n = temp;
}//重写一次swap ， 来提高效率；


template <typename T>
void Heapify(std::vector<T>& vec, Size n, Size Mubiao) {
    Size largest = Mubiao;     //Mubiao为最大   
    Size left = Mubiao * 2 + 1; // 左子节点设置
    Size right = Mubiao * 2 + 2;// 右子节点设置
    //如果左子节点大于最大节点，则将largest换为左节点
    if (left < n && vec[left] > vec[largest]) {
        largest = left;
    }
    //同理可设定右节点
    if (right < n && vec[right] > vec[largest]) {
        largest = right;
    }
    //如果largest不是Mubiao，则交换二者，并且递归
    if (largest != Mubiao) {
        Swap(vec[Mubiao], vec[largest]);
        Heapify(vec, n, largest); 
    }
}


template <typename T>
void HeapSort(std::vector<T>& vec) {
    Size n = vec.size();
    for (int i = n/2-1; i>=0; --i) {  
        Heapify(vec, n, i);
    }
    for (Size i = n - 1; i > 0; --i) {
        Swap(vec[0], vec[i]);  
        Heapify(vec, i, 0);  //重新调整       
    }
}

#endif // HEAPSORT