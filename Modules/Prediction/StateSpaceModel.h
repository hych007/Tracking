// StateSpaceModel.h
#ifndef _STATESPACEMODEL_H_
#define _STATESPACEMODEL_H_

#include <opencv\cv.h>

namespace Prediction
{
	class StateSpaceModel
	{
	public:
		StateSpaceModel(float x0 = 0, float y0 = 0);

		cv::Mat A, C, Q, P, xHat;
		float R;
	};
}

#endif