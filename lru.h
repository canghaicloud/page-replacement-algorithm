#ifndef LRU_H
#define LRU_H

#endif // LRU_H
#pragma once
#include<iostream>
#include<stdlib.h>
#include<memory.h>
#include<sstream>
using namespace std;

struct memory_1 {
    int pagenumber;
    int access_time;
};
typedef memory_1 MEMORYA;
MEMORYA* MEMORYATable;

int selectMax(MEMORYA* b, int memory_size) {
    int tag = 0;
    int max = -1;
    for (int k = 0; k < memory_size; k++) {
        if (b[k].access_time > max) {
            max = b[k].access_time;
            tag = k;
        }
    }
    return tag;
}

//寻找页面在内存中的编号，未找到返回-1
int PositionOfMemory(MEMORYA* b, int NO, int memory_size) {
    for (int i = 0; i < memory_size; i++) {
        if (b[i].pagenumber == NO) {
            return i;
        }
    }
    return -1;
}
string lru(int memorysize, int random_size, int* random) {
    MEMORYATable = (MEMORYA*)malloc(sizeof(MEMORYA) * memorysize);
    int page_fault_time = 0;
    stringstream ss;
    for (int i = 0; i < memorysize; i++) {
        MEMORYATable[i].pagenumber = -1;
        MEMORYATable[i].access_time = random_size - i - 1;
    }
    int value;
    int k, l;
    for (int i = 0; i < random_size; i++) {
        value = PositionOfMemory(MEMORYATable, random[i], memorysize);
        if (value >= 0) {//在内存中则更新时间戳
            //ss << "No page missing occurred on page" << random[i] << endl;
            ss << "页 " << random[i] << " 没有发生缺页" << endl;
            MEMORYATable[value].access_time = 0;
            for (k = 0; k < memorysize; k++)
                if (k != value)
                    MEMORYATable[k].access_time++;
        }
        else {
            page_fault_time++;
            value = selectMax(MEMORYATable, memorysize);//选择最近最久未使用页面
            //ss << "Page " << random[i] << " is missing, replace page " << MEMORYATable[value].pagenumber << endl;
            ss << "页 " << random[i] << " 发生缺页,替换页 "<<MEMORYATable[value].pagenumber << endl;
            MEMORYATable[value].pagenumber = random[i];
            MEMORYATable[value].access_time = 0;
            for (l = 0; l < memorysize; l++)//更新其他页面时间戳
                if (l != value)
                    MEMORYATable[l].access_time++;
        }
    }
    ss << "缺页次数为:" << page_fault_time << endl;
    ss << "缺页率为：:" << (double)page_fault_time / random_size * 100 << "%" << endl;
    free(MEMORYATable);
    return ss.str();
}
