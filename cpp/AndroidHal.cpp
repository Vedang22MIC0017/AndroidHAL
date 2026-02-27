#include "AndroidHal.h"

#include <cmath>

namespace androidhal {

bool MockV4L2Device::open(const std::string& node) {
    nodeName = node;
    opened = true;
    return opened;
}

Frame MockV4L2Device::captureFrame() {
    Frame frame;
    frame.width = 640;
    frame.height = 480;
    frame.data.resize(frame.width * frame.height);
    if (!opened) {
        return frame;
    }
    for (std::uint32_t y = 0; y < frame.height; ++y) {
        for (std::uint32_t x = 0; x < frame.width; ++x) {
            std::size_t index = static_cast<std::size_t>(y) * frame.width + x;
            frame.data[index] = static_cast<std::uint8_t>((x + y) % 256);
        }
    }
    return frame;
}

bool MockAudioDevice::open(const std::string& device) {
    deviceName = device;
    opened = true;
    level = 0.1f;
    return opened;
}

float MockAudioDevice::readLevel() {
    if (!opened) {
        return 0.0f;
    }
    level += 0.05f;
    if (level > 1.0f) {
        level = 0.1f;
    }
    return level;
}

AndroidHal::AndroidHal(IV4L2Device& cameraDevice, IAudioDevice& audioDevice)
    : camera(cameraDevice),
      audio(audioDevice),
      cameraOpen(false),
      audioOpen(false) {}

bool AndroidHal::openCamera(const std::string& node) {
    cameraOpen = camera.open(node);
    return cameraOpen;
}

Frame AndroidHal::captureFrame() {
    if (!cameraOpen) {
        Frame empty;
        empty.width = 0;
        empty.height = 0;
        return empty;
    }
    return camera.captureFrame();
}

bool AndroidHal::openAudio(const std::string& device) {
    audioOpen = audio.open(device);
    return audioOpen;
}

float AndroidHal::readAudioLevel() {
    if (!audioOpen) {
        return 0.0f;
    }
    return audio.readLevel();
}

}  // namespace androidhal

