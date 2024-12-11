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


//��������w��̋�؂蕶���ŕ�������
std::vector<std::string>split(const std::string& inputstring, char delimiter) {
	std::vector<std::string>tokens;
	std::string token;

	std::stringstream stringstream(inputstring);

	while (getline(stringstream, token, delimiter)) {
		tokens.push_back(token);
	}

	return tokens;
}
//�t�@�C����ǂݍ���Ń������ɓW�J����
std::vector<char>readFileToMemory(const std::string& filename)
{
	//���̓t�@�C���X�g���[�����J���i�o�C�i�����[�h�ŊJ���j
	std::ifstream file(filename, std::ios::binary | std::ios::ate);

	if (file.is_open() == false) {
		std::cerr << "�t�@�C�����J���܂���" << filename << std::endl;
		return {};
	}

	//�t�@�C���T�C�Y���擾����
	std::streamsize size = file.tellg();

	std::vector<char> buffer(size);	//�t�@�C���̓��e���i�[���邽�߂̃o�b�t�@


	//�t�@�C���̓��e���x�N�^�[�ɓǂݍ���
	file.seekg(0, std::ios::beg);	//�t�@�C���|�C���^��擪�ɖ߂�
	if (file.read(buffer.data(), size))
	{
		std::cout << "�t�@�C��������ɓǂݍ��܂�܂����B�T�C�Y" << size << "�o�C�g" << std::endl;
	}
	else {
		std::cerr << "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
		buffer.clear();
	}

	return buffer;
}

//���_�f�[�^
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

	//���_�f�[�^���擾����
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

//�e�N�X�`�����W
struct TEXCOORD {
	float u, v;
};

std::vector<TEXCOORD>GetTexCoord(const std::vector<std::string>& lines)
{
	std::vector<TEXCOORD>texcoords{};

	//�e�N�X�`�����W���擾����
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

//�@���x�N�g��
struct NORMAL {
	float nx, ny, nz;
};

std::vector<NORMAL> GetNormal(const std::vector<std::string>& lines)
{
	std::vector<NORMAL>normals{};
	//�@���x�N�g�����擾����
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

//USEMATERIA�擾
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
//���_�����\��������̃C���f�b�N�X���K�肷��
struct VERTEXINFOINDEX {
	unsigned int vIndex;	//���_�C���f�b�N�X
	unsigned int tIndex;	//�e�N�X�`���C���f�b�N�X
	unsigned int nIndex;	//�@���C���f�b�N�X
};

//�����̒��ɂ̓X�y�[�X�ŋ�؂�ꂽ�����񌻂񂪓����Ă���if 1/2/3 4/5/6 �j
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
			std::cout << "���_�C���f�b�N�X�E�e�N�X�`���C���f�b�N�X�E�@���C���f�b�N�X�ȊO������܂�" << std::endl;
		}
	}
	return polygonindexes;
}
//�ʂ��\�����钸�_�C���f�b�N�X���擾����
std::vector<std::vector<VERTEXINFOINDEX>>GetFace(const std::vector<std::string>& lines)
{
	//�|���S�����\�����钸�_���C���f�b�N�X���i�[����
	std::vector<std::vector<VERTEXINFOINDEX>>polygonindexes{};

	for (const auto& line : lines) {
		if (line[0] == '#')continue;	//�R�����g�s�̓X�L�b�v����

		//FACE�����擾����
		if (line[0] == 'f' && isSpace(line[1]))
		{
			std::vector<std::string>tokens = split(line, ' ');
			if (tokens.size() == 4)
			{
				std::vector<VERTEXINFOINDEX>polygonindex{};
				//�|���S���C���f�b�N�X���擾����
				polygonindex = GetPolygonIndex(tokens);
				//�|���S���C���f�b�N�X�Q�Ɋi�[����
				polygonindexes.push_back(polygonindex);
			}
			else {
				std::cout << "3�p�`�|���S���ȊO�����݂��܂�" << std::endl;
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
	buffer = readFileToMemory(filename);	//�t�@�C����ǂݍ���Ń������ɓW�J����

	//�t�@�C�����s�P�ʂŕ�������
	lines = split(buffer.data(), '\n');

	std::vector<VERTEX> vertices{};
	std::vector<TEXCOORD> texcoords{};
	std::vector<NORMAL> normals{};
	std::vector<std::string> usematerials{};
	std::vector<std::vector<VERTEXINFOINDEX>> polygonindexes;

	//���W�f�[�^���擾����
	vertices = GetVertex(lines);

	//�e�N�X�`�����W���擾����
	texcoords = GetTexCoord(lines);

	//�@���x�N�g��
	normals = GetNormal(lines);

	//usematerial���擾����
	usematerials = GetUseMaterial(lines);


	//FACE�����擾����
	polygonindexes = GetFace(lines);

	std::cout << "�|���S���C���f�b�N�X��" << polygonindexes.size() << std::endl;

	//�\�����邽�߂�3D���_�f�[�^
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

