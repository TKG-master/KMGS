#include "ParesObj.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <SimpleMath.h>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <assimp/cimport.h>
#include "renderer.h"

#pragma comment (lib,"assimp-vc143-mtd.lib")


//文字列を指定の区切り文字で分割する
std::vector<std::string>split(const std::string& inputstring, char delimiter) {
	std::vector<std::string>tokens;
	std::string token;

	std::stringstream stringstream(inputstring);

	while (getline(stringstream, token, delimiter)) {
		tokens.push_back(token);
	}

	return tokens;
}
//ファイルを読み込んでメモリに展開する
std::vector<char>readFileToMemory(const std::string& filename)
{
	//入力ファイルストリームを開く（バイナリモードで開く）
	std::ifstream file(filename, std::ios::binary | std::ios::ate);

	if (file.is_open() == false) {
		std::cerr << "ファイルが開けません" << filename << std::endl;
		return {};
	}

	//ファイルサイズを取得する
	std::streamsize size = file.tellg();

	std::vector<char> buffer(size);	//ファイルの内容を格納するためのバッファ


	//ファイルの内容をベクターに読み込む
	file.seekg(0, std::ios::beg);	//ファイルポインタを先頭に戻す
	if (file.read(buffer.data(), size))
	{
		std::cout << "ファイルが正常に読み込まれました。サイズ" << size << "バイト" << std::endl;
	}
	else {
		std::cerr << "ファイルの読み込みに失敗しました" << std::endl;
		buffer.clear();
	}

	return buffer;
}

//頂点データ
struct VERTEX {
	float x, y, z;
};

bool isSpace(const char c) {
	if (c == ' ' || c == '\t') {
		return true;
	}

	return false;
}

std::vector<VERTEX>GetVertex(const std::vector<std::string>& lines)
{
	std::vector<VERTEX> vertexes{};

	//頂点データを取得する
	for (const auto& line : lines) {
		if (line[0] == 'v' && isSpace(line[1])) {

			std::vector<std::string> tokens = split(line, ' ');
			if (tokens.size() == 4) {
				VERTEX vertex;
				vertex.x = std::stof(tokens[1]);
				vertex.y = std::stof(tokens[2]);
				vertex.z = std::stof(tokens[3]);
				vertexes.push_back(vertex);
			}
		}
	}
	return vertexes;
}

//テクスチャ座標
struct TEXCOORD {
	float u, v;
};

std::vector<TEXCOORD>GetTexCoord(const std::vector<std::string>& lines)
{
	std::vector<TEXCOORD>texcoords{};

	//テクスチャ座標を取得する
	for (const auto& line : lines)
	{
		if (line[0] == 'v' && line[1] == 't')
		{
			std::vector<std::string>tokens = split(line, ' ');
			if (tokens.size() == 3) {
				TEXCOORD tex;
				tex.u = std::stof(tokens[1]);
				tex.v = std::stof(tokens[2]);
				texcoords.push_back(tex);
			}
		}
	}
	return texcoords;
}

//法線ベクトル
struct NORMAL {
	float nx, ny, nz;
};

std::vector<NORMAL> GetNormal(const std::vector<std::string>& lines)
{
	std::vector<NORMAL>normals{};
	//法線ベクトルを取得する
	for (const auto& line : lines) {
		if (line[0] == 'v' && line[1] == 'n') {
			std::vector<std::string>tokens = split(line, ' ');
			if (tokens.size() == 4) {
				NORMAL n;
				n.nx = std::stof(tokens[1]);
				n.ny = std::stof(tokens[2]);
				n.nz = std::stof(tokens[3]);
				normals.push_back(n);
			}
		}
	}
	return normals;
}

//USEMATERIA取得
std::vector<std::string>GetUseMaterial(const std::vector<std::string>& lines)
{
	std::vector<std::string>usematerials{};

	for (const auto& line : lines) {
		if (line[0] == 'u' && line[1] == 's' && line[2] == 'e' && line[3] == 'm' && line[4] == 't' && line[5] == 'l') {
			std::vector<std::string>tokens = split(line, ' ');
			if (tokens.size() == 2) {
				std::string mtrlname;
				mtrlname = tokens[1];
				usematerials.push_back(mtrlname);
			}
		}
	}
	return usematerials;
}
//頂点情報を構成する情報のインデックスを規定する
struct VERTEXINFOINDEX {
	unsigned int vIndex;	//頂点インデックス
	unsigned int tIndex;	//テクスチャインデックス
	unsigned int nIndex;	//法線インデックス
};

