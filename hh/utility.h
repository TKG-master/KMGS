#pragma once
#include	<string>
#include	<SimpleMath.h>
#include	<assimp/matrix4x4.h>

namespace utility
{
	std::string wide_to_multi_winapi(std::wstring const& src);
	std::wstring utf8_to_wide_winapi(std::string const& src);
	std::string utf8_to_multi_winapi(std::string const& src);

	DirectX::SimpleMath::Matrix aiMtxToDxMtx(aiMatrix4x4 aimatrix);
};