#define MAGIC_ENUM_RANGE_MIN 0
#define MAGIC_ENUM_RANGE_MAX 1024
#include <magic_enum/magic_enum.hpp>
#include <easylogging++.h>
#include "amxxmodule.h"
#include "elpplog.h"
#include "AmxContextGuard.h"
#include "utils/string_utils.h"

INITIALIZE_EASYLOGGINGPP

class EngineLogAppender : public el::LogDispatchCallback
{
protected:
    void handle(const el::LogDispatchData* data) noexcept override
    {
        using namespace el;
        using namespace el::base::type;

        if (data->logMessage()->logger()->id() != base::consts::kDefaultLoggerId)
        {
            return;
        }

        std::string message = data->logMessage()->message();
        std::string func = data->logMessage()->func();
        Level level = data->logMessage()->level();

        if (level == Level::Error && g_CurrentAmx != nullptr)
        {
            MF_LogError(g_CurrentAmx, AMX_ERR_NATIVE, "[ERROR] [%s] %s", func.c_str(), message.c_str());
        }
        else
        {
            std::string level_str = magic_enum::enum_name(level).data();
            str_utils::to_upper(level_str);

            if (level == Level::Warning || level == Level::Error || level == Level::Fatal)
            {
                MF_Log("[%s] [%s] %s", level_str.c_str(), func.c_str(), message.c_str());
            }
            else
            {
                MF_Log("[%s] %s", level_str.c_str(), message.c_str());
            }
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

    el::Helpers::installLogDispatchCallback<EngineLogAppender>("EngineLogAppender");
}
