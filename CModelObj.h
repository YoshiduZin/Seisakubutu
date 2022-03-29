/*!
*	@brief	OBJ用モデルクラス
*
*
**/
#pragma once
#include "GL.h"
#include "CTexture.h"
#include "CModel.h"
#include "vector"


struct SObjModelHeader {
	char fileType[2];
	unsigned short verversion;
	int		m_materialCnt;
	SVector3D m_cut;
};


class CMeshObj {
public:
	struct SVertex{
		CVector3D v;
		CVector3D n;
		CVector2D t;
	};
	SVertex *mp_vertex_array;
	
	std::vector<int> *m_colIdex;
	CVector3D	*m_colmin;
	CVector3D	*m_colmax;
	int			m_vertexNum;		//頂点数
	CMaterial	m_material;		//マテリアルデータ
	CVector3D	m_max;
	CVector3D	m_min;
	CVector3D	m_cut;
	unsigned long *m_colmask;
	CVector3D	m_length;
	GLuint		m_buffer;
	GLuint		m_vao;
	
	CMeshObj();
	void Render(CShader *shader);
	void Release();
	void CreatCollsionIndex(CVector3D cut);
	bool CollisionRay(CVector3D *c, CVector3D *n, const CVector3D &s, const CVector3D &e,const CVector3D& dir,float *pLength);
	int CollisionSphere(CCollTriangle *out, const CVector3D &center, float radius, int maxcnt,int matNo);
	int CollisionCupsel(CCollTriangle *out, const CVector3D &top, const CVector3D &bottom, float radius, int maxcnt,int matNo);
	int GetIndex(int x, int y, int z) {
		return x + (z*m_cut.ix) + (y*m_cut.iz*m_cut.ix);
	}
	void LoadBinary(FILE *fp, const char *filepath);
};
/*!
		@brief	OBJファイル用モデルクラス
**/
class CModelObj : public CModel {
private:
	
	CMeshObj *m_mesh;
	int		m_materialCnt;
	CVector3D	m_cut;
	/*!
		@brief	マテリアルデータの読み込み
		@param	path		[in]	ファイル名
		@retval	無し
	**/
	bool	LoadMaterial(char *path);
	bool	LoadBinary(const char *path);
public:

	/*!
		@brief	コンストラクタ
	**/
	CModelObj();

	/*!
		@brief	デストラクタ
	**/
	~CModelObj();

	/*!
		@brief	OBJファイルからモデルデータを読み込む
		@param	path				[in] ファイル名
		@retval	無し
	**/
	bool	Load(const char *path);


	/*!
	@brief	OBJファイルからモデルデータを読み込む
	@param	path				[in] ファイル名
	@param	raw					[in] X分割数
	@param	col					[in] Z分割数
	@retval	無し
	**/
	bool	Load(const char *path,int cut_x,int cut_y, int cut_z);

	/*!
		@brief	描画を行う
		@param	m				[in] ワールド行列
		@retval	無し
	**/
	void	Render(CMatrix &m);

	/*!
		@brief	描画する
		@retval	無し
	**/
	void Render();

	/*!
		@brief	モデルデータを破棄する
		@retval	無し
	**/
	void	Release();


	/*!
	@brief	マテリアルの取得
	@param	no				[in] マテリアル番号
	@retval	マテリアルのポインタ
	**/
	CMaterial	*GetMaterial(int no) const {
		return &m_mesh[no].m_material;
	}
	/*!
	@brief	マテリアル数の取得
	@param	no				[in] マテリアル番号
	@retval	マテリアルのポインタ
	**/
	int GetMaterialSize() const {
		return m_materialCnt;
	}

	/*!
	@brief	線分とモデルの判定
	@param	c				[out] 接触地点
	@param	s				[in] 線分の開始地点
	@param	e				[in] 線分の終了地点
	@retval	true:接触　false:非接触
	**/
	bool CollisionRay(CVector3D *c, CVector3D *n, const CVector3D &s, const CVector3D &e)const;


	/*!
	@brief	球とモデルの判定
	@param	out				[out] 接触データ
	@param	center			[in] 球の中心
	@param	radius			[in] 球の半径
	@retval	接触ポリゴン数
	**/
	int CollisionSphere(CCollTriangle *out, const CVector3D &center, float radius, int maxcnt = 64)const;



	/*!
	@brief	カプセルとモデルの判定
	@param	out				[out] 接触データ
	@param	top				[in] カプセルの天井
	@param	bottom			[in] カプセルの底
	@param	radius			[in] 球の半径
	@retval	接触ポリゴン数
	**/
	int CollisionCupsel(CCollTriangle *out, const CVector3D &top, const CVector3D &bottom, float radius, int maxcnt = 64)const;


	/*!
	@brief	モデルオブジェクトの生成[obj]
	@param	path			[in] モデルファイル名
	@param	raw					[in] X分割数
	@param	col					[in] Z分割数
	@retval 成功:モデルオブジェクト 失敗:null
	**/
	static CModelObj* CreateModel(char *path, int cut_x=1, int cut_y=1, int cut_z=1);


	friend class CModelA3M;
};