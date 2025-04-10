#pragma once

#include <algorithm>
#include <cfloat>
#include <random>

namespace Toon
{
    // 根据数值类型自动选择整数/实数均匀分布的类型萃取模板
    // 使用std::conditional在编译时判断类型是否为整数类型
    template<typename NumericType>
    using uniform_distribution = typename std::conditional<std::is_integral<NumericType>::value,
        std::uniform_int_distribution<NumericType>,
        std::uniform_real_distribution<NumericType>>::type;

    // 通用随机数生成器模板类
    // 模板参数RandomEngine可指定随机数引擎，默认为std::default_random_engine
    template<typename RandomEngine = std::default_random_engine>
    class RandomNumberGenerator
    {
    private:
        RandomEngine m_engine; // 内部存储的随机数引擎实例

    public:
        // 完美转发构造函数，支持任意类型参数的引擎初始化
        template<typename... Params>
        explicit RandomNumberGenerator(Params&&... params) : m_engine(std::forward<Params>(params)...)
        {
        }

        // 种子设置接口，支持多参数种子初始化
        template<typename... Params>
        void seed(Params&&... seeding)
        {
            m_engine.seed(std::forward<Params>(seeding)...);
        }

        // 通用分布生成方法
        // 模板参数DistributionFunc指定分布类型，Params为分布构造参数
        template<typename DistributionFunc, typename... Params>
        typename DistributionFunc::result_type distribution(Params&&... params)
        {
            DistributionFunc dist(std::forward<Params>(params)...); // 构造临时分布对象
            return dist(m_engine); // 通过引擎生成随机数
        }

        // 自动类型均匀分布生成器
        // 通过uniform_distribution类型萃取自动选择分布类型
        template<typename NumericType>
        NumericType uniformDistribution(NumericType lower, NumericType upper)
        {
            if (lower == upper)  // 边界相等时的短路返回
            {
                return lower;
            }
            return distribution<uniform_distribution<NumericType>>(lower, upper);
        }

        // 生成[0,1)范围的浮点数
        // 使用std::nextafter确保1.0的上界为exclusive
        float uniformUnit() { return uniformDistribution(0.f, std::nextafter(1.f, FLT_MAX)); }

        // 生成[-1,1)范围的对称分布浮点数
        float uniformSymmetry() { return uniformDistribution(-1.f, std::nextafter(1.f, FLT_MAX)); }

        // 伯努利分布生成器
        // 直接包装std::bernoulli_distribution
        bool bernoulliDistribution(float probability) { return distribution<std::bernoulli_distribution>(probability); }

        // 正态分布生成器
        // 显式指定float类型正态分布
        float normalDistribution(float mean, float stddev)
        {
            return distribution<std::normal_distribution<float>>(mean, stddev);
        }

        // 范围生成器模板方法
        // 使用std::generate填充指定范围的元素
        template<typename DistributionFunc, typename Range, typename... Params>
        void generator(Range&& range, Params&&... params)
        {
            DistributionFunc dist(std::forward<Params>(params)...); // 构造分布对象
            return std::generate(std::begin(range), std::end(range), [&] { return dist(m_engine); });
        }
    };

    // 预绑定分布的随机数生成器模板类
    // DistributionFunc为绑定的分布类型，SeedType为种子类型
    template<typename DistributionFunc,
        typename RandomEngine = std::default_random_engine,
        typename SeedType = std::seed_seq>
    class DistRandomNumberGenerator
    {
        using ResultType = typename DistributionFunc::result_type; // 分布结果类型别名

    private:
        RandomEngine      m_engine;   // 随机数引擎
        DistributionFunc* m_dist = nullptr; // 堆分配的分布对象指针

    public:
        // 构造函数接受种子序列，注释中的params参数被保留但不使用
        template<typename... Params>
        explicit DistRandomNumberGenerator(SeedType&& seeding, Params&&...  /*params*/) : m_engine(seeding)
        {
            // 分布对象创建逻辑被注释，需根据实际需求实现
        }

        ~DistRandomNumberGenerator() { CHAOS_DELETE_T(m_dist); } // 自定义内存释放宏

        // 种子重置接口
        template<typename... Params>
        void seed(Params&&... params)
        {
            m_engine.seed(std::forward<Params>(params)...);
        }

        // 生成下一个随机数
        ResultType next() { return (*m_dist)(m_engine); }
    };

    // 默认随机数生成器类型别名
    // 使用mt19937引擎，适合高性能需求场景
    using DefaultRNG = RandomNumberGenerator<std::mt19937>;
}
