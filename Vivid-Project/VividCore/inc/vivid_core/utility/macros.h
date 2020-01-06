#pragma once

#if defined(DEEP_DEBUG)
#define VE_NEW(type) vivid_core::memory::memory_tracker::get_instance()->allocate<type>
#define VE_NEWARR(type,length) vivid_core::memory::memory_tracker::get_instance()->allocate_array<type>(length)
#define VE_DEL(ptr) vivid_core::memory::memory_tracker::get_instance()->free(ptr)
#define VE_DELARR(ptr) vivid_core::memory::memory_tracker::get_instance()->free(ptr)
#else
#define VE_NEW(type) new (std::nothrow) type
#define VE_NEWARR(type,length) new (std::nothrow) type[length]
#define VE_DEL(ptr) noexcept(delete ptr)
#define VE_DELARR(ptr) noexcept(delete[] ptr)
#endif

#define START_NAME(val) namespace val {
#define END_NAME(val) } //val

#define START_ENGINE START_NAME(vivid_core)
#define END_ENGINE END_NAME(vivid_core)