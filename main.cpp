#include "stdafx.h"
#include "GID.h"
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#include "Screen/Game.h"

void RenderSkybox();

void MainLoop(void) {

	//--------------------------------------------------------------
	//�Q�[�����̓����͂����ɏ���
	//�Q�[�����͂��̊֐�_��1�b�Ԃ�60��Ăяo���Ă���
	//--------------------------------------------------------------
	
	//�X�J�C�{�b�N�X�̕`��
	RenderSkybox();


	Base::KillCheck();
	Base::UpdateAll();
	Base::CollisionAll();
	Base::RenderAll();
	Base::DrawAll();



	//���E�̎���\��
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
	glEnable(GL_BLEND);//�u�����h�̗L����
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//�Œ�V�F�[�_�[�p
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_ALPHA_TEST);

	CFPS::SetFPS(60);
	//�t���[�����䏉����
	CFPS::Init();
	//�{�^���̐ݒ�
	CInput::Init();
	/* ����̃����[�h */
	CInput::SetButton(0, CInput::eReload, 'R');
	/* �ړ� */
	CInput::SetButton(0, CInput::eUp, 'W');
	CInput::SetButton(0, CInput::eDown, 'S');
	CInput::SetButton(0, CInput::eLeft, 'A');
	CInput::SetButton(0, CInput::eRight, 'D');
	/* �v���C���[�̏�� */
	//�̐�UP
	CInput::SetButton(0, CInput::eChange1, 'C');
	//�̐�Down
	CInput::SetButton(0, CInput::eChange2, VK_SHIFT);
	/* ����{�^�� */
	CInput::SetButton(0, CInput::eGet, VK_SPACE);
	/* ���j���[�{�^�� */
	CInput::SetButton(0, CInput::ePause, VK_TAB);
	/* �}�E�X���� */
	//�U��
	CInput::SetButton(0, CInput::eMouseL, VK_LBUTTON);
	//�\��
	CInput::SetButton(0, CInput::eMouseR, VK_RBUTTON);


	CInput::SetMouseInside(true);
	CInput::ShowCursor(false);
	CInput::UpDate();
	CInput::UpDate();


	//���C�g�ݒ�
	CLight::SetType(0, CLight::eLight_Direction);
	CLight::SetPos(0, CVector3D(0, 200, 200));
	CLight::SetDir(0, CVector3D(-1, -2, 1).GetNormalize());
	CLight::SetColor(0, CVector3D(0.2f, 0.2f, 0.2f), CVector3D(0.8f, 0.8f, 0.8f));


	CLight::SetFogParam(CVector4D(1, 1, 1, 1), 700, 800);
	
	//�J����������
	CCamera::GetCamera()->LookAt(CVector3D(10, 10, 10),
		CVector3D(0, 0, 0),
		CVector3D(0.0, 1.0, 0.0));

	SetCurrentDirectory("data");


	CShader::GetInstance("StaticMesh");
	CShader::GetInstance("SkinMesh");
	CSound::GetInstance();
	
	//������

	//���f���̓ǂݍ���
	/* �v���C���[ */
	ADD_RESOURCE("Player", CModel::CreateModel("Charactor/Player/Player.a3m"));
	
	/* �v���C���[�̗̑� */
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

	//�]���r
	ADD_RESOURCE("Zombie", CModel::CreateModel("Enemy/Zombie.a3m"));

	/* BossEnemy */
	ADD_RESOURCE("BossEnemy", CModel::CreateModel("BossEnemy/BossEnemy.a3m"));

	/* ���� */
	ADD_RESOURCE("Wepon", CModel::CreateModel("Wepon/Scar/Scar.obj"));

	/* �e�� */
	ADD_RESOURCE("AmmoBox", CModel::CreateModel("Wepon/AmmoBox/AmmoBox.obj"));

	/* �� */
	ADD_RESOURCE("Key1", CModel::CreateModel("Object/Key/Key1.obj"));
	ADD_RESOURCE("Key2", CModel::CreateModel("Object/Key/Key2.obj"));

	/* �G�t�F�N�g */
	//�e�e
	ADD_RESOURCE("Bullet", CModel::CreateModel("Effect/BulletHE.obj"));

	/* �}�b�v�֌W */
	ADD_RESOURCE("TutorialField", CModel::CreateModel("Field/KariField/KariField.obj"));
	ADD_RESOURCE("TitleField", CModel::CreateModel("Field/Tutorial/TutorialfField.obj"));
	
	//�h�A
	ADD_RESOURCE("Door", CModel::CreateModel("Field/MainField/MainDoor.obj"));

	/* ���̑� */
	//�������
	ADD_RESOURCE("Sousa", CImage::CreateImage("Image/Sousa/Sousa.png"));
	//�摜�\��(�����ɂ����h�~)
	ADD_RESOURCE("UI_Haikei", CImage::CreateImage("Image/UI/Matome.png"));
	//��ʕ\��(����A�C�R��)
	ADD_RESOURCE("UI_Icon1", CImage::CreateImage("Image/UI/Icon1.png"));
	//�摜�\��(�e�򐔂Ƒ��U���̎d�؂�)
	ADD_RESOURCE("UI_Shikiri", CImage::CreateImage("Image/UI/Shikiri.png"));
	//��ʕ\��(����)
	ADD_RESOURCE("UI_Numbers", CImage::CreateImage("Image/UI/UI.png"));
	//����L�[�\��
	ADD_RESOURCE("SpaceKey", CImage::CreateImage("Image/UI/SpaceKey.png"));
	//�e��30
	ADD_RESOURCE("Tama30", CImage::CreateImage("Image/UI/Tama30.png"));
	//�e��100
	ADD_RESOURCE("Tama100", CImage::CreateImage("Image/UI/Tama100.png"));
	//�^�C�g�����
	ADD_RESOURCE("Title", CImage::CreateImage("Image/GameScene/Title.png"));
	//�^�C�g�����(�I��)
	ADD_RESOURCE("Sentaku", CImage::CreateImage("Image/GameScene/Sentaku.png"));
	//�Q�[���N���A���
	ADD_RESOURCE("GameClear", CImage::CreateImage("Image/GameScene/GameClear.png"));
	//�Q�[���I�[�o�[���
	ADD_RESOURCE("GameOver", CImage::CreateImage("Image/GameScene/GameOver.png"));
	//�|�[�Y���
	ADD_RESOURCE("Pause", CImage::CreateImage("Image/GameScene/Pause.png"));
	//�ē����
	ADD_RESOURCE("Arrow", CModel::CreateModel("Object/Arrow/Arrow.obj"));
	//�Z�[�u�|�C���g
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

	//��ʉ𑜓x�ϓ�
	CCamera::GetCamera()->SetSize((float)w, (float)h);
	//��ʉ𑜓x�Œ�
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

