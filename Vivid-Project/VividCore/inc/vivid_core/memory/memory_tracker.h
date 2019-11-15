#pragma once

#include "vivid_core/utility/errors.h"
#include <iostream>
#include <unordered_map>
#include <utility>
#include <string>
#include <type_traits>
//replaces new with malloc
//#include <cstdlib>

namespace vivid_core
{
	namespace memory
	{
		class memory_tracker
		{
		private:
			struct memory_tracker_item
			{
				std::string name;
				std::size_t size;
				std::size_t count;
			};
			std::unordered_map<void*, memory_tracker_item> _allocated;
			std::size_t _count_alloc_objects, _count_free_objects;
			std::size_t _count_alloc_bytes, _count_free_bytes;
		public:
			memory_tracker();
			virtual ~memory_tracker();
			static memory_tracker * get_instance();

			template <typename T, typename ...Ts>
			T * allocate(Ts... args) noexcept
			{
				//T *res = new (std::nothrow) T(args...);
				void *res_raw = std::malloc(sizeof(T));
				if (!res_raw || res_raw == nullptr)
				{
					return nullptr;
				}
				T *res = new (res_raw) T(args...);
				++_count_alloc_objects;
				_count_alloc_bytes += sizeof(T);
				_allocated[res] = { typeid(T).name(), sizeof(T), 0 };
				return res;
			}

			template <typename T>
			T * allocate_array(std::size_t count) noexcept
			{
				//T *res = new (std::nothrow) T[count];
				void *res_raw = std::malloc(sizeof(T) * count);
				T *res = (T *)res_raw;
				if (!res || res == nullptr)
				{
					return nullptr;
				}
				_count_alloc_objects += count;
				_count_alloc_bytes += sizeof(T) * count;
				_allocated[res] = { typeid(T).name(), sizeof(T), count };
				return res;
			}

			template <typename T>
			int free(T * value) noexcept
			{
				if (!value || value == nullptr)
				{
					return (int)vivid_core::utility::errors::MEMORY_CORRUPT;
				}
				auto value_iter = _allocated.find(value);
				if (value_iter == _allocated.end())
				{
					return (int)vivid_core::utility::errors::OBJECT_NOT_FOUND;
				}
				_allocated.erase(value_iter);
				if constexpr (std::is_nothrow_destructible<T>::value)
				{
					value->~T();
				}
				++_count_free_objects;
				_count_free_bytes += sizeof(T);
				std::free(value);
				//noexcept(delete value);
				return (int)vivid_core::utility::errors::NONE;
			}

			template <typename T>
			int free_array(T * value) noexcept
			{
				if (!value || value == nullptr)
				{
					return (int)vivid_core::utility::errors::MEMORY_CORRUPT;
				}
				auto value_iter = _allocated.find(value);
				if (value_iter == _allocated.end())
				{
					return (int)vivid_core::utility::errors::OBJECT_NOT_FOUND;
				}
				++_count_free_objects;
				_count_free_bytes += sizeof(T) * value_iter->second.count;
				_allocated.erase(value_iter);
				std::free(value);
				//noexcept(delete[] value);
				return (int)vivid_core::utility::errors::NONE;
			}

			void dump(std::ostream &);
			std::size_t size() const;
			bool empty() const;

			std::size_t get_count_alloc_objects() const;
			std::size_t get_count_free_objects() const;
			std::size_t get_count_alloc_bytes() const;
			std::size_t get_count_free_bytes() const;
		};
	}
}