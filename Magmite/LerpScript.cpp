
#include "LerpScript.hpp"


namespace maingame
{

	lerp_script::lerp_script(magmite::game& _game, magmite::eid_type _id, magmite::eid_type _target_id, float _duration, sf::Vector2f _destination)
		: game(&_game), id(_id), target_id(_target_id)
	{
		if (_duration < 0.001f) _duration = 0.001f;

		end_time = game->get_time().game_time() + _duration;

		auto& target_go = game->active_scene().get_game_object(target_id);

		auto start = target_go.transform().position;
		destination = _destination;
		direction = (start - _destination) / _duration;
	}

	void lerp_script::update()
	{
		float game_time = game->get_time().game_time();
		auto& target_go = game->active_scene().get_game_object(target_id);

		if (game_time >= end_time)
		{
			target_go.transform().position = destination;
			game->active_scene().destroy_game_object(id);
			return;
		}

		target_go.transform().position = destination + direction * (end_time - game_time);
	}

}