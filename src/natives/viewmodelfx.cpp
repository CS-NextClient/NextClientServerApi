#include "main.h"
#include "amxxmodule.h"
#include "asserts.h"

cell AMX_NATIVE_CALL ncl_viewmodelfx_begin(AMX* amx, cell* params)
{
    enum args_e
    {
        arg_count,
        arg_index
    };
    ASSERT_ARG_IS_PLAYER(arg_index);

    NAPI()->ViewmodelFX()->Begin(params[arg_index]);

    ASSERT_NO_NAPI_ERRORS();
    return TRUE;
}

cell AMX_NATIVE_CALL ncl_viewmodelfx_end(AMX* amx, cell* params)
{
    NAPI()->ViewmodelFX()->End();

    ASSERT_NO_NAPI_ERRORS();
    return TRUE;
}

cell AMX_NATIVE_CALL ncl_write_rendermode(AMX* amx, cell* params)
{
    enum args_e
    {
        arg_count,
        arg_rendermode
    };

    NAPI()->ViewmodelFX()->WriteRenderMode(params[arg_rendermode]);

    ASSERT_NO_NAPI_ERRORS();
    return TRUE;
}

cell AMX_NATIVE_CALL ncl_write_renderamt(AMX* amx, cell* params)
{
    enum args_e
    {
        arg_count,
        arg_renderamt
    };

    NAPI()->ViewmodelFX()->WriteRenderAmt(params[arg_renderamt]);

    ASSERT_NO_NAPI_ERRORS();
    return TRUE;
}

cell AMX_NATIVE_CALL ncl_write_renderfx(AMX* amx, cell* params)
{
    enum args_e
    {
        arg_count,
        arg_renderfx
    };

    NAPI()->ViewmodelFX()->WriteRenderFX(params[arg_renderfx]);

    ASSERT_NO_NAPI_ERRORS();
    return TRUE;
}

cell AMX_NATIVE_CALL ncl_write_renderskin(AMX* amx, cell* params)
{
    enum args_e
    {
        arg_count,
        arg_skin
    };

    NAPI()->ViewmodelFX()->WriteSkin(params[arg_skin]);

    ASSERT_NO_NAPI_ERRORS();
    return TRUE;
}

cell AMX_NATIVE_CALL ncl_write_renderbody(AMX* amx, cell* params)
{
    enum args_e
    {
        arg_count,
        arg_body
    };

    NAPI()->ViewmodelFX()->WriteBody(params[arg_body]);

    ASSERT_NO_NAPI_ERRORS();
    return TRUE;
}

cell AMX_NATIVE_CALL ncl_write_rendercolor(AMX* amx, cell* params)
{
    enum args_e
    {
        arg_count,
        arg_r,
        arg_g,
        arg_b
    };

    NAPI()->ViewmodelFX()->WriteRenderColor(params[arg_r], params[arg_g], params[arg_b]);

    ASSERT_NO_NAPI_ERRORS();
    return TRUE;
}

AMX_NATIVE_INFO nativeInfoViewmodelFX[] = {
        {"ncl_viewmodelfx_begin", ncl_viewmodelfx_begin},
        {"ncl_viewmodelfx_end",   ncl_viewmodelfx_end},
        {"ncl_write_rendermode",  ncl_write_rendermode},
        {"ncl_write_renderamt",   ncl_write_renderamt},
        {"ncl_write_renderfx",    ncl_write_renderfx},
        {"ncl_write_renderskin",  ncl_write_renderskin},
        {"ncl_write_renderbody",  ncl_write_renderbody},
        {"ncl_write_rendercolor", ncl_write_rendercolor},

        {nullptr,                 nullptr}
};

void AddNatives_ViewmodelFX()
{
    MF_AddNatives(nativeInfoViewmodelFX);
}