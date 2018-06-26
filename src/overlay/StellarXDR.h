#pragma once
#include "xdr/epc-ledger-entries.h"
#include "xdr/epc-ledger.h"
#include "xdr/epc-overlay.h"
#include "xdr/epc-transaction.h"
#include "xdr/epc-types.h"

namespace epc
{

std::string xdr_printer(const PublicKey& pk);
}
