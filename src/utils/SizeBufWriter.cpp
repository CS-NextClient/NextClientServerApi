#include "SizeBufWriter.h"
#include <easylogging++.h>

SizeBufWriter::SizeBufWriter(sizebuf_t* output_buf, size_t maxsize) :
    output_buf_(output_buf),
    maxsize_(maxsize)
{
    temp_buf_data_.resize(maxsize);

    temp_buf_.buffername = "SizeBufWriter::temp_buf_";
    temp_buf_.data = temp_buf_data_.data();
    temp_buf_.maxsize = maxsize;
    temp_buf_.cursize = 0;
    temp_buf_.flags = SIZEBUF_ALLOW_OVERFLOW;
}

void SizeBufWriter::Send()
{
    g_RehldsFuncs->MSG_WriteBuf(output_buf_, temp_buf_.cursize, temp_buf_.data);
}

SizeBufWriter* SizeBufWriter::WriteByte(uint8_t data)
{
    g_RehldsFuncs->MSG_WriteByte(&temp_buf_, data);
    return this;
}

SizeBufWriter* SizeBufWriter::WriteString(std::string_view data)
{
    g_RehldsFuncs->MSG_WriteString(&temp_buf_, data.data());
    return this;
}

SizeBufWriter* SizeBufWriter::WriteLong(long data)
{
    g_RehldsFuncs->MSG_WriteLong(&temp_buf_, data);
    return this;
}

SizeBufWriter* SizeBufWriter::WriteBuf(const std::vector<uint8_t>& data)
{
    g_RehldsFuncs->MSG_WriteBuf(&temp_buf_, data.size(), data.data());
    return this;
}

std::vector<uint8_t> SizeBufWriter::GetTempBufCurSizeSlice()
{
    return std::vector<uint8_t>(
        temp_buf_data_.begin(), temp_buf_data_.begin() + temp_buf_.cursize
    );
}

void SizeBufWriter::ReplaceTempBufWithSlice(std::vector<uint8_t>& slice)
{
    if (slice.size() > maxsize_)
    {
        LOG(ERROR) << "overflow (size: " << slice.size() << ", max: " << maxsize_ << ")";
        return;
    }

    temp_buf_data_.assign(slice.begin(), slice.end());
    temp_buf_data_.resize(maxsize_);

    temp_buf_.cursize = slice.size();
}

sizebuf_t* SizeBufWriter::GetTempSizeBuf()
{
    return &temp_buf_;
}

sizebuf_t* SizeBufWriter::GetOutputSizeBuf() const
{
    return output_buf_;
}
