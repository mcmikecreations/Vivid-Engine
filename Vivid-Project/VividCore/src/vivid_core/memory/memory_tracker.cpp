#include "vivid_core/memory/memory_tracker.h"

using namespace VividCore::Memory;

static memory_tracker * tracker = nullptr;

memory_tracker::memory_tracker()
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