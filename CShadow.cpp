#include "CShadow.h"

CShadow *CShadow::m_shadow=nullptr;

CShadow::CShadow(int screenWidth, int screenHeight,float length,int texWidth, int texHeight): m_state(eNone) {
	
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	m_texHeight = texHeight;
	m_texWidth = texWidth;
	m_length = length;

	glActiveTexture(GL_TEXTURE0);

	// �J���[�o�b�t�@�p�̃e�N�X�`����p�ӂ���
	glGenTextures(1, &m_effectBuffer);
	glBindTexture(GL_TEXTURE_2D, m_effectBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_screenWidth, m_screenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// �f�v�X�o�b�t�@�p�̃����_�[�o�b�t�@��p�ӂ���
	glGenRenderbuffersEXT(1, &m_depthrenderbuffer);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_depthrenderbuffer);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, m_screenWidth, m_screenHeight);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);

	// �t���[���o�b�t�@�I�u�W�F�N�g���쐬����
	glGenFramebuffersEXT(1, &m_effectFrameBuffer);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_effectFrameBuffer);

	// �t���[���o�b�t�@�I�u�W�F�N�g�ɃJ���[�o�b�t�@�Ƃ��ăe�N�X�`������������
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_effectBuffer, 0);

	// �t���[���o�b�t�@�I�u�W�F�N�g�Ƀf�v�X�o�b�t�@�Ƃ��ă����_�[�o�b�t�@����������
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, m_depthrenderbuffer);


	glGenTextures(1, &m_edgeBuffer);
	glBindTexture(GL_TEXTURE_2D, m_edgeBuffer);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_screenWidth, m_screenHeight, 0,
		GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);


	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,
		GL_TEXTURE_2D, m_edgeBuffer, 0);


	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_edgeBuffer);


	// �t���[���o�b�t�@�I�u�W�F�N�g�̌�������������
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	



	// �V�F�[�_�v���O�����̍쐬
	m_effectShader = CShader::GetInstance("Effect");
	m_noeffectShader = CShader::GetInstance("NoEffect");
	m_depthShader = CShader::GetInstance("Depth");



	
	glGenTextures(1, &m_texBuffer);
	//�[�x�o�b�t�@�i�[�p�e�N�X�`���[���쐬

	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, m_texBuffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	static const GLfloat border[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_texWidth, m_texHeight, 0,
		GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);

	//�t���[���o�b�t�@���쐬
	glGenFramebuffersEXT(1, &m_frameBuffer);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_frameBuffer);
	glClearDepth(1.0f);

	//�t���[���o�b�t�@�̐[�x�o�b�t�@���e�N�X�`���[��
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, m_texBuffer, 0);

	glBindFramebufferEXT(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);

}
CShadow::~CShadow() {
	glDeleteFramebuffersEXT(1,&m_frameBuffer);
	glDeleteTextures(1,&m_texBuffer);

	glDeleteTextures(1, &m_edgeBuffer);

	glDeleteFramebuffers(1, &m_effectFrameBuffer);
	glDeleteTextures(1, &m_effectBuffer);

	glDeleteRenderbuffers(1, &m_depthrenderbuffer);

	delete m_depthShader;
	delete m_effectShader;
	delete m_noeffectShader;
}
void CShadow::Render(std::function<void()> render,bool shadow,bool autoCamera, bool edge, bool effect,bool clear) {
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	if (shadow) {
		if (autoCamera) AutoCamera();
		//glPushAttrib(GL_LIGHTING_BIT);

		CCamera* buf = CCamera::GetCurrent();
		CCamera* c = CCamera::GetCamera(CCamera::eShadowCamera);
		CCamera::SetCurrent(c);
		c->SetProjectionMatrix(m_lightProj);
		c->SetViewMatrix(m_lightView);
		//��������̃����_�����O
	
		glViewport(0, 0, m_texWidth, m_texHeight);

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_frameBuffer);

		if (clear) glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// �J���[����
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		//���C�e�B���O����
		glDisable(GL_LIGHTING);
		CLight::SetLighting(false);

		//�O�ʃJ�����O
		glCullFace(GL_FRONT);
		m_state = eShadow;
		render();


		glEnable(GL_TEXTURE_2D);
		// �e�N�X�`�����[�h�Ɉڍs
		glActiveTexture(GL_TEXTURE7);
		//glMatrixMode(GL_TEXTURE);



		static  const CMatrix texMat(0.5f, 0.0f, 0.0f, 0.5f,
			0.0f, 0.5f, 0.0f, 0.5f,
			0.0f, 0.0f, 0.5f, 0.5f,
			0.0f, 0.0f, 0.0f, 1.0f);
		CLight::m_shadowMatrix = texMat * m_lightProj*m_lightView *
				buf->GetViewMatrix().GetInverse();

		//glLoadMatrixf(CLight::m_shadowMatrix.f);

		// �t���[���o�b�t�@�I�u�W�F�N�g����������
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_effectFrameBuffer);
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
		// �J���[�o�b�t�@�ƃf�v�X�o�b�t�@���N���A
		if (clear)  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glCullFace(GL_BACK);
		m_state = eDisplay;
		glEnable(GL_LIGHTING);
		CLight::SetLighting(true);


		//glPopAttrib();

		//�ʏ탌���_�����O
		CCamera::SetCurrent(buf);

		glActiveTexture(GL_TEXTURE7);
		glBindTexture(GL_TEXTURE_2D, m_texBuffer);

		glActiveTexture(GL_TEXTURE0);
		render();
		glActiveTexture(GL_TEXTURE7);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE0);
		glDisable(GL_TEXTURE_2D);
		glFlush();
	} else {
		// �t���[���o�b�t�@�I�u�W�F�N�g����������
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_effectFrameBuffer);
		// �J���[�o�b�t�@�ƃf�v�X�o�b�t�@���N���A
		if(clear) glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		render();
		glFlush();
	}

	// �t���[���o�b�t�@�I�u�W�F�N�g�̌�������������
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glViewport(0,0, m_screenWidth, m_screenHeight);
	// �A�e�t���ƉB�ʏ��������͍s��Ȃ�
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	CShader *s = effect ? m_effectShader : m_noeffectShader;
	// �e�N�X�`���}�b�s���O��L���ɂ���
	glBindTexture(GL_TEXTURE_2D, m_effectBuffer);
	glEnable(GL_TEXTURE_2D);
	s->enable();
	CVector3D vertices[] = {
		CVector3D(0,0,0),
		CVector3D(1,0,0),
		CVector3D(1,1,0),
		CVector3D(0,1,0)
	};
	glEnableVertexAttribArray(CShader::eVertexLocation);
	glVertexAttribPointer(CShader::eVertexLocation, 3, GL_FLOAT, GL_FALSE,0, vertices);

	glUniform1i(glGetUniformLocation(s->GetProgram(), "tDiffuse"), 0);
	/* �S��ʂɎl�p�`��`�� */
	glDrawArrays(GL_QUADS, 0, 4);
	s->disable();
	glDisableVertexAttribArray(CShader::eVertexLocation);

	if (edge) {

		/* �e�N�X�`���I�u�W�F�N�g���������� */
		glBindTexture(GL_TEXTURE_2D, m_edgeBuffer);
		m_depthShader->enable();
		glUniform1i(glGetUniformLocation(m_depthShader->GetProgram(), "depth"), 0);
		glUniform2f(glGetUniformLocation(m_depthShader->GetProgram(), "vScreenSize"), (float)viewport[2], (float)viewport[3]);
		
		
		glEnableVertexAttribArray(CShader::eVertexLocation);
		glVertexAttribPointer(CShader::eVertexLocation, 3, GL_FLOAT, GL_FALSE, 0, vertices);

		/* �S��ʂɎl�p�`��`�� */
		glDrawArrays(GL_QUADS, 0, 4);
		
		

		glDisableVertexAttribArray(CShader::eVertexLocation);

		m_depthShader->disable();
	}

	// �e�N�X�`���}�b�s���O�𖳌��ɂ���
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	m_state = eNone;
}

