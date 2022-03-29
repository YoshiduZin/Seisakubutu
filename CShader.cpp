#include <stdio.h>
#include <stdlib.h>
#include "CShader.h"

const char* mesh_vert= "#version 430\n\n"\
"uniform mat4 WorldMatrix;\n"\
"uniform mat4 ModelViewMatrix;\n"\
"uniform mat4 ProjectionMatrix;\n"\
"uniform mat4 ShadowTextureMatrix;\n"\
"layout(location = 0) in vec3	Vertex;\n"\
"layout(location = 1) in vec3	Normal;\n"\
"layout(location = 2) in vec2	TexCoord;\n"\
"//フラグメントシェーダーに渡す変数\n"\
"out vec3 V;//座標\n"\
"out vec3 N;//法線ベクトル\n"\
"out vec2 texCoord;\n"\
"out vec4 vShadowCoord;    //!< シャドウデプスマップの参照用座標\n"\
"void main(void)\n"\
"{\n"\
"	V = vec3(WorldMatrix * vec4(Vertex, 1));\n"\
"	gl_Position = ProjectionMatrix * ModelViewMatrix * vec4(Vertex, 1);\n"\
"	N = normalize(mat3(WorldMatrix) * Normal);\n"\
"	vShadowCoord = ShadowTextureMatrix * ModelViewMatrix * vec4(Vertex, 1);    // 影用座標値(光源中心座標)\n"\
"\n"\
"	texCoord = TexCoord;\n"\
"}";
const char *skin_mesh_vert = "#version 430\n\n"\
"uniform mat4 Transforms[180];\n"\
"uniform mat4 WorldMatrix;\n"\
"uniform mat4 LocalMatrix;\n"\
"uniform mat4 ModelViewMatrix;\n"\
"uniform mat4 ProjectionMatrix;\n"\
"uniform mat4 ShadowTextureMatrix;\n"\
"uniform int useSkin = 0;\n"\
"layout(location = 0) in vec3 Vertex;\n"\
"layout(location = 1) in vec3 Normal;\n"\
"layout(location = 2) in vec2 TexCoord;\n"\
"layout(location = 3) in vec4 weights;\n"\
"layout(location = 4) in vec4 indices;\n"\
"//フラグメントシェーダーに渡す変数\n"\
"out vec3 V;//座標\n"\
"out vec3 N;//法線ベクトル\n"\
"out vec2 texCoord;\n"\
"out vec4 vShadowCoord;    //!< シャドウデプスマップの参照用座標\n"\
"void main(void)\n"\
"{\n"\
"	if (useSkin==1) {\n"\
"		mat4 comb = mat4(0);\n"\
"		comb += Transforms[int(indices.x)] * weights.x;\n"\
"		comb += Transforms[int(indices.y)] * weights.y;\n"\
"		comb += Transforms[int(indices.z)] * weights.z;\n"\
"		comb += Transforms[int(indices.w)] * weights.w;\n"\
"		vec4 skinPosition = ModelViewMatrix * comb * LocalMatrix*vec4(Vertex, 1);\n"\
"		V = vec3(WorldMatrix * comb * vec4(Vertex, 1));\n"\
"		gl_Position = ProjectionMatrix * skinPosition;\n"\
"		N = normalize(mat3(WorldMatrix * comb*LocalMatrix) * Normal);\n"\
"	} else {\n"\
"		V = vec3(WorldMatrix * vec4(Vertex, 1));\n"\
"		gl_Position = ProjectionMatrix * ModelViewMatrix * LocalMatrix * vec4(Vertex, 1);\n"\
"		N = normalize(mat3(WorldMatrix) * Normal);\n"\
"	}\n"\
"	vShadowCoord = ShadowTextureMatrix * ModelViewMatrix * LocalMatrix * vec4(Vertex, 1);    // 影用座標値(光源中心座標)\n"\
"	texCoord = TexCoord;\n"\
"}";
const char *mesh_flag = "#version 430\n\n"\
"uniform vec3 lightPos[5];\n"\
"uniform vec3 lightDir[5];\n"\
"uniform vec3 lightAmbientColor[5];\n"\
"uniform vec3 lightDiffuseColor[5];\n"\
"uniform float lightAttenuation[5];\n"\
"uniform int lightType[5];\n"\
"uniform float lightRadiationAngle[5];\n"\
"uniform vec2 stscroll;\n"\
"uniform vec3 eyeVec;\n"\
"uniform vec3 eyePos;\n"\
"uniform vec4 Ambient;\n"\
"uniform vec4 Diffuse;\n"\
"uniform vec3 Specular;\n"\
"uniform vec3 Emissive;\n"\
"uniform float Pow;\n"\
"uniform float alpha;\n"\
"uniform int lighting;\n"\
"uniform int uSetex;\n"\
"uniform vec4 fogColor;\n"\
"uniform float fogNear;\n"\
"uniform float fogFar;\n"\
"//頂点シェーダーから受け取る変数\n"\
"in vec3 V;//位置\n"\
"in vec3 N;//法線ベクトル\n"\
"in vec2 texCoord;\n"\
"uniform sampler2D sampler;\n"\
"in vec4 vShadowCoord;    //!< シャドウデプスマップの参照用座標\n"\
"out vec4 out_color;\n"\
"uniform sampler2D depth_tex;    //!< デプス値テクスチャ\n"\
"uniform float shadow_ambient;    //!< 影の濃さ\n"\
"void main(void)\n"\
"{\n"\
"	vec4 texColor = vec4(1, 1, 1, 1);\n"\
"	if (uSetex != 0) {\n"\
"		texColor = texture2D(sampler, texCoord + stscroll);\n"\
"	}\n"\
"	vec3 A = vec3(0, 0, 0);\n"\
"	vec3 D = vec3(0, 0, 0);\n"\
"	vec3 S = vec3(0, 0, 0);\n"\
"	vec3 color;\n"\
"	float visibility = 1.0;\n"\
"	if (lighting == 1) {\n"\
"		for (int i = 0; i < 5; i++) {\n"\
"			if (lightType[i] == 0) continue;\n"\
"			vec3 vec = vec3(0, 0, 0);\n"\
"			float p = 0;\n"\
"			if (lightType[i] == 1) {\n"\
"				vec = -lightDir[i];\n"\
"				p = 1;\n"\
"			}else\n"\
"			if (lightType[i] == 2 || lightType[i] == 3) {\n"\
"					vec = vec3(V - lightPos[i]);\n"\
"					float l = length(vec);\n"\
"					vec = normalize(vec);\n"\
"					if (l > 0)\n"\
"						p = clamp(1 / (pow(l * lightAttenuation[i], 2)), 0.0, 1.0);\n"\
"					else\n"\
"						p = 0;\n"\
"					if (lightType[i] == 3) {\n"\
"						float t = dot(vec, lightDir[i]);\n"\
"						t = clamp(t + sin(lightRadiationAngle[i]), 0.0, 1.0);\n"\
"						//if(t<1) p = 0;\n"\
"						p *= pow(t, 20);\n"\
"					}\n"\
"					vec = -vec;\n"\
"				}\n"\
"			float NL = dot(N, vec);\n"\
"			//NL = (NL>0.5) ? 1.0:0;\n"\
"			vec3 Reflect = normalize(2 * NL * N - vec);\n"\
"			S += pow(clamp(dot(Reflect, -eyeVec), 0.0, 1.0), Pow) * p;\n"\
"			if (lightType[i] == 4) {\n"\
"				D += lightDiffuseColor[i];\n"\
"				A += lightDiffuseColor[i];\n"\
"			}\n"\
"			else {\n"\
"				D += lightDiffuseColor[i] * clamp(NL, 0.0, 1.0) * p;\n"\
"				A += lightAmbientColor[i] * p;\n"\
"			}\n"\
"		}\n"\
"		float l = length(eyePos - V);\n"\
"		float f = clamp((fogFar - l) / (fogFar - fogNear), 0.0, 1.0);\n"\
"		color = texColor.xyz * (visibility * Diffuse.xyz * clamp(D, 0.0, 1.0) + Ambient.xyz * clamp(A, 0.0, 1.0)) + visibility * Specular * clamp(S, 0.0, 1.0) + Emissive;\n"\
"		out_color = vec4(color + fogColor.xyz * (1.0 - f), clamp((texColor.w * Diffuse.w * alpha) - ((1.0 - fogColor.w) * (1.0 - f)), 0.0f, 1.0f));\n"\
"	}\n"\
"	else {\n"\
"		color = Diffuse.xyz + Ambient.xyz;\n"\
"		out_color = (texColor * vec4(color, Diffuse.w * alpha));\n"\
"	}\n"\
"}";

