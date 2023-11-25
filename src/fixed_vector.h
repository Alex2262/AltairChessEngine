

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

    inline size_t size() { return current_index; }
    inline bool empty() { return current_index == 0; }

    inline auto begin() { return fixed_vector.begin(); }
    inline auto end() { return begin() + current_index; }

    inline T& operator[](size_t index) { return fixed_vector[index]; }
    inline const T& operator[](size_t index) const { return fixed_vector[index]; }

    inline void clear() { current_index = 0; }

    inline void push_back(T element) {
        fixed_vector[current_index] = element;
        current_index++;
    }

    inline void pop(size_t index) {
        current_index--;
        if (index == current_index) return;

        for (size_t i = index + 1; i <= current_index; i++) {
            fixed_vector[i - 1] = fixed_vector[i];
        }
    }

    inline T pop() {
        current_index--;
        return fixed_vector[current_index];
    }
};

#endif //ALTAIR_FIXED_VECTOR_H
