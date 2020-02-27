/**
 * @file
 * vuo.test.compatibleWith107AndUp node implementation.
 *
 * @copyright Copyright © 2012–2020 Kosada Incorporated.
 * This code may be modified and distributed under the terms of the GNU Lesser General Public License (LGPL) version 2 or later.
 * For more information, see https://vuo.org/license.
 */

#include "node.h"

VuoModuleMetadata({
					 "compatibleOperatingSystems": {
						"macosx" : { "min": "10.7" }
					 }
				 });

void nodeEvent() { }
