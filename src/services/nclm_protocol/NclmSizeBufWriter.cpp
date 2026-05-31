#include "NclmSizeBufWriter.h"

#include "nclm_proto.h"

NclmSizeBufWriter::NclmSizeBufWriter(cssdk::SizeBuf* output_buf, size_t maxsize) :
    SizeBufWriter(output_buf, maxsize)
{
    WriteByte(SVC_NCL_MESSAGE);
    WriteLong(NCLM_HEADER_OLD);
}

void NclmSizeBufWriter::Send()
{
    std::vector<uint8_t> slice = GetTempBufCurSizeSlice();
    std::vector<uint8_t> escaped_slice;
    escaped_slice.reserve(slice.size() * 11 / 10); // reserve 10% extra space to avoid allocations

    for (uint8_t symbol : slice)
    {
        auto it = escaping_symbols_.find(symbol);
        if (it != escaping_symbols_.end())
        {
            escaped_slice.push_back('^');
            escaped_slice.push_back(it->second);
        }
        else
        {
            escaped_slice.push_back(symbol);
        }
    }
    escaped_slice.push_back(0);

    if (!ReplaceTempBufWithSlice(escaped_slice))
    {
        return;
    }
    SizeBufWriter::Send();
}
