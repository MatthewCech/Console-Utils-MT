#pragma once

#define UNUSED(x) (void)(x)
#define LOG(x) std::cout << x << std::endl
#define DUMP(x) LOG(#x << ":" << x)
