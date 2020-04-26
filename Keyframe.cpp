//
// Created by Edge on 2020/4/26.
//

#include "Keyframe.h"
#include <iostream>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION

#include "stb_image_resize.h"

using std::string;
using std::ifstream;

Keyframe::Keyframe(string filename) {
    m_pixel = stbi_load(filename.c_str(), &m_width, &m_height, &m_channel, 0);
}

void Keyframe::interpolate(Keyframe *next, float delta, Keyframe &target) {
    // FIXME I'm idiot, for sure keyframe is real
    if (!target.m_pixel) {
        stbir_resize_uint8(next->m_pixel, m_width, m_height, 0,
                           target.m_pixel, m_width, m_height, 0, m_channel);
    }
    for (int i = 0; i < m_width; ++i) {
        for (int j = 0; j < m_height; ++j) {
            for (int k = 0; k < m_channel; ++k) {
                target.m_pixel[i] = m_pixel[i] * (1 - delta) + next->m_pixel[i] * delta;
            }
        }
    }
}

Keyframe &Keyframe::operator=(Keyframe *keyframe) {
    // FIXME I'm idiot, for sure keyframe is real
    if (!m_pixel) {
        stbir_resize_uint8(keyframe->m_pixel, m_width, m_height, 0,
                           m_pixel, m_width, m_height, 0, m_channel);
    }
    for (int i = 0; i < m_width * m_height * m_channel; ++i) {
        m_pixel[i] = keyframe->m_pixel[i];
    }
}

Keyframe::~Keyframe() {
    stbi_image_free(m_pixel);
}

void KeyframeAnimation::loadAnimation(const string &keyframeSeriesName) {
    // Input format require keyframeSeriesName.kfd
    // in side .kfd file
    // <timeline> <keyframe image file name>
    ifstream ifs(keyframeSeriesName);
    std::string keyframeFilename;
    int timeline;
    while (ifs >> timeline >> keyframeFilename) {
        m_keyframeTimeline.insert(std::pair<int, Keyframe *>(timeline, new Keyframe(keyframeFilename)));
    }
    ifs.close();
}

void KeyframeAnimation::getKeyframeAtTime(int t, Keyframe &result) {
    int maxTimeline = (--m_keyframeTimeline.end())->first;
    if (!maxTimeline) {
        return;
    }

    t = (((t % maxTimeline) + maxTimeline) % maxTimeline);
    auto keyframeIt = m_keyframeTimeline.lower_bound(t);
    if (keyframeIt->first != t) {
        Keyframe *last = keyframeIt->second;
        int len = keyframeIt->first;
        len -= (--keyframeIt)->first;
        t -= keyframeIt->first;
        float delta = (float) t / (float) len;
        Keyframe *first = keyframeIt->second;
        first->interpolate(last, delta, result);
    } else {
        result = keyframeIt->second;
    }
}
