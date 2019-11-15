#include "vivid_core/memory/memory_tracker.h"

using namespace vivid_core::memory;

static memory_tracker * tracker = nullptr;

memory_tracker::memory_tracker() : _count_alloc_objects(0), _count_free_objects(0), _count_alloc_bytes(0), _count_free_bytes(0)
{
}

memory_tracker::~memory_tracker()
{
	if (tracker != nullptr)
	{
		delete tracker;
		tracker = nullptr;
	}
}

memory_tracker * memory_tracker::get_instance()
{
	if (tracker == nullptr)
	{
		tracker = new memory_tracker();
	}
	return tracker;
}

void memory_tracker::dump(std::ostream &stream)
{
	stream << "alloc: " << _count_alloc_bytes << " free: " << _count_free_bytes << std::endl;
	if (_allocated.empty()) return;
	for (auto& it : _allocated) {
		stream << it.first << " " << it.second.name << "(" << it.second.size << ")";
		if (it.second.count != 0)
		{
			stream << "[" << it.second.count << "]";
		}
		stream << std::endl;
	}
}

std::size_t memory_tracker::size() const
{
	return _allocated.size();
}

bool memory_tracker::empty() const
{
	return _allocated.empty();
}

std::size_t memory_tracker::get_count_alloc_objects() const
{
	return _count_alloc_objects;
}

std::size_t memory_tracker::get_count_free_objects() const
{
	return _count_free_objects;
}

std::size_t memory_tracker::get_count_alloc_bytes() const
{
	return _count_alloc_bytes;
}

std::size_t memory_tracker::get_count_free_bytes() const
{
	return _count_free_bytes;
}