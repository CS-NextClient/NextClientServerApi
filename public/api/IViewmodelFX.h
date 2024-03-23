#pragma once

class IViewmodelFX {
public:
	virtual ~IViewmodelFX() = default;

	virtual void Begin(int client) = 0;
	virtual void End() = 0;

	virtual void WriteRenderMode(int rendermode) = 0;
	virtual void WriteRenderAmt(int renderamt) = 0;
	virtual void WriteRenderColor(int r, int g, int b) = 0;
	virtual void WriteRenderFX(int renderfx) = 0;
	virtual void WriteSkin(int skin) = 0;
	virtual void WriteBody(int body) = 0;
};
