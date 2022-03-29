#include "CTextureFrame.h"


CTextureFrame::CTextureFrame(CTexture* tex, const CVector4D& clear_color)
{
	m_clear_color = clear_color;

	mp_texture = tex;
	//�`�揈�����e�N�X�`���[�ɏ������߂�悤�ɐݒ�
	//�t���[���o�b�t�@�쐬
	glGenFramebuffersEXT(1, &m_frame);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_frame);


	//�����_�[�o�b�t�@�쐬
	glGenRenderbuffersEXT(1, &m_render);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_render);

	//�������m��
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, mp_texture->m_width, mp_texture->m_height);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);


	//�e�N�X�`���[�ڑ�
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, mp_texture->m_bufID, 0);

	//�����_�[�o�b�t�@�ڑ�
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, m_render);


	//�ʏ�`��֖߂�
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

CTextureFrame::~CTextureFrame()
{
	glDeleteRenderbuffers(1, &m_render);
	glDeleteFramebuffers(1, &m_frame);
}

void CTextureFrame::BeginDraw()
{
	//�t���[���o�b�t�@�L�����B�ȍ~�̕`�揈���� m_black�̉摜�֏������܂��B
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_frame);
	float back_color[4];
	glGetFloatv(GL_COLOR_CLEAR_VALUE,back_color);
	//�����ŏ���
	glClearColor(m_clear_color.r, m_clear_color.g, m_clear_color.b, m_clear_color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//�N���A�J���[�����ɖ߂�
	glClearColor(back_color[0], back_color[1], back_color[2], back_color[3]);
}

void CTextureFrame::EndDraw()
{
	
	//m_black�ւ̏������ݏI��
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	//�����܂ł̕`�施�߂���U����
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
