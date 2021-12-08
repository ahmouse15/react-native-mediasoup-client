#pragma once

# pragma comment(lib, "secur32.lib")
# pragma comment(lib, "winmm.lib")
# pragma comment(lib, "dmoguids.lib")
# pragma comment(lib, "wmcodecdspuuid.lib")
# pragma comment(lib, "msdmo.lib")
# pragma comment(lib, "Strmiids.lib")

#include "JSValue.h"
#include "NativeModules.h"
#include "mediasoupclient.hpp"

using namespace winrt::Microsoft::ReactNative;

namespace winrt::ReactNativeMediasoupClient
{

REACT_MODULE(ReactNativeModule, L"ReactNativeMediasoupClient")
struct ReactNativeModule
{
    // See https://microsoft.github.io/react-native-windows/docs/native-modules for details on writing native modules

    REACT_INIT(Initialize)
    void Initialize(ReactContext const &reactContext) noexcept
    {
        m_reactContext = reactContext;
    }
    
    REACT_METHOD(sampleMethod)
    void sampleMethod(std::string stringArgument, int numberArgument, std::function<void(std::string)> &&callback) noexcept
    {
        // TODO: Implement some actually useful functionality
        callback("Received numberArgument: " + std::to_string(numberArgument) + " stringArgument: " + stringArgument);
    }

    REACT_METHOD(mediasoupInitialize)
        void mediasoupInitialize() noexcept {
            mediasoupclient::Initialize();
    }

    private:
        ReactContext m_reactContext{nullptr};
};

} // namespace winrt::ReactNativeMediasoupClient
