#pragma once

#include <string>

class IPrivatePrecache {
public:
	virtual ~IPrivatePrecache() = default;

	virtual int PrecacheModel(const std::string& filepath, const std::string& nclFilepath) = 0;
	virtual int PrecacheSound(const std::string& filepath, const std::string& nclFilepath) = 0;
	virtual bool UploadFile(const std::string& filepath, const std::string& nclFilepath) = 0;
};