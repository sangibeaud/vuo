/**
 * @file
 * VuoType interface.
 *
 * @copyright Copyright © 2012–2022 Kosada Incorporated.
 * This interface description may be modified and distributed under the terms of the GNU Lesser General Public License (LGPL) version 2 or later.
 * For more information, see https://vuo.org/license.
 */

#pragma once

#include "VuoBase.hh"
#include "VuoModule.hh"

class VuoCompilerType;

/**
 * This base class represents the metadata of one type.
 */
class VuoType : public VuoBase<VuoCompilerType,void>, public VuoModule
{
public:
	VuoType(string typeName);
	virtual ~VuoType(void);  ///< to make this class dynamic_cast-able

	static const string listTypeNamePrefix;
	static const string dictionaryTypeNamePrefix;
	static bool isListTypeName(string typeName);
	static bool isDictionaryTypeName(string typeName);
	static string extractInnermostTypeName(string typeName);
};
