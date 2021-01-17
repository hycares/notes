#include <unordered_map>
#include <utility>

using namespace std;

// 实现双链表
struct DNode {
    DNode* prev;
    DNode* next;
    int key;
    int val;

    DNode() : prev(nullptr), next(nullptr), key(0), val(0) {}
    DNode(DNode *p, DNode *n, int k, int v) : prev(p), next(n), key(k), val(v) {}
    DNode(int k, int v) : DNode() {
        this->key = k;
        this->val = v;
    }
};

// 双向链表技巧，维护一个头指针和尾指针，这样就不必判断是否为空

class LRUCache {
private:
    unordered_map<int, DNode *> hashtable;
    DNode *head;
    DNode *tail;
    int caps;
public:
    LRUCache(int capacity) {
        caps = capacity;
        head = new DNode();
        tail = new DNode();
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        auto hit = hashtable.find(key);
        if (hit != hashtable.end()) {
            toFront(hit->second);
            return hit->second->val;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if (get(key) != -1) {
            head->next->val = value;
        }
        else {
            DNode *node = new DNode(key, value);
            hashtable[key] = node;
            toFront(node);
            if (hashtable.size() > caps) {
                auto p = tail->prev;
                p->prev->next = p->next;
                p->next->prev = p->prev;
                hashtable.erase(p->key);
                delete p;
            }
        }
    }

    void toFront(DNode *p) {
        if (p->prev) p->prev->next = p->next;
        if (p->next) p->next->prev = p->prev;
        p->next = head->next;
        head->next->prev = p;
        head->next = p;
        p->prev = head;
    }
};