const char *solid_vert = "#version 430\n\n"\
"uniform mat4 PVWMatrix;\n"\
"layout(location = 0) in vec3	Vertex;\n"\
"void main(void)\n"\
"{\n"\
"	gl_Position = PVWMatrix * vec4(Vertex, 1);\n"\
"}";

const char* solid_flag = "#version 430\n\n"\
"uniform vec4 Color;\n"\
"out vec4 out_color;\n"\
"void main() {\n"\
"	out_color = Color;\n"\
"}";

const char* trail_vert ="#version 430\n"\
"uniform mat4 PVWMatrix;\n"\
"layout(location = 0) in vec3	Vertex;\n"\
"layout(location = 2) in vec2	TexCoord;\n"\
"layout(location = 5) in vec4	VertexColor;\n"\
"out vec2 texCoord;\n"\
"out vec4 vertex_color;\n"\
"void main(void)\n"\
"{\n"\
"	gl_Position = PVWMatrix * vec4(Vertex, 1);\n"\
"	vertex_color = VertexColor;\n"\
"	texCoord = TexCoord;\n"\
"}\n";
const char* trail_flag = "#version 430\n"\
"uniform sampler2D sampler;\n"\
"in vec2 texCoord;\n"\
"in vec4 vertex_color;\n"\
"out vec4 out_color;\n"\
"void main() {\n"\
"	vec4 texColor = vec4(1, 1, 1, 1);\n"\
"	texColor = texture2D(sampler, texCoord);\n"\
"	out_color = vertex_color * texColor;\n"\
"};\n";

