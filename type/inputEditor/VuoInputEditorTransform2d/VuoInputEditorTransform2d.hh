/**
 * @file
 * VuoInputEditorTransform2d interface.
 *
 * @copyright Copyright © 2012–2022 Kosada Incorporated.
 * This code may be modified and distributed under the terms of the MIT License.
 * For more information, see https://vuo.org/license.
 */

#pragma once

#include "VuoInputEditorWithDialog.hh"
#include "VuoDoubleSpinBox.hh"

extern "C" {
#include "VuoTransform2d.h"
}

/**
 * A VuoInputEditorTransform2d factory.
 */
class VuoInputEditorTransform2dFactory : public VuoInputEditorFactory
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.vuo.inputEditor" FILE "VuoInputEditorTransform2d.json")
	Q_INTERFACES(VuoInputEditorFactory)

public:
	virtual VuoInputEditor * newInputEditor(void);
};

/**
 * An input editor that displays widgets for editing a VuoTransform2d value,
 * allowing the user to specify the XY translation, rotation (roll), and XY scale.
 *
 * This input editor recognizes the following keys in the JSON details object:
 *   - "suggestedMin" and "suggestedMax" define the range of the slider (if both are defined)
 *		or spin box (if one is defined) but don't affect the line edit. By default, the dialog
 *      contains a spin box with unbounded range.
 *	 - "suggestedStep" defines the step size of the slider or spin box. By default, the step size is 1.
 *
 * @eg{
 *   {
 *     "suggestedMin" : -1.0,
 *     "suggestedMax" : 1.0,
 *     "suggestedStep" : 0.25
 *   }
 * }
 */
class VuoInputEditorTransform2d : public VuoInputEditorWithDialog
{
	Q_OBJECT

protected:
	void setUpDialog(QDialog &dialog, json_object *originalValue, json_object *details);
	json_object * getAcceptedValue(void);
	virtual bool supportsTabbingBetweenPorts(void) { return true; }			///< This editor does support tabbing between ports.

private:

	VuoTransform2d currentTransform;

	enum coord
	{
		xTranslation,
		yTranslation,
		rotation,
		xScale,
		yScale
	};

	map<coord, double> suggestedMinForCoord;	///< The minimum <coord>-value selectable via spinbox or slider.
	map<coord, double> suggestedMaxForCoord;	///< The maximum <coord>-value selectable via spinbox or slider.
	map<coord, double> suggestedStepForCoord;	///< The spinbox step value for <coord>.

	map<coord, QSlider *> sliderForCoord;
	map<coord, VuoDoubleSpinBox *> spinboxForCoord;

	coord getCoordFromQObject(QObject* sender);
	void setCoordMap(map<coord, double>* coordMap, VuoTransform2d transform);
	void setTransformProperty(coord whichCoord, double value);

	double sliderToDouble(int sliderMin, int sliderMax, double valueMin, double valueMax, int value);
	int doubleToSlider(int sliderMin, int sliderMax, double valueMin, double valueMax, double value);

	VuoDoubleSpinBox* initSpinBox(coord whichCoord, QDialog& dialog, double initialValue);
	QSlider* initSlider(coord c, QDialog& dialog, double initialValue);

private slots:
	void onSliderUpdate(int sliderValue);
	void onSpinboxUpdate(QString spinboxValue);
};

