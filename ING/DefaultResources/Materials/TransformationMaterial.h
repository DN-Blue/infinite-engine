#ifndef  TRANSFORMATIONMATERIAL_H
#define TRANSFORMATIONMATERIAL_H

#include "../../INGLib.h"

using namespace DirectX;

namespace Infinite {

	namespace DefaultResources {

		struct TransformationMaterialInput {
			XMMATRIX mWorld;
			XMMATRIX mView;
			XMMATRIX mProjection;
			XMVECTOR viewPos;
			XMVECTOR time;
		};

	}

}

#endif // ! TRANSFORMATIONMATERIAL_H
