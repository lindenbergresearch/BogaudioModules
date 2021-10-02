#pragma once

#include <cassert>
#include <cmath>

#include "ffft/FFTReal.h"
#include "buffer.hpp"

namespace bogaudio::dsp {

struct Window {
    int _size;
    float *_window;
    float _sum;


    explicit Window(int size) : _size(size), _window(new float[_size]{}), _sum(0.0) {}


    virtual ~Window() {
        delete[] _window;
    }


    inline int size() const { return _size; }


    inline float at(int i) {
        assert(i >= 0 && i < _size);
        return _window[i];
    }


    inline float sum() const { return _sum; }


    void apply(float *in, float *out);
};


struct HanningWindow : Window {
    explicit HanningWindow(int size, float alpha = 0.5);
};


struct HammingWindow : HanningWindow {
    explicit HammingWindow(int size) : HanningWindow(size, 0.54) {}
};


struct KaiserWindow : Window {
    explicit KaiserWindow(int size, float alpha = 7.865f);


    float i0(float x);
};


struct PlanckTaperWindow : Window {
    PlanckTaperWindow(int size, int taperSamples);
};


struct FFT1024 {
    void *_fft = nullptr;


    FFT1024();


    ~FFT1024();


    void do_fft(float *out, float *in);
};


struct FFT4096 {
    void *_fft = nullptr;


    FFT4096();


    ~FFT4096();


    void do_fft(float *out, float *in);
};


struct FFT8192 {
    void *_fft = nullptr;


    FFT8192();


    ~FFT8192();


    void do_fft(float *out, float *in);
};


struct FFT16384 {
    void *_fft = nullptr;


    FFT16384();


    ~FFT16384();


    void do_fft(float *out, float *in);
};


struct FFT32768 {
    void *_fft = nullptr;


    FFT32768();


    ~FFT32768();


    void do_fft(float *out, float *in);
};


struct SpectrumAnalyzer : OverlappingBuffer<float> {
    enum Size {
        SIZE_128 = 128,
        SIZE_256 = 256,
        SIZE_512 = 512,
        SIZE_1024 = 1024,
        SIZE_2048 = 2048,
        SIZE_4096 = 4096,
        SIZE_8192 = 8192,
        SIZE_16384 = 16384,
        SIZE_32768 = 32768
    };

    static constexpr Size maxSize = SIZE_32768;

    enum Overlap {
        OVERLAP_1 = 1,
        OVERLAP_2 = 2,
        OVERLAP_4 = 4,
        OVERLAP_8 = 8
    };

    enum WindowType {
        WINDOW_NONE,
        WINDOW_HANNING,
        WINDOW_HAMMING,
        WINDOW_KAISER
    };

    const float _sampleRate;
    ffft::FFTReal<float> *_fft = nullptr;
    FFT1024 *_fft1024 = nullptr;
    FFT4096 *_fft4096 = nullptr;
    FFT8192 *_fft8192 = nullptr;
    FFT16384 *_fft16384 = nullptr;
    FFT32768 *_fft32768 = nullptr;
    Window *_window = nullptr;
    float *_windowOut = nullptr;
    float *_fftOut = nullptr;


    SpectrumAnalyzer(
          Size size,
          Overlap overlap,
          WindowType windowType,
          float sampleRate,
          bool autoProcess = true
    );


    ~SpectrumAnalyzer() override;


    void processBuffer(float *samples) override;


    void getMagnitudes(float *bins, int nBins);
};

} // namespace bogaudio
