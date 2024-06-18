#pragma once

#include "all.def"
#include "CardScript.hpp"
#include <unordered_set>
#include <queue>
#include <random>

namespace maingame
{
	struct game_manager
	{
		magmite::game* game = nullptr;
		magmite::eid_type id = magmite::invalid_eid;

		std::mt19937 rng = std::mt19937(static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count()));

		std::array<magmite::eid_type, 52> cards;

		std::queue<size_t>
			red_cards,
			black_cards;

		std::vector<size_t>
			red_hand,
			black_hand,
			red_score,
			black_score;

		sf::Vector2f global_deck_pos = sf::Vector2f(100, 400);
		sf::Vector2f red_deck_pos = sf::Vector2f(1400, 500);
		sf::Vector2f black_deck_pos = sf::Vector2f(1400, 200);

		sf::Vector2f red_card_pos = sf::Vector2f(650, 400);
		sf::Vector2f black_card_pos = sf::Vector2f(850, 270);

		std::array<sf::Vector2f, 3> red_hand_pos = {
			sf::Vector2f(600, 650),
			sf::Vector2f(750, 650),
			sf::Vector2f(900, 650)
		};
		std::array<sf::Vector2f, 3> black_hand_pos = {
			sf::Vector2f(600, 50),
			sf::Vector2f(750, 50),
			sf::Vector2f(900, 50)
		};

		size_t state = 0;
		size_t selected = SIZE_MAX;
		size_t bot_selected = SIZE_MAX;
		float timer = NAN;

		game_manager(magmite::game& _game, magmite::eid_type _id);

		void lerp_object(magmite::eid_type eid, float duration, sf::Vector2f destination);

		void show_card(magmite::eid_type eid, size_t cid);
		void hide_card(magmite::eid_type eid);

		size_t card_score(size_t cid);

		void init();
		void start();
		void update();
	};
}