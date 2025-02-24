VuoCompileLibraries(
	VuoBarcode.cc
)
target_link_libraries(vuo.image.libraries
	PRIVATE
		CONAN_PKG::zxing
)
target_sources(vuo.image.libraries PRIVATE
	VuoBarcode.h
)

VuoCompileTypes(
	VuoBlurShape.c
	VuoColorSample.c
	VuoFace.c
	VuoHorizontalReflection.c
	VuoImageFormat.c
	VuoImageNoise.c
	VuoImageStereoType.c
	VuoPixelShape.c
	VuoSizingMode.c
	VuoThresholdType.c
	VuoVerticalReflection.c
)
target_sources(vuo.image.types PRIVATE
	VuoBlurShape.h
	VuoColorSample.h
	VuoFace.h
	VuoHorizontalReflection.h
	VuoImageFormat.h
	VuoImageNoise.h
	VuoImageStereoType.h
	VuoPixelShape.h
	VuoSizingMode.h
	VuoThresholdType.h
	VuoVerticalReflection.h
)

VuoCompileNodes(
	vuo.image.analogDistortion.fs
	vuo.image.apply.mask.c
	vuo.image.areEqual.c
	vuo.image.blend.c
	vuo.image.blur.c
	vuo.image.blur.directional.c
	vuo.image.blur.radial.c
	vuo.image.bulge.c
	vuo.image.bulge2.c
	vuo.image.color.adjust.c
	vuo.image.color.cga.c
	vuo.image.color.combine.hsl.c
	vuo.image.color.combine.rgb.c
	vuo.image.color.gray.c
	vuo.image.color.invert.c
	vuo.image.color.map.c
	vuo.image.color.mask.brightness.c
	vuo.image.color.offset.radial.rgb.c
	vuo.image.color.offset.rgb.c
	vuo.image.color.sepia.c
	vuo.image.color.solarize.c
	vuo.image.color.split.hsl.c
	vuo.image.color.split.rgb.c
	vuo.image.crop.c
	vuo.image.crop.pixels.c
	vuo.image.crosshatch.c
	vuo.image.dilate.c
	vuo.image.feedback.c
	vuo.image.fetch.c
	vuo.image.fetch.list.c
	vuo.image.filmGrain.c
	vuo.image.findBarcode.c
	vuo.image.findBarcode2.c
	vuo.image.flip.horizontal.c
	vuo.image.flip.vertical.c
	vuo.image.frost.c
	vuo.image.sample.color.c
	vuo.image.get.cube.c
	vuo.image.get.face.c
	vuo.image.get.height.c
	vuo.image.get.size.c
	vuo.image.get.width.c
	vuo.image.halftone.cmyk.c
	vuo.image.interpretData.c
	vuo.image.kaleidoscope.c
	vuo.image.make.checkerboard.c
	vuo.image.make.checkerboard2.c
	vuo.image.make.color.c
	vuo.image.make.cube.c
	vuo.image.make.gradient.linear.c
	vuo.image.make.gradient.linear2.c
	vuo.image.make.gradient.radial.c
	vuo.image.make.gradient.radial2.c
	vuo.image.make.noise.c
	vuo.image.make.noise.sphere.c
	vuo.image.make.random.c
	vuo.image.make.shadertoy.c
	vuo.image.make.shadertoy2.cc
	vuo.image.make.stripe.c
	vuo.image.make.text.c
#	vuo.image.make.triangle.c
	vuo.image.make.web.m
	vuo.image.mask.brightness.c
	vuo.image.mipmap.c
	vuo.image.mirror.c
	vuo.image.outline.c
	vuo.image.pixellate.c
#	vuo.image.pixellate.details.c
	vuo.image.pixellate.radial.c
	vuo.image.populated.c
	vuo.image.posterize.c
	vuo.image.reduceHaze.c
	vuo.image.render.window.c
	vuo.image.render.window2.c
	vuo.image.resize.c
	vuo.image.resize.larger.c
	vuo.image.reveal.linear.fs
	vuo.image.ripple.c
	vuo.image.ripple.radial.c
	vuo.image.rotate.c
	vuo.image.save.c
	vuo.image.scramble.c
	vuo.image.sharpen.c
	vuo.image.stainedGlass.c
	vuo.image.streak.fs
	vuo.image.streak.radial.fs
	vuo.image.tile.c
	vuo.image.tileable.c
	vuo.image.toon.c
	vuo.image.translate.fs
	vuo.image.twirl.c
	vuo.image.twirl2.c
	vuo.image.vignette.c
	vuo.image.vignette2.c
	vuo.image.wrapMode.c
)
target_include_directories(vuo.image.nodes
	PRIVATE
	../vuo.data
	../vuo.layer
	../vuo.noise
	../vuo.scene
	../vuo.time
)
target_link_libraries(vuo.image.nodes
	PRIVATE
		CONAN_PKG::freeimage
)

if (VuoPro)
	include(pro/pro.cmake)
endif()

VuoNodeSet()
