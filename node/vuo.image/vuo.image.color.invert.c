/**
 * @file
 * vuo.image.color.invert node implementation.
 *
 * @copyright Copyright © 2012–2016 Kosada Incorporated.
 * This code may be modified and distributed under the terms of the MIT License.
 * For more information, see http://vuo.org/license.
 */

#include "node.h"
#include "VuoImageRenderer.h"

VuoModuleMetadata({
					 "title" : "Invert Image Colors",
					 "keywords" : [ "reverse", "negative", "filter" ],
					 "version" : "1.1.2",
					 "node" : {
						 "exampleCompositions" : [ ]
					 }
				 });

static const char * invertFragmentShader = VUOSHADER_GLSL_SOURCE(120,
	include(VuoGlslAlpha)

	varying vec4 fragmentTextureCoordinate;
	uniform sampler2D texture;

	void main(void)
	{
		vec4 color = VuoGlsl_sample(texture, fragmentTextureCoordinate.xy);
		color.rgb /= color.a > 0. ? color.a : 1.;
		color.rgb = 1. - color.rgb;
		color.rgb *= color.a;
		gl_FragColor = color;
	}
);

struct nodeInstanceData
{
	VuoGlContext glContext;
	VuoShader shader;
	VuoImageRenderer imageRenderer;
};

struct nodeInstanceData * nodeInstanceInit(void)
{
	struct nodeInstanceData * instance = (struct nodeInstanceData *)malloc(sizeof(struct nodeInstanceData));
	VuoRegister(instance, free);

	instance->glContext = VuoGlContext_use();

	instance->imageRenderer = VuoImageRenderer_make(instance->glContext);
	VuoRetain(instance->imageRenderer);

	instance->shader = VuoShader_make("Invert Color Shader");
	VuoShader_addSource(instance->shader, VuoMesh_IndividualTriangles, NULL, NULL, invertFragmentShader);
	VuoRetain(instance->shader);
	return instance;
}

void nodeInstanceEvent
(
		VuoInstanceData(struct nodeInstanceData *) instance,
		VuoInputData(VuoImage) image,
		VuoOutputData(VuoImage) invertedImage
)
{
	if (!image)
	{
		*invertedImage = NULL;
		return;
	}

	int w = image->pixelsWide, h = image->pixelsHigh;

	VuoShader_setUniform_VuoImage((*instance)->shader, "texture", image);
	*invertedImage = VuoImageRenderer_draw((*instance)->imageRenderer, (*instance)->shader, w, h, VuoImage_getColorDepth(image));
}

void nodeInstanceFini(VuoInstanceData(struct nodeInstanceData *) instance)
{
	VuoRelease((*instance)->shader);
	VuoRelease((*instance)->imageRenderer);
	VuoGlContext_disuse((*instance)->glContext);
}
