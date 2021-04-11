/**
 * @file
 * vuo.type.real.boolean node implementation.
 *
 * @copyright Copyright © 2012–2021 Kosada Incorporated.
 * This code may be modified and distributed under the terms of the MIT License.
 * For more information, see https://vuo.org/license.
 */

#include "node.h"

VuoModuleMetadata({
					 "title" : "Is Real Nonzero",
					 "keywords" : [ "0", "1", "true", "false" ],
					 "version" : "1.0.0"
				 });

void nodeEvent
(
	VuoInputData(VuoReal, {"default":0.0}) real,
	VuoOutputData(VuoBoolean) boolean
)
{
	*boolean = (! VuoReal_areEqual(real, 0));
}
