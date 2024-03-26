#define M_PI       3.14159265358979323846

typedef struct
{
	DWORD R;
	DWORD G;
	DWORD B;
	DWORD A;
}RGBA;

class Color
{
public:
	RGBA red = { 255,0,0,255 };
	RGBA Magenta = { 255,0,255,255 };
	RGBA yellow = { 255,255,0,255 };
	RGBA grayblue = { 128,128,255,255 };
	RGBA green = { 128,224,0,255 };
	RGBA darkgreen = { 0,224,128,255 };
	RGBA brown = { 192,96,0,255 };
	RGBA pink = { 255,168,255,255 };
	RGBA DarkYellow = { 216,216,0,255 };
	RGBA SilverWhite = { 236,236,236,255 };
	RGBA purple = { 144,0,255,255 };
	RGBA Navy = { 88,48,224,255 };
	RGBA skyblue = { 0,136,255,255 };
	RGBA graygreen = { 128,160,128,255 };
	RGBA blue = { 0,96,192,255 };
	RGBA orange = { 255,128,0,255 };
	RGBA peachred = { 255,80,128,255 };
	RGBA reds = { 255,128,192,255 };
	RGBA darkgray = { 96,96,96,255 };
	RGBA Navys = { 0,0,128,255 };
	RGBA darkgreens = { 0,128,0,255 };
	RGBA darkblue = { 0,128,128,255 };
	RGBA redbrown = { 128,0,0,255 };
	RGBA purplered = { 128,0,128,255 };
	RGBA greens = { 0,255,0,255 };
	RGBA envy = { 0,255,255,255 };
	RGBA black = { 0,0,0,255 };
	RGBA gray = { 128,128,128,255 };
	RGBA white = { 255,255,255,255 };
	RGBA blues = { 30,144,255,255 };
	RGBA lightblue = { 135,206,250,160 };
	RGBA Scarlet = { 220, 20, 60, 160 };
	RGBA white_ = { 255,255,255,200 };
	RGBA whitefull = { 255,255,255,255 };
	RGBA gray_ = { 128,128,128,200 };
	RGBA black_ = { 0,0,0,200 };
	RGBA red_ = { 255,0,0,200 };
	RGBA Magenta_ = { 255,0,255,200 };
	RGBA yellow_ = { 255,255,0,200 };
	RGBA grayblue_ = { 128,128,255,200 };
	RGBA green_ = { 128,224,0,200 };
	RGBA darkgreen_ = { 0,224,128,200 };
	RGBA brown_ = { 192,96,0,200 };
	RGBA pink_ = { 255,168,255,200 };
	RGBA darkyellow_ = { 216,216,0,200 };
	RGBA silverwhite_ = { 236,236,236,200 };
	RGBA purple_ = { 144,0,255,200 };
	RGBA Blue_ = { 88,48,224,200 };
	RGBA skyblue_ = { 0,136,255,200 };
	RGBA graygreen_ = { 128,160,128,200 };
	RGBA blue_ = { 0,96,192,200 };
	RGBA orange_ = { 255,128,0,200 };
	RGBA pinks_ = { 255,80,128,200 };
	RGBA Fuhong_ = { 255,128,192,200 };
	RGBA darkgray_ = { 96,96,96,200 };
	RGBA Navy_ = { 0,0,128,200 };
	RGBA darkgreens_ = { 0,128,0,200 };
	RGBA darkblue_ = { 0,128,128,200 };
	RGBA redbrown_ = { 128,0,0,200 };
	RGBA purplered_ = { 128,0,128,200 };
	RGBA greens_ = { 0,255,0,200 };
	RGBA envy_ = { 0,255,255,200 };

	RGBA glassblack = { 0, 0, 0, 160 };
	RGBA GlassBlue = { 65,105,225,80 };
	RGBA glassyellow = { 255,255,0,160 };
	RGBA glass = { 200,200,200,60 };

	RGBA filled = { 0, 0, 0, 150 };

	RGBA Plum = { 221,160,221,160 };

};
Color Col;

