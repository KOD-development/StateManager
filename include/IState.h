#pragma once

#include <SFML/Window/Event.hpp>
#include <memory>
#include <optional>
#include <unordered_map>

namespace kod {

class IState
{
public:
	IState() = default;
	virtual ~IState() = default;
	virtual void draw() = 0;
	virtual void update(const size_t dt) = 0;
	virtual void input(const std::optional<sf::Event>& event) = 0;
	virtual void input() = 0;
};

} // namespace kod