const char* image_vert = "#version 430\n\n"\
"uniform mat4 PVWMatrix;\n"\
"layout(location = 0) in vec3	Vertex;\n"\
"layout(location = 2) in vec2	TexCoord;\n"\
"out vec2 texCoord;\n"\
"void main(void)\n"\
"{\n"\
"	gl_Position = PVWMatrix * vec4(Vertex, 1);\n"\
"	texCoord = TexCoord;\n"\
"}";
const char* image_flag = "#version 430\n\n"\
"uniform vec4 Color;\n"\
"in vec2 texCoord;\n"\
"uniform sampler2D sampler;\n"\
"out vec4 out_color;\n"\
"void main() {\n"\
"	vec4 texColor = vec4(1, 1, 1, 1);\n"\
"	texColor = texture2D(sampler, texCoord);\n"\
"	out_color = texColor * Color;\n"\
"}";

std::map<std::string, CShader*> CShader::m_instances;
CShader* CShader::GetInstance(std::string type)
{
	if (!m_instances[type]) m_instances[type] = new CShader(type);
	return m_instances[type];
}
CShader::CShader():program(0){
}

CShader::CShader(std::string type) {
	if (type == "SkinMesh") {
		loadraw(skin_mesh_vert, mesh_flag);
	} else
	if (type == "StaticMesh") {
		loadraw(mesh_vert, mesh_flag);
	} else
	if (type == "Effect") {
	//	load("shader\\effect.vert", "shader\\effect.frag");
	}else
	if (type == "NoEffect") {
	//	load("shader\\effect.vert", "shader\\noeffect.frag");
	}else
	if (type == "Depth") {
	//	load("shader\\showdepth.vert", "shader\\showdepth.frag");
	}else
	if (type == "Image") {
		loadraw(image_vert, image_flag);
	}else
	if (type == "Solid") {
		loadraw(solid_vert, solid_flag);
	}else
	if (type == "Trail") {
		loadraw(trail_vert, trail_flag);
	//	load("shader\\trail.vert", "shader\\trail.frag");
	}
	else {
		printf("\nシェーダー無し\n");
	}

}
CShader::CShader(const char* vertexPath,const char* pixelPath){
	load(vertexPath,pixelPath);
}

