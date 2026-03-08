#include <algorithm>
#include <cstddef>
#include <initializer_list>

template<typename T, std::size_t size>
class Array {
public:
    Array() : Array({}) {};
    Array(std::initializer_list<T> arr) {
        std::size_t i = 0;
        for (const auto& item : arr) {
            if (i < size) {
                data[i++] = item;
            }
        }
        for (; i < size; ++i) {
            data[i] = T();
        }
    }
    Array(const Array& other) {
        for (std::size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    Array(Array&& other) noexcept {
        for (std::size_t i = 0; i < size; ++i) {
            data[i] = std::move(other.data[i]);
        }
    }
    Array& operator=(const Array& other) {
        if (this != &other) {
            for (std::size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            for (std::size_t i = 0; i < size; ++i) {
                data[i] = std::move(other.data[i]);
            }
        }
        return *this;
    }
    ~Array() = default;
    T& operator[](std::size_t index) {
        return data[index];
    }
    const T& operator[](std::size_t index) const {
        return data[index];
    }

    T& Front() {
        return *begin();
    }
    const T& Front() const {
        return *cbegin();
    }
    T& Back() {
        return *(end() - 1);
    }
    const T& Back() const {
        return *(cend() - 1);
    }
    T* Data() {
        return data;
    }
    const T* Data() const {
        return data;
    }
    bool Empty() const {
        return size == 0;
    }
    std::size_t Size() const {
        return size;
    }
    void Swap(Array& other) {
        for (std::size_t i = 0; i < size; ++i) {
            std::swap(data[i], other.data[i]);
        }
    }
    void Fill(T&& value) {
        std::fill(begin(), end(), value);
    }
    T* begin() {
        return data;
    }
    const T* cbegin() const {
        return data;
    }
    T* end() {
        return data + size;
    }
    const T* cend() const {
        return data + size;
    }

    bool operator==(const Array& other) const {
        return std::equal(cbegin(), cend(), other.cbegin());
    }
    bool operator!=(const Array& other) const {
        return !(*this == other);
    }
    bool operator<(const Array& other) const {
        return std::lexicographical_compare(cbegin(), cend(), other.cbegin(), other.cend());
    }
    bool operator>(const Array& other) const {
        return other < *this;
    }
    bool operator<=(const Array& other) const {
        return *this == other || *this < other;
    }
    bool operator>=(const Array& other) const {
        return *this == other || *this > other;
    }

private:
    T data[size];
};


template<typename T, std::size_t size>
void swap(Array<T, size>& a, Array<T, size>& b) {
    a.Swap(b);
}

template<std::size_t index, typename T, std::size_t size>
T& get(Array<T, size>& arr) {
    return arr[index];
}

template<std::size_t index, typename T, std::size_t size>
T get(Array<T, size>&& arr) {
    return arr[index];
}

template <std::size_t index, typename T, std::size_t size>
const T& get(const Array<T, size>& arr) {
    return arr[index];
}