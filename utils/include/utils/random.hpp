#pragma once

#include <random>
#include <vector>

namespace utils
{

template <class T>
class RandUniform
{
public:
    inline T operator()(T min, T max) const
    {
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(_engine);
    }

    std::vector<T> generateVec(size_t size, T min, T max) const
    {
        std::vector<T> vec;
        while (size--) {
            vec.push_back(this->operator()(min, max));
        }
        return vec;
    }

private:
    static std::random_device _rd;
    static std::default_random_engine _engine;
};

template <class T>
std::random_device RandUniform<T>::_rd{};

template <class T>
std::default_random_engine RandUniform<T>::_engine{_rd()};

template <class T>
class RandNormal
{
public:
    inline T operator()(double mean, double sigma) const
    {
        std::normal_distribution<double> distribution(mean, sigma);
        return static_cast<T>(distribution(_engine));
    }

    std::vector<T> generateVec(size_t size, T mean, T sigma) const
    {
        std::vector<T> vec;
        while (size--) {
            vec.push_back(this->operator()(mean, sigma));
        }
        return vec;
    }

private:
    static std::random_device _rd;
    static std::default_random_engine _engine;
};

template <class _ValTy>
std::random_device RandNormal<_ValTy>::_rd{};
template <class _ValTy>
std::default_random_engine RandNormal<_ValTy>::_engine{_rd()};

}  // namespace utils