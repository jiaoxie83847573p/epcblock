// Copyright 2017 epc Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "test/TestPrinter.h"
#include "lib/util/format.h"
#include "test/TestMarket.h"

namespace Catch
{
std::string
StringMaker<epc::OfferState>::convert(epc::OfferState const& os)
{
    return fmt::format(
        "selling: {}, buying: {}, price: {}, amount: {}, type: {}",
        xdr::xdr_to_string(os.selling), xdr::xdr_to_string(os.buying),
        xdr::xdr_to_string(os.price), os.amount,
        os.type == epc::OfferType::PASSIVE ? "passive" : "active");
}

std::string
StringMaker<epc::CatchupRange>::convert(epc::CatchupRange const& cr)
{
    return fmt::format("[{}..{}], applyBuckets: {}", cr.first.first(),
                       cr.first.last(), cr.second);
}

std::string
StringMaker<epc::historytestutils::CatchupPerformedWork>::convert(
    epc::historytestutils::CatchupPerformedWork const& cm)
{
    return fmt::format("{}, {}, {}, {}, {}, {}, {}, {}",
                       cm.mHistoryArchiveStatesDownloaded,
                       cm.mLedgersDownloaded, cm.mLedgersVerified,
                       cm.mLedgerChainsVerificationFailed,
                       cm.mBucketsDownloaded, cm.mBucketsApplied,
                       cm.mTransactionsDownloaded, cm.mTransactionsApplied);
}
}
