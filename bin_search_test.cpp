/*
 * =====================================================================================
 *
 *       Filename:  bin_search_test.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/11/2016 04:22:44 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  seth.hg@gmail.com
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <vector>

using namespace std;

enum CMP_RES_T {
    EQ          =   0,
    MOVE_LEFT   =   -1,
    MOVE_RIGHT  =   1,
};

CMP_RES_T cmp_int(const int& dst, const int& src)
{
    if (src < dst)
    {
        return MOVE_LEFT;
    }

    if (src > dst)
    {
        return MOVE_RIGHT;
    }

    return EQ;
}

// 二分查找算法，返回数组中不小于val的第一个元素的下标
template<typename T1, typename T2>
int bin_search(std::vector<T1> array, const T2& val, CMP_RES_T (*cmp_func)(const T1&, const T2&))
{
    int left = 0, right = array.size() - 1;
    int mid;
    CMP_RES_T res;

    while (true)
    {
        if (left > right)
        {
            // 如果数组中没有等于val的值，则返回右侧的下标，
            // 即数组中>val的最小元素
            return left % array.size();
        }
        mid = (left + right) / 2;
        res = cmp_func(array[mid], val);
        if (res == EQ)
        {
            return mid;
        }
        if (MOVE_LEFT == res)
        {
            right = mid - 1;
        }
        else if (MOVE_RIGHT == res)
        {
            left = mid + 1;
        }
    }
}

int main()
{
    vector<int> array;
    int val = 0;
    for (int i = 0; i < 1000; i++)
    {
        val += (random() % 10) + 1;
        array.push_back(val);
    }

    int idx;
    for (int i = 0; i < 100000; i++)
    {
        int r = random() % val;
        idx = bin_search(array, r, cmp_int);
        //cout << "r = " << r << ", idx = " << idx << ", array[idx] = " << array[idx] << " array[idx+1] = " << array[idx+1] << endl;
        printf("r = %d, array[%d] = %d, array[%d] = %d\n", r, idx, array[idx], idx+1, array[idx+1]);
        assert(array[idx] >= r);
        if (idx)
            assert(array[idx-1] < r);
    }

    idx = bin_search(array, val + 1, cmp_int);
    cout << idx << endl;
    assert(idx == 0);
    //assert(idx == array.size() - 1);
    idx = bin_search(array, 0, cmp_int);
    cout << idx << endl;
    assert(idx == 0);
    //assert(idx <= 0);

    return 0;
}
