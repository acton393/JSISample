// Copyright 2004-present Facebook. All Rights Reserved.

#pragma once

#include "Test.h"
#include "jsi.h"

#if ANDROID
#include <jni.h>
#endif

#if ANDROID
extern "C" {
JNIEXPORT void JNICALL
Java_com_testmodule_MainActivity_install(JNIEnv* env, jobject thiz, jlong runtimePtr);
}
#endif

using namespace facebook;

namespace example {

  /*
    * Exposes Test to JavaScript realm.
    */
  class TestBinding : public jsi::HostObject {
  public:
    /*
      * Installs TestBinding into JavaSctipt runtime.
      * Thread synchronization must be enforced externally.
      */
    static void install(
                        jsi::Runtime &runtime,
                        std::shared_ptr<TestBinding> testBinding);

    TestBinding(std::unique_ptr<Test> test);

    /*
      * `jsi::HostObject` specific overloads.
      */
    jsi::Value get(jsi::Runtime &runtime, const jsi::PropNameID &name) override;
    
    void set(jsi::Runtime& runtime, const jsi::PropNameID& name, const jsi::Value& value) override;

  private:
    std::unique_ptr<Test> test_;
  };

} // namespace example
