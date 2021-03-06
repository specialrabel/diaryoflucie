#include "stdafx.h"
#include "D2Dmanager.h"

D2Dmanager::D2Dmanager()
{

}

D2Dmanager::~D2Dmanager()
{
}

HRESULT D2Dmanager::Init()
{
	pD2DFactory = nullptr;
	pRenderTarget = nullptr;

	HRESULT hr = E_FAIL;
	//---------------------------------------------------------------------------
	//	D2D Factory 생성
	//---------------------------------------------------------------------------
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
		assert(hr == S_OK);

	/*
	---------------------------------------------------------------------------
		Hwnd Render Target 생성
		Render Target 을 사용시, WIC를 통한 DC , HBITMAP 생성 및 이미지 파일 변환 필요X 
	---------------------------------------------------------------------------
	*/
		hr = pD2DFactory->CreateHwndRenderTarget(RenderTargetProperties(),
			HwndRenderTargetProperties(_hWnd, SizeU(WINSIZEX, WINSIZEY)),
			&pRenderTarget);

		assert(hr == S_OK);

		//백버퍼용 링크
		hr = pRenderTarget->CreateCompatibleRenderTarget(
			SizeF(WINSIZEX, WINSIZEY),
			SizeU(WINSIZEX, WINSIZEY),
			&RenderTarget);

		assert(hr == S_OK);
	/*
	---------------------------------------------------------------------------
	//	IDWriteFactory 생성
		D2D는 TEXTOUT이 없기떄문에 필요함.
	//---------------------------------------------------------------------------
	*/

		hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(pWriteFactory),
			reinterpret_cast<IUnknown**>(&pWriteFactory));
		assert(hr == S_OK);

		// 브러쉬 생성
		defaultBrush = CreateBrush(RGB(0, 0, 0));

		hr = pWriteFactory->CreateTextFormat(L"맑은고딕", NULL, DWRITE_FONT_WEIGHT_REGULAR,
			DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 17.0f, L"", &pDefaultTextFormat);
		assert(hr == S_OK);

		CoInitialize(NULL);

	return S_OK;
}

void D2Dmanager::release()
{
	defaultBrush->Release();
	pDefaultTextFormat->Release();
	pWriteFactory->Release();
	pRenderTarget->Release();
	pD2DFactory->Release();
}

void D2Dmanager::Update()
{
}

void D2Dmanager::Render()
{
	RenderTarget->GetBitmap(&bitmap);

	pRenderTarget->BeginDraw();
	pRenderTarget->Clear(ColorF(RGB(0, 0, 0)));

	pRenderTarget->DrawBitmap(
		bitmap,
		D2D1::RectF(0, 0, WINSIZEX, WINSIZEY),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);

	pRenderTarget->EndDraw();
}

void D2Dmanager::BeginDraw()
{
	pRenderTarget->BeginDraw();
	pRenderTarget->Clear(ColorF(RGB(0, 0, 0)));
}

void D2Dmanager::EndDraw()
{
	pRenderTarget->EndDraw();
}

ID2D1SolidColorBrush* D2Dmanager::CreateBrush(COLORREF rgb, float opacity)
{
	ID2D1SolidColorBrush* brush;
	brush = nullptr;

	pRenderTarget->CreateSolidColorBrush(ColorF(rgb, opacity), &brush);

	return brush;
}

void D2Dmanager::DrawLine(ID2D1SolidColorBrush* brush, float x1, float y1, float x2, float y2, float strokeWidth)
{
	pRenderTarget->DrawLine(Point2F(x1, y1), Point2F(x2, y2), brush, strokeWidth);
}

D2D1_RECT_F D2Dmanager::RectMake(float x1, float y1, float width, float height)
{
	D2D1_RECT_F rc = { x1, y1, x1 + width, y1 + height };
	return rc;
}

D2D1_RECT_F D2Dmanager::RectMakeCenter(float x1, float y1, float width, float height)
{
	D2D1_RECT_F rc = { x1 - width / 2, y1 - height / 2, x1 + width / 2, y1 + height / 2 };
	return rc;
}

void D2Dmanager::Rectangle(D2D1_RECT_F rect, float opacity)
{
	float cam_x = CAMERAMANAGER->get_camera_x();
	float cam_y = CAMERAMANAGER->get_camera_y();

	pRenderTarget->DrawRectangle(
		D2D1::RectF(rect.left - cam_x, rect.top - cam_y, rect.right - cam_x, rect.bottom - cam_y),
		defaultBrush,
		opacity);
}

