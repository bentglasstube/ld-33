#include "game_screen.h"

#include "input.h"

void GameScreen::init(Graphics& graphics) {
  map.reset(new Map(graphics));
  tanker.reset(new Tanker(graphics, 1, 7));
}

bool GameScreen::update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed) {
  if (!tanker->moving()) {
    if (input.key_pressed_or_held(SDLK_a)) {
      if (map->sailable(tanker->x_pos() - 1, tanker->y_pos())) tanker->start_moving(Tanker::LEFT);
    } else if (input.key_pressed_or_held(SDLK_d)) {
      if (map->sailable(tanker->x_pos() + 1, tanker->y_pos())) tanker->start_moving(Tanker::RIGHT);
    } else if (input.key_pressed_or_held(SDLK_w)) {
      if (map->sailable(tanker->x_pos(), tanker->y_pos() - 1)) tanker->start_moving(Tanker::UP);
    } else if (input.key_pressed_or_held(SDLK_s)) {
      if (map->sailable(tanker->x_pos(), tanker->y_pos() + 1)) tanker->start_moving(Tanker::DOWN);
    }
  }

  if (input.key_pressed(SDLK_ESCAPE)) return false;

  if (input.key_pressed(SDLK_SPACE)) {
    tanker->toggle_leaking();
  }

  tanker->update(elapsed);
  map->update(elapsed);

  if (tanker->is_leaking()) map->dump_oil(tanker->x_behind(), tanker->y_behind());

  return true;
}

void GameScreen::draw(Graphics& graphics) {
  map->draw(graphics);
  tanker->draw(graphics);
}

Screen* GameScreen::next_screen() {
  return NULL;
}

std::string GameScreen::get_music_track() {
  return "";
}
