struct prg : public quad_base {
  GLint ul_name;

  virtual void do_attach_shaders() {
    attach(
      GL_FRAGMENT_SHADER, "");
  }

  virtual void do_update_uniforms() { glUniform1f(ul_name, name); }

  virtual void do_bind_uniform_locations() {
    uniform_location(&ul_name, "name");
  }
} prg;
