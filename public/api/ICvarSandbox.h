#pragma once

#include <string>

enum SandboxCvar {
	cl_forwardspeed = 0,
	cl_backspeed,
	cl_sidespeed,
	sensitivity,
	gl_fog,
	cl_minmodels,
	viewmodel_disable_shift,
	viewmodel_offset_x,
	viewmodel_offset_y,
	viewmodel_offset_z,
	cl_bobstyle,
	cl_bobcycle,
	cl_bobup,
	cl_bob,
	cl_bobamt_vert,
	cl_bobamt_lat,
	cl_bob_lower_amt,
	cl_rollangle,
	cl_rollspeed,
	viewmodel_lag_scale,
	viewmodel_lag_speed,
	// since Next Client v2.1.4
	cl_crosshair_type,
	cl_crosshair_size,
	cl_crosshair_color,
	cl_crosshair_translucent,
	// since Next Client v2.1.8
	cl_weather,
    // since Next Client v2.1.10
    cl_min_t,
    cl_min_ct,
    cl_corpsestay,
    r_decals,
    // since Next Client v2.2.0
    cl_yawspeed,
    cl_pitchspeed,
	// since Next Client v2.4.0
	cl_fog_density,
    cl_fog_r,
    cl_fog_g,
    cl_fog_b,
    viewmodel_fov
};

class ICvarSandbox
{
public:
    virtual ~ICvarSandbox() = default;

    virtual void Begin(int client) = 0;
    virtual void End() = 0;
    virtual void WriteCvar(SandboxCvar cvar, const std::string& value) = 0;
};