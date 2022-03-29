#pragma once
#include "GL.h"
#include <map>
#include <string>
class CFont {
private:
	HFONT Hfont;
	HDC Hdc;
	int height;
	static std::map<std::string, CFont*> m_instances;
public:
	/*!
	@brief	�R���X�g���N�^
	@param	font			[in]	�t�H���g
	@param	size			[in]	�T�C�Y
	**/
	CFont(const char *font = "�l�r�S�V�b�N", int size=24);
	/*!
	@brief	�����̕\��
	@param	x				[in]	���ʒu
	@param	y				[in]	�c�ʒu
	@param	r				[in]	�F�i�ԁj
	@param	g				[in]	�F�i�΁j
	@param	b				[in]	�F�i�j
	@param	format			[in]	������A����
	**/
	void Draw(int x,int y,float r,float g,float b, const char *format, ...);
	void Draw(int x, int y, float r, float g, float b, const wchar_t *format, ...);

	/*!
	@brief	���
	**/
	void Release();

	static CFont* GetInstance(std::string name);
	static void CreateInstance(std::string name, const char* font = "�l�r�S�V�b�N", int size = 24);
};

#define FONT_T()	CFont::GetInstance("default")
#define FONT(name)	CFont::GetInstance(name)
#define CREATE_FONT(name)	CFont::CreateInstance(name)
#define CREATE_FONT_F(name,font,size)	CFont::CreateInstance(name,font,size)