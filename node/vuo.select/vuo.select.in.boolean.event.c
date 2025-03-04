/**
 * @file
 * vuo.select.in.boolean.event node implementation.
 *
 * @copyright Copyright © 2012–2022 Kosada Incorporated.
 * This code may be modified and distributed under the terms of the MIT License.
 * For more information, see https://vuo.org/license.
 */

#include "node.h"

VuoModuleMetadata({
					 "title" : "Select Event Input (Boolean)",
					 "keywords" : [ "switch", "multiplexer", "if then else statement", "case", "route", "condition", "control flow",
						"activate", "deactivate", "enable", "disable", "choose", "pick", "mode", "block", "door" ],
					 "version" : "2.0.0",
					 "node": {
						  "isDeprecated" : true,
						  "exampleCompositions" : [ ]
					 }
				 });

void nodeEvent
(
		VuoInputData(VuoBoolean, {"default":false}) which,
		VuoInputEvent({"eventBlocking":"door","hasPortAction":false}) falseOption,
		VuoInputEvent({"eventBlocking":"door","hasPortAction":false}) trueOption,
		VuoOutputEvent() out
)
{
	if (which == false)
		*out = falseOption;
	else
		*out = trueOption;
}
