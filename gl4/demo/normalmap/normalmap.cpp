#include "app.h"
#include "bitmaptext.h"
#include <sstream>
#include "common.h"
#include "light.h"
#include "quad.h"
#include "texutil.h"
#include "stream_util.h"

namespace zxd {

quad q;

struct use_normal_map_view_program : public zxd::program {
  GLint ul_normal_map;

  virtual void update_model(const mat4 &_m_mat) {
    m_mat = _m_mat;
    mv_mat = v_mat * m_mat;
    mv_mat_it = glm::inverse(glm::transpose(mv_mat));
    mvp_mat = p_mat * mv_mat;

    glUniformMatrix4fv(ul_mv_mat_it, 1, 0, value_ptr(mv_mat_it));
    glUniformMatrix4fv(ul_mv_mat, 1, 0, value_ptr(mv_mat));
    glUniformMatrix4fv(ul_mvp_mat, 1, 0, value_ptr(mvp_mat));
  }
  virtual void attach_shaders() {
    attach(GL_VERTEX_SHADER, "shader/use_normalmap_view.vs.glsl");
    string_vector sv;
    sv.push_back("#version 430 core\n #define LIGHT_COUNT 1\n");
    sv.push_back(stream_util::read_resource("shader/blinn.frag"));
    attach(GL_FRAGMENT_SHADER, sv, "shader/use_normalmap_view.fs.glsl");

    name("use_normalmap_view");
  }
  virtual void bind_uniform_locations() {
    // uniform_location(&ul_eye, "eye");
    uniform_location(&ul_mv_mat, "mv_mat");
    uniform_location(&ul_mv_mat_it, "mv_mat_it");
    uniform_location(&ul_mvp_mat, "mvp_mat");
    uniform_location(&ul_normal_map, "normal_map");
  }

  virtual void bind_attrib_locations() {
    bind_attrib_location(0, "vertex");
    bind_attrib_location(1, "normal");
    bind_attrib_location(2, "texcoord");
    bind_attrib_location(3, "tangent");
  };
} prg0;

struct use_normal_map_tangent_progrm : public program {
  GLint ul_normal_map;
  GLint ul_m_camera;

  virtual void update_model(const mat4 &_m_mat) {
    m_mat = _m_mat;
    mv_mat = v_mat * m_mat;
    mv_mat_i = glm::inverse(mv_mat);
    m_mat_i = glm::inverse(m_mat);
    mvp_mat = p_mat * mv_mat;
    glUniformMatrix4fv(ul_mvp_mat, 1, 0, glm::value_ptr(mvp_mat));
  };
  virtual void attach_shaders() {
    string_vector sv;
    sv.push_back("#version 430 core\n #define LIGHT_COUNT 1\n");
    attach(GL_VERTEX_SHADER, sv, "shader/use_normalmap_tangent.vs.glsl");
    sv.push_back(stream_util::read_resource("shader/blinn.frag"));
    attach(GL_FRAGMENT_SHADER, sv, "shader/use_normalmap_tangent.fs.glsl");

    name("use_normalmap_tangent");
  }
  virtual void bind_uniform_locations() {
    // uniform_location(&ul_eye, "eye");
    uniform_location(&ul_mvp_mat, "mvp_mat");
    uniform_location(&ul_normal_map, "normal_map");
    uniform_location(&ul_m_camera, "m_camera");
  }
  virtual void bind_attrib_locations() {
    bind_attrib_location(0, "vertex");
    bind_attrib_location(1, "normal");
    bind_attrib_location(2, "texcoord");
    bind_attrib_location(3, "tangent");
  };
} prg1;

GLuint normal_map;
std::vector<zxd::light_source> lights;
zxd::light_model light_model;
zxd::material material;
GLint light_space = 0;  // 0 : view, 1 : tangent

class normal_map_app : public app {
protected:
  bitmap_text m_text;

public:
  normal_map_app() {}

  virtual void init_info() {
    app::init_info();
    m_info.title = "hello world";
    m_info.samples = 4;
  }
  virtual void create_scene() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    prg0.init();
    prg0.p_mat = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 20.0f);
    prg0.v_mat = glm::lookAt(vec3(0, -5, 5), vec3(0.0f), vec3(0, 1, 0));
    prg1.init();
    prg1.p_mat = prg0.p_mat;
    prg1.v_mat = prg0.v_mat;

    q.include_normal(true);
    q.include_texcoord(true);
    q.include_tangent(true);
    q.build_mesh();

    fipImage normal_image = zxd::fipLoadResource("texture/bricks.bmp");

