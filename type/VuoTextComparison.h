/**
 * @file
 * VuoTextComparison C type definition.
 *
 * @copyright Copyright © 2012–2022 Kosada Incorporated.
 * This code may be modified and distributed under the terms of the MIT License.
 * For more information, see https://vuo.org/license.
 */

#pragma once

/// @{ List type.
typedef const struct VuoList_VuoTextComparison_struct { void *l; } * VuoList_VuoTextComparison;
#define VuoList_VuoTextComparison_TYPE_DEFINED
/// @}

/**
 * @ingroup VuoTypes
 * @defgroup VuoTextComparison VuoTextComparison
 * Parameters for comparing two texts.
 *
 * @{
 */

/**
 * Various ways of comparing one text to another to see if they match.
 *
 * @version200Changed{Added `VuoTextComparison_MatchesWildcard`, `VuoTextComparison_MatchesRegEx`.}
 */
typedef enum
{
	VuoTextComparison_Equals,
	VuoTextComparison_Contains,
	VuoTextComparison_BeginsWith,
	VuoTextComparison_EndsWith,
	VuoTextComparison_MatchesWildcard,
	VuoTextComparison_MatchesRegEx,
} VuoTextComparisonType;

/**
 * Parameters for comparing one text to another.
 */
typedef struct
{
	VuoTextComparisonType type;
	bool isCaseSensitive;
} VuoTextComparison;

VuoTextComparison VuoTextComparison_makeFromJson(struct json_object * js);
struct json_object * VuoTextComparison_getJson(const VuoTextComparison value);
//VuoList_VuoTextComparison VuoTextComparison_getAllowedValues(void);
char * VuoTextComparison_getSummary(const VuoTextComparison value);

/// @{
/**
 * Automatically generated function.
 */
char * VuoTextComparison_getString(const VuoTextComparison value);
void VuoTextComparison_retain(VuoTextComparison value);
void VuoTextComparison_release(VuoTextComparison value);
/// @}

/**
 * @}
 */
