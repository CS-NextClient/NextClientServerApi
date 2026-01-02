#include "NclmSizeBufWriter.h"
#include "nclm_proto.h"

NclmSizeBufWriter::NclmSizeBufWriter(sizebuf_t* output_buf, size_t maxsize) :
    SizeBufWriter(output_buf, maxsize)
{
    WriteByte(SVC_NCL_MESSAGE);
    WriteLong(NCLM_HEADER_OLD);
}

void NclmSizeBufWriter::Send()
{
    std::vector<uint8_t> slice = GetTempBufCurSizeSlice();

    for (auto it = slice.begin(); it != slice.end(); it++)
    {
        uint8_t symbol = *it;

        if (escaping_symbols_.count(symbol))
        {
            *it = '^';
            it = slice.insert(it + 1, escaping_symbols_.at(symbol));
        }
    }
    slice.push_back(0);

    ReplaceTempBufWithSlice(slice);
    SizeBufWriter::Send();
}
