#pragma once
#include <unordered_map>

#include <cssdk/public/rehlds/common_rehlds.h>

#include "utils/SizeBufWriter.h"

class NclmSizeBufWriter : public SizeBufWriter
{
    // clang-format off
    const std::unordered_map<uint8_t, uint8_t> escaping_symbols_ = {
        { 0x0, '0' },
        { 0xFF, 'm' },
        { '^', '^' }
    };
    // clang-format on

public:
    explicit NclmSizeBufWriter(cssdk::SizeBuf* output_buf, size_t maxsize);

    void Send() override;
};
