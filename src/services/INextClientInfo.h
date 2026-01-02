#pragma once
#include <kangaru/kangaru.hpp>
#include "NextClientVersion.h"
#include "module_types.h"

class INextClientInfo
{
public:
    virtual ~INextClientInfo() = default;
    virtual bool GetNextClientVersion(ClientId client, NextClientVersion& version) = 0;
    virtual bool IsClientReady(ClientId client) = 0;
    virtual int GetSupportedFeatures(ClientId client) = 0;
};

struct INextClientInfoService : kgr::abstract_service<INextClientInfo> {};
