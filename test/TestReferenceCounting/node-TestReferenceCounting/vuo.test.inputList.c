/**
 * @file
 * vuo.test.inputList node implementation.
 *
 * @copyright Copyright © 2012–2022 Kosada Incorporated.
 * This code may be modified and distributed under the terms of the GNU Lesser General Public License (LGPL) version 2 or later.
 * For more information, see https://vuo.org/license.
 */

#include "node.h"

VuoModuleMetadata({
					 "title" : "Input List",
					 "description" : "",
					 "version" : "1.0.0",
				 });

void nodeEvent
(
		VuoInputData(VuoList_VuoText) listIn,
		VuoOutputData(VuoInteger) outEvent
)
{
	*outEvent = 0;
}