std::string string_To_UTF8(const std::string& str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t* pwBuf = new wchar_t[nwLen + 1];
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}
std::string WStringToUTF8(const wchar_t* lpwcszWString)
{
	char* pElementText;
	int iTextLen = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, (iTextLen + 1) * sizeof(char));
	::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, pElementText, iTextLen, NULL, NULL);
	std::string strReturn(pElementText);
	delete[] pElementText;
	return strReturn;
}
std::wstring MBytesToWString(const char* lpcszString)
{
	int len = strlen(lpcszString);
	int unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, NULL, 0);
	wchar_t* pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, (LPWSTR)pUnicode, unicodeLen);
	std::wstring wString = (wchar_t*)pUnicode;
	delete[] pUnicode;
	return wString;
}

void DrawStrokeText(int x, int y, RGBA* color, const char* str)
{
	ImFont a;
	std::string utf_8_1 = std::string(str);
	std::string utf_8_2 = string_To_UTF8(utf_8_1);
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x - 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x + 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), utf_8_2.c_str());
}
void DrawStrokeText2(int x, int y, RGBA* color, const std::string str)
{
	ImFont a;
	std::string utf_8_1 = std::string(str);
	std::string utf_8_2 = string_To_UTF8(utf_8_1);
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x - 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x + 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), utf_8_2.c_str());
}
void DrawNewText(int x, int y, RGBA* color, const char* str)
{
	ImFont a;
	std::string utf_8_1 = std::string(str);
	std::string utf_8_2 = string_To_UTF8(utf_8_1);
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), utf_8_2.c_str());
}
void DrawRect(int x, int y, int w, int h, RGBA* color, int thickness)
{
	ImGui::GetOverlayDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), 0, 0, thickness);
}
void DrawFilledRect2(const ImVec2& v1, const ImVec2& v2, const ImColor& color)
{
	ImGui::GetOverlayDrawList()->AddRectFilled(v1, ImVec2(v1.x + v2.x, v1.y + v2.y), color, 0, 0);
}
void Border(float x, float y, float w, float h, const ImColor& color)
{
	ImGui::GetOverlayDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::GetColorU32(ImVec4(color.Value.x, color.Value.y, color.Value.z, color.Value.w)), 2, 0, 2);
}
void DrawFilledRect(int x, int y, int w, int h, RGBA* color)
{
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), 0, 0);
}
void DrawLeftProgressBar(int x, int y, int w, int h, int thick, int m_health)
{
	int G = (255 * m_health / 100);
	int R = 255 - G;
	RGBA healthcol = { R, G, 0, 255 };

	DrawFilledRect(x - (w / 2) - 3, y, thick, (h)*m_health / 100, &healthcol);
}
void DrawRightProgressBar(int x, int y, int w, int h, int thick, int m_health)
{
	int G = (255 * m_health / 100);
	int R = 255 - G;
	RGBA healthcol = { R, G, 0, 255 };

	DrawFilledRect(x + (w / 2) - 25, y, thick, (h)*m_health / 100, &healthcol);
}

void DrawCircle(const ImVec2& position, float radius, const ImColor& color, float thickness)
{
	ImGui::GetOverlayDrawList()->AddCircle(position, radius, ImGui::GetColorU32(ImVec4(color.Value.x, color.Value.y, color.Value.z, color.Value.w)), 30, thickness);
}


void DrawString(float fontSize, int x, int y, RGBA* color, bool bCenter, bool stroke, const char* pText, ...)
{
	va_list va_alist;
	char buf[1024] = { 0 };
	va_start(va_alist, pText);
	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
	va_end(va_alist);
	std::string text = WStringToUTF8(MBytesToWString(buf).c_str());
	if (bCenter)
	{
		ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
		x = x - textSize.x / 2;
		y = y - textSize.y;
	}
	if (stroke)
	{
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
	}
	ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), text.c_str());
}
void DrawStringS(float fontSize, int x, int y, RGBA* color, bool bCenter, bool stroke, std::string str, ...)
{
	va_list va_alist;
	char buf[1024] = { 0 };
	std::string text = str;
	if (bCenter)
	{
		ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
		x = x - textSize.x / 2;
		y = y - textSize.y;
	}
	if (stroke)
	{
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
	}
	ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), text.c_str());
}
void DrawCircleFilled(int x, int y, int radius, RGBA* color)
{
	ImGui::GetOverlayDrawList()->AddCircleFilled(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)));
}
void DrawCircle(int x, int y, int radius, RGBA* color, int segments)
{
	ImGui::GetOverlayDrawList()->AddCircle(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), segments);
}
void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, RGBA* color, float thickne)
{
	ImGui::GetOverlayDrawList()->AddTriangle(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), thickne);
}
void DrawTriangleFilled(int x1, int y1, int x2, int y2, int x3, int y3, RGBA* color)
{
	ImGui::GetOverlayDrawList()->AddTriangleFilled(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)));
}

