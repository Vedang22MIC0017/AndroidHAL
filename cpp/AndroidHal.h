#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace androidhal {

struct Frame {
    std::vector<std::uint8_t> data;
    std::uint32_t width;
    std::uint32_t height;
};

class IV4L2Device {
public:
    virtual ~IV4L2Device() = default;
    virtual bool open(const std::string& node) = 0;
    virtual Frame captureFrame() = 0;
};

class IAudioDevice {
public:
    virtual ~IAudioDevice() = default;
    virtual bool open(const std::string& device) = 0;
    virtual float readLevel() = 0;
};

class MockV4L2Device : public IV4L2Device {
public:
    bool open(const std::string& node) override;
    Frame captureFrame() override;

private:
    bool opened = false;
    std::string nodeName;
};

class MockAudioDevice : public IAudioDevice {
public:
    bool open(const std::string& device) override;
    float readLevel() override;

private:
    bool opened = false;
    std::string deviceName;
    float level = 0.0f;
};

class AndroidHal {
public:
    AndroidHal(IV4L2Device& cameraDevice, IAudioDevice& audioDevice);

    bool openCamera(const std::string& node);
    Frame captureFrame();

    bool openAudio(const std::string& device);
    float readAudioLevel();

private:
    IV4L2Device& camera;
    IAudioDevice& audio;
    bool cameraOpen;
    bool audioOpen;
};

}  // namespace androidhal

