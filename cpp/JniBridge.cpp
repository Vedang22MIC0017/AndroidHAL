#include <jni.h>

#include <string>
#include <vector>

#include "AndroidHal.h"

using namespace androidhal;

static MockV4L2Device gCameraDevice;
static MockAudioDevice gAudioDevice;
static AndroidHal gHal(gCameraDevice, gAudioDevice);

extern "C" {

JNIEXPORT jboolean JNICALL
Java_com_example_androidhal_HalService_nativeOpenCamera(JNIEnv* env,
                                                        jobject /*thiz*/,
                                                        jstring node) {
    const char* chars = env->GetStringUTFChars(node, nullptr);
    std::string nodeName(chars ? chars : "");
    env->ReleaseStringUTFChars(node, chars);
    bool ok = gHal.openCamera(nodeName);
    return ok ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT jbyteArray JNICALL
Java_com_example_androidhal_HalService_nativeCaptureFrame(JNIEnv* env,
                                                          jobject /*thiz*/) {
    Frame frame = gHal.captureFrame();
    jsize size = static_cast<jsize>(frame.data.size());
    jbyteArray array = env->NewByteArray(size);
    if (size > 0) {
        env->SetByteArrayRegion(array, 0, size,
                                reinterpret_cast<const jbyte*>(frame.data.data()));
    }
    return array;
}

JNIEXPORT jboolean JNICALL
Java_com_example_androidhal_HalService_nativeOpenAudio(JNIEnv* env,
                                                       jobject /*thiz*/,
                                                       jstring device) {
    const char* chars = env->GetStringUTFChars(device, nullptr);
    std::string deviceName(chars ? chars : "");
    env->ReleaseStringUTFChars(device, chars);
    bool ok = gHal.openAudio(deviceName);
    return ok ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT jfloat JNICALL
Java_com_example_androidhal_HalService_nativeReadAudioLevel(JNIEnv* env,
                                                            jobject /*thiz*/) {
    float level = gHal.readAudioLevel();
    return static_cast<jfloat>(level);
}

}  // extern "C"

