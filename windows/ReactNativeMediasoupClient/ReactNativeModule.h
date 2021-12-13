#pragma once

#include "JSValue.h"
#include "NativeModules.h"
#include "mediasoupclient.hpp"

#define onProduceParamTypes mediasoupclient::SendTransport*, const std::string&, nlohmann::json, const nlohmann::json&
#define onProduceDataParamsTypes mediasoupclient::SendTransport*, const nlohmann::json&, const std::string&, const std::string&, const nlohmann::json&
#define onConnectParamsTypes mediasoupclient::Transport*, const nlohmann::json&
#define onConnectionStateChangeParamsTypes const std::string&

using namespace winrt::Microsoft::ReactNative;

namespace winrt::ReactNativeMediasoupClient
{
    REACT_STRUCT(sendTransportListener)
    struct sendTransportListener : public mediasoupclient::SendTransport::Listener {

        //Stores the function that will be called by onProduce, defaults to empty lambda
        std::function<void(onProduceParamTypes)> onProduceHandler = [](onProduceParamTypes) {};

        //Stores the function that will be called by onProduceData, defaults to empty lambda
        std::function<void(onProduceDataParamsTypes)> onProduceDataHandler = [](onProduceDataParamsTypes) {};

        //Stores the function that will be called by onConnect, defaults to empty lambda
        std::function<void(onConnectParamsTypes)> onConnectHandler = [](onConnectParamsTypes) {};

        //Stores the function that will be called by OnConnectionStateChange, defaults to empty lambda
        std::function<void(onConnectionStateChangeParamsTypes)> onConnectionStateChangeHandler = [](onConnectionStateChangeParamsTypes) {};


        /* Begin OnProduce */
        REACT_METHOD(setOnProduce)
        void setOnProduce(std::function<void(onProduceParamTypes)> callback,
            ReactPromise<int> promise) 
        {
            onProduceHandler = callback;
            promise.Resolve(true); //Job is done, resolve the promise
        }

        std::future<std::string> OnProduce(
            mediasoupclient::SendTransport* transport,
            const std::string& kind,
            nlohmann::json rtpParameters,
            const nlohmann::json& appData) noexcept
        {
            onProduceHandler(transport, kind, rtpParameters, appData);
            std::promise<std::string> promiseObj;
            return promiseObj.get_future();
        } /* End OnProduce */


        /* Begin OnProduceData */
        REACT_METHOD(setOnProduceData)
        void setOnProduceData(std::function<void(onProduceDataParamsTypes)> callback, ReactPromise<int> promise)
        {
            onProduceDataHandler = callback;
            promise.Resolve(true); //Job is done, resolve the promise
        }

        std::future<std::string> OnProduceData(
            mediasoupclient::SendTransport* transport,
            const nlohmann::json& sctpStreamParameters,
            const std::string& label,
            const std::string& protocol,
            const nlohmann::json& appData) noexcept
        {
            std::promise<std::string> promiseObj;
            return promiseObj.get_future();
        } /* End OnProduceData */


        /* Begin OnConnect */
        REACT_METHOD(setOnConnect)
        void setOnConnect(std::function<void(onConnectParamsTypes)> callback, ReactPromise<int> promise)
        {
            onConnectHandler = callback;
            promise.Resolve(true); //Job is done, resolve the promise
        }

        std::future<void> OnConnect(
            mediasoupclient::Transport* transport,
            const nlohmann::json& dtlsParameters) noexcept
        {
            std::promise<void> promiseObj;
            return promiseObj.get_future();
        } /* End OnConnect */


        /* Begin OnConnectionStateChange */
        REACT_METHOD(setOnConnectionStateChange)
        void setOnConnect(std::function<void(onConnectionStateChangeParamsTypes)> callback, ReactPromise<int> promise)
        {
            onConnectionStateChangeHandler = callback;
            promise.Resolve(true); //Job is done, resolve the promise
        }

        void OnConnectionStateChange(mediasoupclient::Transport* transport,
            const std::string& connectionState) noexcept
        {

        } /* End OnConnectionStateChange */

    };


    REACT_MODULE(ReactNativeModule, L"ReactNativeMediasoupClient")
    struct ReactNativeModule
    {
        REACT_INIT(Initialize)
        void Initialize(ReactContext const &reactContext) noexcept
        {
            this->m_reactContext = reactContext;
            mediasoupclient::Initialize();
            this->device = new mediasoupclient::Device();
        }

        
        REACT_FIELD(sendListener)
        sendTransportListener sendListener;
        

        REACT_FIELD(device)
        mediasoupclient::Device* device;

        REACT_FIELD(remoteCapabilities)
        nlohmann::json remoteCapabilities;

        REACT_FIELD(atest)
        std::string atest = "abccdd";


        REACT_METHOD(test)
        void test(std::function<void(std::string)> callback) noexcept {
            //device->Load(remoteCapabilities);
            callback("ping");
        }
        
        /*
            REACT_METHOD(sampleMethod)
        void sampleMethod(std::string stringArgument, int numberArgument, std::function<void(std::string)> &&callback) noexcept
        {
            // TODO: Implement some actually useful functionality
            callback("Received numberArgument: " + std::to_string(numberArgument) + " stringArgument: " + stringArgument);
        }
    
        */


        /*REACT_METHOD(loadDevice)
        void loadDevice(const nlohmann::json& serverRtpCapabilities) noexcept {
            device->Load(remoteCapabilities);
        }*/

        private:
            ReactContext m_reactContext{nullptr};
};

} // namespace winrt::ReactNativeMediasoupClient
