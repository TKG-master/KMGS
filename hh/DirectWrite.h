#pragma once

#include <dwrite.h>
#include <d2d1.h>

#pragma comment(lib,"dwrite.lib")
#pragma comment(lib,"d2d1.lib")

#include <string>
#include <SimpleMath.h>


//=============================================================================
//		フォントリスト
//=============================================================================
enum class Font
{
	Meiryo,
	Arial,
	MeiryoUI,
	HG_SOUEIKAKU_GOTHIC,
	HG_MINCHO_E,
};

//=============================================================================
//		フォント名
//=============================================================================
namespace
{
	//===== 注意：フォントを開いて、"フォント名"を確認して入力 =====
	//正直なんで動くのかわかんないとこもある
	const WCHAR* FontList[]
	{
		L"メイリオ",
		L"Arial",
		L"Meiryo UI",
		L"HG創英角ｺﾞｼｯｸUB",
		L"HG明朝E",
	};
}

//=============================================================================
//		フォント設定
//=============================================================================
struct FontData
{
	Font font;					// フォント名
	IDWriteFontCollection* fontCollection;		// フォントコレクション
	DWRITE_FONT_WEIGHT fontWeight;				// フォントの太さ
	DWRITE_FONT_STYLE fontStyle;				// フォントスタイル
	DWRITE_FONT_STRETCH fontStretch;			// フォントの幅
	FLOAT fontSize;								// フォントサイズ
	WCHAR const* localeName;					// ロケール名
	DWRITE_TEXT_ALIGNMENT textAlignment;		// テキストの配置
	D2D1_COLOR_F Color;							// フォントの色

	// デフォルト設定
	FontData()
	{
		font = Font::Meiryo;
		fontCollection = nullptr;
		fontWeight = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_NORMAL;
		fontStyle = DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL;
		fontStretch = DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_NORMAL;
		fontSize = 20;
		localeName = L"ja-jp";
		textAlignment = DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_LEADING;
		Color = D2D1::ColorF(D2D1::ColorF::White);
	}
};

//=============================================================================
//		DirectWrite設定
//=============================================================================
class DirectWrite
{
private:
	ID2D1Factory* pD2DFactory = NULL;
	IDWriteFactory* pDWriteFactory = NULL;
	IDWriteTextFormat* pTextFormat = NULL;
	IDWriteTextLayout* pTextLayout = NULL;
	ID2D1RenderTarget* pRT = NULL;
	ID2D1SolidColorBrush* pSolidBrush = NULL;
	IDXGISurface* pBackBuffer = NULL;
	//時間を保持する
	std::string timeString;
	//ポジション
	DirectX::SimpleMath::Vector2 position;


	// フォントデータ
	FontData* Setting = new FontData();
	// stringをwstringへ変換する
	std::wstring StringToWString(std::string oString);

public:

	// デフォルトコンストラクタを制限
	DirectWrite() = delete;

	// コンストラクタ
	// 第1引数：フォント設定
	DirectWrite(FontData* set) : Setting(set) {
		FontNameDefault = set->font;
		FontSizeDefault = set->fontSize;
		FontColorDefault = set->Color;
	};

	// コンストラクタ
	// 第1引数：フォント名（L"メイリオ", L"Arial", L"Meiryo UI"等）
	// 第2引数：フォントコレクション（nullptr）
	// 第3引数：フォントの太さ（DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_WEIGHT_BOLD等）
	// 第4引数：フォントスタイル（DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STYLE_OBLIQUE, DWRITE_FONT_STYLE_ITALIC）
	// 第5引数：フォントの幅（DWRITE_FONT_STRETCH_NORMAL,DWRITE_FONT_STRETCH_EXTRA_EXPANDED等）
	// 第6引数：フォントサイズ（20, 30等）
	// 第7引数：ロケール名（L"ja-jp"等）
	// 第8引数：テキストの配置（DWRITE_TEXT_ALIGNMENT_LEADING：前, 等）
	// 第9引数：フォントの色（D2D1::ColorF(D2D1::ColorF::Black)：黒, D2D1::ColorF(D2D1::ColorF(0.0f, 0.2f, 0.9f, 1.0f))：RGBA指定等）
	DirectWrite(Font font,						// フォント名
		IDWriteFontCollection* fontCollection,	// フォントコレクション
		DWRITE_FONT_WEIGHT fontWeight,			// フォントの太さ
		DWRITE_FONT_STYLE fontStyle,			// フォントスタイル
		DWRITE_FONT_STRETCH fontStretch,		// フォントの幅
		FLOAT fontSize,							// フォントサイズ
		WCHAR const* localeName,				// ロケール名
		DWRITE_TEXT_ALIGNMENT textAlignment,	// テキストの配置
		D2D1_COLOR_F Color						// フォントの色
	);

	// フォント設定
	// 第1引数：フォントデータ構造体
	void SetFont(FontData* set);

