/**
 * @file
 * VuoListPosition C type definition.
 *
 * @copyright Copyright © 2012–2022 Kosada Incorporated.
 * This code may be modified and distributed under the terms of the MIT License.
 * For more information, see https://vuo.org/license.
 */

#pragma once

/// @{ List type.
typedef void * VuoList_VuoListPosition;
#define VuoList_VuoListPosition_TYPE_DEFINED
/// @}

/**
 * @ingroup VuoTypes
 * @defgroup VuoListPosition VuoListPosition
 * A position in a list.
 *
 * @{
 */

/**
 * A position in a list.
 */
typedef enum
{
	VuoListPosition_Beginning,
	VuoListPosition_End
} VuoListPosition;

VuoListPosition VuoListPosition_makeFromJson(struct json_object * js);
struct json_object * VuoListPosition_getJson(const VuoListPosition value);
VuoList_VuoListPosition VuoListPosition_getAllowedValues(void);
char * VuoListPosition_getSummary(const VuoListPosition value);

/**
 * Automatically generated function.
 */
///@{
char * VuoListPosition_getString(const VuoListPosition value);
void VuoListPosition_retain(VuoListPosition value);
void VuoListPosition_release(VuoListPosition value);
///@}

/**
 * @}
 */

