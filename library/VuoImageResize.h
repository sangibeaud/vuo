/**
 * @file
 * VuoImageResize interface.
 *
 * @copyright Copyright © 2012–2017 Kosada Incorporated.
 * This code may be modified and distributed under the terms of the MIT License.
 * For more information, see http://vuo.org/license.
 */
#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "VuoImage.h"
#include "VuoImageRenderer.h"
#include "../node/vuo.image/VuoSizingMode.h"

typedef void *VuoImageResize;	///< Resize state data.

VuoImageResize VuoImageResize_make(void);
VuoImage VuoImageResize_resize(VuoImage image, VuoImageResize resize, VuoImageRenderer renderer, VuoSizingMode sizingMode, VuoInteger width, VuoInteger height);

#ifdef __cplusplus
}
#endif
