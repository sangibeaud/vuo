/**
 * @file
 * vuo.ui.slider node implementation.
 *
 * @copyright Copyright © 2012–2021 Kosada Incorporated.
 * This code may be modified and distributed under the terms of the MIT License.
 * For more information, see https://vuo.org/license.
 */

#include "node.h"

#include "VuoAnchor.h"
#include "VuoLayer.h"
#include "VuoPoint2d.h"
#include "VuoRenderedLayers.h"
#include "VuoText.h"
#include "VuoUiTheme.h"
#include "VuoUiThemeBase.hh"

VuoModuleMetadata({
					  "title" : "Make Slider",
					  "keywords" : [
						  "gui", "user interface", "interact", "widget", "control",
						  "track bar",
					  ],
					  "version" : "1.0.0",
					  "node": {
						  "exampleCompositions" : [ "AdjustColorWithSlider.vuo", "vuo-example://vuo.audio/ControlLoudness.vuo", "DisplayControlPanel.vuo", "DisplayProgressBar.vuo" ]
					  }
				 });

struct nodeInstanceData
{
	bool first;
	VuoRenderedLayers renderedLayers;
	uint64_t id;

	struct {
		VuoText label;
		VuoReal value;
		VuoRange range;
		VuoOrientation orientation;
		VuoAnchor anchor;
		VuoPoint2d position;
		VuoReal trackLength;
		VuoUiTheme theme;
		bool hovering;
		bool pressed;
	} prior;

	VuoReal dragStartedAtValue;
	VuoReal dragStartedAtPosition;
};

extern "C" struct nodeInstanceData *nodeInstanceInit(
	VuoInputData(VuoReal) setValue,
	VuoInputData(VuoRange) range)
{
	struct nodeInstanceData *instance = (struct nodeInstanceData *)calloc(1,sizeof(struct nodeInstanceData));
	VuoRegister(instance, free);

	instance->first = true;
	instance->renderedLayers = VuoRenderedLayers_makeEmpty();
	VuoRenderedLayers_retain(instance->renderedLayers);
	instance->id = VuoSceneObject_getNextId();
	instance->prior.value = VuoRange_clamp(VuoRange_getOrderedRange(range), setValue);

	return instance;
}

