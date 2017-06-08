#pragma once

template <typename T> inline static T* cast(void* ptr) { return reinterpret_cast<T*>(ptr); }