bool CShader::readRaw(GLuint program, GLuint shader, const char* code) {
	
	int size = strlen(code);
	glShaderSource(shader, 1, (const GLchar * *)& code, &size);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if (compiled) {
		GLint length;
		GLchar* log;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		if (length > 0) {
			log = new GLchar[length];
			glGetShaderInfoLog(shader, length, &length, log);
			fprintf(stderr, "compile log='%s'\n", log);
			delete log;
		}
	}
	//delete[] code;

	glAttachShader(program, shader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &linked);

	if (linked) {
		//	glUseProgram(program);
	}
	else {
		GLint length;
		GLchar* log;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		if (length > 0) {
			log = new GLchar[length];
			glGetShaderInfoLog(shader, length, &length, log);
			fprintf(stderr, "compile log='%s'\n", log);
			delete log;
		}
	}


	glDeleteShader(shader);
	//glDeleteShader(flagShader);

	return true;

}
bool CShader::readFile(GLuint program,GLuint shader, const char *file) {
	FILE *fp;
	fopen_s(&fp,file, "rb");
	if(!fp) {
		printf("ファイルが開けません[%s]\n",file);
		return false;
	}
	fseek( fp, 0, SEEK_END );
	int size = ftell( fp );
	fseek( fp, 0, SEEK_SET );
	GLchar *code = new char[size];
	fread(code,size,1,fp);
	fclose(fp);

	glShaderSource(shader,1,(const GLchar **)&code,&size);
	glCompileShader(shader);
	glGetShaderiv(shader,GL_COMPILE_STATUS,&compiled);

	if(compiled) {
		GLint length;
		GLchar *log;
		glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&length);
		if (length > 0) {
			log = new GLchar[length];
			glGetShaderInfoLog(shader, length, &length, log);
			fprintf(stderr, "compile log='%s'\n", log);
			delete log;
		}
	}
	delete[] code;  

	glAttachShader(program,shader);
	glLinkProgram(program);

	glGetProgramiv(program,GL_LINK_STATUS,&linked);

	if(linked) {
	//	glUseProgram(program);
	} else {
		GLint length;
		GLchar *log;
		glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&length);
		if (length > 0) {
			log = new GLchar[length];
			glGetShaderInfoLog(shader, length, &length, log);
			fprintf(stderr, "compile log='%s'\n", log);
			delete log;
		}
	}

	
	glDeleteShader(shader);
	//glDeleteShader(flagShader);

	return true;
 
}
bool CShader::loadraw(const char* vertexcode, const char* flagcode) {

	program = glCreateProgram();
	if (vertexcode) {

		bool ret = readRaw(program, glCreateShader(GL_VERTEX_SHADER), vertexcode);
		if (!ret) return false;
	}
	if (flagcode) {

		bool ret = readRaw(program, glCreateShader(GL_FRAGMENT_SHADER), flagcode);
		if (!ret) return false;
	}


	return true;

}
bool CShader::load(const char* vertexPath,const char* flagPath){

	program = glCreateProgram();
	if(vertexPath) {

		bool ret = readFile(program,glCreateShader(GL_VERTEX_SHADER),vertexPath);
		if(!ret) return false;
	}
	if(flagPath) {
		
		bool ret = readFile(program,glCreateShader(GL_FRAGMENT_SHADER),flagPath);
		if(!ret) return false;
	}
	

	return true;
	
}
bool CShader::load(const char* path, GLuint type){
	if (!program) program = glCreateProgram();
	if (path) {
		bool ret = readFile(program, glCreateShader(type), path);
		if (!ret) return false;
	}
	return true;
}
CShader::~CShader(){
	if (program>0) glDeleteProgram(program);

}
void CShader::enable(){
	glUseProgram(program);
}
void CShader::disable(){
	glUseProgram(0);
}