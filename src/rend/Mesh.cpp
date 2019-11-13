#include "Mesh.h"

namespace rend
{

void Mesh::setBuffer(const std::string& name, const std::sr1::shared_ptr<Buffer>& buffer)
{
  for(std::sr1::vector<std::sr1::shared_ptr<BufferData> >::iterator it =
    buffers.begin(); it != buffers.end(); it++)
  {
    if((*it)->name == name)
    {
      (*it)->buffer = buffer;

      return;
    }
  }

  std::sr1::shared_ptr<BufferData> bd = std::sr1::make_shared<BufferData>();
  bd->name = name;
  bd->buffer = buffer;
  buffers.push_back(bd);
}


void Mesh::setTexture(const std::string& name, const std::sr1::shared_ptr<TextureAdapter>& texture)
{
  for(std::sr1::vector<std::sr1::shared_ptr<TextureData> >::iterator it =
    textures.begin(); it != textures.end(); it++)
  {
    if((*it)->name == name)
    {
      (*it)->texture = texture;

      return;
    }
  }

  std::sr1::shared_ptr<TextureData> td = std::sr1::make_shared<TextureData>();
  td->name = name;
  td->texture = texture;
  textures.push_back(td);
}

}
