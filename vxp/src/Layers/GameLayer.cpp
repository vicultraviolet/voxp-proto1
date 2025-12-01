#include "Pch.hpp"
#include "Layers/GameLayer.hpp"

namespace Vxp
{
	GameLayer::GameLayer(
		Na::Ref<Na::Window> window,
		Na::Ref<Na::HL::Display> display,
		Na::View<Na::Graphics::Renderer> renderer
	)
	: Na::Layer(0), m_Window(window), m_Display(display), m_Renderer(renderer)
	{

	}

	GameLayer::~GameLayer(void)
	{

	}

	void GameLayer::on_event(Na::Event& e)
	{
		
	}

	void GameLayer::update(double dt)
	{
		
	}

	void GameLayer::draw(void)
	{

	}
} // namespace Vxp
