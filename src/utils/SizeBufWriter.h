#pragma once
#include <vector>
#include "rehlds_api_provider.h"

class SizeBufWriter
{
    sizebuf_t* output_buf_{};
    sizebuf_t temp_buf_{};
    size_t maxsize_{};
    std::vector<uint8_t> temp_buf_data_{};

public:
    explicit SizeBufWriter(sizebuf_t* output_buf, size_t maxsize);
    virtual ~SizeBufWriter() = default;

    virtual void Send();
    SizeBufWriter* WriteByte(uint8_t data);
    SizeBufWriter* WriteString(std::string_view data);
    SizeBufWriter* WriteLong(long data);
    SizeBufWriter* WriteBuf(const std::vector<uint8_t>& data);

protected:
    std::vector<uint8_t> GetTempBufCurSizeSlice();
    void ReplaceTempBufWithSlice(std::vector<uint8_t>& slice);
    sizebuf_t* GetTempSizeBuf();
    sizebuf_t* GetOutputSizeBuf() const;
};
