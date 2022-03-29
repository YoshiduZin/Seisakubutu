#include "stdafx.h"
#include "GID.h"
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#include "Screen/Game.h"

void RenderSkybox();

void MainLoop(void) {

	//--------------------------------------------------------------
	//ゲーム中の動きはここに書く
	//ゲーム中はこの関数_を1秒間に60回呼び出している
	//--------------------------------------------------------------
	
	//スカイボックスの描画
	RenderSkybox();


	Base::KillCheck();
	Base::UpdateAll();
	Base::CollisionAll();
	Base::RenderAll();
	Base::DrawAll();



	//世界の軸を表示
	//Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(100, 0, 0), CVector4D(1, 0, 0, 1));
	//Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(0, 100, 0), CVector4D(0, 1, 0, 1));
	//Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(0, 0, 100), CVector4D(0, 0, 1, 1));

	//for (int i = -5; i <= 5; i++) {
	//	Utility::DrawLine(CVector3D(-5, 0, i * 1.0f), CVector3D(5, 0, i*1.0f), CVector4D(0.2, 0.2, 0.2, 1));
	//	Utility::DrawLine(CVector3D(i*1.0f, 0, -5), CVector3D(i*1.0f, 0, 5), CVector4D(0.2, 0.2, 0.2, 1));
	//}
	
}
void Init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);//ブレンドの有効化
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//固定シェーダー用
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_ALPHA_TEST);

	CFPS::SetFPS(60);
	//フレーム制御初期化
	CFPS::Init();
	//ボタンの設定
	CInput::Init();
	/* 武器のリロード */
	CInput::SetButton(0, CInput::eReload, 'R');
	/* 移動 */
	CInput::SetButton(0, CInput::eUp, 'W');
	CInput::SetButton(0, CInput::eDown, 'S');
	CInput::SetButton(0, CInput::eLeft, 'A');
	CInput::SetButton(0, CInput::eRight, 'D');
	/* プレイヤーの状態 */
	//体制UP
	CInput::SetButton(0, CInput::eChange1, 'C');
	//体制Down
	CInput::SetButton(0, CInput::eChange2, VK_SHIFT);
	/* 決定ボタン */
	CInput::SetButton(0, CInput::eGet, VK_SPACE);
	/* メニューボタン */
	CInput::SetButton(0, CInput::ePause, VK_TAB);
	/* マウス操作 */
	//攻撃
	CInput::SetButton(0, CInput::eMouseL, VK_LBUTTON);
	//構え
	CInput::SetButton(0, CInput::eMouseR, VK_RBUTTON);


	CInput::SetMouseInside(true);
	CInput::ShowCursor(false);
	CInput::UpDate();
	CInput::UpDate();


	//ライト設定
	CLight::SetType(0, CLight::eLight_Direction);
	CLight::SetPos(0, CVector3D(0, 200, 200));
	CLight::SetDir(0, CVector3D(-1, -2, 1).GetNormalize());
	CLight::SetColor(0, CVector3D(0.2f, 0.2f, 0.2f), CVector3D(0.8f, 0.8f, 0.8f));


	CLight::SetFogParam(CVector4D(1, 1, 1, 1), 700, 800);
	
	//カメラ初期化
	CCamera::GetCamera()->LookAt(CVector3D(10, 10, 10),
		CVector3D(0, 0, 0),
		CVector3D(0.0, 1.0, 0.0));

	SetCurrentDirectory("data");


	CShader::GetInstance("StaticMesh");
	CShader::GetInstance("SkinMesh");
	CSound::GetInstance();
	
	//初期化

	//モデルの読み込み
	/* プレイヤー */
	ADD_RESOURCE("Player", CModel::CreateModel("Charactor/Player/Player.a3m"));
	
	/* プレイヤーの体力 */
	ADD_RESOURCE("Hp10", CImage::CreateImage("Image/Hp/Hp10.png"));
	ADD_RESOURCE("Hp9", CImage::CreateImage("Image/Hp/Hp9.png"));
	ADD_RESOURCE("Hp8", CImage::CreateImage("Image/Hp/Hp8.png"));
	ADD_RESOURCE("Hp7", CImage::CreateImage("Image/Hp/Hp7.png"));
	ADD_RESOURCE("Hp6", CImage::CreateImage("Image/Hp/Hp6.png"));
	ADD_RESOURCE("Hp5", CImage::CreateImage("Image/Hp/Hp5.png"));
	ADD_RESOURCE("Hp4", CImage::CreateImage("Image/Hp/Hp4.png"));
	ADD_RESOURCE("Hp3", CImage::CreateImage("Image/Hp/Hp3.png"));
	ADD_RESOURCE("Hp2", CImage::CreateImage("Image/Hp/Hp2.png"));
	ADD_RESOURCE("Hp1", CImage::CreateImage("Image/Hp/Hp1.png"));
	ADD_RESOURCE("Hp0", CImage::CreateImage("Image/Hp/Hp0.png"));

	//ゾンビ
	ADD_RESOURCE("Zombie", CModel::CreateModel("Enemy/Zombie.a3m"));

	/* BossEnemy */
	ADD_RESOURCE("BossEnemy", CModel::CreateModel("BossEnemy/BossEnemy.a3m"));

	/* 武器 */
	ADD_RESOURCE("Wepon", CModel::CreateModel("Wepon/Scar/Scar.obj"));

	/* 弾薬箱 */
	ADD_RESOURCE("AmmoBox", CModel::CreateModel("Wepon/AmmoBox/AmmoBox.obj"));

	/* 鍵 */
	ADD_RESOURCE("Key1", CModel::CreateModel("Object/Key/Key1.obj"));
	ADD_RESOURCE("Key2", CModel::CreateModel("Object/Key/Key2.obj"));

	/* エフェクト */
	//銃弾
	ADD_RESOURCE("Bullet", CModel::CreateModel("Effect/BulletHE.obj"));

	/* マップ関係 */
	ADD_RESOURCE("TutorialField", CModel::CreateModel("Field/KariField/KariField.obj"));
	ADD_RESOURCE("TitleField", CModel::CreateModel("Field/Tutorial/TutorialfField.obj"));
	
	//ドア
	ADD_RESOURCE("Door", CModel::CreateModel("Field/MainField/MainDoor.obj"));

	/* その他 */
	//操作説明
	ADD_RESOURCE("Sousa", CImage::CreateImage("Image/Sousa/Sousa.png"));
	//画像表示(見えにくい防止)
	ADD_RESOURCE("UI_Haikei", CImage::CreateImage("Image/UI/Matome.png"));
	//画面表示(武器アイコン)
	ADD_RESOURCE("UI_Icon1", CImage::CreateImage("Image/UI/Icon1.png"));
	//画像表示(弾薬数と装填数の仕切り)
	ADD_RESOURCE("UI_Shikiri", CImage::CreateImage("Image/UI/Shikiri.png"));
	//画面表示(数字)
	ADD_RESOURCE("UI_Numbers", CImage::CreateImage("Image/UI/UI.png"));
	//決定キー表示
	ADD_RESOURCE("SpaceKey", CImage::CreateImage("Image/UI/SpaceKey.png"));
	//弾薬30
	ADD_RESOURCE("Tama30", CImage::CreateImage("Image/UI/Tama30.png"));
	//弾薬100
	ADD_RESOURCE("Tama100", CImage::CreateImage("Image/UI/Tama100.png"));
	//タイトル画面
	ADD_RESOURCE("Title", CImage::CreateImage("Image/GameScene/Title.png"));
	//タイトル画面(選択)
	ADD_RESOURCE("Sentaku", CImage::CreateImage("Image/GameScene/Sentaku.png"));
	//ゲームクリア画面
	ADD_RESOURCE("GameClear", CImage::CreateImage("Image/GameScene/GameClear.png"));
	//ゲームオーバー画面
	ADD_RESOURCE("GameOver", CImage::CreateImage("Image/GameScene/GameOver.png"));
	//ポーズ画面
	ADD_RESOURCE("Pause", CImage::CreateImage("Image/GameScene/Pause.png"));
	//案内矢印
	ADD_RESOURCE("Arrow", CModel::CreateModel("Object/Arrow/Arrow.obj"));
	//セーブポイント
	ADD_RESOURCE("Save", CModel::CreateModel("Object/Save/Save.obj"));

	Base::Add(new Game);
}


