#include <game.h>
#include <filesystem>
using namespace oct;
using namespace glm;
vec4 background = vec4(vec3(0.20784314f), 1.0f);
auto main()->int
{
	return game::run();
}
void game::load()
{
	// Loading cards
	std::string cardsPath = "assets/cards";
	uint32_t id = 0;
	std::vector<card> deck;
	for (const auto& entry : std::filesystem::directory_iterator(cardsPath))
	{
		std::string path = entry.path().string();
		std::string base_filename = path.substr(path.find_last_of("/\\") + 1);
		std::string extension = base_filename.substr(base_filename.find_last_of(".") + 1);
		if (extension == "png")
		{
			std::string::size_type const p(base_filename.find_last_of('.'));
			std::string name = base_filename.substr(0, p);
			deck.push_back(card(name, path, id++));
		}
	}
	for (auto& reel : game::machine->reels)
		reel.attach_deck(deck);
	sound::load_sound("assets/sounds/score.wav");
	render_cmd::set_clear_color(background);
}
void game::on_switch_click(switch_button_click_event& e)
{
	if (!game::machine->running())
	{
		e.button().switch_on();
		game::machine->start();
	}
	else if (game::machine->peak_velocity()) // Автомат не следует останавливать, пока она все еще набирает скорость, верно?
	{
		e.button().switch_off();
		game::machine->stop();
	}
}
void game::rendering()
{
	render_cmd::clear();
	renderer2d::begin_projection();
	//renderer2d::draw_quad(vec3(x, 0.0f, -5.0f), vec2(1.0f, 1.0f), vec4(0.1f, 0.1f, 0.2f, 1.0f));
	renderer2d::draw(game::machine);
	renderer2d::end_projection();
}
void game::integration(float dt)
{
	for (auto& reel : game::machine->reels)
		reel.integrate(dt);
}