    glGenTextures(1, &normal_map);
    glBindTexture(GL_TEXTURE_2D, normal_map);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, normal_image.getWidth(),
      normal_image.getHeight(), 0, GL_BGR, GL_UNSIGNED_BYTE,
      normal_image.accessPixels());

    // light
    zxd::light_source dir_light;
    dir_light.position = vec4(1, -1, 1, 0);
    dir_light.diffuse = vec4(1, 1, 1, 1);
    dir_light.specular = vec4(1, 1, 1, 1);
    dir_light.linear_attenuation = 1.0f;

    lights.push_back(dir_light);

    light_model.local_viewer = 1;

    // material
    material.ambient = vec4(0.2);
    material.diffuse = vec4(0.8);
    material.specular = vec4(1.0);
    material.shininess = 50;

    bind_uniform_locations(prg0);

    set_v_mat(&prg0.v_mat);

    m_text.init();
    m_text.reshape(m_info.wnd_width, m_info.wnd_height);
  }

  virtual void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, normal_map);
    if (light_space == 0) {
      glUseProgram(prg0);
      prg0.update_model(mat4(1.0));
      glUniform1i(prg0.ul_normal_map, 0);

      for (int i = 0; i < lights.size(); ++i) {
        lights[i].update_uniforms(prg0.v_mat);
      }
    } else {
      glUseProgram(prg1);
      prg1.update_model(mat4(1.0));
      glUniform1i(prg1.ul_normal_map, 0);

      // get camera model position
      vec3 camera = glm::column(prg1.mv_mat_i, 3).xyz();
      glUniform3fv(prg1.ul_m_camera, 1, glm::value_ptr(camera));

      for (int i = 0; i < lights.size(); ++i) {
        lights[i].update_uniforms(prg1.m_mat_i);
      }
    }
    light_model.update_uniforms();
    material.update_uniforms();
    q.draw();

    //glDisable(GL_SCISSOR_TEST);
    //glBindTexture(GL_TEXTURE_2D, normal_map);
    //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glViewport(0, 0, m_info.wnd_width, m_info.wnd_height);
    glEnable(GL_BLEND);
    glDisable(GL_SCISSOR_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    std::stringstream ss;
    ss << "q : lighting space : " << (light_space == 0 ? "view" : "tangent")
       << std::endl;
    ss << "w : local viewer " << static_cast<GLint>(light_model.local_viewer)
       << std::endl;
    ss << "fps : " << m_fps << std::endl;
    m_text.print(ss.str(), 10, m_info.wnd_height - 25);
    glDisable(GL_BLEND);
  }

  virtual void update() {}

  virtual void glfw_resize(GLFWwindow *wnd, int w, int h) {
    app::glfw_resize(wnd, w, h);
    m_text.reshape(w, h);
  }

  virtual void bind_uniform_locations(zxd::program &program) {
    light_model.bind_uniform_locations(program.object, "lm");
    for (int i = 0; i < lights.size(); ++i) {
      std::stringstream ss;
      ss << "lights[" << i << "]";
      lights[i].bind_uniform_locations(program.object, ss.str());
    }
    material.bind_uniform_locations(program.object, "mtl");
  }

  virtual void glfw_key(
    GLFWwindow *wnd, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
      switch (key) {
        case GLFW_KEY_ESCAPE:
          glfwSetWindowShouldClose(m_wnd, GL_TRUE);
          break;
        case GLFW_KEY_Q:
          light_space ^= 1;
          if (light_space == 0) {
            prg0.v_mat = *m_v_mat;

            set_v_mat(&prg0.v_mat);
            bind_uniform_locations(prg0);
          } else {
            prg1.v_mat = *m_v_mat;
            set_v_mat(&prg1.v_mat);
            bind_uniform_locations(prg1);
          }

          break;
        case GLFW_KEY_W:
          light_model.local_viewer ^= 1;
          break;

        default:
          break;
      }
    }
    app::glfw_key(wnd, key, scancode, action, mods);
  }

  virtual void glfw_mouse_button(
    GLFWwindow *wnd, int button, int action, int mods) {
    app::glfw_mouse_button(wnd, button, action, mods);
  }

  virtual void glfw_mouse_move(GLFWwindow *wnd, double x, double y) {
    app::glfw_mouse_move(wnd, x, y);
  }

  virtual void glfw_mouse_wheel(
    GLFWwindow *wnd, double xoffset, double yoffset) {
    app::glfw_mouse_wheel(wnd, xoffset, yoffset);
  }
};
}

int main(int argc, char *argv[]) {
  zxd::normal_map_app app;
  app.run();
}