	// フォント設定
	// 第1引数：フォント名（L"メイリオ", L"Arial", L"Meiryo UI"等）
	// 第2引数：フォントコレクション（nullptr）
	// 第3引数：フォントの太さ（DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_WEIGHT_BOLD等）
	// 第4引数：フォントスタイル（DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STYLE_OBLIQUE, DWRITE_FONT_STYLE_ITALIC）
	// 第5引数：フォントの幅（DWRITE_FONT_STRETCH_NORMAL,DWRITE_FONT_STRETCH_EXTRA_EXPANDED等）
	// 第6引数：フォントサイズ（20, 30等）
	// 第7引数：ロケール名（L"ja-jp"等）
	// 第8引数：テキストの配置（DWRITE_TEXT_ALIGNMENT_LEADING：前, 等）
	// 第9引数：フォントの色（D2D1::ColorF(D2D1::ColorF::Black)：黒, D2D1::ColorF(D2D1::ColorF(0.0f, 0.2f, 0.9f, 1.0f))：RGBA指定等）
	void SetFont(Font font,							// フォント名
		IDWriteFontCollection* fontCollection,		// フォントコレクション
		DWRITE_FONT_WEIGHT fontWeight,				// フォントの太さ
		DWRITE_FONT_STYLE fontStyle,				// フォントスタイル
		DWRITE_FONT_STRETCH fontStretch,			// フォントの幅
		FLOAT fontSize,								// フォントサイズ
		WCHAR const* localeName,					// ロケール名
		DWRITE_TEXT_ALIGNMENT textAlignment,		// テキストの配置
		D2D1_COLOR_F Color);						// フォントの色

	// 文字描画
	// string：文字列
	// pos：描画ポジション
	// options：テキストの整形
	void DrawString(std::string str, DirectX::SimpleMath::Vector2 pos, D2D1_DRAW_TEXT_OPTIONS options);

	// 文字描画
	// string：文字列
	// rect：領域指定
	// options：テキストの整形
	void DrawString(std::string str, D2D1_RECT_F rect, D2D1_DRAW_TEXT_OPTIONS options);

	// 初期化
	void Init();

	void SetTimeranning(int minutes, int seconds);

	void SetPosition(DirectX::SimpleMath::Vector2 pos);

	std::string GetTimerannig() { return this->timeString; };

	DirectX::SimpleMath::Vector2 GetPosition() { return this->position; };



	// 終了処理
	void Release();

	//=== デフォルト(最初に生成したものを保存) ===
	Font FontNameDefault;
	FLOAT FontSizeDefault;
	D2D1_COLOR_F FontColorDefault;
	DWRITE_READING_DIRECTION ReadingDirectionDefault = DWRITE_READING_DIRECTION_LEFT_TO_RIGHT;
	DWRITE_FLOW_DIRECTION FlowDirectionDefault = DWRITE_FLOW_DIRECTION_TOP_TO_BOTTOM;

	//=== フォント ===
	std::vector<Font> FontNameList;				// 使用順に格納されたフォント名
	std::vector<int> FontNameCount;				// フォントを何文字使用するか
	//=== フォントサイズ ===
	std::vector<FLOAT> FontSizeList;			// 使用順に格納されたフォントサイズ
	std::vector<int> FontSizeCount;				// そのサイズを何文字使用するか
	//=== 文字の色 ===
	std::vector<D2D1_COLOR_F> FontColorList;	// 使用順に格納されたフォントの色
	std::vector<int> FontColorCount;			// その色を何文字使用するか



#pragma region DIRECTION解説

	/*
	
	========== 一文字ずつのDirection ==========

	DWRITE_READING_DIRECTION_LEFT_TO_RIGHT
	・テキストが左から右に流れる横書きの方向(日本語とか英語とか)

	DWRITE_READING_DIRECTION_RIGHT_TO_LEFT
	・テキストが右から左に流れる横書きの方向(アラビア語やヘブライ語とか)

	DWRITE_READING_DIRECTION_TOP_TO_BOTTOM
	・テキストが上から下に流れる縦書きの方向(日本語の縦書きとか)

	DWRITE_READING_DIRECTION_BOTTOM_TO_TOP
	・テキストが下から上に流れる縦書きの方向(正直見たことない)

	
	========== 行のDirection ==========

	DWRITE_FLOW_DIRECTION_TOP_TO_BOTTOM
	・行が上から下に流れる(縦書きの日本語や中国語、韓国語とか)

	DWRITE_FLOW_DIRECTION_BOTTOM_TO_TOP
	・行が下から上に流れる(正直見たことない)

	DWRITE_FLOW_DIRECTION_LEFT_TO_RIGHT
	・行が左から右に流れる(英語やフランス語などの横書き)

	DWRITE_FLOW_DIRECTION_RIGHT_TO_LEFT
	・行が右から左に流れる(アラビア語やヘブライ語とか)

	*/

#pragma endregion


	//=== 文字の流れる方向を制御 ===
	void SetReadingDirection(DWRITE_READING_DIRECTION direction) { pTextFormat->SetReadingDirection(direction); };
	//=== 行の流れる方向を制御 ===
	void SetFlowDirection(DWRITE_FLOW_DIRECTION direction) { pTextFormat->SetFlowDirection(direction); };


	void SetReadingDirectionDefault(DWRITE_READING_DIRECTION dw) { ReadingDirectionDefault = dw; }
	void SetFlowDirectionDefault(DWRITE_FLOW_DIRECTION dw) { FlowDirectionDefault = dw; }


};