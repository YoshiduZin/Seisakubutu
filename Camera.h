#pragma once
#include "../stdafx.h"
#include "../Base/Base.h"

class Camera : public Base
{
public:
	/* CMatrix */
	//�v���C���[�̍s��
	CMatrix Player_Matrix;
	//�x�_
	CMatrix Parent_Matrix;
	//�J�����̍s��
	CMatrix Camera_Matrix;

	CMatrix Move_Camera;
public:
	//�R���X�g���N�^
	Camera();
	//�X�V
	void Update();
	//�`��
	void Render();
};
