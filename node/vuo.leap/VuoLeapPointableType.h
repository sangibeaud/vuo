/**
 * @file
 * VuoLeapPointableType C type definition.
 *
 * @copyright Copyright © 2012–2022 Kosada Incorporated.
 * This code may be modified and distributed under the terms of the MIT License.
 * For more information, see https://vuo.org/license.
 */

#pragma once

/// @{ List type.
typedef const struct VuoList_VuoLeapPointableType_struct { void *l; } * VuoList_VuoLeapPointableType;
#define VuoList_VuoLeapPointableType_TYPE_DEFINED
/// @}

/**
 * @ingroup VuoTypes
 * @defgroup VuoLeapPointableType VuoLeapPointableType
 * Whether a pointable is a finger or a tool.
 *
 * @{
 */

/**
 * Whether a pointable is a finger or a tool.
 */
typedef enum {
	VuoLeapPointableType_Finger,
	VuoLeapPointableType_Tool
} VuoLeapPointableType;

VuoLeapPointableType VuoLeapPointableType_makeFromJson(struct json_object * js);
struct json_object * VuoLeapPointableType_getJson(const VuoLeapPointableType value);
VuoList_VuoLeapPointableType VuoLeapPointableType_getAllowedValues(void);
char * VuoLeapPointableType_getSummary(const VuoLeapPointableType value);

/// @{
/**
 * Automatically generated function.
 */
char * VuoLeapPointableType_getString(const VuoLeapPointableType value);
/// @}

/**
 * @}
*/
