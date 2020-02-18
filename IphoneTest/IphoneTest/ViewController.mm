//
//  ViewController.m
//  IphoneTest
//
//  Created by zifan.zx on 2019/9/2.
//  Copyright © 2019 zifan.zx. All rights reserved.
//

#import "ViewController.h"
#include "jsi.h"
#include "c++/TestBinding.h"
#include "JSCRuntime.h"
@interface ViewController (){
    std::shared_ptr<jsi::Runtime> _runtime;
}
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    _runtime = facebook::jsc::makeJSCRuntime();
    
    std::string code = std::string("var a = 2;");
    _runtime->evaluateJavaScript(
                                 std::make_unique<facebook::jsi::StringBuffer>(code), std::string("http://www.baidu.com"));
    auto test = std::make_unique<example::Test>();
    std::shared_ptr<example::TestBinding> testBinding_ = std::make_shared<example::TestBinding>(std::move(test));
    example::TestBinding::install((*_runtime),  testBinding_);
    // Do any additional setup after loading the view.
    
}


@end
