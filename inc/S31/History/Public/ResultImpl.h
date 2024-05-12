#pragma once

#include <memory>

namespace S31::History
{
class ChangeSequenceReport;
class ResultIt;

class ResultItImpl
{
public:
    virtual ~ResultItImpl() noexcept = default;
    virtual std::shared_ptr<ResultItImpl> next() = 0;
    virtual ChangeSequenceReport& data() = 0;
    virtual bool equals(const ResultItImpl& rhs) const = 0;
};

class ResultImpl
{
public:
    virtual ~ResultImpl() noexcept = default;
    virtual ResultIt begin() const = 0;
};

}
