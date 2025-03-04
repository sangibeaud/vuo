/**
 * @file
 * VuoImageBlend interface.
 *
 * @copyright Copyright © 2012–2022 Kosada Incorporated.
 * This code may be modified and distributed under the terms of the MIT License.
 * For more information, see https://vuo.org/license.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "VuoBlendMode.h"
#include "VuoImage.h"

typedef void *VuoImageBlend;  ///< State data for the image blender.

VuoImageBlend VuoImageBlend_make(VuoBlendMode blendMode);
VuoImage VuoImageBlend_blend(VuoImageBlend blend, VuoImage background, VuoImage foreground, VuoReal foregroundOpacity, VuoBoolean replaceOpacity);

#ifdef __cplusplus
}
#endif
