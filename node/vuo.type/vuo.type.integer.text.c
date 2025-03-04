﻿/**
 * @file
 * vuo.type.integer.text node implementation.
 *
 * @copyright Copyright © 2012–2022 Kosada Incorporated.
 * This code may be modified and distributed under the terms of the MIT License.
 * For more information, see https://vuo.org/license.
 */

#include "node.h"
#include <stdlib.h>
#include <string.h>

VuoModuleMetadata({
					 "title" : "Convert Integer to Text",
					 "keywords" : [ ],
					 "version" : "1.0.1",
					 "node": {
						   "exampleCompositions" : [ ],
						   "isDeprecated": true
					  }
				 });

void nodeEvent
(
	VuoInputData(VuoInteger, {"default":0}) integer,
	VuoOutputData(VuoText) text
)
{
	*text = VuoText_makeWithoutCopying(VuoInteger_getString(integer));
}
