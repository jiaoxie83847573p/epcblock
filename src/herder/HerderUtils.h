#pragma once

// Copyright 2017 epc Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "xdr/epc-types.h"
#include <vector>

namespace epc
{

struct SCPEnvelope;
struct SCPStatement;
struct epcValue;

std::vector<Hash> getTxSetHashes(SCPEnvelope const& envelope);
std::vector<epcValue> getepcValues(SCPStatement const& envelope);
}
