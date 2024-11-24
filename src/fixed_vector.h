

#ifndef ALTAIR_FIXED_VECTOR_H
#define ALTAIR_FIXED_VECTOR_H


#include <cstdint>
#include <cstring>
#include <array>

template <typename T, size_t FixedSize>
class FixedVector {

private:
    size_t current_index = 0;
    std::array<T, FixedSize> fixed_vector{};

public:
    FixedVector() = default;

    size_t size() { return current_index; }
    bool empty() { return current_index == 0; }

    auto begin() { return fixed_vector.begin(); }
    auto end() { return begin() + current_index; }

    T& operator[](size_t index) { return fixed_vector[index]; }
    const T& operator[](size_t index) const { return fixed_vector[index]; }

    void clear() { current_index = 0; }

    void push_back(T element) {
        fixed_vector[current_index] = element;
        current_index++;
    }

    void pop(size_t index) {
        current_index--;
        if (index == current_index) return;

        for (size_t i = index + 1; i <= current_index; i++) {
            fixed_vector[i - 1] = fixed_vector[i];
        }
    }

    T pop() {
        current_index--;
        return fixed_vector[current_index];
    }
};

#endif //ALTAIR_FIXED_VECTOR_H
