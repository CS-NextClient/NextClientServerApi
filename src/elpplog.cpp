#include "elpplog.h"

#define MAGIC_ENUM_RANGE_MIN 0
#define MAGIC_ENUM_RANGE_MAX 1024
#include <magic_enum/magic_enum.hpp>
#include <easylogging++.h>

#include <cssdk/public/rehlds.h>
#include <amxx/api.h>
#include <metamod/api.h>
#include <metamod/engine.h>
#include <core/rehlds_api.h>

#include "AmxContextGuard.h"
#include "utils/string_utils.h"

INITIALIZE_EASYLOGGINGPP

static bool IsHighSeverity(el::Level level)
{
    return level == el::Level::Warning || level == el::Level::Error || level == el::Level::Fatal;
}

static void LogMessage(const char* format, ...)
{
    char buffer[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    if (core::rehlds_api::ServerStatic()->IsLogActive())
    {
        metamod::engine::AlertMessage(cssdk::AlertType::Logged, "[%s] %s\n", amxx::MODULE_LOG_TAG, buffer);
    }
    else
    {
        amxx::PrintConsole("[%s] %s\n", amxx::MODULE_LOG_TAG, buffer);
    }
}

class LogAppender : public el::LogDispatchCallback
{
protected:
    void handle(const el::LogDispatchData* data) noexcept override
    {
        if (data->logMessage()->logger()->id() != el::base::consts::kDefaultLoggerId)
        {
            return;
        }

        std::string message = data->logMessage()->message();
        std::string func = data->logMessage()->func();
        el::Level level = data->logMessage()->level();

        if (level == el::Level::Error && g_CurrentAmx != nullptr)
        {
            amxx::LogError(g_CurrentAmx, AmxError::Native, "[ERROR] [%s] %s", func.c_str(), message.c_str());
            return;
        }

        std::string level_str = magic_enum::enum_name(level).data();
        str_utils::to_upper(level_str);

        if (level == el::Level::Info)
        {
            LogMessage("%s", message.c_str());
        }
        else if (IsHighSeverity(level))
        {
            LogMessage("[%s] [%s] %s", level_str.c_str(), func.c_str(), message.c_str());
        }
        else
        {
            LogMessage("[%s] %s", level_str.c_str(), message.c_str());
        }
    }
};

void ConfigureElppLogger()
{
    el::Configurations config;
    config.setToDefault();
    config.set(el::Level::Global, el::ConfigurationType::Enabled, "true");
    config.set(el::Level::Global, el::ConfigurationType::ToStandardOutput, "false");
    config.set(el::Level::Global, el::ConfigurationType::ToFile, "false");

    el::Loggers::reconfigureLogger(el::base::consts::kDefaultLoggerId, config);

    el::Helpers::installLogDispatchCallback<LogAppender>("LogAppender");
}
