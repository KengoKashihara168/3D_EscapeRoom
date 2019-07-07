/*************************/
/* since:2018.01.21      */
/* file :SingletonDR.h   */
/* name :Kengo Kashihara */
/*************************/
#pragma once
#include "DeviceResources.h"

class SingletonDR
{
private:
	SingletonDR() {};

	void operator=(const SingletonDR& obj) {}

	SingletonDR(const SingletonDR &obj) {}

public:
	static SingletonDR& GetInstance();

	 static void SetDeviceResources(DX::DeviceResources* dr);

	 ID3D11Device* GetDevice();
	
	 ID3D11DeviceContext* GetContext();

	 DirectX::CommonStates* GetCommonStates();

	 DirectX::SpriteBatch* GetSpriteBatch();

	 RECT GetRectSize();

private:
	static DX::DeviceResources* m_deviceResources;
};