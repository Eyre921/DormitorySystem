#include "globals.h"
#include <memory>

// 定义全局 UserManager 对象
std::unique_ptr<UserManager> userManager = std::make_unique<UserManager>();
