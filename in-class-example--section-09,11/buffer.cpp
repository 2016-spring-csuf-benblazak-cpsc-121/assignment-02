/* ----------------------------------------------------------------------------
 * Copyright &copy; 2016 YOUR_NAME <YOUR_EMAIL>
 * Released under the [MIT License] (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */

/**
 * Implements `buffer.h`.
 */

#include <iostream>

#include "buffer.h"

typedef  unsigned int  uint;

// ----------------------------------------------------------------------------

Buffer::Buffer(unsigned int size_x, unsigned int size_y)
    : size_x(size_x), size_y(size_y)
{
    data_ = new char[size_x * size_y];
    clear();
}

Buffer::~Buffer() {
    delete[] data_;
}

char Buffer::get(unsigned int x, unsigned int y) const {
    return data_[ y * size_x + x ];
}

void Buffer::set(unsigned int x, unsigned int y, char c) {
    data_[ y * size_x + x ] = c;
}

void Buffer::set(unsigned int x, unsigned int y, std::string s) {
    uint original_x = x;
    uint original_y = y;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '\n') {
            y++;
            x = original_x;
        } else {
            set(x, y, s[i]);
            x++;
        }
    }
}

void Buffer::draw() const {
    for (uint y = 0; y < size_y; y++) {
        for (uint x = 0; x < size_x; x++) {
            std::cout << get(x, y);
        }
        std::cout << std::endl;
    }
}

void Buffer::clear() {
    for (uint y = 0; y < size_y; y++) {
        for (uint x = 0; x < size_x; x++) {
            data_[y * size_x + x] = ' ';
        }
    }
}

