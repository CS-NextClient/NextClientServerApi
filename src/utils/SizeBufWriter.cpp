#include "SizeBufWriter.h"
#include <easylogging++.h>
#include <core/rehlds_api.h>

using namespace core::rehlds_api;

SizeBufWriter::SizeBufWriter(cssdk::SizeBuf* output_buf, size_t maxsize) :
    output_buf_(output_buf),
    maxsize_(maxsize)
{
    temp_buf_data_.resize(maxsize);

    temp_buf_.buffer_name = "SizeBufWriter::temp_buf_";
    temp_buf_.data = temp_buf_data_.data();
    temp_buf_.max_size = maxsize;
    temp_buf_.cur_size = 0;
    temp_buf_.flags = cssdk::SIZEBUF_ALLOW_OVERFLOW;
}

void SizeBufWriter::Send()
{
    Funcs()->msg_write_buf(output_buf_, temp_buf_.cur_size, temp_buf_.data);
}

SizeBufWriter& SizeBufWriter::WriteByte(uint8_t data)
{
    Funcs()->msg_write_byte(&temp_buf_, data);
    return *this;
}

SizeBufWriter& SizeBufWriter::WriteShort(int16_t data)
{
    Funcs()->msg_write_short(&temp_buf_, data);
    return *this;
}

SizeBufWriter& SizeBufWriter::WriteUShort(uint16_t data)
{
    Funcs()->msg_write_short(&temp_buf_, data);
    return *this;
}

SizeBufWriter& SizeBufWriter::WriteString(const std::string& data)
{
    Funcs()->msg_write_string(&temp_buf_, data.c_str());
    return *this;
}

SizeBufWriter& SizeBufWriter::WriteLong(uint32_t data)
{
    Funcs()->msg_write_long(&temp_buf_, data);
    return *this;
}

SizeBufWriter& SizeBufWriter::WriteBuf(const std::vector<uint8_t>& data)
{
    Funcs()->msg_write_buf(&temp_buf_, data.size(), const_cast<uint8_t*>(data.data()));
    return *this;
}

std::vector<uint8_t> SizeBufWriter::GetTempBufCurSizeSlice()
{
    return std::vector(temp_buf_data_.begin(), temp_buf_data_.begin() + temp_buf_.cur_size);
}

bool SizeBufWriter::ReplaceTempBufWithSlice(std::vector<uint8_t>& slice)
{
    if (slice.size() > maxsize_)
    {
        LOG(ERROR) << "overflow (size: " << slice.size() << ", max: " << maxsize_ << ")";
        temp_buf_.cur_size = 0;
        return false;
    }

    temp_buf_data_.assign(slice.begin(), slice.end());
    temp_buf_data_.resize(maxsize_);

    temp_buf_.cur_size = slice.size();
    return true;
}

cssdk::SizeBuf* SizeBufWriter::GetTempSizeBuf()
{
    return &temp_buf_;
}

cssdk::SizeBuf* SizeBufWriter::GetOutputSizeBuf() const
{
    return output_buf_;
}
