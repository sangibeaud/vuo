/**
 * @file
 * vuo.text.removeHtml node implementation.
 *
 * @copyright Copyright © 2012–2016 Kosada Incorporated.
 * This code may be modified and distributed under the terms of the MIT License.
 * For more information, see http://vuo.org/license.
 */

#include "node.h"
#include "VuoTextHtml.h"

VuoModuleMetadata({
					  "title" : "Remove HTML",
					  "keywords" : [
						  "strip", "filter", "interpret",
						  "xml", "markup", "tags", "character", "entity", "reference"
					  ],
					  "version" : "1.0.0",
					  "node": {
						  "exampleCompositions" : [ ]
					  },
					  "dependencies" : [
						  "VuoTextHtml"
					  ]
				 });

void nodeEvent
(
		VuoInputData(VuoText) text,
		VuoOutputData(VuoText) modifiedText
)
{
	*modifiedText = VuoText_removeHtml(text);
}
