
#include "MainGame.hpp"

#include "CardScript.hpp"
#include "GameManager.hpp"

#include <iostream>
#include <random>

namespace maingame
{
	auto create_card(magmite::game* game, card_script::card_type type, size_t value) ->magmite::eid_type;

	sf::Font font{};
	sf::Text red_score_text{};
	sf::Text black_score_text{};
	sf::Text win_text{};

	void init_game(
		magmite::game& game,
		magmite::scene& scene,
		sf::RenderWindow& wnd
	)
	{
		/* init card */ do {
			break;
			auto card_eid = scene.add_game_object();
			auto& card_go = scene.get_game_object(card_eid);

			//volatile const auto x = cat_ent.id();

			//std::launder(&x);

			//std::cin.get();

			auto script_id = card_go.add_component<magmite::behaviour>();
			auto& script = card_go.get_component<magmite::behaviour>();

			script.bind<card_script>(game, card_eid);

			auto& scr = script.get_as<card_script>();

			scr.value = 2;
			scr.type = card_script::card_type::back;
		} while (false);

		/* init game_manager */ {
			auto gm_eid = scene.add_game_object();

			auto& gm_go = scene.get_game_object(gm_eid);

			//volatile const auto x = cat_ent.id();

			//std::launder(&x);

			//std::cin.get();

			auto script_id = gm_go.add_component<magmite::behaviour>();
			auto& script = gm_go.get_component<magmite::behaviour>();

			script.bind<game_manager>(game, gm_eid);

			auto& scr = script.get_as<game_manager>();

			size_t nb = 0, nr = 0;
			auto rng = std::mt19937(static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count()));

			std::vector<magmite::eid_type> t_rc, t_bc;

			for (size_t i = 0; i < 52; ++i)
			{
				auto type = static_cast<card_script::card_type>(i / 13);
				auto value = (i / 13) + 1;
				scr.cards[i] = create_card(&game, type, value);

				auto& card_go = scene.get_game_object(scr.cards[i]);
				card_go.transform().position = { 100, 320 };

				if (nb >= 26)
				{
					t_rc.push_back(i);
				}
				else if (nr >= 26)
				{
					t_bc.push_back(i);
				}
				else
				{
					auto val = (rng() % 100);
					if (val < 50)
					{
						t_rc.push_back(i);
					}
					else
					{
						t_bc.push_back(i);
					}
				}
			}

			while (t_rc.size() > 0)
			{
				size_t rn = rng() % t_rc.size();
				scr.red_cards.push(t_rc[rn]);
				t_rc.erase(t_rc.begin() + rn);
			}

			while (t_bc.size() > 0)
			{
				size_t rn = rng() % t_bc.size();
				scr.black_cards.push(t_bc[rn]);
				t_bc.erase(t_bc.begin() + rn);
			}

			// texts

			red_score_text.setFont(font);
			black_score_text.setFont(font);
			win_text.setFont(font);

			red_score_text.setPosition(20, 860);
			black_score_text.setPosition(20, 20);
			win_text.setPosition(600, 438);

			red_score_text.setCharacterSize(20);
			black_score_text.setCharacterSize(20);
			win_text.setCharacterSize(32);

			red_score_text.setFillColor(sf::Color::Red);
			black_score_text.setFillColor(sf::Color::Black);
			win_text.setFillColor({ 0, 0, 0, 0 });

			red_score_text.setString("Red Score: 0");
			black_score_text.setString("Black Score: 0");
		}
	}

	// impl

	auto create_card(magmite::game* game, card_script::card_type type, size_t value)
		-> magmite::eid_type
	{
		magmite::scene& scene = game->active_scene();

		auto card_eid = scene.add_game_object();

		auto& card_go = scene.get_game_object(card_eid);

		auto script_id = card_go.add_component<magmite::behaviour>();
		auto& script = card_go.get_component<magmite::behaviour>();

		script.bind<card_script>(*game, card_eid);

		auto& scr = script.get_as<card_script>();

		scr.value = 2;
		scr.type = card_script::card_type::back;

		return card_eid;
	}
}
