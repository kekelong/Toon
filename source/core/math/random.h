#pragma once

#include <algorithm>
#include <cfloat>
#include <random>

namespace Toon
{
    // ������ֵ�����Զ�ѡ������/ʵ�����ȷֲ���������ȡģ��
    // ʹ��std::conditional�ڱ���ʱ�ж������Ƿ�Ϊ��������
    template<typename NumericType>
    using uniform_distribution = typename std::conditional<std::is_integral<NumericType>::value,
        std::uniform_int_distribution<NumericType>,
        std::uniform_real_distribution<NumericType>>::type;

    // ͨ�������������ģ����
    // ģ�����RandomEngine��ָ����������棬Ĭ��Ϊstd::default_random_engine
    template<typename RandomEngine = std::default_random_engine>
    class RandomNumberGenerator
    {
    private:
        RandomEngine m_engine; // �ڲ��洢�����������ʵ��

    public:
        // ����ת�����캯����֧���������Ͳ����������ʼ��
        template<typename... Params>
        explicit RandomNumberGenerator(Params&&... params) : m_engine(std::forward<Params>(params)...)
        {
        }

        // �������ýӿڣ�֧�ֶ�������ӳ�ʼ��
        template<typename... Params>
        void seed(Params&&... seeding)
        {
            m_engine.seed(std::forward<Params>(seeding)...);
        }

        // ͨ�÷ֲ����ɷ���
        // ģ�����DistributionFuncָ���ֲ����ͣ�ParamsΪ�ֲ��������
        template<typename DistributionFunc, typename... Params>
        typename DistributionFunc::result_type distribution(Params&&... params)
        {
            DistributionFunc dist(std::forward<Params>(params)...); // ������ʱ�ֲ�����
            return dist(m_engine); // ͨ���������������
        }

        // �Զ����;��ȷֲ�������
        // ͨ��uniform_distribution������ȡ�Զ�ѡ��ֲ�����
        template<typename NumericType>
        NumericType uniformDistribution(NumericType lower, NumericType upper)
        {
            if (lower == upper)  // �߽����ʱ�Ķ�·����
            {
                return lower;
            }
            return distribution<uniform_distribution<NumericType>>(lower, upper);
        }

        // ����[0,1)��Χ�ĸ�����
        // ʹ��std::nextafterȷ��1.0���Ͻ�Ϊexclusive
        float uniformUnit() { return uniformDistribution(0.f, std::nextafter(1.f, FLT_MAX)); }

        // ����[-1,1)��Χ�ĶԳƷֲ�������
        float uniformSymmetry() { return uniformDistribution(-1.f, std::nextafter(1.f, FLT_MAX)); }

        // ��Ŭ���ֲ�������
        // ֱ�Ӱ�װstd::bernoulli_distribution
        bool bernoulliDistribution(float probability) { return distribution<std::bernoulli_distribution>(probability); }

        // ��̬�ֲ�������
        // ��ʽָ��float������̬�ֲ�
        float normalDistribution(float mean, float stddev)
        {
            return distribution<std::normal_distribution<float>>(mean, stddev);
        }

        // ��Χ������ģ�巽��
        // ʹ��std::generate���ָ����Χ��Ԫ��
        template<typename DistributionFunc, typename Range, typename... Params>
        void generator(Range&& range, Params&&... params)
        {
            DistributionFunc dist(std::forward<Params>(params)...); // ����ֲ�����
            return std::generate(std::begin(range), std::end(range), [&] { return dist(m_engine); });
        }
    };

    // Ԥ�󶨷ֲ��������������ģ����
    // DistributionFuncΪ�󶨵ķֲ����ͣ�SeedTypeΪ��������
    template<typename DistributionFunc,
        typename RandomEngine = std::default_random_engine,
        typename SeedType = std::seed_seq>
    class DistRandomNumberGenerator
    {
        using ResultType = typename DistributionFunc::result_type; // �ֲ�������ͱ���

    private:
        RandomEngine      m_engine;   // ���������
        DistributionFunc* m_dist = nullptr; // �ѷ���ķֲ�����ָ��

    public:
        // ���캯�������������У�ע���е�params��������������ʹ��
        template<typename... Params>
        explicit DistRandomNumberGenerator(SeedType&& seeding, Params&&...  /*params*/) : m_engine(seeding)
        {
            // �ֲ����󴴽��߼���ע�ͣ������ʵ������ʵ��
        }

        ~DistRandomNumberGenerator() { CHAOS_DELETE_T(m_dist); } // �Զ����ڴ��ͷź�

        // �������ýӿ�
        template<typename... Params>
        void seed(Params&&... params)
        {
            m_engine.seed(std::forward<Params>(params)...);
        }

        // ������һ�������
        ResultType next() { return (*m_dist)(m_engine); }
    };

    // Ĭ����������������ͱ���
    // ʹ��mt19937���棬�ʺϸ��������󳡾�
    using DefaultRNG = RandomNumberGenerator<std::mt19937>;
}
