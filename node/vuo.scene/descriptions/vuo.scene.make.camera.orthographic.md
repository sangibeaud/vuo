Creates an orthographic camera that can be added to a 3D scene. 

The camera uses an [orthographic projection](https://en.wikipedia.org/wiki/Graphical_projection). Unlike a human eye or a typical camera lens, the orthographic projection makes objects appear the same size regardless of their distance from the camera. It doesn't have a vanishing point.

   - `Name` — A name to identify the camera, allowing other nodes to select it from a list of cameras. 
   - `Position` — The position of the camera, in Vuo Coordinates. 
   - `Rotation` — The rotation of the camera, in degrees. If this is (0,0,0), the camera points toward negative infinity on the Z axis. 
   - `Width` — The width of the area visible to the camera, in Vuo Coordinates. The height is determined by the width and the aspect ratio when the scene is rendered. 
   - `Distance Min`, `Distance Max` — The minimum and maximum distance from the camera at which an object is visible (clipping planes), in Vuo Coordinates. If `Distance Min` is negative, then objects behind the camera are visible. 
