/**
 * @file
 * vuo.type.integer.point4d node implementation.
 *
 * @copyright Copyright © 2012–2022 Kosada Incorporated.
 * This code may be modified and distributed under the terms of the MIT License.
 * For more information, see https://vuo.org/license.
 */

#include "node.h"

VuoModuleMetadata({
					 "title" : "Convert Integer to 4D Point (0,Y,0,0)",
					 "keywords" : [ ],
					 "version" : "1.0.1"
				 });

void nodeEvent
(
		VuoInputData(VuoInteger, {"default":0}) y,
		VuoOutputData(VuoPoint4d, {"name":"(0,Y,0,0)"}) point4d
)
{
	*point4d = VuoPoint4d_make(0, y, 0, 0);
}
