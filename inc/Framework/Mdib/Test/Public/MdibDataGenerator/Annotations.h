#pragma once

#include <Framework/Mdib/Public/Model/Metric/Sample.h>
#include <Framework/Mdib/Public/Model/Metric/Annotation.h>
#include <Framework/Mdib/Public/Model/CodedValueFactory.h>

#include <memory>

namespace DFL
{
namespace Mdib
{
namespace Test
{

/**
 * @brief Base class to add annotations to sample.
 */
class AnnotationAdder
{
    public:
        /**
         * @brief Destructor.
         */
        virtual ~AnnotationAdder() noexcept = default;

        /**
         * @brief Adds annotations to the sample.
         */
        virtual Sample add(Sample&& s) = 0;
};

using AnnotationAdderPtr = std::unique_ptr<AnnotationAdder>;

/**
 * @brief Gives from time to time an ECG annotation.
 */
class AnnotationAdderSomeECG: public AnnotationAdder
{
    public:
        /**
         * @brief Adds annotations to the sample.
         */
        Sample add(Sample&& s) override
        {
            m_counter++;
            if (m_counter % 300 == 0)
            {
                return Sample(s.value(), Annotations{Annotation::MDC_EVT_ECG_PACED_BEAT});
            }
            if (m_counter % 500 == 0)
            {
                // Missed beat within some regular ECG rhythm - MDC_EVT_ECG_BEAT_MISSED - 3078
                // 3 * pow(2,16) + 3078 = 199686
                return Sample(s.value(), Annotations{CodedValueFactory::create11073Annotation("199686")});
            }
            return std::move(s);
        }

    private:
        unsigned int m_counter = 0;
};

/**
 * @brief Gives 10% of the samples an INVALID annotation (in continuous blocks).
 */
class AnnotationAdderSomeInvalid: public AnnotationAdder
{
    public:
        /**
         * @brief Adds annotations to the sample.
         */
        Sample add(Sample&& s) override
        {
            m_counter++;
            if ((m_counter / 10) % 10 == 0)
            {
                return Sample(s.value(), Annotations{Annotation::MDC_EVT_FLAG_INVALID});
            }
            return std::move(s);
        }

    private:
        unsigned int m_counter = 0;
};


}
}
}
