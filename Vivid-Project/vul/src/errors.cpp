#include "errors.h"

bool vul::operator ==(const vul::error& l, const int& r) { return (int)l == r; }