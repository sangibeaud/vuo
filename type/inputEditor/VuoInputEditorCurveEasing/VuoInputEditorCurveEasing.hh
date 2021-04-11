/**
 * @file
 * VuoInputEditorCurveEasing interface.
 *
 * @copyright Copyright © 2012–2021 Kosada Incorporated.
 * This code may be modified and distributed under the terms of the MIT License.
 * For more information, see https://vuo.org/license.
 */

#pragma once

#include "VuoInputEditorWithMenu.hh"

/**
 * A VuoInputEditorCurveEasing factory.
 */
class VuoInputEditorCurveEasingFactory : public VuoInputEditorFactory
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.vuo.inputEditor" FILE "VuoInputEditorCurveEasing.json")
	Q_INTERFACES(VuoInputEditorFactory)

public:
	virtual VuoInputEditor * newInputEditor(void);
};

/**
 * An input editor that displays a menu of VuoCurveEasing values.
 */
class VuoInputEditorCurveEasing : public VuoInputEditorWithMenu
{
	Q_OBJECT

public:
	VuoInputEditorMenuItem * setUpMenuTree();
};

