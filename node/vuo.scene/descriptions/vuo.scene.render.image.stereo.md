Creates an image that is a stereoscopic snapshot of a 3D scene.

Use this in conjunction with the [Make Stereo Camera](vuo-node://vuo.scene.make.camera.stereo) or [Make Targeted Stereo Camera](vuo-node://vuo.scene.make.camera.stereo.target) nodes.

   - `Objects` — The 3D objects to place in the scene.
   - `Camera Name` — The name of the camera through which the scene is viewed. The camera is selected from any in `Objects`. If no matching camera is found, then a camera from `Objects` is arbitrarily chosen. If there is no camera, the default camera is used.
   - `Width`, `Height` — The width and height of the resulting images, in pixels.
   - `Color Depth` — The number of bits to use to represent each color channel in the output image; higher values are more precise but use more graphics storage space.  Images are typically 8 bits per channel ("8bpc"), though if you're working with image feedback, you may want to use higher precision.
   - `Multisampling` — How smooth edges of layers are.
      - A value of 1 means each pixel is evaluated once — no smoothing.
      - A value of 2, 4, or 8 means each pixel that lies on the edge of a layer is sampled multiple times and averaged together, to provide a smoother appearance.
   - `Left Image`, `Right Image` — The snapshot images of the scene, one for the left and right eyes. If no scene object is visible in part of the image, that part of the image will be transparent.
   - `Left Depth Image`, `Right Depth Image` — Counterparts to the snapshot images. The depth image represents the distance between the camera and objects in the scene. Objects closer to the camera are darker, objects further from the camera are lighter. 

Even with `Multisampling` greater than 1, images may still have aliasing (since interior pixels are only evaluated once). For more thorough antialiasing, you can use File > Export > Movie's Antialiasing setting.
