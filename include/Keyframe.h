//
// Created by Edge on 2020/4/26.
//

#ifndef FLUIDDYNAMIC_KEYFRAME_H
#define FLUIDDYNAMIC_KEYFRAME_H

#include <map>
#include <string>
#include <cstdint>

class Keyframe {
public:
    Keyframe(): m_pixel(nullptr) {}
    Keyframe(std::string filename);
    void interpolate(Keyframe *next, float delta, Keyframe &target);
    Keyframe &operator = (Keyframe *keyframe);
    virtual ~Keyframe();
    float *m_pixel;
    int m_width, m_height, m_channel;
};

class KeyframeAnimation {
public:
    void loadAnimation(const std::string &keyframeSeriesName);
    void getKeyframeAtTime(int t, Keyframe &result);
private:
    std::map<int, Keyframe *> m_keyframeTimeline;
};


#endif //FLUIDDYNAMIC_KEYFRAME_H