void DrawLine4D(int x1, int y1, int x2, int y2, RGBA* color, int thickness)
{
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), thickness);
}

void DrawLine(int x1, int y1, int x2, int y2, RGBA* color, int thickness)
{
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), thickness);
}
void DrawCornerBox(int x, int y, int w, int h, int borderPx, RGBA* color)
{
	DrawFilledRect(x + borderPx, y, w / 3, borderPx, color); //top 
	DrawFilledRect(x + w - w / 3 + borderPx, y, w / 3, borderPx, color); //top 
	DrawFilledRect(x, y, borderPx, h / 3, color); //left 
	DrawFilledRect(x, y + h - h / 3 + borderPx * 2, borderPx, h / 3, color); //left 
	DrawFilledRect(x + borderPx, y + h + borderPx, w / 3, borderPx, color); //bottom 
	DrawFilledRect(x + w - w / 3 + borderPx, y + h + borderPx, w / 3, borderPx, color); //bottom 
	DrawFilledRect(x + w + borderPx, y, borderPx, h / 3, color);//right 
	DrawFilledRect(x + w + borderPx, y + h - h / 3 + borderPx * 2, borderPx, h / 3, color);//right 
}
void DrawNormalBox(int x, int y, int w, int h, int borderPx, RGBA* color)
{
	DrawFilledRect(x + borderPx, y, w, borderPx, color); //top 
	DrawFilledRect(x + w - w + borderPx, y, w, borderPx, color); //top 
	DrawFilledRect(x, y, borderPx, h, color); //left 
	DrawFilledRect(x, y + h - h + borderPx * 2, borderPx, h, color); //left 
	DrawFilledRect(x + borderPx, y + h + borderPx, w, borderPx, color); //bottom 
	DrawFilledRect(x + w - w + borderPx, y + h + borderPx, w, borderPx, color); //bottom 
	DrawFilledRect(x + w + borderPx, y, borderPx, h, color);//right 
	DrawFilledRect(x + w + borderPx, y + h - h + borderPx * 2, borderPx, h, color);//right 
}
void DrawLine2(const ImVec2& from, const ImVec2& to, uint32_t color, float thickness)
{
	float a = (color >> 24) & 0xff;
	float r = (color >> 16) & 0xff;
	float g = (color >> 8) & 0xff;
	float b = (color) & 0xff;
	ImGui::GetOverlayDrawList()->AddLine(from, to, ImGui::GetColorU32(ImVec4(r / 255, g / 255, b / 255, a / 255)), thickness);
}

auto RectFilled(float x0, float y0, float x1, float y1, ImColor color, float rounding, int rounding_corners_flags)-> VOID
{
	auto vList = ImGui::GetOverlayDrawList();
	vList->AddRectFilled(ImVec2(x0, y0), ImVec2(x1, y1), color, rounding, rounding_corners_flags);
}


static void DrawPlayerBar(int x, int y, RGBA* back_color, RGBA* main_color, RGBA* line_color, const char* pText, ...)
{
	va_list va_alist;
	char buf[1024] = { 0 };
	va_start(va_alist, pText);
	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
	va_end(va_alist);
	std::string text = WStringToUTF8(MBytesToWString(buf).c_str());

	const ImVec2 text_dimension = ImGui::CalcTextSize(text.c_str());
	const float text_width = text_dimension.x + 5.f;
	const float mid_width = x - (text_width / 2.f);
	RGBA green_color = *line_color;

	DrawFilledRect(mid_width + 2.f, y - 25.f, text_width + 10.f, text_dimension.y + 5.f, back_color);
	DrawLine(mid_width, y - 25.f, mid_width, (y - 25.f) + text_dimension.y + 5.f, &green_color, 3.f);
	DrawNewText(mid_width + 6.f, (y - 25.f) + 2.f, main_color, text.c_str());

}

