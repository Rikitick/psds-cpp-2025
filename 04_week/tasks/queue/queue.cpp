#include <algorithm>
#include <initializer_list>
#include <vector>
#include <stack>


class Queue {
public:
    Queue();
    Queue(std::stack<int> st);
    Queue(std::vector<int> vec);
    Queue(std::initializer_list<int> list);
    Queue(int n);

    size_t Size() const;
    bool Empty() const;
    void Push(int val);
    bool Pop();
    int& Front();
    const int& Front() const;
    int& Back();
    const int& Back() const;
    void Clear();
    void Swap(Queue& other);

    friend bool operator==(const Queue& a, const Queue& b);
    friend bool operator!=(const Queue& a, const Queue& b);

private:
    mutable std::vector<int> in;
    mutable std::vector<int> out;

    void prepareOut() const {
        if (out.empty()) {
            while (!in.empty()) {
                out.push_back(in.back());
                in.pop_back();
            }
        }
    }

    void prepareIn() const {
        if (in.empty()) {
            while (!out.empty()) {
                in.push_back(out.back());
                out.pop_back();
            }
        }
    }
};

Queue::Queue() = default;

Queue::Queue(std::stack<int> st) {
    while (!st.empty()) {
        this->Push(st.top());
        st.pop();
    }
    std::reverse(in.begin(), in.end());
}

Queue::Queue(std::vector<int> vec) {
    in.reserve(vec.size());
    out.reserve(vec.size());
    in = vec;
}

Queue::Queue(std::initializer_list<int> list) {
    in.reserve(list.size());
    out.reserve(list.size());
    in = list;
}

Queue::Queue(int n) {
    in.reserve(n);
    out.reserve(n);
}

size_t Queue::Size() const {
    return in.size() + out.size();
}

bool Queue::Empty() const {
    return in.empty() && out.empty();
}

void Queue::Push(int val) {
    in.push_back(val);
}

bool Queue::Pop() {
    prepareOut();
    if (out.empty())
        return false;
    out.pop_back();
    return true;
}

int& Queue::Front() {
    prepareOut();
    return out.back();
}

const int& Queue::Front() const {
    prepareOut();
    return out.back();
}

int& Queue::Back() {
    prepareIn();
    return in.back();
}

const int& Queue::Back() const {
    prepareIn();
    return in.back();
}

void Queue::Clear() {
    if (!in.empty())
        in.clear();
    if (!out.empty())
        out.clear();
}

void Queue::Swap(Queue& other) {
    std::swap(in, other.in);
    std::swap(out, other.out);
}

bool operator==(const Queue& a, const Queue& b) {
    if ((a.in.size() + a.out.size()) != (b.in.size() + b.out.size()))
        return false;

    auto get_val = [](const Queue& q, size_t index) {
        if (index < q.out.size())
            return q.out[q.out.size() - 1 - index];
        return q.in[index - q.out.size()];
    };

    size_t total_size = a.in.size() + a.out.size();
    for (size_t i = 0; i < total_size; ++i)
        if (get_val(a, i) != get_val(b, i))
            return false;

    return true;
}

bool operator!=(const Queue& a, const Queue& b) {
    return !(a == b);
}