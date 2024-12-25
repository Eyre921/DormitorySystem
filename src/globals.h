#ifndef GLOBALS_H
#define GLOBALS_H

#include <memory>
#include "UserManager.h"

// 声明全局 unique_ptr
extern std::unique_ptr<UserManager> userManager;

#endif // GLOBALS_H
