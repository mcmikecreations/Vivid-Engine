#pragma once
//By Freeeaky
#include "vivid_core/utility/macros.h"

START_ENGINE
START_NAME(mtl)
START_NAME(threading)

class fiber
{
public:
	using callback_t = void(*)(fiber*);

private:
	void* _fiber = nullptr;
	bool _thread_fiber = false;

	fiber* _return_fiber = nullptr;

	callback_t _callback = nullptr;
	void* _userdata = nullptr;

	fiber(void* fiber) :
		_fiber(fiber)
	{};

public:
	fiber();
	fiber(const fiber&) = delete;
	~fiber();

	// Convert current thread to a fiber
	void from_current_thread();

	// Set callback
	void set_callback(callback_t);

	// Fiber switching
	void switch_to(fiber*, void* = nullptr);
	void switch_back();

	// Getter
	inline callback_t get_callback() const { return _callback; };
	inline void* get_userdata() const { return _userdata; };
	inline bool is_valid() const { return _fiber && _callback; };
};

END_NAME(threading)
END_NAME(mtl)
END_ENGINE