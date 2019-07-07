//
// Game.cpp
//

#include "pch.h"
#include "Game.h"

#include "SceneBase.h"
#include "SceneTitle\SceneTitle.h"
#include "SceneGame\SceneGame.h"
#include "SceneResult\SceneResult.h"

#include "SingletonDR.h"
#include "SceneGame\EventFlag.h"

#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

extern void ExitGame();

using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;

Game::Game()
	:m_scene(nullptr)
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
	// キーボードの作成
	m_keyboard = std::make_unique<Keyboard>();

	// マウスの作成
	m_mouse = std::make_unique<Mouse>();
	m_mouse->SetWindow(window);

    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

	// デバイスリソース用シングルトンの初期化
	SingletonDR::GetInstance().SetDeviceResources(m_deviceResources.get());

	// シーンの生成
	m_scene = new SceneTitle();
	m_scene->Initialize();
	m_scene->SetSceneType(SceneBase::SceneType::SceneTitle);

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */

}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
    elapsedTime;

	// シーンの更新
	m_scene->Update();
	if (m_scene->GetCnageFlag())
	{
		ChangeScene();
	}

	auto kb = Keyboard::Get().GetState();

	// Escキーが押された
	if (kb.Escape)
	{
		OnDeviceLost();
		// ゲームを終了する
		ExitGame();
	}

}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
	// Don't try to render anything before the first Update.
	if (m_timer.GetFrameCount() == 0)
	{
		return;
	}

	Clear();

	m_deviceResources->PIXBeginEvent(L"Render");
	auto context = m_deviceResources->GetD3DDeviceContext();

	// ここから描画処理を記述する

	// シーンの描画
	if(m_scene != nullptr)
	{
		m_scene->Render();
	}

	// ここまで

    m_deviceResources->PIXEndEvent();

    // Show the new frame.
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::Black);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 600;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    ID3D11Device* device = m_deviceResources->GetD3DDevice();
	ID3D11DeviceContext* context =  m_deviceResources->GetD3DDeviceContext();

    // TODO: Initialize device dependent objects here (independent of window size).
    device;

}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.

	
}

void Game::ChangeScene()
{
	m_scene->Finalize();

	switch (m_scene->GetSceneType())
	{
	case SceneBase::SceneType::SceneTitle:
		delete m_scene;
		m_scene = new SceneGame();
		m_scene->SetSceneType(SceneBase::SceneType::SceneGame);
		break;
	case SceneBase::SceneType::SceneGame:
		delete m_scene;
		m_scene = new SceneResult();
		m_scene->SetSceneType(SceneBase::SceneType::SceneResult);
		break;
	case SceneBase::SceneType::SceneResult:
		delete m_scene;
		m_scene = new SceneTitle();
		m_scene->SetSceneType(SceneBase::SceneType::SceneTitle);
		break;
	}

	m_scene->Initialize();
}

void Game::OnDeviceLost()
{
	// TODO: Add Direct3D resource cleanup here.

	// シーンの解放
	m_scene->Finalize();
	delete m_scene;
	m_scene = nullptr;
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
