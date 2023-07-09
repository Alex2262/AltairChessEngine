//
// Created by Alexander Tian on 6/24/23.
//

#ifndef ALTAIRCHESSENGINE_FIXED_VECTOR_H
#define ALTAIRCHESSENGINE_FIXED_VECTOR_H

// A lot of code in here is influenced by Conor Anstey (Ciekce)

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

    inline T pop() {
        current_index--;
        return fixed_vector[current_index];
    }
};

#endif //ALTAIRCHESSENGINE_FIXED_VECTOR_H
