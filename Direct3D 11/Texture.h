#pragma once
#include "Direct3D.h"
#include <string>
#include <wincodec.h>
#pragma comment(lib, "Windowscodecs.lib")


class Texture
{
public:
	Texture( );
	Texture( const std::wstring &Filename, const Direct3D &D3D );
	Texture(const Texture &Tex);
	Texture(Texture &&Tex);
	~Texture( );
	Texture &operator=(Texture &&Tex);
	Texture &operator=(const Texture &Tex);
	const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> &GetResource( )const;

private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;

};

