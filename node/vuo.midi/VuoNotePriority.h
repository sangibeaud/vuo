/**
 * @file
 * VuoNotePriority C type definition.
 *
 * @copyright Copyright © 2012–2022 Kosada Incorporated.
 * This code may be modified and distributed under the terms of the MIT License.
 * For more information, see https://vuo.org/license.
 */

#pragma once

/// @{ List type.
typedef void * VuoList_VuoNotePriority;
#define VuoList_VuoNotePriority_TYPE_DEFINED
/// @}

/**
 * @ingroup VuoTypes
 * @defgroup VuoNotePriority VuoNotePriority
 * Specifies the algorithm for collapsing multiple simultaneously-pressed notes into a single note.
 *
 * @{
 */

/**
 * Specifies the algorithm for collapsing multiple simultaneously-pressed notes into a single note.
 */
typedef enum
{
	VuoNotePriority_First,
	VuoNotePriority_Last,
	VuoNotePriority_Lowest,
	VuoNotePriority_Highest,
} VuoNotePriority;

VuoNotePriority VuoNotePriority_makeFromJson(struct json_object * js);
struct json_object * VuoNotePriority_getJson(const VuoNotePriority value);
VuoList_VuoNotePriority VuoNotePriority_getAllowedValues(void);
char * VuoNotePriority_getSummary(const VuoNotePriority value);

/**
 * Automatically generated function.
 */
///@{
char * VuoNotePriority_getString(const VuoNotePriority value);
void VuoNotePriority_retain(VuoNotePriority value);
void VuoNotePriority_release(VuoNotePriority value);
///@}

/**
 * @}
 */

