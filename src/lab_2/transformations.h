#include "globals.h"
#include <stdio.h>

#define IS_NOT_RANDOM 0
#define IS_RANDOM 1

const mat4 IDENTITY_MATRIX = mat4(
  1.0f, 0.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 1.0f, 0.0f,
  0.0f, 0.0f, 0.0f, 1.0f
);

void transformTriangle(GLuint gWorldLocation, float randomSeed) {
  if (randomSeed == IS_NOT_RANDOM) {
    randomSeed = 0;
  }

  // Translation
  vec3 translationVector = vec3(
    transX * (1 + randomSeed),
    transY * (1 - randomSeed),
    transZ * (1 + (randomSeed / 2))
  );

  mat4 productMatrix = translate(IDENTITY_MATRIX, translationVector);

  // Rotation
  productMatrix = rotate_x_deg(
    productMatrix,
    rotX * (1 + randomSeed)
  );
  productMatrix = rotate_y_deg(
    productMatrix,
    rotY * (1 + (3 * randomSeed / 4))
  );
  productMatrix = rotate_z_deg(
    productMatrix,
    rotZ * (1 - randomSeed)
  );

  // Scaling
  vec3 scaleVector = vec3(scaleX, scaleY, scaleZ);
  productMatrix = scale(productMatrix, scaleVector);

  // Pass the productMatrix in as the value for the `gWorld`
  glUniformMatrix4fv(gWorldLocation, 1, GL_FALSE, (float *)&productMatrix);
  // Draw points 0-3 from the currently bound VAO with current in-use shader
  glDrawArrays(GL_TRIANGLES, 0, 3);

}