void Release()
{
	CLoadThread::ClearInstance();
	CSound::ClearInstance();
	CResourceManager::ClearInstance();
}

static void ResizeCallback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);

	//画面解像度変動
	CCamera::GetCamera()->SetSize((float)w, (float)h);
	//画面解像度固定
	//CCamera::GetCamera()->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	//CCamera::GetCamera()->SetScreenRect(CRect(0, 0, (float)w, (float)h));
	CCamera::GetCamera()->Viewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	CMatrix mProj;
	mProj.Perspective(Utility::DgreeToRadian(60.0), (float)w / (float)h, 0.1, 10000.0);
	CCamera::GetCurrent()->SetProjectionMatrix(mProj);
	glLoadMatrixf(mProj.f);

	glfwGetWindowPos(window, &GL::window_x, &GL::window_y);
	GL::UpdateWindowRect(GL::window_x, GL::window_y, w, h);
	CInput::UpdateClipCursor(true);

}
static void WheelCallback(GLFWwindow* _window, double _offsetx, double _offsety) {
	CInput::AddMouseWheel((int)_offsety);

}
static void PosCallback(GLFWwindow* _window, int x, int y) {
	GL::window_x = x;
	GL::window_y = y;
	GL::UpdateWindosRect(x, y, GL::window_width, GL::window_height);
	CInput::UpdateClipCursor(true);

}
static void FocusCallback(GLFWwindow* _window, int f) {
	CInput::UpdateClipCursor(f);
	GL::focus = f;
}

static void error_callback(int error, const char* description)
{
	printf("Error: %s\n", description);
}