extern "C" void nodeInstanceEvent(
	VuoInstanceData(struct nodeInstanceData *) instance,
	VuoInputData(VuoRenderedLayers) window,
	VuoInputEvent({"data":"window"}) windowEvent,
	VuoInputData(VuoText, {"default":"Slider"}) label,
	VuoInputEvent({"data":"label"}) labelEvent,
	VuoInputData(VuoReal, {"default":0}) setValue,
	VuoInputEvent({"data":"setValue", "hasPortAction":true}) setValueEvent,
	VuoInputData(VuoRange, {"default":{"minimum":0.0,"maximum":1.0}, "requireMin":true, "requireMax":true}) range,
	VuoInputData(VuoOrientation, {"default":"horizontal"}) orientation,
//	VuoInputData(VuoAnchor, {"default":{"horizontalAlignment":"center", "verticalAlignment":"center"}}) anchor,
//	VuoInputEvent({"data":"anchor"}) anchorEvent,
	VuoInputData(VuoPoint2d, {"default":{"x":0.0,"y":0.0}, "suggestedMin":{"x":-1,"y":-1}, "suggestedMax":{"x":1,"y":1}, "suggestedStep":{"x":0.1,"y":0.1}}) position,
	VuoInputData(VuoReal, {"default":1}) trackLength,
	VuoInputData(VuoUiTheme) theme,
	VuoOutputTrigger(updatedLayer, VuoLayer),
	VuoOutputTrigger(changed, VuoReal))
{
	bool renderingDimensionsChanged;
	VuoRenderedLayers_update((*instance)->renderedLayers, window, &renderingDimensionsChanged);

	/// @todo
	VuoAnchor anchor = VuoAnchor_makeCentered();

	VuoUiThemeSlider *sliderTheme = static_cast<VuoUiThemeSlider *>(VuoUiTheme_getSpecificTheme(theme, "VuoUiThemeSlider"));
	VuoLocal(sliderTheme);

	VuoRange rangeOrdered = VuoRange_getOrderedRange(range);
	VuoReal trackLengthClamped = fmax(sliderTheme->minimumTrackLength(), trackLength);

	bool portChanged = false;
	if (!VuoText_areEqual((*instance)->prior.label, label))
	{
		portChanged = true;
		VuoRetain(label);
		VuoRelease((*instance)->prior.label);
		(*instance)->prior.label = label;
	}
	if (!VuoRange_areEqual((*instance)->prior.range, rangeOrdered))
	{
		portChanged = true;
		(*instance)->prior.range = rangeOrdered;
	}
	if (!VuoOrientation_areEqual((*instance)->prior.orientation, orientation))
	{
		portChanged = true;
		(*instance)->prior.orientation = orientation;
	}
	if (!VuoAnchor_areEqual((*instance)->prior.anchor, anchor))
	{
		portChanged = true;
		(*instance)->prior.anchor = anchor;
	}
	if (!VuoPoint2d_areEqual((*instance)->prior.position, position))
	{
		portChanged = true;
		(*instance)->prior.position = position;
	}
	if (!VuoReal_areEqual((*instance)->prior.trackLength, trackLengthClamped))
	{
		portChanged = true;
		(*instance)->prior.trackLength = trackLengthClamped;
	}
	if (!VuoUiTheme_areEqual((*instance)->prior.theme, theme))
	{
		portChanged = true;
		VuoRetain(theme);
		VuoRelease((*instance)->prior.theme);
		(*instance)->prior.theme = theme;
	}


	bool isHovering = (*instance)->prior.hovering;
	bool isPressed  = (*instance)->prior.pressed;
	VuoReal value   = (*instance)->prior.value;

	if (setValueEvent)
	{
		value = VuoRange_clamp(rangeOrdered, setValue);

		if (value != (*instance)->prior.value)
			changed(value);
	}

	if ((*instance)->first)
		changed(value);

	float handleMovementLength = sliderTheme->handleMovementLength(trackLengthClamped);

	VuoList_VuoInteraction interactions = VuoRenderedLayers_getInteractions((*instance)->renderedLayers);
	unsigned long interactionCount = VuoListGetCount_VuoInteraction(interactions);
	for (int i = 0; i < interactionCount; ++i)
	{
		VuoInteraction interaction = VuoListGetValue_VuoInteraction(interactions, i + 1);
		isHovering = VuoRenderedLayers_isPointInLayerId((*instance)->renderedLayers, (*instance)->id, interaction.position);

		VuoPoint2d localPoint;
		if (!VuoRenderedLayers_getInverseTransformedPointLayer((*instance)->renderedLayers, (*instance)->id, interaction.position, &localPoint))
			break;

		if (interaction.type == VuoInteractionType_Press
			&& isHovering)
		{
			if (sliderTheme->isPointInsideSliderHandle((*instance)->renderedLayers,
													 trackLengthClamped,
													 VuoRange_scale(range, VuoRange_make(0, 1), value),
													 position,
													 anchor,
													 orientation,
													 localPoint))
			{
				(*instance)->dragStartedAtValue    = value;
				(*instance)->dragStartedAtPosition = orientation == VuoOrientation_Horizontal ? localPoint.x : localPoint.y;
				isPressed                          = true;
			}
			else
			{
				VuoReal lp = orientation == VuoOrientation_Horizontal ? localPoint.x : localPoint.y;
				VuoReal p  = orientation == VuoOrientation_Horizontal ? position.x   : position.y;

				value = rangeOrdered.minimum + (lp - p + handleMovementLength / 2) * (rangeOrdered.maximum - rangeOrdered.minimum) / handleMovementLength;
				value = VuoRange_clamp(rangeOrdered, value);

				(*instance)->dragStartedAtValue    = value;
				(*instance)->dragStartedAtPosition = lp;

				changed(value);

				isPressed = true;
			}
		}
		else if (interaction.type == VuoInteractionType_Release
			  || interaction.type == VuoInteractionType_Click
			  || interaction.type == VuoInteractionType_DragStart
			  || interaction.type == VuoInteractionType_Drag
			  || interaction.type == VuoInteractionType_DragFinish)
		{
			if (isPressed)
			{
				VuoReal lp = orientation == VuoOrientation_Horizontal ? localPoint.x : localPoint.y;

				value = (*instance)->dragStartedAtValue + (lp - (*instance)->dragStartedAtPosition) * (rangeOrdered.maximum - rangeOrdered.minimum) / handleMovementLength;
				value = VuoRange_clamp(rangeOrdered, value);
				changed(value);
			}

			if (interaction.type == VuoInteractionType_Release
			  || interaction.type == VuoInteractionType_Click
			  || interaction.type == VuoInteractionType_DragFinish)
				isPressed = false;
		}
		else if (interaction.type == VuoInteractionType_Canceled)
			isPressed = false;
	}


	if ((*instance)->first
		|| portChanged
		|| (isHovering != (*instance)->prior.hovering)
		|| (isPressed  != (*instance)->prior.pressed)
		|| !VuoReal_areEqual(value, (*instance)->prior.value))
	{
		VuoLayer layer = sliderTheme->render((*instance)->renderedLayers,
												 label,
												 trackLengthClamped,
												 VuoRange_scale(rangeOrdered, VuoRange_make(0, 1), value),
												 position,
												 anchor,
												 orientation,
												 isHovering || isPressed,
												 isPressed);
		if (layer)
		{
			(*instance)->first          = false;
			(*instance)->prior.hovering = isHovering;
			(*instance)->prior.pressed  = isPressed;
			(*instance)->prior.value    = value;

//		if (VuoAnchor_areEqual(anchor, VuoAnchor_makeCentered()))
			VuoLayer_setId(layer, (*instance)->id);
//		else
//		{
//			VuoSceneObject inner = VuoListGetValue_VuoSceneObject(layer.sceneObject.childObjects, 1);
//			inner.id = (*instance)->id;
//			VuoListSetValue_VuoSceneObject(layer.sceneObject.childObjects,
//										   inner,
//										   1,
//										   false);
//		}

			updatedLayer(layer);
		}
	}
}

extern "C" void nodeInstanceFini(
	VuoInstanceData(struct nodeInstanceData *) instance)
{
	VuoRenderedLayers_release((*instance)->renderedLayers);
	VuoRelease((*instance)->prior.label);
	VuoRelease((*instance)->prior.theme);
}
