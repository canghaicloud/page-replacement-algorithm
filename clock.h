#ifndef CLOCK_H
#define CLOCK_H

#endif // CLOCK_H

#include <vector>
#include <string>
#include <sstream>

std::string clock(int memorysize, int random_size, int* random) {
    std::vector<int> memory(memorysize, -1);
    std::vector<bool> reference(memorysize, false);
    int pointer = 0;
    int page_faults = 0;
    std::ostringstream output;

    for (int i = 0; i < random_size; ++i) {
        int page = random[i];
        auto it = std::find(memory.begin(), memory.end(), page);

        if (it != memory.end()) {
            output << "页 " << page << " 没有发生缺页\n";
            reference[std::distance(memory.begin(), it)] = true;
        } else {
            while (reference[pointer]) {
                reference[pointer] = false;
                pointer = (pointer + 1) % memorysize;
            }

            if (memory[pointer] != -1) {
                output << "页 " << page << " 发生缺页，替换页 " << memory[pointer] << "\n";
            } else {
                output << "页 " << page << " 发生缺页，替换页 -1\n";
            }

            memory[pointer] = page;
            reference[pointer] = true;
            pointer = (pointer + 1) % memorysize;
            ++page_faults;
        }
    }

    double page_fault_rate = static_cast<double>(page_faults) / random_size;
    output << "缺页次数:" << page_faults << "\n";
    output << "缺页率:" << page_fault_rate*100 << "%" << "\n";

    return output.str();
}
