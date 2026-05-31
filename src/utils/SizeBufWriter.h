#pragma once
#include <vector>
#include <string>
#include <cssdk/public/rehlds/common_rehlds.h>

class SizeBufWriter
{
    cssdk::SizeBuf* output_buf_{};
    cssdk::SizeBuf temp_buf_{};
    size_t maxsize_{};
    std::vector<uint8_t> temp_buf_data_{};

public:
    explicit SizeBufWriter(cssdk::SizeBuf* output_buf, size_t maxsize);
    virtual ~SizeBufWriter() = default;

    virtual void Send();
    SizeBufWriter& WriteByte(uint8_t data);
    SizeBufWriter& WriteShort(int16_t data);
    SizeBufWriter& WriteUShort(uint16_t data);
    SizeBufWriter& WriteString(const std::string& data);
    SizeBufWriter& WriteLong(uint32_t data);
    SizeBufWriter& WriteBuf(const std::vector<uint8_t>& data);

protected:
    std::vector<uint8_t> GetTempBufCurSizeSlice();
    bool ReplaceTempBufWithSlice(std::vector<uint8_t>& slice);
    cssdk::SizeBuf* GetTempSizeBuf();
    cssdk::SizeBuf* GetOutputSizeBuf() const;
};
