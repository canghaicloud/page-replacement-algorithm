#ifndef FIFO_H
#define FIFO_H

#endif
#pragma once
#include<iostream>
#include<stdlib.h>
#include<memory.h>
#include<sstream>
using namespace std;
struct page {
    int pagenumber;
    int memorynumber;
    int IsInmemory;
};
typedef page PAGE;
PAGE* PageTable;

string FIFO(int page_size, int requestsize, int memorysize, int* random)
{
    int* memory;
    memory = (int*)malloc(sizeof(int) * memorysize);
    PageTable = (PAGE*)malloc(sizeof(PAGE) * page_size);
    int i, j;
    for (i = 0; i < memorysize; i++)
        memory[i] = -1;
    for (i = 0; i < page_size; i++) {
        PageTable[i].IsInmemory = 0;
        PageTable[i].memorynumber = -1;
        PageTable[i].pagenumber = i;
    }
    int PageFalseTime = 0;
    int FirstIn = 0;
    int FullNumber = 0;
    int index = 0;
    stringstream ss;
    while (FullNumber != memorysize)
    {
        if (PageTable[random[index]].IsInmemory == 0) {
            ss << "页 " << random[index] << " 不在内存中" << endl;
            memory[FullNumber] = random[index];
            PageTable[random[index]].IsInmemory = 1;
            PageTable[random[index]].memorynumber = FullNumber;
            FullNumber++;
            index++;
            PageFalseTime++;
        }
        else if (PageTable[random[index]].IsInmemory == 1) {
            ss << "页 " << random[index] << " 在内存中" << endl;
            index++;
        }
    }
    int next_index = index;
    for (index = next_index; index < requestsize; index++)
    {
        if (PageTable[random[index]].IsInmemory == 1) {
            ss << "页 " << random[index] << " 在内存中" << endl;
        }
        else {
            PageFalseTime++;
            memory[FirstIn] = random[index];
            for (j = 0; j < requestsize; j++) {
                if (PageTable[j].memorynumber == FirstIn) {
                    ss << "页 " << random[index] << " 不在内存中," << "替换页 "<<j<<endl;
                    PageTable[j].memorynumber = -1;
                    PageTable[j].IsInmemory = 0;
                    break;
                }
            }
            PageTable[random[index]].IsInmemory = 1;
            PageTable[random[index]].memorynumber = FirstIn;
            FirstIn = (FirstIn + 1) % memorysize;
        }
    }
    ss << "缺页次数为:" << PageFalseTime << endl;
    ss << "缺页率为:" << (double)PageFalseTime / requestsize * 100 << "%" << endl;
    free(memory);
    free(PageTable);
    return ss.str();
}

