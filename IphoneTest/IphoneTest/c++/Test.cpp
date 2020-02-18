// Copyright 2004-present Facebook. All Rights Reserved.

#include "Test.h"

namespace example {
  Test::Test():intValue(1024),myString("I am an init string"){
  }
  int Test::runTest() const {
    return this->intValue;
  }

  void Test::setMyIntValue(double newIntValue) {
    this->intValue = newIntValue;
  }
  std::string Test::getMyString(){
    return this->myString;
  }
  void Test::setMyString(std::string newString){
    this->myString = std::string(newString);
  }

} // namespace facebook
