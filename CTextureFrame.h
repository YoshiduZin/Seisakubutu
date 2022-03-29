#pragma once
#include "CVector.h"
#include "CTexture.h"

class CTextureFrame {
	CVector4D m_clear_color;
	CTexture *mp_texture;	//!描画先テクスチャー
	GLuint m_frame;			//!フレームバッファ
	GLuint m_render;		//!レンダーバッファ
public:
	/**
	* @fn コンストラクタ
	* コンストラクタ
	* @brief 描画先テクスチャー指定しインスタンスを生成する。
	* @param t	[in]　描画先テクスチャー
	* @param t	[in]　画面消去色

	*/
	CTextureFrame(CTexture* tex,const CVector4D& clear_color);
	/**
	* @fn デストラクタ
	* デストラクタ
	* @brief バッファを破棄します。テクスチャーは破棄されません。
	*/
	~CTextureFrame();
	/**
	* @fn 描画開始
	* 
	* @brief BeginDraw ～　EndDrawの間は、描画先がテクスチャーになります。
	*/
	void BeginDraw();
	/**
	* @fn 描画終了
	*
	* @brief BeginDraw ～　EndDrawの間は、描画先がテクスチャーになります。
	*/
	void EndDraw();

	/*!
		@brief	テクスチャーの幅を取得
		@retval	テクスチャーの幅
	**/
	float GetWidth();
	/*!
		@brief	テクスチャー高さを取得
		@retval	テクスチャー高さ
	**/
	float GetHeight();

	CTexture* GetTexture() {
		return mp_texture;
	}
};
