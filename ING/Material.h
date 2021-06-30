#ifndef MATERIAL_H
#define MATERIAL_H

#include "INGLib.h"

namespace Infinite {

	struct Shader;

	struct ConstantBufferInput;

	struct Material {

		Shader* pShader;

		std::vector< ConstantBufferInput> cbInputs;

		std::vector<ID3D11Buffer*> cbs;

		bool isRegisted = false;

	};

}


#endif