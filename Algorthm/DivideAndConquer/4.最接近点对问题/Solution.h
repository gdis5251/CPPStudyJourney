#pragma once 
#include <iostream>
#include <vector>

struct point {
    double _x;
    double _y;

    point(int x = 0, int y = 0)
    : _x(x),
    _y(y)
    {} 
};

class Solution {
public:
    Solution()
        :_point(nullptr)
    {}
    
    void CreateVec(std::vector<point*>& v) {
        //先输入共有多少个点，并将点由vector组织起来
        int n = 0;
        std::cin >> n;

        for (int i = 0; i < n; i++) {
            _point = new point();
            std::cin >> _point->_x >> _point->_y;

            v.push_back(_point);
        }
    }

    void BubbleSort(std::vector<point*>& v) {
        int flag = 0;

        for (int i = 0; i < (int)v.size(); i++) {
        
            flag = 0;
            for (int j = 0; j < (int)v.size() - i - 1; j++) {
                if (v[j]->_x > v[j + 1]->_x) {
                    std::swap(v[j], v[j + 1]);
                    flag = 1;
                }
            }
            if (flag == 0)
                break;
        }
    }

private:
    point *_point;
};
