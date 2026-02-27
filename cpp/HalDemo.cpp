#include <iostream>
#include <string>

#include "AndroidHal.h"

using namespace androidhal;

int main()
{
    MockV4L2Device cameraDevice;
    MockAudioDevice audioDevice;
    AndroidHal hal(cameraDevice, audioDevice);

    std::cout << "=== AndroidHAL Simulator Demo ===" << std::endl;

    std::string cameraNode = "/dev/video0";
    std::string audioDeviceName = "default";

    bool camOk = hal.openCamera(cameraNode);
    bool audOk = hal.openAudio(audioDeviceName);

    std::cout << "Open camera (" << cameraNode << "): " << (camOk ? "OK" : "FAILED") << std::endl;
    std::cout << "Open audio (" << audioDeviceName << "): " << (audOk ? "OK" : "FAILED") << std::endl;

    androidhal::Frame frame = hal.captureFrame();
    std::cout << "Captured frame: " << frame.width << "x" << frame.height << ", bytes=" << frame.data.size()
              << std::endl;

    if (!frame.data.empty())
    {
        std::cout << "First 8 pixels: ";
        for (std::size_t i = 0; i < 8 && i < frame.data.size(); ++i)
        {
            std::cout << static_cast<int>(frame.data[i]) << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Audio levels: ";
    for (int i = 0; i < 5; ++i)
    {
        float level = hal.readAudioLevel();
        std::cout << level;
        if (i != 4)
        {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;

    std::cout << "=== Demo complete ===" << std::endl;
    return 0;
}
