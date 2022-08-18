#pragma once

#include <tuple>

template<typename TBuildType, typename... TArgs>
class BuilderAbstract {
    using ArgTuple = std::tuple<TArgs...>;
public:
    BuilderAbstract(TArgs ...args)
        : m_params(args...)
    {}

    virtual ~BuilderAbstract() = default;

    TBuildType getInstance() {
        return std::make_from_tuple<TBuildType>(m_params);
    }
private:
    const ArgTuple m_params;
};
