
#include <iostream>
#include <utility>
#include <memory>
#include <thread>
#include <algorithm>
#include <execution>
#include <functional>
#include <chrono>

#include <SFML/Main.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "all.def"
#include "Input.hpp"

struct S
{
	int x{};

	S() { std::cout << "default constructed\n"; }
	S(const S&) { std::cout << "copy constructed\n";  }
	S(S&&) noexcept { std::cout << "move constructed\n"; }
	S& operator=(const S&) { std::cout << "copy assigned\n"; return *this; }
	S& operator=(S&&) noexcept { std::cout << "move assigned\n"; return *this; }
	~S() { std::cout << "destroyed\n"; }
};


int remote_fn(magmite::lua::lua_State* st)
{
	std::cout << "Remote call\n";
	return 0;
}


#include "MainGame.hpp"

int main()
{
#ifdef LUA_TEST
	using namespace magmite::lua;


	auto lstate = luaL_newstate();
	
	lua_pushcfunction(lstate, remote_fn);
	lua_setglobal(lstate, "remote_fn");

	std::fstream fl("resources/script.lua", std::ios::in);

	std::string str;

	while (fl) { str.push_back(fl.get()); }
	str.pop_back();

	// std::cout << str << "\n";

	//if (luaL_dostring(lstate, str.c_str()) != LUA_OK) std::cout << lua_tostring(lstate, -1);
	if (luaL_dofile(lstate, "resources/script.lua") != LUA_OK) std::cout << lua_tostring(lstate, -1);

	lua_close(lstate);

	return 0;
	__assume(false);
#endif

	static magmite::game game{};

	auto& scene = game.active_scene();

	auto wnd = sf::RenderWindow(sf::VideoMode(1600, 900), "MyWindow", sf::Style::Titlebar | sf::Style::Close);

	maingame::init_game(game, scene, wnd);

	std::deque<int>;
	maingame::font.loadFromFile("tuffy.ttf");
	auto font = sf::Font{};
	font.loadFromFile("tuffy.ttf");

	auto txt = sf::Text{};
	txt.setFillColor(sf::Color(0xBF, 0xFF, 0));
	txt.setOutlineColor(sf::Color(0xBF, 0xFF, 0));
	txt.setFont(font);

	auto tp1 = std::chrono::steady_clock::now();
	auto tp2 = tp1;

	size_t frame_count = 0;

	wnd.setVisible(true);

	game.wnd = &wnd;

	// game start
	game.get_time().init();

	/* behaviour system */ {
		auto& behaviour_cell = game.active_scene().ecs_container.get_cell_of_type<magmite::behaviour>();

		for (size_t i = 0; i < behaviour_cell.used_objects; ++i)
		{
			auto& behaviour = behaviour_cell.objects[i];
			behaviour.init();
		}
	
		for (size_t i = 0; i < behaviour_cell.used_objects; ++i)
		{
			auto& behaviour = behaviour_cell.objects[i];
			behaviour.start();
		}
	}
	// ~game_start

	while (wnd.isOpen())
	{
		// events

		sf::Event ev;
		while (wnd.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
			{
				wnd.close();
			}

			if (ev.type == sf::Event::MouseButtonReleased)
			{
				if (ev.mouseButton.button == sf::Mouse::Left)
				{
					// std::cout << "mouse x: " << ev.mouseButton.x << "\n";
					// std::cout << "mouse y: " << ev.mouseButton.y << "\n";

					for (auto& fn : magmite::input::on_lmb_clicked)
					{
						fn({ ev.mouseButton.x, ev.mouseButton.y });
					}
				}
			}
		}

		// ~events
		// input

		for (size_t i = 0; i < sf::Keyboard::KeyCount; ++i)
		{
			sf::Keyboard::Key kc = static_cast<sf::Keyboard::Key>(i);

			magmite::input::key_state_last_frame[i] = magmite::input::key_state[i];
			magmite::input::key_state[i] = sf::Keyboard::isKeyPressed(kc);
			magmite::input::key_down[i] = magmite::input::key_state[i] && !magmite::input::key_state_last_frame[i];
			magmite::input::key_up[i] = !magmite::input::key_state[i] && magmite::input::key_state_last_frame[i];
		}

		// ~input
		// time

		game.get_time().update();

		// ~time
		// logic

		auto& behaviour_cell = game.active_scene().ecs_container.get_cell_of_type<magmite::behaviour>();

		for (size_t i = 0; i < behaviour_cell.used_objects; ++i)
		{
			auto& behaviour = behaviour_cell.objects[i];
			if (behaviour.active()) behaviour.update();
		}

		// ~logic
		// render

		wnd.clear(sf::Color(0, 128, 0));

		auto& renderer_cell = game.active_scene().ecs_container.get_cell_of_type<magmite::renderer>();

		for (size_t i = 0; i < renderer_cell.used_objects; ++i)
		{
			auto& renderer = renderer_cell.objects[i];
			if (renderer.active()) renderer.render(wnd);
		}

		++frame_count;
		tp2 = std::chrono::steady_clock::now();
		txt.setString("FPS: " + std::to_string(frame_count / ((tp2 - tp1).count() / 1.0e9)));
		txt.setPosition(wnd.getSize().x - 20 - txt.getGlobalBounds().width, 20);
		txt.setScale(1.2f, 1.2f);

		if (frame_count == 60)
		{
			frame_count = 0;
			tp1 = tp2;
		}

		wnd.draw(txt);

		wnd.draw(maingame::red_score_text);
		wnd.draw(maingame::black_score_text);
		wnd.draw(maingame::win_text);

		wnd.display();

		// ~render
	}
}
