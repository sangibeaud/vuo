/**
 * @file
 * VuoImageResize implementation.
 *
 * @copyright Copyright © 2012–2017 Kosada Incorporated.
 * This code may be modified and distributed under the terms of the MIT License.
 * For more information, see http://vuo.org/license.
 */

#include <OpenGL/CGLMacro.h>

#include "node.h"
#include "VuoImageResize.h"
#include "../node/vuo.image/VuoSizingMode.h"

/// @{
#ifdef VUO_COMPILER
VuoModuleMetadata({
					 "title" : "VuoImageResize",
					 "dependencies" : [
						 "VuoImageRenderer"
					 ]
				 });
#endif
/// @}

/**
 * Fragment shader that scales and offsets an image.
 */
static const char * applyScaleFragmentShader = VUOSHADER_GLSL_SOURCE(120,
	include(VuoGlslAlpha)

	varying vec4 fragmentTextureCoordinate;
	uniform sampler2D texture;
	uniform vec2 scale;
	uniform vec2 offset;

	bool outOfBounds(vec2 coord)
	{
		return coord.x < 0 || coord.x > 1 || coord.y < 0 || coord.y > 1;
	}

	void main(void)
	{
		vec2 uv = (fragmentTextureCoordinate.xy - offset) * scale;
		gl_FragColor = outOfBounds(uv) ? vec4(0.,0.,0.,0.) : VuoGlsl_sample(texture, uv);
	}
);

/**
 * Fragment shader that scales and offsets an image.
 */
static const char *applyScaleFragmentShaderRect = VUOSHADER_GLSL_SOURCE(120,
	include(VuoGlslAlpha)

	varying vec4 fragmentTextureCoordinate;
	uniform sampler2DRect texture;
	uniform vec2 scale;
	uniform vec2 offset;
	uniform vec2 textureSize;

	bool outOfBounds(vec2 coord)
	{
		return coord.x < 0 || coord.x > 1 || coord.y < 0 || coord.y > 1;
	}

	void main(void)
	{
		vec2 uv = (fragmentTextureCoordinate.xy - offset) * scale;
		gl_FragColor = outOfBounds(uv) ? vec4(0.,0.,0.,0.) : VuoGlsl_sampleRect(texture, uv * textureSize);
	}
);

/**
 * VuoImageResize state data.
 */
struct VuoImageResize_internal
{
	VuoShader shader;
	VuoShader shaderRect;
};

/**
 * Frees VuoImageResize state data.
 */
void VuoImageResize_free(void *ir)
{
	struct VuoImageResize_internal *resize = ir;
	VuoRelease(resize->shader);
	VuoRelease(resize->shaderRect);
	free(ir);
}

/**
 * Create and compile a resize shader for reuse with VuoImage_resizeWithShaderAndContext.
 */
VuoImageResize VuoImageResize_make(void)
{
	struct VuoImageResize_internal *ir = (struct VuoImageResize_internal *)malloc(sizeof(struct VuoImageResize_internal));
	VuoRegister(ir, VuoImageResize_free);

	ir->shader = VuoShader_make("Resize Image Shader");
	VuoRetain(ir->shader);
	VuoShader_addSource(ir->shader, VuoMesh_IndividualTriangles, NULL, NULL, applyScaleFragmentShader);

	ir->shaderRect = VuoShader_make("Resize Image Shader (Rect)");
	VuoRetain(ir->shaderRect);
	VuoShader_addSource(ir->shaderRect, VuoMesh_IndividualTriangles, NULL, NULL, applyScaleFragmentShaderRect);

	return ir;
}

/**
 * Returns a new image resized from image.  Use with @ref VuoImageResize_make().
 */
VuoImage VuoImageResize_resize(VuoImage image, VuoImageResize ir, VuoImageRenderer renderer, VuoSizingMode sizingMode, VuoInteger width, VuoInteger height)
{
	if (!image)
		return NULL;

	float u = width / (float)(image->pixelsWide);
	float v = height / (float)(image->pixelsHigh);

	VuoPoint2d scale = (VuoPoint2d) { 1, 1 };
	VuoPoint2d offset = (VuoPoint2d) { 0, 0 };

	switch(sizingMode)
	{
		case VuoSizingMode_Stretch:
			break;

		case VuoSizingMode_Fit:
			if( u < v && u * image->pixelsHigh < height)
			{
				scale = (VuoPoint2d) { 1, height/(image->pixelsHigh*u) };
				offset = (VuoPoint2d) { 0, ((height-(image->pixelsHigh*u))/2)/height };
			}
			else
			{
				scale = (VuoPoint2d) { width/(image->pixelsWide*v), 1 };
				offset = (VuoPoint2d) { ((width-(image->pixelsWide*v))/2)/width, 0 };
			}
			break;

		case VuoSizingMode_Fill:
			if(u > v)
			{
				scale = (VuoPoint2d) { 1, height/(image->pixelsHigh*u) };
				offset = (VuoPoint2d) { 0, ((height-(image->pixelsHigh*u))/2)/height };
			}
			else
			{
				scale = (VuoPoint2d) { width/(image->pixelsWide*v), 1 };
				offset = (VuoPoint2d) { ((width-(image->pixelsWide*v))/2)/width, 0 };
			}
			break;
	}

	VuoShader shader;
	struct VuoImageResize_internal *resize = ir;
	if (image->glTextureTarget == GL_TEXTURE_2D)
		shader = resize->shader;
	else if (image->glTextureTarget == GL_TEXTURE_RECTANGLE_ARB)
	{
		shader = resize->shaderRect;
		VuoShader_setUniform_VuoPoint2d(shader, "textureSize", (VuoPoint2d){image->pixelsWide, image->pixelsHigh});
	}
	else
	{
		VUserLog("Error: Unknown texture target %s.", VuoGl_stringForConstant(image->glTextureTarget));
		return NULL;
	}

	VuoShader_setUniform_VuoImage  ( shader, "texture", image );
	VuoShader_setUniform_VuoPoint2d( shader, "scale", scale );
	VuoShader_setUniform_VuoPoint2d( shader, "offset", offset );

	return VuoImageRenderer_draw( renderer, shader, width, height, VuoImage_getColorDepth(image) );
}
