#pragma once


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <unordered_map>
#include <string>
#include <string_view>
#include <optional>
#include <fstream>

namespace magmite
{
	struct resource_manager
	{
		[[maybe_unused]]
		std::string base_path;

		std::unordered_map<std::string, std::string> resources;
		std::unordered_map<std::string, sf::Texture> textures;
		std::unordered_map<std::string, sf::SoundBuffer> sound_buffers;

		std::optional<std::reference_wrapper<sf::SoundBuffer>> get_audio(const std::string& path);
		std::optional<std::reference_wrapper<std::string>> get_resource(const std::string& path);
		std::optional<std::fstream> get_resource_file(const std::string& path);
		std::optional<std::reference_wrapper<sf::Texture>> get_texture(const std::string& path);

		void unload_audio(const std::string& path);
		void unload_resource(const std::string& path);
		void unload_texture(const std::string& path);
	};
}

