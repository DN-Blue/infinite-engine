#ifndef SHADER_H
#define SHADER_H

#include "INGLib.h"

namespace Infinite {
	


	struct Shader {

		ID3DBlob* pvsblob;
		ID3DBlob* ppsblob;

		ID3D11VertexShader* pVS;
		ID3D11PixelShader* pPS;

		ID3D11InputLayout* pVertexInputLayout;

	};

}


#endif