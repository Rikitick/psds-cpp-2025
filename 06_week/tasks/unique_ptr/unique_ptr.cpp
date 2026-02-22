#include <cstddef>
#include <string>


class UniquePtr {
public:
    // Конструкторы (объявления)
    UniquePtr();
    UniquePtr(std::string* str);
    UniquePtr(UniquePtr&& other) noexcept;
    ~UniquePtr();

    // Операторы (объявления)
    UniquePtr& operator=(UniquePtr&& other) noexcept;
    std::string& operator*();
    const std::string& operator*() const;
    explicit operator bool() const;
    std::string* operator->() const;

    // Методы (объявления)
    std::string* Get() const;
    std::string* Release();
    void Reset();
    void Reset(std::string* str);
    void Swap(UniquePtr& other);

private:
    std::string* data;
};

// Конструкторы (реализации)
UniquePtr::UniquePtr() : data(nullptr) {}
UniquePtr::UniquePtr(std::string* str) : data(str) {}
UniquePtr::UniquePtr(UniquePtr&& other) noexcept {
    data = other.data;
    other.data = nullptr;
}
UniquePtr::~UniquePtr() {
    if (data) {
        delete data;
    }
    data = nullptr;
}

// Операторы (реализации)
UniquePtr& UniquePtr::operator=(UniquePtr&& other) noexcept {
    if (this != &other) {
        UniquePtr::~UniquePtr();
        data = other.data;
        other.data = nullptr;
    }
    return *this;
}
std::string& UniquePtr::operator*() {
    return *data;
}
const std::string& UniquePtr::operator*() const {
   return *data;
}
UniquePtr::operator bool() const {
    return data != nullptr;
}
std::string* UniquePtr::operator->() const {
    return data;
}

// Методы (реализации)
std::string* UniquePtr::Get() const {
    return data;
}
std::string* UniquePtr::Release() {
    std::string* temp = data;
    data = nullptr;
    return temp;
}
void UniquePtr::Reset() {
    UniquePtr::~UniquePtr();
}
void UniquePtr::Reset(std::string* str) {
    UniquePtr::~UniquePtr();
    data = str;
}
void UniquePtr::Swap(UniquePtr& other) {
    std::swap(data, other.data);
}

// Доп методы 
UniquePtr MakeUnique(const std::string& str) {
    return UniquePtr(new std::string(str));
}
UniquePtr MakeUnique(std::string&& str) noexcept {
    return UniquePtr(new std::string(std::move(str)));
}
void Swap(UniquePtr& ptr1, UniquePtr& ptr2) {
    ptr1.Swap(ptr2);
}