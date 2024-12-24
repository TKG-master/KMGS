#pragma once

#include <dwrite.h>
#include <d2d1.h>

#pragma comment(lib,"dwrite.lib")
#pragma comment(lib,"d2d1.lib")

#include <string>
#include <SimpleMath.h>


//=============================================================================
//		�t�H���g���X�g
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
//		�t�H���g��
//=============================================================================
namespace
{
	//===== ���ӁF�t�H���g���J���āA"�t�H���g��"���m�F���ē��� =====
	//�����Ȃ�œ����̂��킩��Ȃ��Ƃ�������
	const WCHAR* FontList[]
	{
		L"���C���I",
		L"Arial",
		L"Meiryo UI",
		L"HG�n�p�p�޼��UB",
		L"HG����E",
	};
}

//=============================================================================
//		�t�H���g�ݒ�
//=============================================================================
struct FontData
{
	Font font;					// �t�H���g��
	IDWriteFontCollection* fontCollection;		// �t�H���g�R���N�V����
	DWRITE_FONT_WEIGHT fontWeight;				// �t�H���g�̑���
	DWRITE_FONT_STYLE fontStyle;				// �t�H���g�X�^�C��
	DWRITE_FONT_STRETCH fontStretch;			// �t�H���g�̕�
	FLOAT fontSize;								// �t�H���g�T�C�Y
	WCHAR const* localeName;					// ���P�[����
	DWRITE_TEXT_ALIGNMENT textAlignment;		// �e�L�X�g�̔z�u
	D2D1_COLOR_F Color;							// �t�H���g�̐F

	// �f�t�H���g�ݒ�
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
//		DirectWrite�ݒ�
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
	//���Ԃ�ێ�����
	std::string timeString;
	//�|�W�V����
	DirectX::SimpleMath::Vector2 position;


	// �t�H���g�f�[�^
	FontData* Setting = new FontData();
	// string��wstring�֕ϊ�����
	std::wstring StringToWString(std::string oString);

public:

	// �f�t�H���g�R���X�g���N�^�𐧌�
	DirectWrite() = delete;

	// �R���X�g���N�^
	// ��1�����F�t�H���g�ݒ�
	DirectWrite(FontData* set) : Setting(set) {
		FontNameDefault = set->font;
		FontSizeDefault = set->fontSize;
		FontColorDefault = set->Color;
	};

	// �R���X�g���N�^
	// ��1�����F�t�H���g���iL"���C���I", L"Arial", L"Meiryo UI"���j
	// ��2�����F�t�H���g�R���N�V�����inullptr�j
	// ��3�����F�t�H���g�̑����iDWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_WEIGHT_BOLD���j
	// ��4�����F�t�H���g�X�^�C���iDWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STYLE_OBLIQUE, DWRITE_FONT_STYLE_ITALIC�j
	// ��5�����F�t�H���g�̕��iDWRITE_FONT_STRETCH_NORMAL,DWRITE_FONT_STRETCH_EXTRA_EXPANDED���j
	// ��6�����F�t�H���g�T�C�Y�i20, 30���j
	// ��7�����F���P�[�����iL"ja-jp"���j
	// ��8�����F�e�L�X�g�̔z�u�iDWRITE_TEXT_ALIGNMENT_LEADING�F�O, ���j
	// ��9�����F�t�H���g�̐F�iD2D1::ColorF(D2D1::ColorF::Black)�F��, D2D1::ColorF(D2D1::ColorF(0.0f, 0.2f, 0.9f, 1.0f))�FRGBA�w�蓙�j
	DirectWrite(Font font,						// �t�H���g��
		IDWriteFontCollection* fontCollection,	// �t�H���g�R���N�V����
		DWRITE_FONT_WEIGHT fontWeight,			// �t�H���g�̑���
		DWRITE_FONT_STYLE fontStyle,			// �t�H���g�X�^�C��
		DWRITE_FONT_STRETCH fontStretch,		// �t�H���g�̕�
		FLOAT fontSize,							// �t�H���g�T�C�Y
		WCHAR const* localeName,				// ���P�[����
		DWRITE_TEXT_ALIGNMENT textAlignment,	// �e�L�X�g�̔z�u
		D2D1_COLOR_F Color						// �t�H���g�̐F
	);

	// �t�H���g�ݒ�
	// ��1�����F�t�H���g�f�[�^�\����
	void SetFont(FontData* set);

