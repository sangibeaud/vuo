/**
 * @file
 * vuo.test.releaseWithoutRegister node implementation.
 *
 * @copyright Copyright © 2012–2022 Kosada Incorporated.
 * This code may be modified and distributed under the terms of the GNU Lesser General Public License (LGPL) version 2 or later.
 * For more information, see https://vuo.org/license.
 */

#include "node.h"

VuoModuleMetadata({
					 "title" : "Release without Register",
					 "description" : "This node class contains an intentional bug for testing.",
					 "version" : "1.0.0",
				 });

void nodeEvent
(
		VuoOutputData(VuoInteger) outEvent
)
{
	char *x = malloc(1);
	VuoRelease(x);  // intentional bug
	*outEvent = 0;
}
