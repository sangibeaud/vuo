/**
 * @file
 * vuo.dictionary.make.VuoText.VuoReal node implementation.
 *
 * @copyright Copyright © 2012–2022 Kosada Incorporated.
 * This code may be modified and distributed under the terms of the MIT License.
 * For more information, see https://vuo.org/license.
 */

#include "node.h"
#include "VuoDictionary_VuoText_VuoReal.h"

VuoModuleMetadata({
	"title": "Make Dictionary",
	"description": "Creates a dictionary from a list of keys and values.",
	"keywords": [
		"string",
	],
	"version": "1.0.0",
	"node": {
		"exampleCompositions": [ ],
	},
});

void nodeEvent
(
		VuoInputData(VuoList_VuoText) keys,
		VuoInputData(VuoList_VuoReal) values,
		VuoOutputData(VuoDictionary_VuoText_VuoReal) dictionary
)
{
	*dictionary = VuoDictionaryCreateWithLists_VuoText_VuoReal(keys, values);
}