//フルスクリーン?ウインドウモードの切り替え
//Alt+Enterで切り替える
void CheckFullScreen() {
	static CVector2D pos;
	static int key_enter = 0;
	static bool full_screen = false;
	int key_enter_buf = key_enter;
	
	if (key_enter_buf ^ (key_enter = glfwGetKey(GL::window, GLFW_KEY_ENTER)) && key_enter && glfwGetKey(GL::window, GLFW_KEY_LEFT_ALT)) {
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		if (!full_screen) {
			glfwGetWindowPos(GL::window, &pos.ix, &pos.iy);
			glfwSetWindowMonitor(GL::window, monitor, 0, 0, GL::window_width, GL::window_height, mode->refreshRate);
			full_screen = true;
		}
		else {
			glfwSetWindowMonitor(GL::window, nullptr, pos.ix, pos.iy, GL::window_width, GL::window_height, mode->refreshRate);
			full_screen = false;
		}
	}
	
}

int __main(int* argcp, char** argv) {
	// メモリリーク検出
	//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	//OpenGL4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) return -1;
	//	glutInit(argcp, argv);

	GL::window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Simple", nullptr, nullptr);
	glfwGetWindowSize(GL::window, &GL::window_width, &GL::window_height);
	glfwGetWindowPos(GL::window, &GL::window_x, &GL::window_y);

	glfwSetFramebufferSizeCallback(GL::window, ResizeCallback);
	glfwSetScrollCallback(GL::window, WheelCallback);
	glfwSetWindowFocusCallback(GL::window, FocusCallback);
	glfwSetWindowPosCallback(GL::window, PosCallback);
	if (!GL::window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(GL::window);
	glfwSwapInterval(1);
	ResizeCallback(GL::window, SCREEN_WIDTH, SCREEN_HEIGHT);

	GLenum err = glewInit();
	if (err == GLEW_OK) {
		printf("%s\n", glewGetString(GLEW_VERSION));
	}
	else {
		printf("%s\n", glewGetErrorString(err));
		getchar();
		return -1;
	}
	HDC glDc = wglGetCurrentDC();
	GL::hWnd = WindowFromDC(glDc);

	Init();
	///*
	static CVector2D pos;
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwGetWindowPos(GL::window, &pos.ix, &pos.iy);
	glfwSetWindowMonitor(GL::window, monitor, 0, 0, GL::window_width, GL::window_height, mode->refreshRate);
	//*/
	while (!glfwWindowShouldClose(GL::window)) {
		CheckFullScreen();
		static LARGE_INTEGER time;
		static LARGE_INTEGER time_buf;
		static long t_buf = 0;
		//現在のシステムのカウント数を取得
		QueryPerformanceCounter(&time_buf);

		CInput::UpDate();
		//各バッファーをクリア
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		MainLoop();


		glfwSwapBuffers(GL::window);


		CFPS::Wait();

		char title[32];
		sprintf_s(title, "sample fps:%d dt:%.3f", CFPS::GetFPS(), CFPS::GetDeltaTime());
		glfwSetWindowTitle(GL::window, title);

		glfwPollEvents();
		if (glfwGetKey(GL::window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(GL::window, GL_TRUE);
		}

	}

	glfwTerminate();




	Release();
	return 0;
}

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR argv, INT argc)
{
	return __main(&__argc, __argv);
}

int main(int argc, char** argv)
{
	return __main(&argc, argv);
}

void RenderSkybox() {
	static CModel* skybox = nullptr;
	if (!skybox) {
		ADD_RESOURCE("Sky", CModel::CreateModel("Field/Sky/Sky.obj"));
		skybox = GET_RESOURCE("Sky", CModel);
		//メインカメラの設定を複製
		*CCamera::GetCamera(CCamera::eSkyBox) = *CCamera::GetCamera(CCamera::eMainCamera);
		for (int i = 0; i < skybox->GetMaterialSize(); i++) {
			if (CTexture* t = skybox->GetMaterial(i)->m_pTex) {
				t->SetWrapST(GL_CLAMP_TO_EDGE);
				t->SetFilter(GL_LINEAR);
			}
		}
	}
	//デプステストOFF
//ここでの描画は深度バッファへ影響しない
	glDisable(GL_DEPTH_TEST);
	//現在使用中のカメラを取得
	CCamera* back = CCamera::GetCurrent();
	//現在のカメラのビュー行列を取得
	CMatrix matrix = back->GetViewMatrix();
	//スカボックス用カメラを取得
	CCamera* c = CCamera::GetCamera(CCamera::eSkyBox);
	//ビュー行列の座標を無効に
	matrix.m03 = 0; matrix.m13 = 0; matrix.m23 = 0;
	//スカイボックス用のビュー行列設定
	c->SetViewMatrix(matrix);
	//スカイボックス用の投影行列設定(現在のカメラと同じ値にする)
	c->SetProjectionMatrix(back->GetProjectionMatrix());
	//使用するカメラをスカイボックス用に設定
	CCamera::SetCurrent(c);
	//ライティングOFF
	CLight::SetLighting(false);


	//スカボックス描画
	skybox->Render();


	//元の設定に戻す
	CLight::SetLighting(true);
	CCamera::SetCurrent(back);
	glEnable(GL_DEPTH_TEST);

}
