#include "common.h"
#include "stdlib.h"
#include "glEnumString.h"
#include <cstring>
#include <fstream>
#include <sstream>
#include <iterator>
#include <functional>
#include "glm.h"
#include "common.h"

using namespace glm;

//------------------------------------------------------------------------------
void printGLVersion() {
  printf(
    "GL_VERSION : %s\n"
    "GL_SHADING_LANGUAGE_VERSION : %s\n"
    "GL_RENDERER : %s\n"
    "GL_VENDOR : %s\n"
    "GL_SHADING_LANGUAGE_VERSION : %s\n"
    "GLU_VERSION : %s\n",
    glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION),
    glGetString(GL_RENDERER), glGetString(GL_VENDOR),
    glGetString(GL_SHADING_LANGUAGE_VERSION), gluGetString(GLU_VERSION));
}

//------------------------------------------------------------------------------
const GLchar *getExtensions() {
  static GLchar version[10240];
  sprintf(version,
    "GL_EXTENSIONS : %s\n"
    "GLU_EXTENSIONS : %s\n",
    glGetString(GL_EXTENSIONS), glGetString(GLU_EXTENSIONS));
  return version;
}

//--------------------------------------------------------------------
std::string readFile(const std::string &filepath) {
  std::ifstream ifs(filepath);
  if (!ifs) {
    std::stringstream ss;
    ss << "failed to open file " << filepath << std::endl;
    throw std::runtime_error(ss.str());
  }

  // approximate size
  ifs.seekg(std::ios::end);
  GLuint size = ifs.tellg();
  ifs.seekg(std::ios::beg);

  std::string s;
  s.reserve(size);

  std::copy(std::istreambuf_iterator<char>(ifs),
    std::istreambuf_iterator<char>(), std::back_inserter(s));

  return s;
}

//------------------------------------------------------------------------------
GLboolean queryExtension(char *extName) {
  char *p = (char *)glGetString(GL_EXTENSIONS);
  char *end;
  if (p == NULL) return GL_FALSE;
  end = p + strlen(p);
  while (p < end) {
    int n = strcspn(p, " ");
    if ((strlen(extName) == n) && (strncmp(extName, p, n) == 0)) {
      return GL_TRUE;
    }
    p += (n + 1);
  }
  return GL_FALSE;
}

//------------------------------------------------------------------------------
GLboolean invertMatrixd(GLdouble m[16]) {
  double inv[16], det;
  int i;

  inv[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] +
           m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];

  inv[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] -
           m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];

  inv[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] +
           m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];

  inv[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] -
            m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];

  inv[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] -
           m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];

  inv[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] +
           m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];

  inv[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] -
           m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];

  inv[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] +
            m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];

  inv[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] +
           m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];

  inv[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] -
           m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];

  inv[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] +
            m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];

  inv[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] -
            m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];

  inv[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] -
           m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];

  inv[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] +
           m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];

  inv[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] -
            m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];

  inv[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] +
            m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];

  det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

  if (det == 0) return GL_FALSE;

  det = 1.0 / det;

  for (i = 0; i < 16; i++) m[i] = inv[i] * det;

  return GL_TRUE;
}

//------------------------------------------------------------------------------
GLenum rotateEnum(GLenum val, GLenum begin, GLuint size) {
  return begin + (val + 1 - begin) % size;
}

//--------------------------------------------------------------------
void attachShaderFile(GLuint prog, GLenum type, const std::string &file) {
  std::string s = readFile(file);
  StringVector sv;
  sv.push_back(s);
  if (!attachShaderSource(prog, type, sv))
    printf("failed to compile file %s\n", file.c_str());
}

//--------------------------------------------------------------------
void attachShaderSourceAndFile(
  GLuint prog, GLenum type, StringVector &source, const std::string &file) {
  source.push_back(readFile(file));
  attachShaderSource(prog, type, source);
}

//------------------------------------------------------------------------------
bool attachShaderSource(GLuint prog, GLenum type, const StringVector &source) {
  GLuint sh;

  sh = glCreateShader(type);

  CStringVector csv;
  std::transform(source.begin(), source.end(), std::back_inserter(csv),
    std::mem_fn(&std::string::c_str));

  ZCGE(glShaderSource(sh, csv.size(), &csv[0], NULL));

  ZCGE(glCompileShader(sh));

  GLint compiled;
  // check if compile failed
  glGetShaderiv(sh, GL_COMPILE_STATUS, &compiled);
  if (!compiled) {
    GLsizei len;
    glGetShaderiv(sh, GL_INFO_LOG_LENGTH, &len);

    GLchar *log = (GLchar *)malloc(len + 1);
    glGetShaderInfoLog(sh, len, &len, log);
    printf("%s  compilation failed: %s", glShaderTypeToString(type), log);
    free(log);
    return false;
  }
  ZCGE(glAttachShader(prog, sh));
  ZCGE(glDeleteShader(sh));
  return true;
}

//--------------------------------------------------------------------
bool attachShaderSource(GLuint prog, GLenum type, const std::string &source) {
  StringVector sv;
  sv.push_back(source);
  return attachShaderSource(prog, type, sv);
}

//--------------------------------------------------------------------
void setUniformLocation(GLint *loc, GLint program, const std::string &name) {
  *loc = glGetUniformLocation(program, name.c_str());
  if (*loc == -1) {
    printf("failed to get uniform location : %s\n", name.c_str());
  }
}

