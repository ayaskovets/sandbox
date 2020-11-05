#pragma once

class NonCopyAble
{
public:
    NonCopyAble(const NonCopyAble&) = delete;
    NonCopyAble& operator=(const NonCopyAble&) = delete;

protected:
    NonCopyAble() = default;
    ~NonCopyAble() = default;
};

class NonMoveAble
{
public:
    NonMoveAble(NonMoveAble&&) = delete;
    NonMoveAble& operator=(NonMoveAble&&) = delete;

protected:
    NonMoveAble() = default;
    ~NonMoveAble() = default;
};

class NonCopyMoveAble
{
public:
    NonCopyMoveAble(const NonCopyMoveAble&) = delete;
    NonCopyMoveAble(NonCopyMoveAble&&) = delete;
    NonCopyMoveAble& operator=(const NonCopyMoveAble&) = delete;
    NonCopyMoveAble& operator=(NonCopyMoveAble&&) = delete;

protected:
    NonCopyMoveAble() = default;
    ~NonCopyMoveAble() = default;
};
