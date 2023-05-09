#pragma once

namespace util
{

class NonCopyable
{
public:
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;

protected:
    NonCopyable() = default;
    ~NonCopyable() = default;
};

class NonMoveable
{
public:
    NonMoveable(NonMoveable&&) = delete;
    NonMoveable& operator=(NonMoveable&&) = delete;

protected:
    NonMoveable() = default;
    ~NonMoveable() = default;
};

}
