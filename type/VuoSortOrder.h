/**
 * @file
 * VuoSortOrder C type definition.
 *
 * @copyright Copyright © 2012–2022 Kosada Incorporated.
 * This code may be modified and distributed under the terms of the MIT License.
 * For more information, see https://vuo.org/license.
 */

#pragma once

/// @{ List type.
typedef const struct VuoList_VuoSortOrder_struct { void *l; } * VuoList_VuoSortOrder;
#define VuoList_VuoSortOrder_TYPE_DEFINED
/// @}

/**
 * @ingroup VuoTypes
 * @defgroup VuoSortOrder VuoSortOrder
 * Ascending or descending order.
 *
 * @{
 */

/**
 * Ascending or descending order.
 */
typedef enum
{
	VuoSortOrder_Ascending,
	VuoSortOrder_Descending
} VuoSortOrder;

VuoSortOrder VuoSortOrder_makeFromJson(struct json_object * js);
struct json_object * VuoSortOrder_getJson(const VuoSortOrder value);
VuoList_VuoSortOrder VuoSortOrder_getAllowedValues(void);
char * VuoSortOrder_getSummary(const VuoSortOrder value);

/// @{
/**
 * Automatically generated function.
 */
char * VuoSortOrder_getString(const VuoSortOrder value);
/// @}

/**
 * @}
 */
