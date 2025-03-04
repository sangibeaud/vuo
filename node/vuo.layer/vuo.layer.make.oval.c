/**
 * @file
 * vuo.layer.make.oval node implementation.
 *
 * @copyright Copyright © 2012–2022 Kosada Incorporated.
 * This code may be modified and distributed under the terms of the MIT License.
 * For more information, see https://vuo.org/license.
 */

#include "node.h"
#include "VuoLayer.h"

VuoModuleMetadata({
					 "title" : "Make Oval Layer",
					 "keywords" : [ "circle", "rounded", "ellipse", "shape" ],
					 "version" : "1.2.0",
					 "node": {
						  "isDeprecated": true,
						  "exampleCompositions" : [ "DrawShapes.vuo" ]
					 }
				 });

uint64_t nodeInstanceInit(void)
{
	return VuoSceneObject_getNextId();
}

void nodeInstanceEvent
(
	VuoInstanceData(uint64_t) id,
		VuoInputData(VuoText) name,
		VuoInputData(VuoColor,{"default":{"r":1,"g":1,"b":1,"a":1}}) color,
		VuoInputData(VuoAnchor, { "default": { "horizontalAlignment":"center", "verticalAlignment":"center" } }) anchor,
		VuoInputData(VuoPoint2d, {"name":"Position", "default":{"x":0.0,"y":0.0}, "suggestedMin":{"x":-1,"y":-1}, "suggestedMax":{"x":1,"y":1}, "suggestedStep":{"x":0.1,"y":0.1}}) center,
		VuoInputData(VuoReal, {"default":0.0, "suggestedMin":-180, "suggestedMax":180, "suggestedStep":15.0}) rotation,
		VuoInputData(VuoReal, {"default":2.0, "suggestedMin":0.0, "suggestedStep":0.1}) width,
		VuoInputData(VuoReal, {"default":2.0, "suggestedMin":0.0, "suggestedStep":0.1}) height,
		VuoInputData(VuoReal, {"default":1.0, "suggestedMin":0, "suggestedMax":1}) sharpness,
		VuoInputData(VuoReal, {"default":1.0, "suggestedMin":0.0, "suggestedMax":1.0, "suggestedStep":0.1}) opacity,
		VuoOutputData(VuoLayer) layer
)
{
	VuoColor c = color;
	c.a *= opacity;
	*layer = VuoLayer_setAnchor( VuoLayer_makeOval(name, c, center, rotation, width, height, sharpness), anchor, -1, -1, -1);
	VuoLayer_setId(*layer, *id);
}
