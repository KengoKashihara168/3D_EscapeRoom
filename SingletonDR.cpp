/*************************/
/* since:2018.01.21      */
/* file :SingletonDR.cpp */
/* name :Kengo Kashihara */
/*************************/
#include "pch.h"
#include "SingletonDR.h"

DX::DeviceResources* SingletonDR::m_deviceResources = nullptr;

SingletonDR & SingletonDR::GetInstance()
{
	static SingletonDR instance;

	return instance;
}

void SingletonDR::SetDeviceResources(DX::DeviceResources* dr)
{
	m_deviceResources = dr;
}

ID3D11Device* SingletonDR::GetDevice()
{
	return m_deviceResources->GetD3DDevice();
}

ID3D11DeviceContext* SingletonDR::GetContext()
{
	return m_deviceResources->GetD3DDeviceContext();
}

DirectX::CommonStates* SingletonDR::GetCommonStates()
{
	
	static DirectX::CommonStates* commonStates = new DirectX::CommonStates(GetDevice());
	return commonStates;
}

DirectX::SpriteBatch* SingletonDR::GetSpriteBatch()
{
	static DirectX::SpriteBatch* spriteBatch = new DirectX::SpriteBatch(GetContext());
	return spriteBatch;
}

RECT SingletonDR::GetRectSize()
{
	return m_deviceResources->GetOutputSize();
}