//�t���X�N���[��?�E�C���h�E���[�h�̐؂�ւ�
//Alt+Enter�Ő؂�ւ���
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
	// ���������[�N���o
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
		//���݂̃V�X�e���̃J�E���g�����擾
		QueryPerformanceCounter(&time_buf);

		CInput::UpDate();
		//�e�o�b�t�@�[���N���A
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
		//���C���J�����̐ݒ�𕡐�
		*CCamera::GetCamera(CCamera::eSkyBox) = *CCamera::GetCamera(CCamera::eMainCamera);
		for (int i = 0; i < skybox->GetMaterialSize(); i++) {
			if (CTexture* t = skybox->GetMaterial(i)->m_pTex) {
				t->SetWrapST(GL_CLAMP_TO_EDGE);
				t->SetFilter(GL_LINEAR);
			}
		}
	}
	//�f�v�X�e�X�gOFF
//�����ł̕`��͐[�x�o�b�t�@�։e�����Ȃ�
	glDisable(GL_DEPTH_TEST);
	//���ݎg�p���̃J�������擾
	CCamera* back = CCamera::GetCurrent();
	//���݂̃J�����̃r���[�s����擾
	CMatrix matrix = back->GetViewMatrix();
	//�X�J�{�b�N�X�p�J�������擾
	CCamera* c = CCamera::GetCamera(CCamera::eSkyBox);
	//�r���[�s��̍��W�𖳌���
	matrix.m03 = 0; matrix.m13 = 0; matrix.m23 = 0;
	//�X�J�C�{�b�N�X�p�̃r���[�s��ݒ�
	c->SetViewMatrix(matrix);
	//�X�J�C�{�b�N�X�p�̓��e�s��ݒ�(���݂̃J�����Ɠ����l�ɂ���)
	c->SetProjectionMatrix(back->GetProjectionMatrix());
	//�g�p����J�������X�J�C�{�b�N�X�p�ɐݒ�
	CCamera::SetCurrent(c);
	//���C�e�B���OOFF
	CLight::SetLighting(false);


	//�X�J�{�b�N�X�`��
	skybox->Render();


	//���̐ݒ�ɖ߂�
	CLight::SetLighting(true);
	CCamera::SetCurrent(back);
	glEnable(GL_DEPTH_TEST);

}
