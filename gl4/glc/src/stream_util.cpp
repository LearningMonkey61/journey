#include "stream_util.h"

#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>

#include <boost/filesystem.hpp>
#include "string_util.h"

namespace stream_util
{

//--------------------------------------------------------------------
zxd::float_vector read_floats(std::istream& is, GLuint count)
{
  bool count_check = count != -1;
  zxd::float_vector floats;
  GLfloat f;
  while(count && is)
  {
    is >> f;
    floats.push_back(f);
    --count;
  }

  if(is.fail())
  {
    std::stringstream ss;
    ss << "failed to read floats, missing " << count;
    throw std::runtime_error(ss.str());
  }

  if(count_check && count != 0)
  {
    std::stringstream ss;
    ss << "not enough float, missing " << count;
    throw std::runtime_error(ss.str());
  }

  return floats;
}

//--------------------------------------------------------------------
glm::vec4 read_vec4(std::istream& is)
{
  auto floats = read_floats(is, 4);
  return glm::vec4(floats[0], floats[1], floats[2], floats[3]);
}

//--------------------------------------------------------------------
glm::vec3 read_vec3(std::istream& is)
{
  auto floats = read_floats(is, 3);
  return glm::vec3(floats[0], floats[1], floats[2]);
}

//--------------------------------------------------------------------
glm::vec2 read_vec2(std::istream& is)
{
  auto floats = read_floats(is);
  return glm::vec2(floats[0], floats[1]);
}

//--------------------------------------------------------------------
glm::mat4 read_mat(std::istream& is)
{
  auto floats = read_floats(is, 16);
  return glm::mat4(floats[0],  floats[1],  floats[2],  floats[3],
                   floats[4],  floats[5],  floats[6],  floats[7],
                   floats[8],  floats[9],  floats[10], floats[11],
                   floats[12], floats[13], floats[14], floats[15]);
}

//--------------------------------------------------------------------
std::string read_resource(const std::string &filepath)
{
  return read_file(get_resource(filepath));
}

//--------------------------------------------------------------------
std::string read_file(const std::string &filepath)
{
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

//--------------------------------------------------------------------
std::string get_resource(const std::string& name)
{
  namespace bfs = boost::filesystem;
  // from osg
  std::vector<std::string> resources = {"."};
  char* resource_list = std::getenv("GL_FILE_PATH");
  if(resource_list != NULL)
  {
    std::vector<std::string> extra = string_util::split(resource_list, ";");
    resources.insert(resources.end(), 
        std::make_move_iterator(extra.begin()), std::make_move_iterator(extra.end()));
  }

  for(auto& dir : resources)
  {
    bfs::path p(dir);
    p.normalize();
    p /= name;
    if(bfs::exists(p))
      return p.string();
  }

  throw std::runtime_error(name + " not found in all resources");
}
}
