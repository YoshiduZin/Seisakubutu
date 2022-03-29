#pragma once
#include "GL.h"
#include "CMatrix.h"
#include "CRect.h"
class CCamera;
namespace Utility {
	/*!
		@brief	Degree�i�x�j��Radian�ɕϊ�
		@param	d				[in] �p�x
		@retval	Radian�ɕϊ����ꂽ�p�x
	**/

	inline float DgreeToRadian(float d) {
		return (float)(d*M_PI / 180.0f);
	}
	inline float RadianToDgree(float d) {
		return (float)(d *180.0f/ M_PI);
	}
	/*!
		@brief	�p�x�̐��K��
		@param	a				[in] �p�x
		@retval	-PI�`PI
	**/

	inline float NormalizeAngle(float a) {
		if (a>M_PI) return (float)(a - M_PI * 2);
		else if (a<-M_PI) return (float)(a + M_PI * 2);
		return a;
	}
	/*!
		@brief	�p�x�̍����擾
		@param	a			[in] �p�x
		@param	b			[in] �p�x
		@retval	a��b�̊p�x�̍�
	**/
	inline float DiffAngle(float a, float b) {
		if(a*b < 0){
			if(fabsf(a)+fabsf(b) > M_PI) {
				if (b<0) a -= (float)M_PI * 2;
				else a+=(float)M_PI*2;
			}
		}
		return a-b;
	}
	/*!
		@brief	�����擾
		@param	min				[in] �Œ�l
		@param	max				[in] �ő�l
		@retval	�Œ�l�`�ő�l�̗���
	**/

	template <typename T> inline T Rand(T min,T max) {
		return min + ((max-min) * rand()/ RAND_MAX);
	}
	/*!
		@brief	�X�N���[�����W�ϊ������[���h���W
		@param	out				[out] ���[���h���W
		@param	spos			[in] �X�N���[�����W
		@param	mProj			[in] �ˉe�s��
		@param	mView			[in] �r���[�s��
		@param	viewport		[in] �r���[�|�[�g��`
		@retval	����
	**/
	void ScreenToWorld(CVector3D *out, const CVector3D& spos, const CMatrix& mProj, const CMatrix& mView, const CRect& viewport);

	/*!
	@brief	�X�N���[�����W�ϊ������[���h���W
	@param	out				[out] ���[���h���W
	@param	spos			[in] �X�N���[�����W
	@param	camera			[in] �g�p�J����
	@retval	����
	**/
	void ScreenToWorld(CVector3D *out, const CVector3D& spos, const CCamera* camera);
	void ScreenToWorld(CVector3D *out, const CVector3D& spos);
	/*!
		@brief	���[���h���W���X�N���[�����W�ϊ�
		@param	out				[out] �X�N���[�����W
		@param	wpos			[in] ���[���h���W
		@param	mProj			[in] �ˉe�s��
		@param	mView			[in] �r���[�s��
		@param	viewport		[in] �r���[�|�[�g��`
		@retval	����
	**/
	void WorldToScreen(CVector3D *out, const CVector3D& wpos, const CMatrix& mProj, const CMatrix& mView, const CRect& viewport);
	/*!
	@brief	���[���h���W���X�N���[�����W�ϊ�
	@param	out				[out] �X�N���[�����W
	@param	wpos			[in] ���[���h���W
	@param	camera			[in] �g�p�J����
	**/
	void WorldToScreen(CVector3D *out, const CVector3D& wpos, const CCamera* camera);
	void WorldToScreen(CVector3D *out, const CVector3D& wpos);
	void WorldToScreen(CVector2D *out, const CVector3D& wpos);
	/*!
	@brief	��������
	@param	s				[in] �����̎n�_
	@param	e				[in] �����̏I�_
	@param	color			[in] �F
	@retval	����
	**/
	void DrawLine(const CVector2D &s, const CVector2D &e, const CVector4D &color);

	void DrawQuad(const CVector2D &pos, const CVector2D &size, const CVector4D &color);


	void DrawLine(const CVector3D &s, const CVector3D &e, const CVector4D &color);
	void DrawCube(const CVector3D &pos, const float size, const CVector4D &color);
	void DrawCube(const CMatrix &mat, const float size, const CVector4D &color);
	void DrawSphere(const CVector3D &pos, const float size, const CVector4D &color);
	void DrawSphere(const CMatrix &mat, const float size, const CVector4D &color);
	void DrawCircle(const CVector2D &pos, const float size, const CVector4D &color);
	void DrawCapsule(const CVector3D &s, const CVector3D &e, const float rad, const CVector4D &color);
//	void DrawCapsule(CVector2D & s, CVector2D &e, float size, CVector4D & color);//
}

#define RtoD(x) Utility::RadianToDgree(x)
#define DtoR(x) Utility::DgreeToRadian(x)