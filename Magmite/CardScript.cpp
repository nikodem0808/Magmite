#pragma once

#include "CardScript.hpp"

//DEBUG
#include <iostream>

namespace maingame
{
	card_script::card_script(magmite::game& _game, magmite::eid_type _id)
		: game(&_game), id(_id)
	{ }

	void card_script::refresh_card_sprite()
	{
		auto& go = game->active_scene().get_game_object(id);

		auto& renderer = go.get_component<magmite::renderer>();

		size_t i = 13 * static_cast<size_t>(type) + (value - 1);

		size_t x = x_offset + (i % row_size) * x_gap;
		size_t y = y_offset + (i / row_size) * y_gap;

		renderer.sprite.setTextureRect(sf::IntRect(
			x, y,
			sprite_width,
			sprite_height
		));
	}

	void card_script::set_card_sprite(card_type _type, size_t _value)
	{
		type = _type;
		value = _value;
		refresh_card_sprite();
	}

	void card_script::start()
	{
		std::cout << "Have id: " << id << "\n";

		auto& rm = game->get_resource_manager();
		auto txt = rm.get_texture("resources/cards.jpg");

		if (!txt.has_value())
		{
			throw std::runtime_error("[CardScript] Could not load texture 'resources/cards.jpg'");
		}

		auto& go = game->active_scene().get_game_object(id);
		go.add_component<magmite::renderer>();

		std::cout << "Have id: " << id << "\n";

		auto& renderer = go.get_component<magmite::renderer>();
		renderer.sprite.setTexture(txt.value());

		std::cout << "g/o id: " << go.id() << "\n";
		std::cout << "Parent id: " << renderer.parent_id() << "\n";
	}

	void card_script::update()
	{
		auto& go = game->active_scene().get_game_object(id);
		auto& renderer = go.get_component<magmite::renderer>();

		refresh_card_sprite();
	}
}