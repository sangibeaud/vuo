/**
 * @file
 * vuo.window.cursor node implementation.
 *
 * @copyright Copyright © 2012–2022 Kosada Incorporated.
 * This code may be modified and distributed under the terms of the MIT License.
 * For more information, see https://vuo.org/license.
 */

#include "node.h"
#include "VuoWindowProperty.h"

VuoModuleMetadata({
					 "title" : "Change Mouse Cursor",
					 "keywords" : [ "pointer", "hand", "arrow", "hide", "touch", "properties", "set" ],
					 "version" : "1.0.0",
					 "node": {
						 "isDeprecated": true,
						 "exampleCompositions" : [ "DragWithHandCursor.vuo" ]
					 }
				 });

void nodeEvent
(
		VuoInputData(VuoCursor, {"default":"none"}) cursor,
		VuoOutputData(VuoWindowProperty) property
)
{
	(*property).type = VuoWindowProperty_Cursor;
	(*property).cursor = cursor;
}
