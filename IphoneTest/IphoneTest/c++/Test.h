// Copyright 2004-present Facebook. All Rights Reserved.

#pragma once

#include "jsi.h"
#include <string>

namespace example {

  class Test {
  public:
    Test();
  private:
    friend class TestBinding;
    
    int runTest() const;
    std::string getMyString();
    void setMyString(std::string newString);
    void setMyIntValue(double newIntValue);
  private:
    int intValue;
    std::string myString;
  };

} // namespace example
