#include	<filesystem>
#include	<string>
#include	<Windows.h>
#include	<SimpleMath.h>
#include    <assimp\scene.h>


namespace utility {
	// std::string �p�̃f�B���N�g���擾�֐�
	std::filesystem::path get_directory(const std::string& path) {
		return std::filesystem::path(path).parent_path();
	}

	// std::u8string �p�̃f�B���N�g���擾�֐�
	std::filesystem::path get_directory(const std::u8string& path) {
		return std::filesystem::path(path).parent_path();
	}

	// std::wstring �p�̃f�B���N�g���擾�֐�
	std::filesystem::path get_directory(const std::wstring& path) {
		return std::filesystem::path(path).parent_path();
	}

	// ���C�h����(utf16)�����|��������
	std::string wide_to_multi_winapi(std::wstring const& src)
	{
		auto const dest_size = ::WideCharToMultiByte(
			CP_ACP,
			0U,
			src.data(),
			-1,
			nullptr,
			0,
			nullptr,
			nullptr);
		std::vector<char> dest(dest_size, '\0');
		if (::WideCharToMultiByte(
			CP_ACP,
			0U,
			src.data(),
			-1,
			dest.data(),
			static_cast<int>(dest.size()),
			nullptr,
			nullptr) == 0) {
			throw std::system_error{ static_cast<int>(::GetLastError()), std::system_category() };
		}
		dest.resize(std::char_traits<char>::length(dest.data()));
		dest.shrink_to_fit();
		return std::string(dest.begin(), dest.end());
	}

	// utf-8�����C�h����(utf-16)��
	std::wstring utf8_to_wide_winapi(std::string const& src)
	{
		auto const dest_size = ::MultiByteToWideChar(
			CP_UTF8,			 // �\�[�X����UTF-8
			0U,
			src.data(),
			-1,
			nullptr,
			0U);
		std::vector<wchar_t> dest(dest_size, L'\0');
		if (::MultiByteToWideChar(CP_UTF8, 0U, src.data(), -1, dest.data(), static_cast<int>(dest.size())) == 0) {
			throw std::system_error{ static_cast<int>(::GetLastError()), std::system_category() };
		}
		dest.resize(std::char_traits<wchar_t>::length(dest.data()));
		dest.shrink_to_fit();
		return std::wstring(dest.begin(), dest.end());
	}

	// utf8��S-JIS��
	std::string utf8_to_multi_winapi(std::string const& src)
	{
		auto const wide = utf8_to_wide_winapi(src);
		return wide_to_multi_winapi(wide);
	}

	// assimp�s���DIRECTX�̍s��ɕϊ�����
	DirectX::SimpleMath::Matrix aiMtxToDxMtx(aiMatrix4x4 aimatrix)
	{

		DirectX::SimpleMath::Matrix dxmtx = {
		   aimatrix.a1,aimatrix.b1,aimatrix.c1,aimatrix.d1,
		   aimatrix.a2,aimatrix.b2,aimatrix.c2,aimatrix.d2,
		   aimatrix.a3,aimatrix.b3,aimatrix.c3,aimatrix.d3,
		   aimatrix.a4,aimatrix.b4,aimatrix.c4,aimatrix.d4
		};

		return dxmtx;
	}

}

