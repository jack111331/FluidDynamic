//
// Created by Edge on 2020/4/26.
//

#include "Keyframe.h"
#include <iostream>
#include <fstream>
#include <Utility.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#undef STB_IMAGE_IMPLEMENTATION


#define STB_IMAGE_RESIZE_IMPLEMENTATION

#include "stb_image_resize.h"

using std::string;
using std::ifstream;

Keyframe::Keyframe(string filename) {
    uint8_t *pixel = stbi_load(filename.c_str(), &m_width, &m_height, &m_channel, 0);
    m_pixel = new float[(m_width + 2) * (m_height + 2)];
    for (int i = 1; i <= m_width; ++i) {
        for (int j = 1; j <= m_height; ++j) {
            m_pixel[indexOf(i, j, m_width)] = pixel[(i - 1) * m_width + (j - 1)];
        }
    }
    stbi_image_free(pixel);
}

void Keyframe::interpolate(Keyframe *next, float delta, Keyframe &target) {
    if (!target.m_pixel) {
        target.m_width = m_width;
        target.m_height = m_height;
        target.m_channel = m_channel;
        target.m_pixel = new float[(m_width + 2) * (m_height + 2)];
    }
    for (int i = 1; i <= m_width; ++i) {
        for (int j = 1; j <= m_height; ++j) {
            target.m_pixel[indexOf(i, j, m_width)] =
                    m_pixel[indexOf(i, j, m_width)] * (1 - delta) + next->m_pixel[indexOf(i, j, m_width)] * delta;
        }
    }
}

Keyframe &Keyframe::operator=(Keyframe *keyframe) {
    if (!m_pixel) {
        m_width = keyframe->m_width;
        m_height = keyframe->m_height;
        m_channel = keyframe->m_channel;
        m_pixel = new float[(m_width + 2) * (m_height + 2)];
    }
    for (int i = 1; i <= m_width; ++i) {
        for (int j = 1; j <= m_height; ++j) {
            m_pixel[indexOf(i, j, m_width)] = keyframe->m_pixel[indexOf(i, j, m_width)];
        }
    }
}

Keyframe::~Keyframe() {
    delete[] m_pixel;
}

void KeyframeAnimation::loadAnimation(const string &keyframeSeriesName) {
    // Input format require keyframeSeriesName.kfd
    // in side .kfd file
    // <timeline> <keyframe image file name>
    ifstream ifs(keyframeSeriesName);
    std::string keyframeFilename;
    int timeline;
    while (ifs >> timeline >> keyframeFilename) {
        m_keyframeTimeline.insert(std::pair<int, Keyframe *>(timeline, new Keyframe(keyframeSeriesName.substr(0, keyframeSeriesName.find_last_of('/')+1) + keyframeFilename)));
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