D3DXVECTOR3 RotatePoint(D3DXVECTOR3 EntityPos, D3DXVECTOR3 LocalPlayerPos, int posX, int posY, int sizeX, int sizeY, float angle, float zoom, bool* viewCheck)
{
	float r_1, r_2;
	float x_1, y_1;

	r_1 = -(EntityPos.y - LocalPlayerPos.y);
	r_2 = EntityPos.x - LocalPlayerPos.x;
	float Yaw = angle - 90.0f;

	float yawToRadian = Yaw * (float)(M_PI / 180.0F);
	x_1 = (float)(r_2 * (float)cos((double)(yawToRadian)) - r_1 * sin((double)(yawToRadian))) / 20;
	y_1 = (float)(r_2 * (float)sin((double)(yawToRadian)) + r_1 * cos((double)(yawToRadian))) / 20;

	*viewCheck = y_1 < 0;

	x_1 *= zoom;
	y_1 *= zoom;

	int sizX = sizeX / 2;
	int sizY = sizeY / 2;

	x_1 += sizX;
	y_1 += sizY;

	if (x_1 < 5)
		x_1 = 5;

	if (x_1 > sizeX - 5)
		x_1 = sizeX - 5;

	if (y_1 < 5)
		y_1 = 5;

	if (y_1 > sizeY - 5)
		y_1 = sizeY - 5;


	x_1 += posX;
	y_1 += posY;


	return D3DXVECTOR3(x_1, y_1, 0);
}

void DrawRadarHUD(int xAxis, int yAxis, int width, int height)
{
	//RGBA RadarWOW = D3DCOLOR_XRGB((int)(0.85f * 255), (int)(0.85f * 255), (int)(0.85f * 255), (int)(0.85f * 255));
	bool out = false;
	D3DXVECTOR3 siz;
	siz.x = width;
	siz.y = height;
	D3DXVECTOR3 pos;
	pos.x = xAxis;
	pos.y = yAxis;
	float RadarCenterX = pos.x + (siz.x / 2);
	float RadarCenterY = pos.y + (siz.y / 2);
	DrawRect(RadarCenterX - 125, RadarCenterY  - 125, 250, 250, &Col.white_, 3);
	//DrawNormalBox(1, pos.x, pos.y, siz.x, siz.y, &Col.white_);
	DrawLine(RadarCenterX, RadarCenterY, pos.x, pos.y, &Col.white_, 1);
	DrawLine(RadarCenterX, RadarCenterY, pos.x + siz.x, pos.y, &Col.white_, 1);
	DrawLine(pos.x, RadarCenterY, pos.x + siz.x, RadarCenterY, &Col.white_, 1);
	DrawLine(RadarCenterX, RadarCenterY, RadarCenterX, pos.y + siz.y, &Col.white_, 1);
	//Circle(RadarCenterX, RadarCenterY, 2.f, 1.f, D3DXCOLOR(.3f, .3f, .3f, 1.f));
}

void DrawRadarPoint(D3DXVECTOR3 ActorPosition, float ActorDistance, D3DXVECTOR3 LocalPosition, D3DXVECTOR3 LocalYaw, int xAxis, int yAxis, int width, int height, int r, int g, int b, int a)
{

	bool out = false;
	D3DXVECTOR3 siz;
	siz.x = width;
	siz.y = height;
	D3DXVECTOR3 pos;
	pos.x = xAxis;
	pos.y = yAxis;
	bool ck = false;
	int radartype = 0;

	D3DXVECTOR3 single = RotatePoint(ActorPosition, LocalPosition, pos.x, pos.y, siz.x, siz.y, LocalYaw.y + 90, 0.5, &ck);
	//Vector3 single = RotatePoint2(ActorPosition, LocalPosition, LocalYaw.y + 90, false);

	if (ActorDistance >= 0.f && ActorDistance < 100)
	{
		if (single.x < 135)
		{
			single.x = single.x + abs(single.x - 135) * 2;
		}
		else if (single.x > 135)
		{
			single.x = single.x - abs(single.x - 135) * 2;
		}
		//DrawString(std::string(std::to_string((int)ActorDistance)).c_str(), single.x, single.y, 255, 255, 255, 255, true, true, D3DRenderer->pFontDrawingsSmall);
		char name[64];
		sprintf_s(name, "%d", (int)ActorDistance);
		DrawString(10, single.x, single.y, &Col.white_, true, true, name);

		RGBA Uwu = { r, g, b, a };
		DrawFilledRect(single.x, single.y,5, 5, &Uwu );

	}
}