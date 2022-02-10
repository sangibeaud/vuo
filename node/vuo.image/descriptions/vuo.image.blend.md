Blends two images into a single image.

   - `Background` — The background image (bottom layer) to blend.
   - `Foreground` — The foreground image (top layer) to blend.
   - `Blend Mode` — The way that the images should be blended. For information about blend modes, see: 
      - [Wikipedia article on blend modes](https://en.wikipedia.org/wiki/Blend_modes)
      - [Photoshop blend modes](https://helpx.adobe.com/photoshop/using/blending-modes.html)
      - [GIMP blend modes](http://docs.gimp.org/en/gimp-concepts-layer-modes.html)
   - `Foreground Opacity` — The opacity that the foreground image component should have in the blended image, ranging from 0 to 1.
   - `Replace Opacity` — Determines how the foreground image's opacity is combined with the background image's opacity.  If true, the foreground image can make the output image more opaque (like Photoshop does).  If false, the opacity of the background image is used unmodified (like GIMP does).

The resulting image uses the dimensions of the background image (unless the background image is empty, in which case it uses the dimensions of the foreground image).

The foreground image is stretched to match the size of the background image.  If you want to blend images of different sizes without stretching them, use the [Resize Image](vuo-node://vuo.image.resize), [Crop Image](vuo-node://vuo.image.crop), or [Crop Image Pixels](vuo-node://vuo.image.crop.pixels) nodes.

This node outputs an image with a color depth equal to the higher of the two input images' color depths.  For example, if the `Background` image is 8bpc and the `Foreground` image is 16bpc, this node outputs a 16bpc composite image.

Thanks to [Romain Dura](http://mouaif.wordpress.com/2009/01/05/photoshop-math-with-glsl-shaders/) for the GLSL implementations of many blend modes.


![](mountains.png)

![](blend.png)
