#include <iostream>
#include <vector>
#include <iomanip> // 用于格式化输出
#include <algorithm>
#include <random>
#include <chrono>
#include "HeapSort.h" 

// 检查排序是否正确
template <typename T>
bool check(const std::vector<T>& vec) {
    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i - 1] > vec[i]) {
            return false; // 如果前一个元素大于后一个元素，则排序不正确
        }
    }
    return true;
}

// 生成随机序列
std::vector<int> generate_random_sequence(size_t length) {
    std::vector<int> vec(length);
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 1'000'000);
    for (auto& val : vec) {
        val = dist(rng);
    }
    return vec;
}

// 生成有序序列
std::vector<int> generate_sorted_sequence(size_t length) {
    std::vector<int> vec(length);
    for (size_t i = 0; i < length; ++i) {
        vec[i] = i;
    }
    return vec;
}

// 生成逆序序列
std::vector<int> generate_reverse_sequence(size_t length) {
    std::vector<int> vec(length);
    for (size_t i = 0; i < length; ++i) {
        vec[i] = length - i;
    }
    return vec;
}

// 生成部分重复序列
std::vector<int> generate_repeated_sequence(size_t length) {
    std::vector<int> vec(length);
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 100); 
    for (auto& val : vec) {
        val = dist(rng);
    }
    return vec;
}

// 测试排序
void test_sorting() {
    const size_t length = 1'000'000; // 测试序列长度

    // 测试不同类型的序列
    std::vector<std::vector<int>> test_cases = {
        generate_random_sequence(length),
        generate_sorted_sequence(length),
        generate_reverse_sequence(length),
        generate_repeated_sequence(length)
    };

    const char* test_names[] = {"随机序列", "有序序列", "逆序序列", "部分重复序列"};
    std::vector<int> heap_sort_times;
    std::vector<int> std_sort_heap_times;

    std::cout << std::left << std::setw(15) << "序列类型" 
              << std::setw(20) << "堆排序时间(ms)" 
              << std::setw(25) << "std::sort_heap时间(ms)" 
              << "性能差异(%)" << std::endl;

    for (size_t i = 0; i < test_cases.size(); ++i) {
        auto vec1 = test_cases[i];
        auto start = std::chrono::high_resolution_clock::now();
        HeapSort(vec1);
        auto end = std::chrono::high_resolution_clock::now();
        auto heap_sort_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        if (!check(vec1)) {
            std::cerr << "HeapSort failed for " << test_names[i] << std::endl;
            continue;
        }

        auto vec2 = test_cases[i];
        std::make_heap(vec2.begin(), vec2.end());
        start = std::chrono::high_resolution_clock::now();
        std::sort_heap(vec2.begin(), vec2.end());
        end = std::chrono::high_resolution_clock::now();
        auto std_sort_heap_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        if (!check(vec2)) {
            std::cerr << "std::sort_heap failed for " << test_names[i] << std::endl;
        }

        double performance_diff = 
            100.0 * (static_cast<double>(heap_sort_time - std_sort_heap_time) / std_sort_heap_time);

        // 存储时间结果
        heap_sort_times.push_back(heap_sort_time);
        std_sort_heap_times.push_back(std_sort_heap_time);

        // 输出结果行
        std::cout << std::left << std::setw(15) << test_names[i]
                  << std::setw(20) << heap_sort_time 
                  << std::setw(25) << std_sort_heap_time 
                  << std::fixed << std::setprecision(1) << performance_diff << "%" 
                  << std::endl;
    }
}

int main() {
    test_sorting();
    return 0;
}
