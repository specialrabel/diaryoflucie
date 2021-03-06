#pragma once
#include "stdafx.h"
#include "singletonBase.h"

#define fade_in 0
#define fade_out 1
#define fade_init 2

class D2Dmanager : public singletonBase<D2Dmanager>
{
private:
	float fade_opacity;
	bool _fadeIn_end;
	bool _fadeOut_end;
	bool _isPass;

public:

	ID2D1Factory* pD2DFactory;
	ID2D1HwndRenderTarget* pRenderTarget;
	IDWriteFactory* pWriteFactory;				// 공장에서 아래를 찍어냅니다.
	IDWriteTextFormat* pDefaultTextFormat;		//기본 텍스트 포맷
	IDWriteTextFormat* pCustomTextFormat;		//커스텀 텍스트 포맷
	ID2D1SolidColorBrush* defaultBrush;			//기본 검정색 브러쉬
	
	ID2D1DeviceContext* pD2Dcontext;
	ID2D1Effect* compositeEffect;

	ID2D1BitmapRenderTarget* RenderTarget;
	ID2D1Bitmap* bitmap;

	D2Dmanager();
	~D2Dmanager();

	HRESULT Init();
	void release();
	void Update();
	void Render();
	void BeginDraw();
	void EndDraw();

	ID2D1SolidColorBrush* CreateBrush(COLORREF rgb, float opacity = 1.0f);

	// 사각형 렌더 함수
	void Rectangle(D2D1_RECT_F rect, float opacity = 1.0f);
	void Rectangle_brush(ID2D1SolidColorBrush* brush, D2D1_RECT_F rect);
	void Rectangle(ID2D1SolidColorBrush* brush, ID2D1SolidColorBrush* fillbrush, D2D1_RECT_F rect);

	// 사각형 만드는 함수
	D2D1_RECT_F RectMake(float startX, float startY, float width, float height);
	D2D1_RECT_F RectMakeCenter(float startX, float startY, float width, float height);

	void ElipseMakeCenter(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY, float strokeWidth = 1.0f);

	//출력할 문자열, 문자열을 그릴 Rect의 Left, Top, Right, Bottom, 그릴 브러쉬
	void TEXTOUT(ID2D1SolidColorBrush* brush, LPCWSTR string, float startX, float startY, float endX, float endY);
	//출력할 문자열, 문자열을 그릴 Rect의 Left, Top, Right, Bottom, 그릴 브러쉬, 폰트명, 폰트 크기
	void DrawLine(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY, float strokeWidth = 1.0f);
	void DrawTextD2D(ID2D1SolidColorBrush* brush, LPCWSTR fontName, float fontSize, LPCWSTR string, float startX, float startY, float endX, float endY);
	//문자열 가운대 정렬 생성
	void DrawTextD2DCenter(ID2D1SolidColorBrush* brush, LPCWSTR fontName, float fontSize, LPCWSTR string, float startX, float startY, float endX, float endY);
	//문자열 오른쪽 정렬 생성
	void DrawTextD2DRight(ID2D1SolidColorBrush* brush, LPCWSTR fontName, float fontSize, LPCWSTR string, float startX, float startY, float endX, float endY);

	void FillRect(D2D1_RECT_F rect);

	//0:IN, 1:OUT, 2:INIT
	void fade(int isFade);
	bool isFadeIn() { return _fadeIn_end; }
	bool isFadeOut() { return _fadeOut_end; }
	bool isPass() { return _isPass; }

	void setIsPass() { _isPass = true; }


};

