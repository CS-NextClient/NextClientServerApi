#include "asserts.h"

static std::string g_MessageError;

void NApiAssert_SetError(const std::string& text)
{
    g_MessageError = text;
}

bool NApiAssert_ReadAndClearError(std::string& text)
{
    if (g_MessageError.length() == 0)
        return false;

    text = g_MessageError;
    g_MessageError.clear();

    return true;
}