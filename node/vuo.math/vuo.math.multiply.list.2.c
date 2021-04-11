/**
 * @file
 * vuo.math.multiply.list.2 node implementation.
 *
 * @copyright Copyright © 2012–2021 Kosada Incorporated.
 * This code may be modified and distributed under the terms of the MIT License.
 * For more information, see https://vuo.org/license.
 */

#include "node.h"

VuoModuleMetadata({
					  "title" : "Multiply Lists",
					  "keywords" : [ "scale", "product", "times", "*", "•", "×", "x", "arithmetic", "calculate" ],
					  "version" : "1.0.0",
					  "genericTypes" : {
						  "VuoGenericType1" : {
							  "compatibleTypes" : [ "VuoInteger", "VuoReal", "VuoPoint2d", "VuoPoint3d", "VuoPoint4d" ]
						  }
					  },
					  "node" : {
						  "exampleCompositions" : [ ]
					  }
				  });

void nodeEvent
(
		VuoInputData(VuoList_VuoGenericType1) list1,
		VuoInputData(VuoList_VuoGenericType1) list2,
		VuoOutputData(VuoList_VuoGenericType1) productList
)
{
	*productList = VuoListCreate_VuoGenericType1();
	unsigned long list1Count = VuoListGetCount_VuoGenericType1(list1);
	unsigned long list2Count = VuoListGetCount_VuoGenericType1(list2);
	unsigned long maxCount = MAX(list1Count, list2Count);
	for (unsigned long i = 1; i <= maxCount; ++i)
	{
		VuoGenericType1 v1;
		if (list1Count)
			v1 = VuoListGetValue_VuoGenericType1(list1, i);
		else
			v1 = 1;

		VuoGenericType1 v2;
		if (list2Count)
			v2 = VuoListGetValue_VuoGenericType1(list2, i);
		else
			v2 = 1;

		VuoGenericType1 product = VuoGenericType1_scale(v1, v2);
		VuoListAppendValue_VuoGenericType1(*productList, product);
	}
}
