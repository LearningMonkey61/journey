#include "app.h"

#include <sstream>

#include "bitmaptext.h"
#include "geometry.h"
#include "teapot.h"
#include "program.h"

#define WIDTH 800
#define HEIGHT 800

namespace zxd {

geometry_base teapot;

vec4 tess_level_out = vec4(16);
vec2 tess_level_inner = vec2(16);

class program_name : public program
{
public:

  GLint ul_mvp_mat;
  GLint ul_color;

protected:

  void attach_shaders()
  {
    attach(GL_VERTEX_SHADER, "data/shader/dummy.vs.glsl");
    attach(GL_TESS_EVALUATION_SHADER, "data/shader/teapot.te.glsl");
    attach(GL_FRAGMENT_SHADER, {"#version 430 core"}, "data/shader/lightless.fs.glsl");
  }

  void bind_uniform_locations()
  {
    uniform_location(&ul_mvp_mat, "mvp_mat");
    uniform_location(&ul_color, "color");
  }

  void bind_attrib_locations()
  {
  }
} prg;

class teapot_app : public app {
protected:
  bitmap_text m_text;

public:
  virtual void init_info();
  virtual void create_scene();

  virtual void update();

  virtual void display();

  virtual void glfw_resize(GLFWwindow *wnd, int w, int h);

  virtual void glfw_key(
    GLFWwindow *wnd, int key, int scancode, int action, int mods);
};

void teapot_app::init_info() {
  app::init_info();
  m_info.title = "teapot_app";
  m_info.wnd_width = WIDTH;
  m_info.wnd_height = HEIGHT;
}

void teapot_app::create_scene() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  m_text.init();
  m_text.reshape(wnd_width(), wnd_height());

  auto vertices = std::make_shared<vec3_array>();
  auto vertex_ptr = reinterpret_cast<vec3*>(const_cast<float(*)[3]>(TeapotVertices)) ;
  vertices->assign(vertex_ptr, vertex_ptr + NumTeapotVertices);
  teapot.attrib_array(0, vertices);

  auto elements = std::make_shared<uint_array>(GL_ELEMENT_ARRAY_BUFFER);
  auto index_ptr = reinterpret_cast<GLuint*>(const_cast<int(*)[4][4]>(TeapotIndices)) ;
  elements->assign(index_ptr, index_ptr + NumTeapotIndices);
  teapot.elements(elements);

  teapot.add_primitive_set(new draw_elements(GL_PATCHES, NumTeapotVertices, GL_UNSIGNED_INT, 0));
  teapot.bind_and_update_buffer();

  prg.init();
  prg.p_mat = glm::perspective(fpi4, wnd_aspect(), 0.1f, 1000.0f);
  prg.v_mat = glm::lookAt(vec3(0, -20, 0), vec3(0), pza);
  set_v_mat(&prg.v_mat);
}

void teapot_app::update() {}

void teapot_app::display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  prg.use();
  glPatchParameteri(GL_PATCH_VERTICES, NumTeapotVerticesPerPatch);
  glPatchParameterfv(GL_PATCH_DEFAULT_OUTER_LEVEL, glm::value_ptr(tess_level_out));
  glPatchParameterfv(GL_PATCH_DEFAULT_INNER_LEVEL, glm::value_ptr(tess_level_inner));

  mat4 mvp_mat = prg.p_mat * prg.v_mat * glm::rotate(fpi2, pxa);
  glUniformMatrix4fv(prg.ul_mvp_mat, 1, 0, glm::value_ptr(mvp_mat));
  glUniform4f(prg.ul_color, 1, 1, 1, 1);

  teapot.draw();
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  std::stringstream ss;
  ss << "";
  m_text.print(ss.str(), 10, m_info.wnd_height - 20);
  glDisable(GL_BLEND);
}

void teapot_app::glfw_resize(GLFWwindow *wnd, int w, int h) {
  app::glfw_resize(wnd, w, h);
  m_text.reshape(m_info.wnd_width, m_info.wnd_height);
}

void teapot_app::glfw_key(
  GLFWwindow *wnd, int key, int scancode, int action, int mods) {
  if (action == GLFW_PRESS) {
    switch (key) {
      case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(m_wnd, GL_TRUE);
        break;
      default:
        break;
    }
  }
  app::glfw_key(wnd, key, scancode, action, mods);
}

}

int main(int argc, char *argv[]) {
  zxd::teapot_app app;
  app.run();
}
