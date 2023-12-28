#include <unordered_map>
#include <list>
#include <string>

using namespace std;

class LFUCache {
public:
    LFUCache(int capacity) : capacity(capacity), pageFaults(0), accesses(0) {
    }

    // 访问页面的函数
    string accessPage(int page) {
        accesses++;
        if (pageTable.find(page) != pageTable.end()) {
            // 页面命中
            updatePage(page);
            return "页 " + to_string(page) + " 没有发生缺页";
        } else {
            // 页面缺失
            pageFaults++;
            if (cache.size() >= capacity) {
                evictPage();
            }
            insertPage(page);
            return "页 " + to_string(page) + " 发生缺页，替换页 " + to_string(evictedPage);
        }
    }

    // 获取缺页次数
    int getPageFaults() const {
        return pageFaults;
    }

    // 获取总访问次数
    int getAccesses() const {
        return accesses;
    }

private:
    int capacity;
    int pageFaults;  // 缺页次数
    int accesses;    // 总访问次数
    list<int> cache;  // 维护页面顺序的链表
    unordered_map<int, pair<int, list<int>::iterator>> pageTable;  // 存储页面信息（频率和在链表中的迭代器）
    unordered_map<int, int> frequencyTable;  // 存储页面频率
    int evictedPage = -1;  // 在替换期间存储被替换的页面

    // 更新页面信息
    void updatePage(int page) {
        // 更新频率
        frequencyTable[page]++;
        // 将页面移到链表前端
        cache.erase(pageTable[page].second);
        cache.push_front(page);
        // 更新pageTable中的迭代器
        pageTable[page].second = cache.begin();
    }

    // 插入新页面
    void insertPage(int page) {
        // 将页面插入链表前端
        cache.push_front(page);
        // 更新pageTable中的迭代器
        pageTable[page] = {1, cache.begin()};
        // 更新频率
        frequencyTable[page] = 1;
    }

    // 替换页面
    void evictPage() {
        // 寻找频率最小的页面
        int minFrequency = INT_MAX;
        for (const auto& entry : frequencyTable) {
            if (entry.second < minFrequency) {
                minFrequency = entry.second;
                evictedPage = entry.first;
            }
        }
        // 从cache和pageTable中删除页面
        cache.erase(pageTable[evictedPage].second);
        pageTable.erase(evictedPage);
        frequencyTable.erase(evictedPage);
    }
};

// LFU算法的主函数
string lfu(int memorysize, int random_size, int* random) {
    LFUCache lfuCache(memorysize);
    string lfu_result;

    for (int i = 0; i < random_size; ++i) {
        lfu_result += lfuCache.accessPage(random[i]) + "\n";
    }

    // 计算缺页率
    int pageFaults = lfuCache.getPageFaults();
    int accesses = lfuCache.getAccesses();
    double pageFaultRate = static_cast<double>(pageFaults) / accesses * 100;

    lfu_result += "缺页次数:" + to_string(pageFaults) + "\n";
    lfu_result += "缺页率:" + to_string(pageFaultRate) + "%\n";

    return lfu_result;
}
