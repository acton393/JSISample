// Copyright 2004-present Facebook. All Rights Reserved.

#include "TestBinding.h"

#include "Test.h"
#include <iostream>

namespace example {

  static jsi::Object getModule(
                                jsi::Runtime &runtime,
                                const std::string &moduleName) {
    auto batchedBridge =
    runtime.global().getPropertyAsObject(runtime, "__fbBatchedBridge");
    auto getCallableModule =
    batchedBridge.getPropertyAsFunction(runtime, "getCallableModule");
    auto module = getCallableModule
    .callWithThis(
                  runtime,
                  batchedBridge,
                  {jsi::String::createFromUtf8(runtime, moduleName)})
    .asObject(runtime);
    return module;
  }

  void TestBinding::install(
                                  jsi::Runtime &runtime,
                                  std::shared_ptr<TestBinding> testBinding) {
    auto testModuleName = "nativeTest";
    auto object = jsi::Object::createFromHostObject(runtime, testBinding);
    runtime.global().setProperty(runtime, testModuleName, std::move(object));
  }

  TestBinding::TestBinding(std::unique_ptr<Test> test)
  : test_(std::move(test)) {}

  void TestBinding::set(jsi::Runtime& runtime, const jsi::PropNameID& name, const jsi::Value& value)
  {
    auto propertyName = name.utf8(runtime);
    if (propertyName == "MyString") {
      auto &test = *test_;
      test.setMyString(value.asString(runtime).utf8(runtime));
    }
    
    if (propertyName == "intValue") {
      auto &test = *test_;
      test.setMyIntValue(value.asNumber());
    }
    
  }

  jsi::Value TestBinding::get(
                                    jsi::Runtime &runtime,
                                    const jsi::PropNameID &name) {
    auto methodName = name.utf8(runtime);
    auto &test = *test_;

    if (methodName == "runTest") {
      return jsi::Function::createFromHostFunction(runtime, name, 0, [&test](
                                                                              jsi::Runtime &runtime,
                                                                              const jsi::Value &thisValue,
                                                                              const jsi::Value *arguments,
                                                                              size_t count) -> jsi::Value {
        return test.runTest();
      });
    }
    if (methodName == "getMyString") {
      return jsi::Function::createFromHostFunction(runtime, name, 0, [&test](
                                                                              jsi::Runtime &runtime,
                                                                              const jsi::Value &thisValue,
                                                                              const jsi::Value *arguments,
                                                                              size_t count) -> jsi::Value {
        auto result = test.getMyString();
        return jsi::Value(jsi::String::createFromAscii(runtime, result.c_str()));
      });
    }

    return jsi::Value::undefined();
  }

} // namespace example

#if ANDROID
extern "C"
{
JNIEXPORT void JNICALL
Java_com_testmodule_MainActivity_install(JNIEnv *env, jobject thiz, jlong runtimePtr) {
  auto test = std::make_unique<example::Test>();
  auto testBinding = std::make_shared<example::TestBinding>(std::move(test));
  jsi::Runtime *runtime = (jsi::Runtime *) runtimePtr;

  example::TestBinding::install(*runtime, testBinding);
}
}
#endif
