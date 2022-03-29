#include "CTextureFrame.h"


CTextureFrame::CTextureFrame(CTexture* tex, const CVector4D& clear_color)
{
	m_clear_color = clear_color;

	mp_texture = tex;
	//描画処理がテクスチャーに書き込めるように設定
	//フレームバッファ作成
	glGenFramebuffersEXT(1, &m_frame);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_frame);


	//レンダーバッファ作成
	glGenRenderbuffersEXT(1, &m_render);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_render);

	//メモリ確保
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, mp_texture->m_width, mp_texture->m_height);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);


	//テクスチャー接続
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, mp_texture->m_bufID, 0);

	//レンダーバッファ接続
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, m_render);


	//通常描画へ戻す
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

CTextureFrame::~CTextureFrame()
{
	glDeleteRenderbuffers(1, &m_render);
	glDeleteFramebuffers(1, &m_frame);
}

void CTextureFrame::BeginDraw()
{
	//フレームバッファ有効化。以降の描画処理は m_blackの画像へ書き込まれる。
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_frame);
	float back_color[4];
	glGetFloatv(GL_COLOR_CLEAR_VALUE,back_color);
	//透明で消去
	glClearColor(m_clear_color.r, m_clear_color.g, m_clear_color.b, m_clear_color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//クリアカラーを元に戻す
	glClearColor(back_color[0], back_color[1], back_color[2], back_color[3]);
}

void CTextureFrame::EndDraw()
{
	
	//m_blackへの書き込み終了
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	//ここまでの描画命令を一旦処理
	glFlush();
}

float CTextureFrame::GetWidth()
{
	return mp_texture->m_width;
}

float CTextureFrame::GetHeight()
{
	return mp_texture->m_height;
}
