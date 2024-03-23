#pragma once

#include <vector>
#include <stddef.h>
#include "rehlds_api_provider.h"

class SizeBufWriter {
	sizebuf_t* output_buf_;
	sizebuf_t temp_buf_;
	size_t maxsize_;
	std::vector<uint8_t> temp_buf_data_;

protected:
	std::vector<uint8_t> GetTempBufCurSizeSlice() {
		return std::vector<uint8_t>(
			temp_buf_data_.begin(), temp_buf_data_.begin() + temp_buf_.cursize
		);
	}

	void ReplaceTempBufWithSlice(std::vector<uint8_t>& slice) {
		if(slice.size() > maxsize_) MF_Log("%s: overflow");

		temp_buf_data_.assign(slice.begin(), slice.end());
		temp_buf_data_.resize(maxsize_);

		temp_buf_.cursize = slice.size();
	}

	sizebuf_t* GetTempSizeBuf() {
		return &temp_buf_;
	}	

	sizebuf_t* GetOutputSizeBuf() {
		return output_buf_;
	}

public:
	SizeBufWriter(sizebuf_t* output_buf, size_t maxsize)
		: output_buf_(output_buf), maxsize_(maxsize) {
		temp_buf_data_.resize(maxsize);

		temp_buf_.buffername = "SizeBufWriter::temp_buf_";
		temp_buf_.data = temp_buf_data_.data();
		temp_buf_.maxsize = maxsize;
		temp_buf_.cursize = 0;
		temp_buf_.flags = SIZEBUF_ALLOW_OVERFLOW;
	}
	~SizeBufWriter() { }

	SizeBufWriter* WriteByte(uint8_t data) {
		g_RehldsFuncs->MSG_WriteByte(&temp_buf_, data);
		return this;
	}

	SizeBufWriter* WriteString(std::string data) {
		g_RehldsFuncs->MSG_WriteString(&temp_buf_, data.c_str());
		return this;
	}

	SizeBufWriter* WriteLong(long data) {
		g_RehldsFuncs->MSG_WriteLong(&temp_buf_, data);
		return this;
	}

	SizeBufWriter* WriteBuf(std::vector<uint8_t> data) {
		g_RehldsFuncs->MSG_WriteBuf(&temp_buf_, data.size(), data.data());
		return this;
	}

	virtual void Send() {
		g_RehldsFuncs->MSG_WriteBuf(output_buf_, temp_buf_.cursize, temp_buf_.data);
	}
};