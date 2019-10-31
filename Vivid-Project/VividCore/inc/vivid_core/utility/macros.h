#pragma once

#if defined(DEEP_DEBUG)
#define VE_NEW(type) Memory::memory_tracker::get_instance()->allocate<type>
#define VE_NEWARR(type,length) Memory::memory_tracker::get_instance()->allocate_array<type>(length)
#define VE_DEL(ptr) Memory::memory_tracker::get_instance()->free(ptr)
#define VE_DELARR(ptr) Memory::memory_tracker::get_instance()->free(ptr)
#else
#define VE_NEW(type) new (std::nothrow) type
#define VE_NEWARR(type,length) new (std::nothrow) type[length]
#define VE_DEL(ptr) noexcept(delete ptr)
#define VE_DELARR(ptr) noexcept(delete[] ptr)
#endif