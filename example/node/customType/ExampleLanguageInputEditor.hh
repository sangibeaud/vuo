/**
 * @file
 * ExampleLanguageInputEditor interface.
 *
 * @copyright Copyright © 2012–2022 Kosada Incorporated.
 * This code may be modified and distributed under the terms of the MIT License.
 * For more information, see https://vuo.org/license.
 */

#pragma once

#include "VuoInputEditorWithMenu.hh"

/**
 * An ExampleLanguageInputEditor factory.
 */
class ExampleLanguageInputEditorFactory : public VuoInputEditorFactory
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.vuo.inputEditor" FILE "ExampleLanguageInputEditor.json")
	Q_INTERFACES(VuoInputEditorFactory)

public:
	VuoInputEditor *newInputEditor();
};

/**
 * An input editor that displays a menu of ExampleLanguage values.
 */
class ExampleLanguageInputEditor : public VuoInputEditorWithMenu
{
	Q_OBJECT

public:
	VuoInputEditorMenuItem * setUpMenuTree();
};
