Creates a perspective camera that can be added to a 3D scene. 

The camera uses a [perspective projection](https://en.wikipedia.org/wiki/Graphical_projection). Like a human eye or a typical camera lens, the perspective projection makes near objects seem larger than distant objects.

   - `Name` — A name to identify the camera, allowing other nodes to select it from a list of cameras. 
   - `Position` — The position of the camera, in Vuo Coordinates. 
   - `Rotation` — The rotation of the camera, in degrees. If this is (0,0,0), the camera points toward negative infinity on the Z axis. 
   - `Field of View` — The camera's [horizontal angle of view](https://en.wikipedia.org/wiki/Angle_of_view), in degrees.
   - `Distance Min`, `Distance Max` — The minimum and maximum distance in front of the camera at which an object is visible (clipping planes), in Vuo Coordinates. These should be greater than 0. 
