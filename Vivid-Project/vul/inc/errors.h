#pragma once

namespace vul
{
	/// Error enum encapsulates all errors from `vul`.
	enum class error : int
	{
		failure = 0,				///< Failure. Is considered an error too.
		success = 1,				///< Success.
		value_empty = -0x001,		///< An empty (e.g. nullptr) value was given.
		context_mismatch = -0x002,	///< The context doesn't match.
		di_value_error = -0x100,	///< DI: Failed to change value.

	};
	///Encapsulates errors in a convenience wrapper.
	class e
	{
	private:
		int _error;
	public:
		///By default there is no error.
		e(): _error((int)error::success) {}
		e(const e& other) = default;
		e(e&& other) = default;
		///Convert from error enum.
		e(error err) : _error((int)err) {}
		///Convert from error value.
		e(int err) : _error(err) {}

		e& operator =(const e& other) = default;
		e& operator =(e&& other) = default;
		///Get error value from class.
		operator int() const { return _error; }
		///Check if no error occured.
		operator bool() const { return _error == (int)error::success; }
		///Compare error with another.
		bool operator ==(const e& other) const { return _error == other._error; }
		///Compare error with an error enum.
		bool operator ==(const error& other) const { return _error == (int)other; }
		///Compare error with an error value.
		bool operator ==(const int& other) const { return _error == other; }
	};
	///Compare error value with an error enum.
	bool operator ==(const error& l, const int& r);
}