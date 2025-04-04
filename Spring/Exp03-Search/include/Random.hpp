#pragma once
#include <random>
#include <vector>

template<class _ValTy>
    requires std::is_same<_ValTy, int>::value || std::is_same<_ValTy, long long>::value || std::is_same<_ValTy, double>::value
class Rand_Uniform
{
public:
    inline _ValTy operator()(_ValTy min, _ValTy max) const
    {
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(_engine);
    }

    std::vector<_ValTy> generateVec(size_t size, _ValTy min, _ValTy max) const
    {
        std::vector<_ValTy> vec;
        while (size--) { vec.push_back(this->operator()(min, max)); }
        return vec;
    }

private:
    static std::random_device _rd;
    static std::default_random_engine _engine;
};

template<class _ValTy>
    requires std::is_same<_ValTy, int>::value || std::is_same<_ValTy, long long>::value || std::is_same<_ValTy, double>::value
std::random_device Rand_Uniform<_ValTy>::_rd{};
template<class _ValTy>
    requires std::is_same<_ValTy, int>::value || std::is_same<_ValTy, long long>::value || std::is_same<_ValTy, double>::value
std::default_random_engine Rand_Uniform<_ValTy>::_engine{ _rd() };

template<class _ValTy>
    requires std::is_same<_ValTy, int>::value || std::is_same<_ValTy, long long>::value || std::is_same<_ValTy, double>::value
class Rand_Normal
{
public:
    inline _ValTy operator()(double mean, double sigma) const
    {
        std::normal_distribution<double> distribution(mean, sigma);
        return static_cast<_ValTy>(distribution(_engine));
    }

    std::vector<_ValTy> generateVec(size_t size, _ValTy mean, _ValTy sigma) const
    {
        std::vector<_ValTy> vec;
        while (size--) { vec.push_back(this->operator()(mean, sigma)); }
        return vec;
    }

private:
    static std::random_device _rd;
    static std::default_random_engine _engine;
};

template<class _ValTy>
    requires std::is_same<_ValTy, int>::value || std::is_same<_ValTy, long long>::value || std::is_same<_ValTy, double>::value
std::random_device Rand_Normal<_ValTy>::_rd{};
template<class _ValTy>
    requires std::is_same<_ValTy, int>::value || std::is_same<_ValTy, long long>::value || std::is_same<_ValTy, double>::value
std::default_random_engine Rand_Normal<_ValTy>::_engine{ _rd() };