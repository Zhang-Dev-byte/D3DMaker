#include <D3DMaker.h>
#include <wrl.h>
namespace wrl = Microsoft::WRL;
using namespace DirectX;

class Sandbox : public DM::Application {
    virtual void OnRun(Graphics& g) override {
    }
    virtual void OnKeyboardEvent(KeyboardEvent& kbe) override {

    }
    virtual void OnMouseEvent(MouseEvent& me) override {

    }
    virtual void OnRender(Graphics& g) override {

		// create vertex buffer (1 2d triangle at center of screen)
		const Vertex vertices[] =
		{
			{ 0.0f, 0.5f, 255, 0, 0, 0 },
			{ 0.5f, -0.5f, 0, 255, 0, 0 },
			{ -0.5f, -0.5f, 0, 0, 255, 0 },
		};
		wrl::ComPtr<ID3D11Buffer> pVertexBuffer;
		D3D11_BUFFER_DESC bd = {};
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.CPUAccessFlags = 0u;
		bd.MiscFlags = 0u;
		bd.ByteWidth = sizeof(vertices);
		bd.StructureByteStride = sizeof(Vertex);
		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = vertices;
		g.GetDevice().Get()->CreateBuffer(&bd, &sd, &pVertexBuffer);

		// Bind vertex buffer to pipeline
		const UINT stride = sizeof(Vertex);
		const UINT offset = 0u;
		g.GetContext().Get()->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);


		// create pixel shader
		wrl::ComPtr<ID3D11PixelShader> pPixelShader;
		wrl::ComPtr<ID3DBlob> pBlob;
		D3DReadFileToBlob(L"PixelShader.cso", &pBlob);
		g.GetDevice().Get()->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);

		// bind pixel shader
		g.GetContext().Get()->PSSetShader(pPixelShader.Get(), nullptr, 0u);


		// create vertex shader
		wrl::ComPtr<ID3D11VertexShader> pVertexShader;
		D3DReadFileToBlob(L"VertexShader.cso", &pBlob);
		g.GetDevice().Get()->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);

		// bind vertex shader
		g.GetContext().Get()->VSSetShader(pVertexShader.Get(), nullptr, 0u);


		// input (vertex) layout (2d position only)
		wrl::ComPtr<ID3D11InputLayout> pInputLayout;
		const D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ "Position",0,DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{ "Color",0,DXGI_FORMAT_R8G8B8A8_UNORM,0,8u,D3D11_INPUT_PER_VERTEX_DATA,0 },
		};
		g.GetDevice().Get()->CreateInputLayout(
			ied, (UINT)std::size(ied),
			pBlob->GetBufferPointer(),
			pBlob->GetBufferSize(),
			&pInputLayout
		);

		// bind vertex layout
		g.GetContext().Get()->IASetInputLayout(pInputLayout.Get());


		// bind render target
		g.GetContext().Get()->OMSetRenderTargets(1u, g.GetTarget().GetAddressOf(), nullptr);


		// Set primitive topology to triangle list (groups of 3 vertices)
		g.GetContext().Get()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


		// configure viewport
		D3D11_VIEWPORT vp;
		vp.Width = 1280;
		vp.Height = 720;
		vp.MinDepth = 0;
		vp.MaxDepth = 1;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		g.GetContext().Get()->RSSetViewports(1u, &vp);


		g.GetContext().Get()->Draw((UINT)std::size(vertices), 0u);
    }
};

DM::Application* DM::CreateApplication() {
    return new Sandbox();
}