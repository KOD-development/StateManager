#include <gtest/gtest.h>
#include <StateManager.h>
#include <memory>

namespace kod {

	// Dummy/mock state for testing
	class MockState : public IState {
	public:
		void draw() override {}
		void update([[maybe_unused]] const size_t dt) override {}
		void input([[maybe_unused]] const std::optional<sf::Event>& event) override {}
		void input() override {}
	};

} // namespace kod

TEST(StateManagerTest, PushValidState_ShouldBeCurrent)
{
	kod::StateManager manager;
	auto state = std::make_shared<kod::MockState>();

	manager.pushState(state);

	EXPECT_EQ(manager.currentState(), state);
}

TEST(StateManagerTest, PushNullState_ShouldNotChangeStack)
{
	kod::StateManager manager;

	manager.pushState(nullptr);

	EXPECT_EQ(manager.currentState(), nullptr);
}

TEST(StateManagerTest, PopState_ShouldRemoveTopState)
{
	kod::StateManager manager;
	auto s1 = std::make_shared<kod::MockState>();
	auto s2 = std::make_shared<kod::MockState>();

	manager.pushState(s1);
	manager.pushState(s2);
	manager.popState();

	EXPECT_EQ(manager.currentState(), s1);
}

TEST(StateManagerTest, PopEmptyStack_ShouldNotCrash)
{
	kod::StateManager manager;

	manager.popState();  // Brak wyjątków / błędów
	EXPECT_EQ(manager.currentState(), nullptr);
}

TEST(StateManagerTest, CurrentStateOnEmpty_ShouldReturnNullptr)
{
	kod::StateManager manager;

	EXPECT_EQ(manager.currentState(), nullptr);
}