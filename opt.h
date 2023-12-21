#ifndef OPT_H
#define OPT_H

#endif // OPT_H
#include<iostream>
#include<climits>
#include<cstdlib>
#include<sstream>
using namespace std;

struct memory {
    int pagenumber;
    int next_occurrence;
};

typedef memory MEMORY;

MEMORY* MEMORYTable;

int findOptimalPage(int* reference_string, int reference_length, MEMORY* b, int memory_size, int current_index) {
    int farthest_occurrence = INT_MIN;
    int replace_index = -1;

    for (int i = 0; i < memory_size; ++i) {
        int page = b[i].pagenumber;
        int next_occurrence = INT_MAX;

        for (int j = current_index + 1; j < reference_length; ++j) {
            if (reference_string[j] == page) {
                next_occurrence = j;
                break;
            }
        }

        if (next_occurrence > farthest_occurrence) {
            farthest_occurrence = next_occurrence;
            replace_index = i;
        }
    }

    return replace_index;
}

string opt(int memorysize, int reference_size, int* reference_string) {
    MEMORYTable = (MEMORY*)malloc(sizeof(MEMORY) * memorysize);
    int page_fault_time = 0;
    stringstream ss;

    for (int i = 0; i < memorysize; i++) {
        MEMORYTable[i].pagenumber = -1;
        MEMORYTable[i].next_occurrence = -1;
    }

    for (int i = 0; i < reference_size; i++) {
        int page_number = reference_string[i];
        int position = -1;

        for (int j = 0; j < memorysize; j++) {
            if (MEMORYTable[j].pagenumber == page_number) {
                position = j;
                break;
            }
        }

        if (position >= 0) {
            ss << "页 " << page_number << " 没有发生缺页" << endl;
            //ss << "No page missing occurred on page " << page_number << endl;
        }
        else {
            page_fault_time++;
            int replace_index = findOptimalPage(reference_string, reference_size, MEMORYTable, memorysize, i);

            if (replace_index != -1) {
                ss << "页 " << page_number << " 发生缺页，替换页 " << MEMORYTable[replace_index].pagenumber << endl;
                //ss << "Page " <<page_number << " is missing, replace page " << MEMORYTable[replace_index].pagenumber << endl;
                MEMORYTable[replace_index].pagenumber = page_number;
                MEMORYTable[replace_index].next_occurrence = -1;
            }
        }

        for (int j = 0; j < memorysize; j++) {
            if (MEMORYTable[j].pagenumber != -1) {
                MEMORYTable[j].next_occurrence = INT_MAX;

                for (int k = i + 1; k < reference_size; k++) {
                    if (reference_string[k] == MEMORYTable[j].pagenumber) {
                        MEMORYTable[j].next_occurrence = k;
                        break;
                    }
                }
            }
        }
    }

    ss << "缺页次数为:" << page_fault_time << endl;
    ss << "缺页率为:" << (double)page_fault_time / reference_size * 100 << "%" << endl;

    //ss << "The number of missing pages:" << page_fault_time;
    //ss << "Page absence rate:" << (double)page_fault_time / reference_size * 100 << "%" << endl;

    free(MEMORYTable);
    return ss.str();
}
