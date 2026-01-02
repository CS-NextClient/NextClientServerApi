#pragma once
#include <unordered_map>
#include "utils/SizeBufWriter.h"

class NclmSizeBufWriter : public SizeBufWriter
{
    const std::unordered_map<uint8_t, uint8_t> escaping_symbols_ =
      {
        { 0x0, '0' },
        { 0xFF, 'm' },
        { '^', '^' }
    };

public:
    explicit NclmSizeBufWriter(sizebuf_t* output_buf, size_t maxsize);

    void Send() override;
};
