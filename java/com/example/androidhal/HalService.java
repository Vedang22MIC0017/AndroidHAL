package com.example.androidhal;

public class HalService {

    static {
        System.loadLibrary("androidhal_sim");
    }

    private native boolean nativeOpenCamera(String node);
    private native byte[] nativeCaptureFrame();
    private native boolean nativeOpenAudio(String device);
    private native float nativeReadAudioLevel();

    public boolean openCamera(String node) {
        return nativeOpenCamera(node);
    }

    public byte[] captureFrame() {
        return nativeCaptureFrame();
    }

    public boolean openAudio(String device) {
        return nativeOpenAudio(device);
    }

    public float readAudioLevel() {
        return nativeReadAudioLevel();
    }
}