//--------------------------------------------------------------------
GLfloat getTime() { return glutGet(GLUT_ELAPSED_TIME) / 1000.0; }

//--------------------------------------------------------------------
GLfloat getNormalizedTime() {
  return glutGet(GLUT_ELAPSED_TIME) % 1000 / 1000.0f;
}

//--------------------------------------------------------------------
GLfloat updateFps() {
  static GLfloat fps = 0;
  static GLuint lastTime = 0;
  static GLuint time = 0;
  static GLuint count = 0;

  GLuint curTime = glutGet(GLUT_ELAPSED_TIME);

  time += curTime - lastTime;
  ++count;

  if (time >= 1000) {
    fps = count;
    time %= 1000;
    count = 0;
  }

  lastTime = curTime;

  return fps;
}

//--------------------------------------------------------------------
void loadGL() {
  if (!gladLoadGL()) {
    printf("glad failed to load gl");
    return;
  }

  if (GLVersion.major < 2) {
    printf("Your system doesn't support OpenGL >= 2!\n");
  }

  printGLVersion();
  initDebugOutput();
}

//--------------------------------------------------------------------
void initDebugOutput() {
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

  glDebugMessageCallback(glDebugOutput, 0);
  // disable notification
  glDebugMessageControl(
    GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, 0, GL_FALSE);
}

//--------------------------------------------------------------------
void glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity,
  GLsizei length, const GLchar *message, const void *userParam) {
  const char *debugSource = glDebugSourceToString(source);
  const char *debugType = glDebugTypeToString(type);
  const char *debugSeverity = glDebugSeverityToString(severity);

  printf("%s : %s : %s : %d : %.*s\n", debugSeverity, debugSource, debugType,
    id, length, message);
}

//--------------------------------------------------------------------
void drawTexRect(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1) {
  glBegin(GL_QUADS);

  glTexCoord2f(0, 0);
  glVertex2f(x0, y0);

  glTexCoord2f(1, 0);
  glVertex2f(x1, y0);

  glTexCoord2f(1, 1);
  glVertex2f(x1, y1);

  glTexCoord2f(0, 1);
  glVertex2f(x0, y1);

  glEnd();
}

//--------------------------------------------------------------------
void drawXZRect(GLfloat x0, GLfloat z0, GLfloat x1, GLfloat z1) {
  glBegin(GL_QUADS);
  glVertex3f(x0, 0, z0);
  glVertex3f(x1, 0, z0);
  glVertex3f(x1, 0, z1);
  glVertex3f(x0, 0, z1);
  glEnd();
}

//--------------------------------------------------------------------
void drawXYPlane(
  GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLuint slices /* = 1
*/) {
  GLfloat dx = (x1 - x0) / slices;
  GLfloat dy = (y1 - y0) / slices;
  for (int i = 0; i < slices; ++i) {
    glBegin(GL_QUAD_STRIP);
    GLfloat _y0 = y0 + dy * i;
    GLfloat _y1 = _y0 + dy;
    // loop from end to start to keep ccw order
    for (int j = slices; j >= 0; ++j) {
      GLfloat x = x0 + dx * j;
      glVertex2f(x, _y0);
      glVertex2f(x, _y1);
    }
    glEnd();
  }
}

//--------------------------------------------------------------------
void detachAllShaders(GLuint program) {
  GLuint shaders[256];
  GLsizei count;
  glGetAttachedShaders(program, 256, &count, shaders);
  while (count) {
    glDetachShader(program, shaders[--count]);
  }
}

//--------------------------------------------------------------------
void getModelViewProj(GLfloat *p) {
  GLint mode;
  glGetIntegerv(GL_MATRIX_MODE, &mode);

  glGetFloatv(GL_MODELVIEW_MATRIX, p);

  // place resultin projection matrix, then get it.
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glMultMatrixf(p);
  glGetFloatv(GL_PROJECTION_MATRIX, p);
  glPopMatrix();
  glMatrixMode(mode);
}

//--------------------------------------------------------------------
void matrixAttribPointer(
  GLint index, GLuint divisor /* = 1*/, GLboolean normalize /* = GL_FALSE*/) {
  glVertexAttribPointer(
    index + 0, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), BUFFER_OFFSET(0));
  glVertexAttribPointer(
    index + 1, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), BUFFER_OFFSET(16));
  glVertexAttribPointer(
    index + 2, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), BUFFER_OFFSET(32));
  glVertexAttribPointer(
    index + 3, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), BUFFER_OFFSET(48));

  glEnableVertexAttribArray(index + 0);
  glEnableVertexAttribArray(index + 1);
  glEnableVertexAttribArray(index + 2);
  glEnableVertexAttribArray(index + 3);

  glVertexAttribDivisorARB(index + 0, 1);
  glVertexAttribDivisorARB(index + 1, 1);
  glVertexAttribDivisorARB(index + 2, 1);
  glVertexAttribDivisorARB(index + 3, 1);
}

//--------------------------------------------------------------------
GLint getAttribLocation(GLuint program, const std::string &name) {
  GLint location = glGetAttribLocation(program, name.c_str());
  if (location == -1) {
    std::cout << "failed to get attribute location : " << name << std::endl;
  }
  return location;
}