void D2Dmanager::Rectangle_brush(ID2D1SolidColorBrush* brush, D2D1_RECT_F rect)
{
	float cam_x = CAMERAMANAGER->get_camera_x();
	float cam_y = CAMERAMANAGER->get_camera_y();

	pRenderTarget->DrawRectangle(
		D2D1::RectF(rect.left - cam_x, rect.top - cam_y, rect.right - cam_x, rect.bottom - cam_y),
		brush,
		1.0f);
}
void D2Dmanager::Rectangle(ID2D1SolidColorBrush * brush, ID2D1SolidColorBrush * fillbrush, D2D1_RECT_F rect)
{

	float cam_x = CAMERAMANAGER->get_camera_x();
	float cam_y = CAMERAMANAGER->get_camera_y();

	D2D1_RECT_F rc = D2D1::RectF(rect.left - cam_x, rect.top - cam_y, rect.right - cam_x, rect.bottom - cam_y);

	pRenderTarget->FillRectangle(rc, fillbrush);
	pRenderTarget->DrawRectangle(rc, brush, 1.0f);

}
void D2Dmanager::ElipseMakeCenter(ID2D1SolidColorBrush* brush, float x1, float y1, float width, float height, float strokeWidth)
{
	D2D1_ELLIPSE ellipse;
	ellipse.point.x = x1 + width * 0.5;
	ellipse.point.y = y1 + height * 0.5;
	ellipse.radiusX = width * 0.5;
	ellipse.radiusY = height * 0.5;

	pRenderTarget->DrawEllipse(&ellipse, brush, strokeWidth);
}

void D2Dmanager::TEXTOUT(ID2D1SolidColorBrush* brush, LPCWSTR string, float left, float top, float right, float bottom)
{
	pRenderTarget->DrawTextA(string, lstrlenW(string), pDefaultTextFormat, RectF(left,top, right, bottom), brush);
}

void D2Dmanager::DrawTextD2D(ID2D1SolidColorBrush* brush, LPCWSTR fontName, float fontSize, LPCWSTR string, float x1, float y1, float x2, float y2)
{
	//	TextFormat 생성
	pWriteFactory->CreateTextFormat(fontName, // 글꼴이름
									NULL, 
									DWRITE_FONT_WEIGHT_REGULAR,
									DWRITE_FONT_STYLE_NORMAL,
									DWRITE_FONT_STRETCH_NORMAL,
									fontSize,
									L"",
									&pCustomTextFormat);

	pRenderTarget->DrawTextA(string, lstrlenW(string), pCustomTextFormat, RectF(x1, y1, x2, y2), brush);

	pCustomTextFormat = nullptr;
}

void D2Dmanager::DrawTextD2DCenter(ID2D1SolidColorBrush * brush, LPCWSTR fontName, float fontSize, LPCWSTR string, float startX, float startY, float endX, float endY)
{
	//	TextFormat 생성
	pWriteFactory->CreateTextFormat(fontName, // 글꼴이름
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontSize,
		L"",
		&pCustomTextFormat);

	//가운대 정렬
	pCustomTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

	pRenderTarget->DrawTextA(string, lstrlenW(string), pCustomTextFormat, RectF(startX, startY, endX, endY), brush);

	pCustomTextFormat = nullptr;

}

void D2Dmanager::DrawTextD2DRight(ID2D1SolidColorBrush * brush, LPCWSTR fontName, float fontSize, LPCWSTR string, float startX, float startY, float endX, float endY)
{

	//	TextFormat 생성
	pWriteFactory->CreateTextFormat(fontName, // 글꼴이름
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontSize,
		L"",
		&pCustomTextFormat);

	//가운대 정렬
	pCustomTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);

	pRenderTarget->DrawTextA(string, lstrlenW(string), pCustomTextFormat, RectF(startX, startY, endX, endY), brush);

	pCustomTextFormat = nullptr;

	
}

void D2Dmanager::FillRect(D2D1_RECT_F rect)
{
	defaultBrush->SetColor(ColorF(ColorF::Black));

	pRenderTarget->FillRectangle(rect, defaultBrush);
}

void D2Dmanager::fade(int isFade)
{
	D2D1_RECT_F rc;
	image* aa;

	aa = IMAGEMANAGER->addImage("aa", L"image/fade/black.png", 1600, 900);


	if (isFade == fade_in)
	{
		if (fade_opacity < 1.5f)
		{
			fade_opacity += 0.02f;

			aa->render(CAMERAMANAGER->get_camera_x(), CAMERAMANAGER->get_camera_y(), fade_opacity);

			_fadeIn_end = false;
		}

		else if (fade_opacity >= 1.5f)
		{
			fade_opacity = 1.0f;

			aa->render(CAMERAMANAGER->get_camera_x(), CAMERAMANAGER->get_camera_y(), fade_opacity);

			_fadeIn_end = true;
		}
	}
	else if (isFade == fade_out)
	{
		if (fade_opacity > -0.5f)
		{
			fade_opacity -= 0.01f;

			aa->render(CAMERAMANAGER->get_camera_x(), CAMERAMANAGER->get_camera_y(), fade_opacity);

			_fadeOut_end = false;
		}

		else if (fade_opacity <= -0.5f)
		{
			fade_opacity = 0.0f;

			aa->render(CAMERAMANAGER->get_camera_x(), CAMERAMANAGER->get_camera_y(), fade_opacity);

			_fadeOut_end = true;
		}
	}
	else if (isFade == fade_init)
	{
		_fadeIn_end = false;
		_fadeOut_end = false;
		_isPass = false;

		fade_opacity = 1.0f;
	}
}
