/* Copyright (c) The Grit Game Engine authors 2017
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <cstdlib>
#include <cstdio>

#include <iostream>
#include <memory>
#include <string>

#ifndef STRINGF_H
#define STRINGF_H

template<typename ...Args>
std::string stringf (const std::string &fmt, Args... args)
{
    // MSVC did not have std::snprintf
    size_t output_size = snprintf(nullptr, 0, fmt.c_str(), args...);
	output_size += 1;  // For '\0'.
    std::unique_ptr<char[]> buf(new char[output_size]); 
    snprintf(buf.get(), output_size, fmt.c_str(), args...);
    return std::string(buf.get());
}

#endif
