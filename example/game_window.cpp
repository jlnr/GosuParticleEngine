#include <stdexcept>
#include <Gosu/Utility.hpp>
#include <Gosu/Math.hpp>
#include <Gosu/Image.hpp>
#include <Gosu/Text.hpp>
#include <iostream>
#include <sstream>
#include <Gosu/Graphics.hpp>
#include <Gosu/ImageData.hpp>
#include <Gosu/Inspection.hpp>
#include <Gosu/Timing.hpp>
#include "game_window.hpp"

GameWindow::GameWindow()
:Gosu::Window(1200, 800, false)
,font(graphics(), Gosu::defaultFontName(), 20)
,particle_emitter(graphics(), L"particle_gas.png", RenderLayer::Particles, 100000)
{
}

GameWindow::~GameWindow()
{
}

void GameWindow::draw()
{
    particle_emitter.draw();

	std::wstringstream wss;
	wss << Gosu::fps();
	wss << L"fps - ";
    wss << update_time;
	wss << L"ms / ";
    wss << 1000/60;
    wss << L"ms - ";
    wss << particle_emitter.getCount();
    wss << L" particles";
	font.draw(wss.str(), 0, 0, RenderLayer::GUI);
	graphics().drawTriangle(input().mouseX(), input().mouseY(), Gosu::Color::GRAY,
							input().mouseX()+10, input().mouseY(), Gosu::Color::GRAY,
							input().mouseX(), input().mouseY()+10, Gosu::Color::GRAY, RenderLayer::GUI);
                            
}

void GameWindow::update()
{
    auto start_time = Gosu::milliseconds();
    for(int i = 0; i < 100; i++) {
        Particle p;
        p.x = input().mouseX();
        p.y = input().mouseY();
        p.time_to_live = 1000;
        p.center_x = 0.5;
        p.center_y = 0.5;
        p.scale = 0.1;
        p.color.alpha = 1.0;
        p.color.red = 0.0;
        p.color.blue = 1.0;
        p.color.green = 0.5;
        p.velocity_x = Gosu::random(-1, 1)*10;
        p.velocity_y = Gosu::random(-1, 1)*10;
        p.friction = 0.0;
        p.angle = 0.0;
        p.angular_velocity = 0.0;
        p.zoom = 0.0;
        p.fade = 10;
        particle_emitter.emit(p);
    }
    particle_emitter.update(1.0/60.0);
    update_time = Gosu::milliseconds() - start_time;
}
