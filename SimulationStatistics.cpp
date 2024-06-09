#include "SimulationStatistics.h"
#include <sstream>
#include <iomanip>
#include <iostream>

SimulationStatistics::SimulationStatistics(sf::Clock& _clock) : clock(_clock) {

	if (!font.loadFromFile("resources/fonts/arial.ttf"))
	{
		throw std::runtime_error("Could not load font");
	}
	fpsText.setFont(font);
	fpsText.setCharacterSize(24);
	fpsText.setFillColor(sf::Color::White);
	fpsText.setPosition(10, 10);
}

void SimulationStatistics::calculateFPS() {
	float deltaTime = clock.restart().asSeconds();
	frameTimes += deltaTime;
	frameCount++;
	if (frameCount == frameRateCount) // calculate average every N frames
	{
		averageFPS = (float)frameCount / frameTimes;

		// reset for the next N frames
		frameTimes = 0.0f;
		frameCount = 0;
	}
	fps = 1.f / deltaTime;

}

void SimulationStatistics::draw(sf::RenderWindow& window)
{
	sf::RectangleShape rect(sf::Vector2f(500, 50));
	rect.setFillColor(sf::Color::Black);
	rect.setPosition(0, 0);
	window.draw(rect);
	std::stringstream ss;
	ss << "Average FPS : " << std::fixed << std::setprecision(0) << averageFPS << " | FPS : " << fps;
	fpsText.setString(ss.str());
	window.draw(fpsText);
}