#pragma once
#include "CVector.h"
#include "CTexture.h"

class CTextureFrame {
	CVector4D m_clear_color;
	CTexture *mp_texture;	//!�`���e�N�X�`���[
	GLuint m_frame;			//!�t���[���o�b�t�@
	GLuint m_render;		//!�����_�[�o�b�t�@
public:
	/**
	* @fn �R���X�g���N�^
	* �R���X�g���N�^
	* @brief �`���e�N�X�`���[�w�肵�C���X�^���X�𐶐�����B
	* @param t	[in]�@�`���e�N�X�`���[
	* @param t	[in]�@��ʏ����F

	*/
	CTextureFrame(CTexture* tex,const CVector4D& clear_color);
	/**
	* @fn �f�X�g���N�^
	* �f�X�g���N�^
	* @brief �o�b�t�@��j�����܂��B�e�N�X�`���[�͔j������܂���B
	*/
	~CTextureFrame();
	/**
	* @fn �`��J�n
	* 
	* @brief BeginDraw �`�@EndDraw�̊Ԃ́A�`��悪�e�N�X�`���[�ɂȂ�܂��B
	*/
	void BeginDraw();
	/**
	* @fn �`��I��
	*
	* @brief BeginDraw �`�@EndDraw�̊Ԃ́A�`��悪�e�N�X�`���[�ɂȂ�܂��B
	*/
	void EndDraw();

	/*!
		@brief	�e�N�X�`���[�̕����擾
		@retval	�e�N�X�`���[�̕�
	**/
	float GetWidth();
	/*!
		@brief	�e�N�X�`���[�������擾
		@retval	�e�N�X�`���[����
	**/
	float GetHeight();

	CTexture* GetTexture() {
		return mp_texture;
	}
};
