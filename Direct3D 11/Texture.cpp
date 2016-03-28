#include "Texture.h"
#include <memory>
#include <assert.h>

Texture::Texture( )
{
	CoInitialize( nullptr );
}

Texture::Texture( const std::wstring &Filename, const Direct3D & D3D )
{
	Microsoft::WRL::ComPtr<IWICImagingFactory2> factory;
	Microsoft::WRL::ComPtr<IWICBitmapDecoder> decoder;
	Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> frame;
	Microsoft::WRL::ComPtr<IWICFormatConverter> converter;

	// Initialize the IWICImagingFactory
	HRESULT hr = CoCreateInstance(
		CLSID_WICImagingFactory, nullptr,
		CLSCTX_INPROC_SERVER, IID_PPV_ARGS( factory.GetAddressOf() ) );
	assert( SUCCEEDED( hr ) );

	// Create a decoder from file
	hr = factory->
		CreateDecoderFromFilename( Filename.data( ), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, decoder.GetAddressOf( ) );
	assert( SUCCEEDED( hr ) );

	// Get the first frame, which images only have 1 frame
	hr = decoder->GetFrame( 0, frame.GetAddressOf( ) );
	assert( SUCCEEDED( hr ) );

	// Create a converter to convert to Packed BGRA, for use with D3D
	hr = factory->CreateFormatConverter( converter.GetAddressOf( ) );
	assert( SUCCEEDED( hr ) );

	// Initialize the converter	
	hr = converter->Initialize( frame.Get( ), GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 1.0f, WICBitmapPaletteTypeCustom );
	assert( SUCCEEDED( hr ) );

	// Get width and height of the image
	UINT width = 0, height = 0;
	hr = converter->GetSize( &width, &height );
	assert( SUCCEEDED( hr ) );

	// Create a temporary buffer to initialize the ID3D11Texture2D
	UINT buffer_size = width * height * sizeof( unsigned int );
	std::unique_ptr<BYTE[]> data( std::make_unique<BYTE[]>(buffer_size));
	assert( data != nullptr );

	// Pass nullptr, to get the entire image
	UINT stride = width * sizeof( unsigned int );
	hr = converter->CopyPixels( nullptr, stride, buffer_size, data.get() );
	assert( SUCCEEDED( hr ) );

	BYTE *pixels = data.get( );
	// Create the shader resource
	ID3D11Texture2D *tex = D3D.CreateTexture( width, height, DXGI_FORMAT_B8G8R8A8_UNORM, D3D11_BIND_SHADER_RESOURCE, &pixels );
	srv = D3D.CreateShaderResource( tex );
}

Texture::Texture(const Texture & Tex)
	:
	srv(Tex.srv)
{
}

Texture::Texture(Texture && Tex)
	:
	srv(std::move(srv))
{
}

Texture::~Texture( )
{ 
}

Texture & Texture::operator=(Texture && Tex)
{
	srv = std::move(Tex.srv);
	return *this;
}

Texture & Texture::operator=(const Texture & Tex)
{
	srv = Tex.srv;
	return *this;
}

const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& Texture::GetResource( ) const
{
	return srv;
}
