#pragma once
#include <exception>
#ifdef OCTAVIAN_DEBUG
#define OCTAVIAN_ASSERT_PTR(obj) if(!obj) throw std::exception("Null pointer was encountred.");
#else
#define OCTAVIAN_ASSERT_PTR
#endif