/**
 * @file
 * VuoInputEditorAnchor interface.
 *
 * @copyright Copyright © 2012–2015 Kosada Incorporated.
 * This code may be modified and distributed under the terms of the MIT License.
 * For more information, see https://vuo.org/license.
 */

#ifndef VUOINPUTEDITORANCHOR
#define VUOINPUTEDITORANCHOR

#include "VuoInputEditor.hh"
#include "VuoInputEditorWithDialog.hh"

extern "C"
{
	#include "VuoAnchor.h"
}

/**
 * A VuoInputEditorAnchor factory.
 */
class VuoInputEditorAnchorFactory : public VuoInputEditorFactory
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.vuo.inputEditor" FILE "VuoInputEditorAnchor.json")
	Q_INTERFACES(VuoInputEditorFactory)

public:
	virtual VuoInputEditor * newInputEditor(void);
};

/**
 * An input editor that edits any type.
 */
class VuoInputEditorAnchor : public VuoInputEditorWithDialog
{
	Q_OBJECT

protected:
	void setUpDialog(QDialog &dialog, json_object *originalValue, json_object *details);
	json_object* getAcceptedValue();

private:
	QPushButton* matrix[9];
	json_object* currentValue;
	QIcon* renderIconWithLineSegments(const float* points, const unsigned int length);
	QIcon* iconForAnchorIndex(const int anchor);

	// Return the index in ANCHOR_MAP that a VuoAnchor corresponds to.
	int VuoAnchorToIndex(const VuoAnchor anchor);

	// corresponds to the matching button index (0-8)
	const VuoAnchor ANCHOR_MAP[9] =
	{
		VuoAnchor_make(VuoHorizontalAlignment_Left,   VuoVerticalAlignment_Top   ),
		VuoAnchor_make(VuoHorizontalAlignment_Center, VuoVerticalAlignment_Top   ),
		VuoAnchor_make(VuoHorizontalAlignment_Right,  VuoVerticalAlignment_Top   ),
		VuoAnchor_make(VuoHorizontalAlignment_Left,   VuoVerticalAlignment_Center),
		VuoAnchor_make(VuoHorizontalAlignment_Center, VuoVerticalAlignment_Center),
		VuoAnchor_make(VuoHorizontalAlignment_Right,  VuoVerticalAlignment_Center),
		VuoAnchor_make(VuoHorizontalAlignment_Left,   VuoVerticalAlignment_Bottom),
		VuoAnchor_make(VuoHorizontalAlignment_Center, VuoVerticalAlignment_Bottom),
		VuoAnchor_make(VuoHorizontalAlignment_Right,  VuoVerticalAlignment_Bottom)
	};

private slots:
	void onSetAnchor();
};

#endif
