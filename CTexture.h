#pragma once

#include "GL.h"
#include "CResource.h"

class CTexture : public CResource{
private:
	unsigned char *m_data;
	int m_wrap;
	int m_filter;
public:
	int	m_width;
	int m_height;
	int m_internalFormat;
	int m_format;
	unsigned int m_imgSize;
	int m_type;

	unsigned int m_bufID;
	bool loadTiff(const char *path);
	bool loadBmp(const char *path);
	bool loadPng(const char *path);
public:
	CTexture();
	~CTexture();
	static CTexture* LoadTexture(const char *path);
	bool Load(const char *path);
	void MapTexture();
	void UnmapTexture();
	void Release();

	void SetWrapST(int wrapst);
	void SetFilter(int filter);

	
	void Draw();
};