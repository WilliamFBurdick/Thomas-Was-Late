#include "TextureHolder.h"
#include <assert.h>
using namespace sf;
using namespace std;

TextureHolder* TextureHolder::m_s_Instance = nullptr;
TextureHolder::TextureHolder()
{
	//insure that only one instance of this class exists, if not, exit the program
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

Texture& TextureHolder::GetTexture(std::string const& filename)
{
	//get reference to map instance
	auto& m = m_s_Instance->m_Textures;
	//search for texture in map
	auto keyValuePair = m.find(filename);
	//if found return the texture
	if (keyValuePair != m.end()) return keyValuePair->second;
	else
	{
		//if not found, load the texture and return it
		auto& texture = m[filename];
		texture.loadFromFile(filename);
		return texture;
	}
}