Creates a scene object in the shape of a cube.

   - `Transform` — Changes the cube's translation, rotation, or scale, in Vuo Coordinates.
   - `Material` — A color, image, cubemap, or shader to apply to all 6 sides of the cube. If no material is provided, this node uses a default shader that stretches a gradient-colored checkerboard across each cube face.

By default, the cube has a width, height, and depth of 1 and is centered at (0,0,0).

For individual control over the material of each side of the cube, use the [Make Cube with Materials](vuo-node://vuo.scene.make.cube) node.
