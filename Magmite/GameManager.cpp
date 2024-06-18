#pragma once

#include "GameManager.hpp"
#include "LerpScript.hpp"
#include "MainGame.hpp"


#include <iostream>

namespace maingame
{
	game_manager::game_manager(magmite::game& _game, magmite::eid_type _id)
		: game(&_game), id(_id), cards{}
	{ }

	void game_manager::lerp_object(magmite::eid_type eid, float duration, sf::Vector2f destination)
	{
		auto lerp_id = game->active_scene().add_game_object();
		auto& lerp_go = game->active_scene().get_game_object(lerp_id);

		lerp_go.add_component<magmite::behaviour>();
		auto& lerp_scr = lerp_go.get_component<magmite::behaviour>();
		lerp_scr.bind<lerp_script>(*game, lerp_id, eid, duration, destination);
	}

	void game_manager::show_card(magmite::eid_type eid, size_t cid)
	{
		auto& go = game->active_scene().get_game_object(eid);
		auto& scr = go.get_component<magmite::behaviour>().get_as<card_script>();

		auto type = static_cast<card_script::card_type>(cid / 13);
		auto value = (cid % 13) + 1;

		// std::cout << cid << ": " << (int)type << ", " << value << "\n";

		scr.set_card_sprite(type, value);
	}

	void game_manager::hide_card(magmite::eid_type eid)
	{
		auto& go = game->active_scene().get_game_object(eid);
		auto& scr = go.get_component<magmite::behaviour>().get_as<card_script>();

		scr.set_card_sprite(card_script::card_type::back, 2);
	}

	size_t game_manager::card_score(size_t cid)
	{
		auto type = cid / 13;
		auto value = (cid % 13);

		return 4 * value + type + 1;
	}

	void game_manager::init()
	{
		;
	}

	void game_manager::start()
	{
		;
	}

	void game_manager::update()
	{

		auto& scene = game->active_scene();

		switch (state)
		{
		case 0:
		{
			// black
			while (black_hand.size() < 3)
			{
				if (black_cards.empty())
				{
					state = 4;
					return;
				}

				black_hand.push_back(black_cards.front());
				black_cards.pop();
			}

			for (size_t i = 0; i < 3; ++i)
			{
				auto& card_go = scene.get_game_object(cards[black_hand[i]]);
				card_go.transform().position = black_hand_pos[i];

				//lerp_object(cards[black_hand[i]], 1.5f - i * 0.2f, black_hand_pos[i]);
			}

			// red
			while (red_hand.size() < 3)
			{
				if (red_cards.empty())
				{
					state = 4;
					return;
				}

				red_hand.push_back(red_cards.front());
				red_cards.pop();
			}

			for (size_t i = 0; i < 3; ++i)
			{
				auto& card_go = scene.get_game_object(cards[red_hand[i]]);
				card_go.transform().position = red_hand_pos[i];

				//lerp_object(cards[red_hand[i]], 1.5f - i * 0.2f, red_hand_pos[i]);
				
				show_card(card_go.id(), red_hand[i]);
				//show_card(cards[red_hand[i]], red_hand[i]);
			}

			timer = game->get_time().game_time() + 1.5f;
			state = 1;
		} break;

		case 1:
		{
			if (game->get_time().game_time() < timer)
			{
				//return;
			}

			size_t cid = SIZE_MAX;

			if (magmite::input::key_down[sf::Keyboard::A])
			{
				cid = 0;
			}
			else if (magmite::input::key_down[sf::Keyboard::S])
			{
				cid = 1;
			}
			else if (magmite::input::key_down[sf::Keyboard::D])
			{
				cid = 2;
			}

			if (cid != SIZE_MAX)
			{
				selected = cid;
				bot_selected = rng() % black_hand.size();

				auto& rc_go = scene.get_game_object(cards[red_hand[cid]]);
				auto& bc_go = scene.get_game_object(cards[black_hand[bot_selected]]);

				rc_go.transform().position = red_card_pos;
				bc_go.transform().position = black_card_pos;
				//lerp_object(rc_go.id(), 1.5f, red_card_pos);
				//lerp_object(bc_go.id(), 1.3f, black_card_pos);

				show_card(bc_go.id(), black_hand[bot_selected]);

				timer = game->get_time().game_time() + 2.5f;
				state = 2;
			}
		} break;

		case 2:
		{
			if (game->get_time().game_time() < timer)
			{
				return;
			}

			auto& rc_go = scene.get_game_object(cards[red_hand[selected]]);
			auto& bc_go = scene.get_game_object(cards[black_hand[bot_selected]]);

			auto red_sc = card_score(red_hand[selected]);
			auto black_sc = card_score(black_hand[bot_selected]);
			
			if (red_sc > black_sc)
			{
				red_score.push_back(red_hand[selected]);
				red_hand.erase(red_hand.begin() + selected);
				red_score.push_back(black_hand[bot_selected]);
				black_hand.erase(black_hand.begin() + bot_selected);

				rc_go.transform().position = red_deck_pos;
				bc_go.transform().position = red_deck_pos;
				//lerp_object(rc_go.id(), 1.5f, red_deck_pos);
				//lerp_object(bc_go.id(), 1.3f, red_deck_pos);
			}
			else
			{
				black_score.push_back(red_hand[selected]);
				red_hand.erase(red_hand.begin() + selected);
				black_score.push_back(black_hand[bot_selected]);
				black_hand.erase(black_hand.begin() + bot_selected);

				rc_go.transform().position = black_deck_pos;
				bc_go.transform().position = black_deck_pos;
				//lerp_object(rc_go.id(), 1.5f, black_deck_pos);
				//lerp_object(bc_go.id(), 1.3f, black_deck_pos);
			}

			hide_card(rc_go.id());
			hide_card(bc_go.id());

			size_t red_total = 0;
			size_t black_total = 0;

			for (size_t cid : red_score)
			{
				red_total += card_score(cid);
			}

			for (size_t cid : black_score)
			{
				black_total += card_score(cid);
			}

			red_score_text.setString("Red Score: " + std::to_string(red_total));
			black_score_text.setString("Black Score: " + std::to_string(black_total));

			timer = game->get_time().game_time() + 1.5f;
			state = 3;
		} break;

		case 3:
		{
			if (game->get_time().game_time() < timer)
			{
				//return;
			}
			state = 0;
		} break;

		case 4:
		{
			size_t red_total = 0;
			size_t black_total = 0;

			for (size_t cid : red_score)
			{
				red_total += card_score(cid);
			}

			for (size_t cid : black_score)
			{
				black_total += card_score(cid);
			}

			if (red_total > black_total)
			{
				win_text.setString("Red Wins");
				win_text.setFillColor(sf::Color::Red);
			}
			else
			{
				win_text.setString("Black Wins");
				win_text.setFillColor(sf::Color::Black);
			}

			timer = game->get_time().game_time() + 5.0f;
			state = 5;
		} break;
		case 5:
		{
			if (game->get_time().game_time() < timer)
			{
				return;
			}
			game->wnd->close();
		} break;
		}
	}
}