	// �t�H���g�ݒ�
	// ��1�����F�t�H���g���iL"���C���I", L"Arial", L"Meiryo UI"���j
	// ��2�����F�t�H���g�R���N�V�����inullptr�j
	// ��3�����F�t�H���g�̑����iDWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_WEIGHT_BOLD���j
	// ��4�����F�t�H���g�X�^�C���iDWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STYLE_OBLIQUE, DWRITE_FONT_STYLE_ITALIC�j
	// ��5�����F�t�H���g�̕��iDWRITE_FONT_STRETCH_NORMAL,DWRITE_FONT_STRETCH_EXTRA_EXPANDED���j
	// ��6�����F�t�H���g�T�C�Y�i20, 30���j
	// ��7�����F���P�[�����iL"ja-jp"���j
	// ��8�����F�e�L�X�g�̔z�u�iDWRITE_TEXT_ALIGNMENT_LEADING�F�O, ���j
	// ��9�����F�t�H���g�̐F�iD2D1::ColorF(D2D1::ColorF::Black)�F��, D2D1::ColorF(D2D1::ColorF(0.0f, 0.2f, 0.9f, 1.0f))�FRGBA�w�蓙�j
	void SetFont(Font font,							// �t�H���g��
		IDWriteFontCollection* fontCollection,		// �t�H���g�R���N�V����
		DWRITE_FONT_WEIGHT fontWeight,				// �t�H���g�̑���
		DWRITE_FONT_STYLE fontStyle,				// �t�H���g�X�^�C��
		DWRITE_FONT_STRETCH fontStretch,			// �t�H���g�̕�
		FLOAT fontSize,								// �t�H���g�T�C�Y
		WCHAR const* localeName,					// ���P�[����
		DWRITE_TEXT_ALIGNMENT textAlignment,		// �e�L�X�g�̔z�u
		D2D1_COLOR_F Color);						// �t�H���g�̐F

	// �����`��
	// string�F������
	// pos�F�`��|�W�V����
	// options�F�e�L�X�g�̐��`
	void DrawString(std::string str, DirectX::SimpleMath::Vector2 pos, D2D1_DRAW_TEXT_OPTIONS options);

	// �����`��
	// string�F������
	// rect�F�̈�w��
	// options�F�e�L�X�g�̐��`
	void DrawString(std::string str, D2D1_RECT_F rect, D2D1_DRAW_TEXT_OPTIONS options);

	// ������
	void Init();

	void SetTimeranning(int minutes, int seconds);

	void SetPosition(DirectX::SimpleMath::Vector2 pos);

	std::string GetTimerannig() { return this->timeString; };

	DirectX::SimpleMath::Vector2 GetPosition() { return this->position; };



	// �I������
	void Release();

	//=== �f�t�H���g(�ŏ��ɐ����������̂�ۑ�) ===
	Font FontNameDefault;
	FLOAT FontSizeDefault;
	D2D1_COLOR_F FontColorDefault;
	DWRITE_READING_DIRECTION ReadingDirectionDefault = DWRITE_READING_DIRECTION_LEFT_TO_RIGHT;
	DWRITE_FLOW_DIRECTION FlowDirectionDefault = DWRITE_FLOW_DIRECTION_TOP_TO_BOTTOM;

	//=== �t�H���g ===
	std::vector<Font> FontNameList;				// �g�p���Ɋi�[���ꂽ�t�H���g��
	std::vector<int> FontNameCount;				// �t�H���g���������g�p���邩
	//=== �t�H���g�T�C�Y ===
	std::vector<FLOAT> FontSizeList;			// �g�p���Ɋi�[���ꂽ�t�H���g�T�C�Y
	std::vector<int> FontSizeCount;				// ���̃T�C�Y���������g�p���邩
	//=== �����̐F ===
	std::vector<D2D1_COLOR_F> FontColorList;	// �g�p���Ɋi�[���ꂽ�t�H���g�̐F
	std::vector<int> FontColorCount;			// ���̐F���������g�p���邩



#pragma region DIRECTION���

	/*
	
	========== �ꕶ������Direction ==========

	DWRITE_READING_DIRECTION_LEFT_TO_RIGHT
	�E�e�L�X�g��������E�ɗ���鉡�����̕���(���{��Ƃ��p��Ƃ�)

	DWRITE_READING_DIRECTION_RIGHT_TO_LEFT
	�E�e�L�X�g���E���獶�ɗ���鉡�����̕���(�A���r�A���w�u���C��Ƃ�)

	DWRITE_READING_DIRECTION_TOP_TO_BOTTOM
	�E�e�L�X�g���ォ�牺�ɗ����c�����̕���(���{��̏c�����Ƃ�)

	DWRITE_READING_DIRECTION_BOTTOM_TO_TOP
	�E�e�L�X�g���������ɗ����c�����̕���(�����������ƂȂ�)

	
	========== �s��Direction ==========

	DWRITE_FLOW_DIRECTION_TOP_TO_BOTTOM
	�E�s���ォ�牺�ɗ����(�c�����̓��{��⒆����A�؍���Ƃ�)

	DWRITE_FLOW_DIRECTION_BOTTOM_TO_TOP
	�E�s���������ɗ����(�����������ƂȂ�)

	DWRITE_FLOW_DIRECTION_LEFT_TO_RIGHT
	�E�s��������E�ɗ����(�p���t�����X��Ȃǂ̉�����)

	DWRITE_FLOW_DIRECTION_RIGHT_TO_LEFT
	�E�s���E���獶�ɗ����(�A���r�A���w�u���C��Ƃ�)

	*/

#pragma endregion


	//=== �����̗��������𐧌� ===
	void SetReadingDirection(DWRITE_READING_DIRECTION direction) { pTextFormat->SetReadingDirection(direction); };
	//=== �s�̗��������𐧌� ===
	void SetFlowDirection(DWRITE_FLOW_DIRECTION direction) { pTextFormat->SetFlowDirection(direction); };


	void SetReadingDirectionDefault(DWRITE_READING_DIRECTION dw) { ReadingDirectionDefault = dw; }
	void SetFlowDirectionDefault(DWRITE_FLOW_DIRECTION dw) { FlowDirectionDefault = dw; }


};