void CShadow::DrawDepthTex(int w, int h)
{
	//glUseProgram(0);

	CMatrix	mProj;

	mProj.Ortho(0, w, 0, h, -1, 1);
	CShader* s = CShader::GetInstance("Image");

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texBuffer);

	CVector3D vertices[] = {
		CVector3D(0,0,0),
		CVector3D(1,0,0),
		CVector3D(1,1,0),
		CVector3D(0,1,0)
	};
	CVector2D texcoord[] = {
		CVector2D(0,0),
		CVector2D(1,0),
		CVector2D(1,1),
		CVector2D(0,1)
	};


	glEnableVertexAttribArray(CShader::eVertexLocation);
	glEnableVertexAttribArray(CShader::eTexcoordlLocation);
	glVertexAttribPointer(CShader::eVertexLocation, 3, GL_FLOAT, GL_FALSE, 0, vertices);
	glVertexAttribPointer(CShader::eTexcoordlLocation, 2, GL_FLOAT, GL_FALSE, 0, texcoord);

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableVertexAttribArray(CShader::eVertexLocation);
	glDisableVertexAttribArray(CShader::eTexcoordlLocation);


	glBindTexture(GL_TEXTURE_2D, 0);

	/*glBindTexture(GL_TEXTURE_2D, m_effectBuffer);
	glNormal3d(0, 0, -1);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex3f(ww + 150, hh, 0);
	glTexCoord2d(1, 0); glVertex3f(ww + 150+150, hh, 0);
	glTexCoord2d(1, 1); glVertex3f(ww + 150+150, hh + 150, 0);
	glTexCoord2d(0, 1); glVertex3f(ww + 150, hh + 150, 0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();*/
}
void CShadow::AutoCamera() {
	CVector3D d = CCamera::GetCurrent()->GetDir();
	CVector3D ld = CCamera::GetCurrent()->GetPos() + CCamera::GetCurrent()->GetDir() * m_length;
	ld.y = 0;
	CVector3D lp = ld - CLight::GetDirPointer()[0] * m_length/2;
	CMatrix mProj, mView;
	mProj.Ortho(-m_length, m_length, -m_length, m_length, 0.05f, m_length*5);
	mView.LookAtView(lp, ld, CVector3D(0, 1, 0));
	SetLightProjectionMatrix(mProj);
	SetLightViewMatrix(mView);
}

void CShadow::CreateInscance(int screenWidth, int screenHeight, float length, int texWidth, int texHeight)
{
	if (m_shadow) return;
	m_shadow = new CShadow(screenWidth, screenHeight, length, texWidth, texHeight);
}

CShadow* CShadow::GetInstance()
{
	if (!m_shadow) CreateInscance((int)CCamera::GetCurrent()->GetWhidth(), (int)CCamera::GetCurrent()->GetHeight());
	return m_shadow;
}

void CShadow::ClearInstance()
{
	if (!m_shadow) return;
	delete m_shadow;
	m_shadow = nullptr;
}