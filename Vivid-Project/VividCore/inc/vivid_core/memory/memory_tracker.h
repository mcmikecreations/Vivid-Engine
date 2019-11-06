#pragma once

#include "vivid_core/utility/errors.h"
#include <iostream>
#include <unordered_map>
#include <utility>
#include <string>
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
			std::size_t _count_alloc, _count_free;
		public:
			memory_tracker();
			virtual ~memory_tracker();
			static memory_tracker * get_instance();

			template <typename T, typename ...Ts>
			T * allocate(Ts... args) noexcept
			{
				//T *res = new (std::nothrow) T(args...);
				void *res_raw = std::malloc(sizeof(T));
				if (!res || res == nullptr)
				{
					return nullptr;
				}
				T *res = new (res_raw) T(args...);
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
				_allocated[res] = { typeid(T).name(), sizeof(T), count };
				return res;
			}

			template <typename T>
			int free(T * value) noexcept
			{
				if (!value || value == nullptr)
				{
					return (int)VividCore::Utility::Errors::MEMORY_CORRUPT;
				}
				auto value_iter = _allocated.find(value);
				if (value_iter == _allocated.end())
				{
					return (int)VividCore::Utility::Errors::OBJECT_NOT_FOUND;
				}
				std::size_t cnt = value_iter->second.count;
				_allocated.erase(value_iter);
				std::free(value);
				//if (cnt == 0)
				//{
				//	noexcept(delete value);
				//}else{
				//	noexcept(delete[] value);
				//}

				return (int)VividCore::Utility::Errors::NONE;
			}

			void dump(std::ostream &);
			std::size_t size() const;
			bool empty() const;

			std::size_t get_count_alloc() const;
			std::size_t get_count_free() const;
		};
	}
}