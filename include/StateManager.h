#pragma once
#include "IState.h"

#include <memory>
#include <vector>

namespace kod {

class StateManager
{
public:
	StateManager();
	void pushState(std::shared_ptr<kod::IState> state);
	void popState();
	std::shared_ptr<kod::IState> currentState();

private:
	std::vector<std::shared_ptr<kod::IState>> m_states;
};

} // namespace kod
