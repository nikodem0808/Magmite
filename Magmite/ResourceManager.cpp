
#include "ResourceManager.hpp"

namespace magmite
{
	auto resource_manager::get_audio(const std::string& path)
		-> std::optional<std::reference_wrapper<sf::SoundBuffer>>
	{
		auto i = sound_buffers.find(path);
		if (i != sound_buffers.end())
		{
			return { i->second };
		}

		sf::SoundBuffer buf;
		bool success = buf.loadFromFile(path);
		if (!success)
		{
			return std::nullopt;
		}

		sound_buffers.insert({ path, std::move(buf) });

		return sound_buffers.at(path);
	}


	auto resource_manager::get_resource(const std::string& path)
		-> std::optional<std::reference_wrapper<std::string>>
	{

		auto i = resources.find(path);
		if (i != resources.end())
		{
			return { i->second };
		}

		std::string res;

		std::fstream fl;
		fl.open(path, std::ios::in);

		if (!fl.good())
		{
			return std::nullopt;
		}

		auto start = fl.tellg();
		fl.seekg(0, std::ios::end);
		auto end = fl.tellg();
		fl.seekg(0, std::ios::beg);

		auto size = end - start;
		res.reserve(size);

		for (auto i = size; i > 0; --i)
		{
			res.push_back(fl.get());
		}

		fl.close();

		auto& target = resources[path];
		target = std::move(res);

		return target;
	}

	auto resource_manager::get_resource_file(const std::string& path)
		-> std::optional<std::fstream>
	{
		std::fstream fl;

		fl.open(path, std::ios::in);

		if (!fl.good())
		{
			return std::nullopt;
		}

		return fl;
	}

	auto resource_manager::get_texture(const std::string& path)
		-> std::optional<std::reference_wrapper<sf::Texture>>
	{
		auto i = textures.find(path);
		if (i != textures.end())
		{
			return { i->second };
		}

		sf::Texture txt;
		bool success = txt.loadFromFile(path);
		if (!success)
		{
			return std::nullopt;
		}

		textures.insert({ path, std::move(txt) });

		return textures.at(path);
	}

	//

	void resource_manager::unload_audio(const std::string& path)
	{
		auto i = sound_buffers.find(path);
		if (i != sound_buffers.end())
		{
			sound_buffers.erase(i);
		}
	}

	void resource_manager::unload_resource(const std::string& path)
	{
		auto i = resources.find(path);
		if (i != resources.end())
		{
			resources.erase(i);
		}
	}

	void resource_manager::unload_texture(const std::string& path)
	{
		auto i = textures.find(path);
		if (i != textures.end())
		{
			textures.erase(i);
		}
	}
}

