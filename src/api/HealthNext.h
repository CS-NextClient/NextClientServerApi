#pragma once

#include <events.h>

class HealthNext : public IEventServerActivated,
                   public IEventMessageBeginPost,
                   public IEventMessageEndPost
{
    int message_HealthNEx_{};
    int message_Health_{};

    bool should_send_health_ex_{};
    int msg_save_hp_{};
    int msg_save_dest_{};
    float msg_save_origin_[3]{};
    edict_t* msg_save_ed_{};

public:
    void OnServerActivated(edict_t* pEdictList, int edictCount, int clientMax) override;
    void OnMessageBeginPost(int msg_dest, int msg_type, const float *pOrigin, edict_t *ed) override;
    void OnMessageEndPost() override;
};
