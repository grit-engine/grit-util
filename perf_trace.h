/* Copyright (c) The Grit Game Engine authors 2016
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

#ifndef PerfTrace_h
#define PerfTrace_h

typedef micros_t unsigned long long;

/** A way to trace performance on a per-frame basis.
 *
 * Example: 
 * Define an enum with an enumerator for each trace point.  They should occur sequentially
 * in time.
 * enum {
 *   TRACE_BEFORE_A,
 *   TRACE_BEFORE_B,
 *   TRACE_AFTER_B,
 *   TRACE_BEFORE_C,
 *   TRACE_AFTER_C,
 *   TRACE_AFTER_A,
 *   TRACE_SIZE,  // Must be the last in the list.
 * };
 * Then, in code, when you want to start tracing a sequence of 100 frames:
 * FrameTraceBuffer<TRACE_SIZE> trace_buf(100);
 * trace_buf->setEnabled(true);
 * for (each frame) {
 *   trace_buf.trace(TRACE_BEFORE_A);
 *   trace_buf.trace(TRACE_BEFORE_C);
 *   trace_buf.trace(TRACE_AFTER_C);
 *   trace_buf.trace(TRACE_AFTER_A);
 *   trace_buf.advance();
 * }
 * The buffer will disable itself when it reaches the maximum number of frames.
 */
template<std::size_t N>
class FrameTraceBuffer {

    public:

    FrameTraceBuffer(std::size_t num_frames=600)
        : enabled(false)
    {
        reset(num_frames);
    }

    /** Clear all data, also set the size of the buffer. */
    void reset (std::size_t num_frames)
    {
        frames.resize(num_frames);
        for (auto &frame_ptr : frames) {
            frame_ptr.reset(new std::array<micros_t, N>());
            frame_ptr->fill(0);
        }
        enabled = true;
    }

    bool setEnabled (bool v)
    { enabled = v; }

    bool isEnabled (void) const
    { return enabled; }

    std::size_t length (void) const
    { return frames.length(); }

    void advance (void)
    {
        currentIndex++;
        if (currentIndex >= length()) {
            currentIndex = 0;
            enabled = false;
        }
    }

    void trace (std::size_t trace_point)
    { currentFrame()[trace_point] = micros(); }

    void get (std::size_t frame, std::size_t trace_point)

    std::vector<std::string> toCsv (void)
    {
        std::vector<std::string> lines;
        for (std::size_t i = 0; i < length(); ++i) {
            std::stringstream line;
            for (std::size_t j = 0; j < N; ++j) {
                if (j > 0) line << ",";
                line << frames[i][j];
            }
            line << "\n";
            lines.emplace_back(line.str());
        }
        return lines;
    }

    private:

    std::array<micros_t> &currentFrame (void)
    { return frames[currentIndex]; }

    std::vector<std::unique<std::array<micros_t, N>>> frames;
    bool enabled;
    std::size_t currentIndex;
};

#endif