//引数の中にはスペースで区切られた文字列現んが入っている（f 1/2/3 4/5/6 ）
std::vector<VERTEXINFOINDEX> GetPolygonIndex(std::vector<std::string>& spaceSeparatedTokens)
{
	std::vector<VERTEXINFOINDEX>polygonindexes{};

	for (int i = 1; i < spaceSeparatedTokens.size(); i++)
	{
		std::vector<std::string> vertexinfoinedxes = split(spaceSeparatedTokens[i], '/');
		if (vertexinfoinedxes.size() == 3)
		{
			VERTEXINFOINDEX pidx;
			pidx.vIndex = std::stoi(vertexinfoinedxes[0]) - 1;
			pidx.tIndex = std::stoi(vertexinfoinedxes[1]) - 1;
			pidx.nIndex = std::stoi(vertexinfoinedxes[2]) - 1;
			polygonindexes.push_back(pidx);
		}
		else {
			std::cout << "頂点インデックス・テクスチャインデックス・法線インデックス以外があります" << std::endl;
		}
	}
	return polygonindexes;
}
//面を構成する頂点インデックスを取得する
std::vector<std::vector<VERTEXINFOINDEX>>GetFace(const std::vector<std::string>& lines)
{
	//ポリゴンを構成する頂点情報インデックスを格納する
	std::vector<std::vector<VERTEXINFOINDEX>>polygonindexes{};

	for (const auto& line : lines) {
		if (line[0] == '#')continue;	//コメント行はスキップする

		//FACE情報を取得する
		if (line[0] == 'f' && isSpace(line[1]))
		{
			std::vector<std::string>tokens = split(line, ' ');
			if (tokens.size() == 4)
			{
				std::vector<VERTEXINFOINDEX>polygonindex{};
				//ポリゴンインデックスを取得する
				polygonindex = GetPolygonIndex(tokens);
				//ポリゴンインデックス群に格納する
				polygonindexes.push_back(polygonindex);
			}
			else {
				std::cout << "3角形ポリゴン以外が存在します" << std::endl;
			}
		}
	}
	return polygonindexes;
}


void GetVertex3D(const char* filename, std::vector<VERTEX_3D>& verticesFor3DVisualization, std::vector<unsigned int>& IndexesFor3DVisualization)
{
	std::vector<char> buffer{};
	std::vector<std::string> lines{};

	//const* char filename = "asset/model/player.obj;
	buffer = readFileToMemory(filename);	//ファイルを読み込んでメモリに展開する

	//ファイルを行単位で分割する
	lines = split(buffer.data(), '\n');

	std::vector<VERTEX> vertices{};
	std::vector<TEXCOORD> texcoords{};
	std::vector<NORMAL> normals{};
	std::vector<std::string> usematerials{};
	std::vector<std::vector<VERTEXINFOINDEX>> polygonindexes;

	//座標データを取得する
	vertices = GetVertex(lines);

	//テクスチャ座標を取得する
	texcoords = GetTexCoord(lines);

	//法線ベクトル
	normals = GetNormal(lines);

	//usematerialを取得する
	usematerials = GetUseMaterial(lines);


	//FACE情報を取得する
	polygonindexes = GetFace(lines);

	std::cout << "ポリゴンインデックス数" << polygonindexes.size() << std::endl;

	//表示するための3D頂点データ
	for (auto& vertexinfoidx : polygonindexes)
	{
		int cnt = 0;
		for (auto& idx : vertexinfoidx) {
			VERTEX_3D v{};
			v.Position = DirectX::SimpleMath::Vector3(
				vertices[idx.vIndex].x,
				vertices[idx.vIndex].y,
				vertices[idx.vIndex].z);

			v.Normal = DirectX::SimpleMath::Vector3(normals[idx.nIndex].nx, normals[idx.nIndex].ny, normals[idx.nIndex].nz);

			v.TexCoord = DirectX::SimpleMath::Vector2(texcoords[idx.tIndex].u, texcoords[idx.tIndex].v);

			v.Diffuse = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);

			verticesFor3DVisualization.push_back(v);

			IndexesFor3DVisualization.push_back(static_cast<int>(verticesFor3DVisualization.max_size()) - 1);
		}
	}
}

