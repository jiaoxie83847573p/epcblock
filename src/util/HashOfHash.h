#pragma once
#include <xdr/epc-types.h>

namespace std
{
template <> struct hash<epc::uint256>
{
    size_t operator()(epc::uint256 const& x) const noexcept;
};
}
