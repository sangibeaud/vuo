/**
 * @file
 * vuo.layer.make.realSize node implementation.
 *
 * @copyright Copyright © 2012–2017 Kosada Incorporated.
 * This code may be modified and distributed under the terms of the MIT License.
 * For more information, see http://vuo.org/license.
 */

#include "node.h"
#include "VuoLayer.h"

VuoModuleMetadata({
					 "title" : "Make Image Layer with Shadow (Real Size)",
					 "keywords" : [ "billboard", "sprite", "image", "pixel aligned", "exact", "actual", "glow" ],
					 "version" : "2.1.0",
					 "node" : {
						 "exampleCompositions" : [ ]
					 }
				 });

void nodeEvent
(
		VuoInputData(VuoText) name,
		VuoInputData(VuoImage) image,
		VuoInputData(VuoPoint2d, {"default":{"x":0.0,"y":0.0}, "suggestedMin":{"x":-1,"y":-1}, "suggestedMax":{"x":1,"y":1}, "suggestedStep":{"x":0.1,"y":0.1}}) center,
		VuoInputData(VuoReal, {"default":1.0, "suggestedMin":0.0, "suggestedMax":1.0, "suggestedStep":0.1}) opacity,
		VuoInputData(VuoBoolean, {"default":false}) preservePhysicalSize,
		VuoInputData(VuoColor, {"default":{"r":0,"g":0,"b":0,"a":1}}) shadowColor,
		VuoInputData(VuoReal, {"default":4, "suggestedMin":0, "suggestedMax":20}) shadowBlur,
		VuoInputData(VuoReal, {"default":315.0, "suggestedMin":0, "suggestedMax":360}) shadowAngle,
		VuoInputData(VuoReal, {"default":0.005, "suggestedMin":0, "suggestedStep":0.005}) shadowDistance,
		VuoOutputData(VuoLayer) layer
)
{
	*layer = VuoLayer_makeRealSizeWithShadow(name, image, center, opacity, preservePhysicalSize, shadowColor, shadowBlur, shadowAngle, shadowDistance);
}
