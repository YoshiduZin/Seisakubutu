#pragma once
#include "../stdafx.h"
#include "../Base/Base.h"

class Camera : public Base
{
public:
	/* CMatrix */
	//プレイヤーの行列
	CMatrix Player_Matrix;
	//支点
	CMatrix Parent_Matrix;
	//カメラの行列
	CMatrix Camera_Matrix;

	CMatrix Move_Camera;
public:
	//コンストラクタ
	Camera();
	//更新
	void Update();
	//描画
	void Render();
};
